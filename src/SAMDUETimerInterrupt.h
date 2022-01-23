/****************************************************************************************************************************
  SAMDUETimerInterrupt.h
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

#ifndef SAMDUETIMERINTERRUPT_H
#define SAMDUETIMERINTERRUPT_H

#include "SAMDUETimerInterrupt.hpp"
#include "SAMDUETimerInterrupt_Impl.h"

#endif    // SAMDUETIMERINTERRUPT_H
