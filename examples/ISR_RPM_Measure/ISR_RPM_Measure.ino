/****************************************************************************************************************************
   ISR_RPM_Measure.ino
   For SAM DUE boards
   Written by Khoi Hoang

   Built by Khoi Hoang https://github.com/khoih-prog/SAMDUE_TimerInterrupt
   Licensed under MIT license

   Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
   unsigned long miliseconds), you just consume only one SAM DUE timer and avoid conflicting with other cores' tasks.
   The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
   Therefore, their executions are not blocked by bad-behaving functions / tasks.
   This important feature is absolutely necessary for mission-critical tasks.

   Based on SimpleTimer - A timer library for Arduino.
   Author: mromani@ottotecnica.com
   Copyright (c) 2010 OTTOTECNICA Italy

   Based on BlynkTimer.h
   Author: Volodymyr Shymanskyy

   Version: 1.1.1

   Version Modified By   Date      Comments
   ------- -----------  ---------- -----------
   1.0.1   K Hoang      06/11/2020 Initial coding
   1.1.1   K.Hoang      06/12/2020 Add Change_Interval example. Bump up version to sync with other TimerInterrupt Libraries
*****************************************************************************************************************************/
/*
   Notes:
   Special design is necessary to share data between interrupt code and the rest of your program.
   Variables usually need to be "volatile" types. Volatile tells the compiler to avoid optimizations that assume
   variable can not spontaneously change. Because your function may change variables while your program is using them,
   the compiler needs this hint. But volatile alone is often not enough.
   When accessing shared variables, usually interrupts must be disabled. Even with volatile,
   if the interrupt changes a multi-byte variable between a sequence of instructions, it can be read incorrectly.
   If your data is multiple variables, such as an array and a count, usually interrupts need to be disabled
   or the entire sequence of your code which accesses the data.

   RPM Measuring uses high frequency hardware timer 1Hz == 1ms) to measure the time from of one rotation, in ms
   then convert to RPM. One rotation is detected by reading the state of a magnetic REED SW or IR LED Sensor
   Asssuming LOW is active.
   For example: Max speed is 600RPM => 10 RPS => minimum 100ms a rotation. We'll use 80ms for debouncing
   If the time between active state is less than 8ms => consider noise.
   RPM = 60000 / (rotation time in ms)

   We use interrupt to detect whenever the SW is active, set a flag
   then use timer to count the time between active state
*/

#if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #error This code is designed to run on SAM DUE board / platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "SAMDTimerInterrupt.h"
// Don't define SAMDUE_TIMER_INTERRUPT_DEBUG > 0. Only for special ISR debugging only. Can hang the system.
#define SAMDUE_TIMER_INTERRUPT_DEBUG      1

#include "SAMDUETimerInterrupt.h"

//#ifndef LED_BUILTIN
//  #define LED_BUILTIN       13
//#endif

#ifndef LED_BLUE
  #define LED_BLUE          2
#endif

#ifndef LED_RED
  #define LED_RED           8
#endif

unsigned int interruptPin = 7;

#define TIMER1_INTERVAL_MS          1L
#define DEBOUNCING_INTERVAL_MS      80

#define LOCAL_DEBUG                 1

volatile unsigned long rotationTime = 0;
float RPM       = 0.00;
float avgRPM    = 0.00;

volatile int debounceCounter;

volatile bool activeState = false;

void detectRotation(void)
{
  activeState = true;
}

void TimerHandler1()
{
  static bool started = false;

  if ( activeState )
  {
    // Reset to prepare for next round of interrupt
    activeState = false;

    if (debounceCounter >= DEBOUNCING_INTERVAL_MS / TIMER1_INTERVAL_MS )
    {

      //min time between pulses has passed
      RPM = (float) ( 60000.0f / ( rotationTime * TIMER1_INTERVAL_MS ) );

      avgRPM = ( 2 * avgRPM + RPM) / 3,

      Serial.println("RPM = " + String(avgRPM) + ", rotationTime ms = " + String(rotationTime * TIMER1_INTERVAL_MS) );

      rotationTime = 0;
      debounceCounter = 0;
    }
    else
      debounceCounter++;
  }
  else
  {
    debounceCounter++;
  }

  if (rotationTime >= 5000)
  {
    // If idle, set RPM to 0, don't increase rotationTime
    RPM = 0;
    Serial.println("RPM = " + String(RPM) + ", rotationTime = " + String(rotationTime) );
    rotationTime = 0;
  }
  else
  {
    rotationTime++;
  }
}

uint16_t attachDueInterrupt(double microseconds, timerCallback callback, const char* TimerName)
{
  DueTimerInterrupt dueTimerInterrupt = DueTimer.getAvailable();
  
  dueTimerInterrupt.attachInterruptInterval(microseconds, callback);

  uint16_t timerNumber = dueTimerInterrupt.getTimerNumber();
  
  Serial.print(TimerName);
  Serial.print(" attached to Timer(");
  Serial.print(timerNumber);
  Serial.println(")");

  return timerNumber;
}

void setup()
{
  pinMode(interruptPin, INPUT_PULLUP);
  
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStarting ISR_RPM_Measure on " + String(BOARD_NAME));
  Serial.println(SAMDUE_TIMER_INTERRUPT_VERSION);
  Serial.println("CPU Frequency = " + String(F_CPU / 1000000) + " MHz");
  Serial.println("Timer Frequency = " + String(SystemCoreClock / 1000000) + " MHz");

  // Interval in microsecs
  attachDueInterrupt(TIMER1_INTERVAL_MS * 1000, TimerHandler1, "ITimer1");

  // Assumming the interruptPin will go LOW
  attachInterrupt(digitalPinToInterrupt(interruptPin), detectRotation, FALLING);
}

void loop()
{

}
