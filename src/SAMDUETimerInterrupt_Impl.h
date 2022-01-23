/****************************************************************************************************************************
  SAMDUETimerInterrupt_Impl.h
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

#ifndef SAMDUETIMERINTERRUPT_IMPL_H
#define SAMDUETIMERINTERRUPT_IMPL_H

#if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #error This code is designed to run on SAM DUE board / platform! Please check your Tools->Board setting.
#endif

#include "Arduino.h"
#include <inttypes.h>

////////////////////////////////////////////////////////////////////

const DueTimerIRQInfo DueTimerInterrupt::Timers[NUM_TIMERS] =
{
  { TC0, 0, TC0_IRQn },
  { TC0, 1, TC1_IRQn },
  { TC0, 2, TC2_IRQn },
  { TC1, 0, TC3_IRQn },
  { TC1, 1, TC4_IRQn },
  { TC1, 2, TC5_IRQn },

#if defined(TC2)
  { TC2, 0, TC6_IRQn },
  { TC2, 1, TC7_IRQn },
  { TC2, 2, TC8_IRQn },
#endif
};

// Fix for compatibility with Servo library
#if USING_SERVO_LIB
  // Set _callbacks as used, allowing DueTimerInterrupt::getAvailable() to work
  void (*DueTimerInterrupt::_callbacks[NUM_TIMERS])() =
  {
    (void (*)()) 1, // Timer 0 - Occupied
    (void (*)()) 0, // Timer 1
    (void (*)()) 1, // Timer 2 - Occupied
    (void (*)()) 1, // Timer 3 - Occupied
    (void (*)()) 1, // Timer 4 - Occupied
    (void (*)()) 1, // Timer 5 - Occupied
  
  #if defined(TC2)
    (void (*)()) 0, // Timer 6
    (void (*)()) 0, // Timer 7
    (void (*)()) 0  // Timer 8
  #endif
  };

#else
  void (*DueTimerInterrupt::_callbacks[NUM_TIMERS])() = {};
#endif

#if defined(TC2)
  double DueTimerInterrupt::_frequency[NUM_TIMERS] = { -1, -1, -1, -1, -1, -1, -1, -1, -1};
#else
  double DueTimerInterrupt::_frequency[NUM_TIMERS] = { -1, -1, -1, -1, -1, -1};
#endif

///////////////////////////////////////////////////////////////////////

/*
  Implementation of the timer _callbacks defined in
  arduino-1.5.2/hardware/arduino/sam/system/CMSIS/Device/ATMEL/sam3xa/include/sam3x8e.h
*/
// Fix for compatibility with Servo library
#if ( !USING_SERVO_LIB || !defined(USING_SERVO_LIB) )

void TC0_Handler()
{
  TC_GetStatus(TC0, 0);
  DueTimerInterrupt::_callbacks[0]();
}

#endif

void TC1_Handler()
{
  TC_GetStatus(TC0, 1);
  DueTimerInterrupt::_callbacks[1]();
}

// Fix for compatibility with Servo library
#if ( !USING_SERVO_LIB || !defined(USING_SERVO_LIB) )

void TC2_Handler()
{
  TC_GetStatus(TC0, 2);
  DueTimerInterrupt::_callbacks[2]();
}

void TC3_Handler()
{
  TC_GetStatus(TC1, 0);
  DueTimerInterrupt::_callbacks[3]();
}

void TC4_Handler()
{
  TC_GetStatus(TC1, 1);
  DueTimerInterrupt::_callbacks[4]();
}

void TC5_Handler()
{
  TC_GetStatus(TC1, 2);
  DueTimerInterrupt::_callbacks[5]();
}
#endif

#if defined(TC2)

void TC6_Handler()
{
  TC_GetStatus(TC2, 0);
  DueTimerInterrupt::_callbacks[6]();
}

void TC7_Handler()
{
  TC_GetStatus(TC2, 1);
  DueTimerInterrupt::_callbacks[7]();
}

void TC8_Handler()
{
  TC_GetStatus(TC2, 2);
  DueTimerInterrupt::_callbacks[8]();
}
#endif

#endif    // SAMDUETIMERINTERRUPT_IMPL_H
