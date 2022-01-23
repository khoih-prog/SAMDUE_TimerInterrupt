/****************************************************************************************************************************
  SAMDUETimerInterrupt.hpp
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

  Version: 1.3.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.1   K Hoang      06/11/2020 Initial coding
  1.1.1   K.Hoang      06/12/2020 Add Change_Interval example. Bump up version to sync with other TimerInterrupt Libraries
  1.2.0   K.Hoang      10/01/2021 Add better debug feature. Optimize code and examples to reduce RAM usage
  1.3.0   K.Hoang      22/01/2022 Fix `multiple-definitions` linker error
*****************************************************************************************************************************/

#pragma once

#ifndef SAMDUETIMERINTERRUPT_HPP
#define SAMDUETIMERINTERRUPT_HPP

#if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #error This code is designed to run on SAM DUE board / platform! Please check your Tools->Board setting.
#endif

#include "Arduino.h"
#include <inttypes.h>

#ifndef SAMDUE_TIMER_INTERRUPT_VERSION
  #define SAMDUE_TIMER_INTERRUPT_VERSION            "SAMDUETimerInterrupt v1.3.0"
  
  #define SAMDUE_TIMER_INTERRUPT_VERSION_MAJOR      1
  #define SAMDUE_TIMER_INTERRUPT_VERSION_MINOR      3
  #define SAMDUE_TIMER_INTERRUPT_VERSION_PATCH      0

  #define SAMDUE_TIMER_INTERRUPT_VERSION_INT        1003000  
#endif

#include "TimerInterrupt_Generic_Debug.h"

#ifdef BOARD_NAME
  #undef BOARD_NAME
#endif

#ifndef BOARD_NAME
  #define BOARD_NAME       "SAM DUE"
#endif

/*
	This fixes compatibility for Arduino Servo Library.
	Uncomment to make it compatible.

	Note that:
		+ Timers: 0,2,3,4,5 WILL NOT WORK, and will
				  neither be accessible by Timer0,...
*/
// #define USING_SERVO_LIB	true

#if USING_SERVO_LIB
	// Arduino Servo library uses timers 0,2,3,4,5. 
  // You must have `#define USING_SERVO_LIB	true` in your sketch.
	#warning Using Servo Library, Timer0, 2, 3, 4 and 5 not available
#endif

#if defined TC2
  #define NUM_TIMERS  9
#else
  #define NUM_TIMERS  6
#endif

typedef void (*timerCallback)  ();

typedef struct
{
	Tc *tc;
	uint32_t channel;
	IRQn_Type irq;
} DueTimerIRQInfo;

typedef struct
{
	const char* tc;
	uint32_t channel;
	const char* irq;
} DueTimerIRQInfoStr;

// For printing info of selected Timer
static const DueTimerIRQInfoStr TimersInfo[NUM_TIMERS] =
{
  { "TC0", 0, "TC0_IRQn" },
  { "TC0", 1, "TC1_IRQn" },
  { "TC0", 2, "TC2_IRQn" },
  { "TC1", 0, "TC3_IRQn" },
  { "TC1", 1, "TC4_IRQn" },
  { "TC1", 2, "TC5_IRQn" },

#if defined(TC2)
  { "TC2", 0, "TC6_IRQn" },
  { "TC2", 1, "TC7_IRQn" },
  { "TC2", 2, "TC8_IRQn" },
#endif
};

class DueTimerInterrupt
{
  protected:

    // Represents the timer id (index for the array of DueTimerIRQInfo structs)
    const unsigned short _timerNumber;

    // Stores the object timer frequency
    // (allows to access current timer period and frequency):
    static double _frequency[NUM_TIMERS];

    // Make Interrupt handlers friends, so they can use _callbacks
    friend void TC0_Handler();
    friend void TC1_Handler();
    friend void TC2_Handler();
    friend void TC3_Handler();
    friend void TC4_Handler();
    friend void TC5_Handler();

#if defined(TC2)
    friend void TC6_Handler();
    friend void TC7_Handler();
    friend void TC8_Handler();
#endif

    static timerCallback _callbacks[NUM_TIMERS];

    // Store timer configuration (static, as it's fixed for every object)
    static const DueTimerIRQInfo Timers[NUM_TIMERS];

  public:
  
    DueTimerInterrupt(const unsigned short& timer) : _timerNumber(timer)
    {
      /*
        The constructor of the class DueTimerInterrupt
      */
    }
    
    static DueTimerInterrupt getAvailable() __attribute__((always_inline))
    {
      /*
        Return the first timer with no callback set
      */

      for (int i = 0; i < NUM_TIMERS; i++)
      {
        if (!_callbacks[i])
        {
          TISR_LOGWARN3(F("Using Timer("), i, F(") = "), TimersInfo[i].tc);
          TISR_LOGWARN3(F("Channel = "), TimersInfo[i].channel, F(", IRQ = "), TimersInfo[i].irq);
   
          return DueTimerInterrupt(i);         
        }
      }

      // Default, return Timer0;
      return DueTimerInterrupt(0);
    }
   
    DueTimerInterrupt& attachInterruptInterval(const double& microseconds, timerCallback callback) __attribute__((always_inline))
    {
      _callbacks[_timerNumber] = callback;

      return startTimer(microseconds);
    }
    
    DueTimerInterrupt& attachInterrupt(const float& frequency, timerCallback callback) __attribute__((always_inline))
    {
      return attachInterruptInterval((double) (1000000.0f / frequency), callback);
    }
    
    DueTimerInterrupt& attachInterrupt(timerCallback callback) __attribute__((always_inline))
    {
      /*
        Links the function passed as argument to the timer of the object
      */

      _callbacks[_timerNumber] = callback;

      return *this;
    }
    
    DueTimerInterrupt& detachInterrupt() __attribute__((always_inline))
    {
      /*
        Links the function passed as argument to the timer of the object
      */

      stopTimer(); // Stop the currently running timer

      _callbacks[_timerNumber] = NULL;

      return *this;
    }
   
    DueTimerInterrupt& startTimer(const double& microseconds= -1) __attribute__((always_inline))
    {
      /*
        Start the timer
        If a period is set, then sets the period and start the timer
        If not period => default to 1Hz
      */

      if (microseconds > 0)
        setPeriod(microseconds);

      // If not yet initialized, set to default 1Hz
      if (_frequency[_timerNumber] <= 0)
        setFrequency(1);

      NVIC_ClearPendingIRQ(Timers[_timerNumber].irq);
      NVIC_EnableIRQ(Timers[_timerNumber].irq);

      TC_Start(Timers[_timerNumber].tc, Timers[_timerNumber].channel);

      return *this;
    }
    
    DueTimerInterrupt& restartTimer(const double& microseconds= -1) __attribute__((always_inline))
    {
      /*
        Restart the timer
        If a period is set, then sets the period and start the timer
        If not period => default to 1Hz
      */
      // If not yet initialized, set to default 1Hz
      if (_frequency[_timerNumber] <= 0)
      {
        setFrequency(1);
      }
      else if (microseconds < 0)
      {
        // Using previous settings if no argument (microseconds = -1)
        setFrequency(_frequency[_timerNumber]);
      }
      else
      {
        setPeriod(microseconds);
      }
      
      NVIC_ClearPendingIRQ(Timers[_timerNumber].irq);
      NVIC_EnableIRQ(Timers[_timerNumber].irq);

      TC_Start(Timers[_timerNumber].tc, Timers[_timerNumber].channel);

      return *this;
    }

    DueTimerInterrupt& stopTimer() __attribute__((always_inline))
    {
      /*
        Stop the timer
      */

      NVIC_DisableIRQ(Timers[_timerNumber].irq);

      TC_Stop(Timers[_timerNumber].tc, Timers[_timerNumber].channel);

      return *this;
    }
    
    DueTimerInterrupt& disableTimer()
    {
      return stopTimer();
    }

    // Picks the best clock to lower the error
    static uint8_t bestClock(const double& frequency, uint32_t& retRC)
    {
      /*
        Pick the best Clock, thanks to Ogle Basil Hall!

        Timer   Definition
        TIMER_CLOCK1  MCK /  2
        TIMER_CLOCK2  MCK /  8
        TIMER_CLOCK3  MCK / 32
        TIMER_CLOCK4  MCK /128
      */
      const struct
      {
        uint8_t flag;
        uint8_t divisor;
      } clockConfig[] =
      {
        { TC_CMR_TCCLKS_TIMER_CLOCK1,   2 },
        { TC_CMR_TCCLKS_TIMER_CLOCK2,   8 },
        { TC_CMR_TCCLKS_TIMER_CLOCK3,  32 },
        { TC_CMR_TCCLKS_TIMER_CLOCK4, 128 }
      };

      float ticks;
      float error;
      int clkId       = 3;
      int bestClock   = 3;
      float bestError = 9.999e99;

      do
      {
        ticks = (float) SystemCoreClock / frequency / (float) clockConfig[clkId].divisor;
        // error = abs(ticks - round(ticks));
        error = clockConfig[clkId].divisor * abs(ticks - round(ticks)); // Error comparison needs scaling

        if (error < bestError)
        {
          bestClock = clkId;
          bestError = error;
        }
      } while (clkId-- > 0);

      ticks = (float) SystemCoreClock / frequency / (float) clockConfig[bestClock].divisor;
      retRC = (uint32_t) round(ticks);

      return clockConfig[bestClock].flag;
    }


    DueTimerInterrupt& setFrequency(const double& frequency = 1)
    {
      /*
        Set the timer frequency (in Hz)
      */
      
      double freqToUse = frequency;

      // Prevent negative frequencies
      if (freqToUse <= 0)
      {
        freqToUse = 1;
      }

      // Remember the frequency — see below how the exact frequency is reported instead
      //_frequency[_timerNumber] = freqToUse;

      // Get current timer configuration
      DueTimerIRQInfo timerIRQInfo = Timers[_timerNumber];

      uint32_t rc = 0;
      uint8_t clock;

      // Tell the Power Management Controller to disable
      // the write protection of the (Timer/Counter) registers:
      pmc_set_writeprotect(false);

      // Enable clock for the timer
      pmc_enable_periph_clk((uint32_t)timerIRQInfo.irq);

      // Find the best clock for the wanted frequency
      clock = bestClock(freqToUse, rc);

      switch (clock)
      {
        case TC_CMR_TCCLKS_TIMER_CLOCK1:
          _frequency[_timerNumber] = (double)SystemCoreClock / 2.0 / (double)rc;
          break;
        case TC_CMR_TCCLKS_TIMER_CLOCK2:
          _frequency[_timerNumber] = (double)SystemCoreClock / 8.0 / (double)rc;
          break;
        case TC_CMR_TCCLKS_TIMER_CLOCK3:
          _frequency[_timerNumber] = (double)SystemCoreClock / 32.0 / (double)rc;
          break;
        default: // TC_CMR_TCCLKS_TIMER_CLOCK4
          _frequency[_timerNumber] = (double)SystemCoreClock / 128.0 / (double)rc;
          break;
      }

      // Set up the Timer in waveform mode which creates a PWM
      // in UP mode with automatic trigger on RC Compare
      // and sets it up with the determined internal clock as clock input.
      TC_Configure(timerIRQInfo.tc, timerIRQInfo.channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | clock);
      
      // Reset counter and fire interrupt when RC value is matched:
      TC_SetRC(timerIRQInfo.tc, timerIRQInfo.channel, rc);
      
      // Enable the RC Compare Interrupt.
      timerIRQInfo.tc->TC_CHANNEL[timerIRQInfo.channel].TC_IER = TC_IER_CPCS;
      
      // ... and disable all others.
      timerIRQInfo.tc->TC_CHANNEL[timerIRQInfo.channel].TC_IDR = ~TC_IER_CPCS;

      return *this;
    }
    
    DueTimerInterrupt& setPeriod(const double& microseconds) __attribute__((always_inline))
    {
      /*
        Set the period of the timer (in microseconds)
      */

      // Convert period in microseconds to frequency in Hz
      double frequency = 1000000.0 / microseconds;
      
      setFrequency(frequency);

      return *this;
    }
    
    DueTimerInterrupt& setInterval(const double& microseconds) __attribute__((always_inline))
    {
      return setPeriod(microseconds);
    }

    double getFrequency() const __attribute__((always_inline))
    {
      /*
        Get current time frequency
      */
      return _frequency[_timerNumber];
    }

    double getPeriod() const __attribute__((always_inline))
    {
      /*
        Get current time period
      */
      return 1.0 / getFrequency() * 1000000;
    }
    
    uint16_t getTimerNumber()
    {
      return _timerNumber;
    }

    bool operator== (const DueTimerInterrupt& rhs) const __attribute__((always_inline))
    {
      return _timerNumber == rhs._timerNumber;
    };

    bool operator!= (const DueTimerInterrupt& rhs) const __attribute__((always_inline))
    {
      return _timerNumber != rhs._timerNumber;
    };
};


////////////////////////////////////////////////////////////////////


/*
  Initializing all timers, so you can use them like this: Timer0.startTimer();
*/
static DueTimerInterrupt DueTimer(0);

static DueTimerInterrupt Timer1(1);

// Fix for compatibility with Servo library
#if ( !USING_SERVO_LIB || !defined(USING_SERVO_LIB) )
  static DueTimerInterrupt Timer0(0);
  static DueTimerInterrupt Timer2(2);
  static DueTimerInterrupt Timer3(3);
  static DueTimerInterrupt Timer4(4);
  static DueTimerInterrupt Timer5(5);
#endif

#if defined(TC2)
  static DueTimerInterrupt Timer6(6);
  static DueTimerInterrupt Timer7(7);
  static DueTimerInterrupt Timer8(8);
#endif

static DueTimerInterrupt DueTimerPtr[NUM_TIMERS] = 
{ 
#if ( !USING_SERVO_LIB || !defined(USING_SERVO_LIB) )
  Timer0,
#endif  

  Timer1,
  
#if ( !USING_SERVO_LIB || !defined(USING_SERVO_LIB) )  
  Timer2,
  Timer3,
  Timer4,
  Timer5,
#endif
 
#if defined(TC2) 
  Timer6, 
  Timer7, 
  Timer8
#endif  
};

///////////////////////////////////////////////////////////////////////

#endif    // SAMDUETIMERINTERRUPT_HPP
