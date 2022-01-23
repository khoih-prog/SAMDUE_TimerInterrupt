/****************************************************************************************************************************
  multiFileProject.ino
  For SAM DUE boards
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/SAMDUE_TimerInterrupt
  Licensed under MIT license

  Now even you use all these new 16 ISR-based timers,with their maximum interval practically unlimited (limited only by
  unsigned long miliseconds), you just consume only one NRF52 timer and avoid conflicting with other cores' tasks.
  The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers
  Therefore, their executions are not blocked by bad-behaving functions / tasks.
  This important feature is absolutely necessary for mission-critical tasks.
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #error This code is designed to run on SAM DUE board / platform! Please check your Tools->Board setting.
#endif

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "SAMDUETimerInterrupt.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "SAMDUE_ISR_Timer.h"

void setup() 
{
  // put your setup code here, to run once:
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
