# SAMDUE_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/SAMDUE_TimerInterrupt.svg?)](https://www.ardu-badge.com/SAMDUE_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SAMDUE_TimerInterrupt.svg)](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SAMDUE_TimerInterrupt.svg)](http://github.com/khoih-prog/SAMDUE_TimerInterrupt/issues)

---
---

## Features

This library enables you to use Interrupt from Hardware Timers on an SAM-DUE-based board.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

### Why do we need this Hardware Timer Interrupt?

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed on-time or not at all, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

#### Important Notes:

1. Inside the attached function, **delay() won’t work and the value returned by millis() will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

### Releases v1.0.1

1. Permit up to 16 super-long-time, super-accurate ISR-based timers to avoid being blocked
2. Using cpp code besides Impl.h code to use if Multiple-Definition linker error3. 
3. Add complicated example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) utilizing and demonstrating the full usage of 16 independent ISR Timers based on just 1 Hardware Timer.

#### Supported Boards

  - **Arduino SAM DUE**.

---
---

## Prerequisite

 1. [`Arduino IDE 1.8.13+` for Arduino](https://www.arduino.cc/en/Main/Software)
 2. [`Arduino SAM DUE core v1.6.12+`](https://www.arduino.cc/en/Guide/ArduinoDue) for SAM DUE ARM Cortex-M3 boards
 3. [`Blynk library 0.6.1+`](https://github.com/blynkkk/blynk-library) to use with certain example.
 4. To use with certain example, depending on which Ethernet card you're using:
   - [`Ethernet library v2.0.0+`](https://www.arduino.cc/en/Reference/Ethernet) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500 (Deprecated, use Arduino Ethernet library).
   - [`Ethernet3 library v1.5.3+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500. ***Ready*** from v1.0.1.
   - [`UIPEthernet library v2.0.9+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60.
 5. To use with certain example
   - [`SimpleTimer library`](https://github.com/schinken/SimpleTimer) for [ISR_16_Timers_Array example](examples/ISR_16_Timers_Array).
   
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**SAMDUE_TimerInterrupt**](https://github.com/khoih-prog/SAMDUE_TimerInterrupt), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/SAMDUE_TimerInterrupt.svg?)](https://www.ardu-badge.com/SAMDUE_TimerInterrupt) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**SAMDUE_TimerInterrupt**](https://github.com/khoih-prog/SAMDUE_TimerInterrupt) page.
2. Download the latest release `SAMDUE_TimerInterrupt-master.zip`.
3. Extract the zip file to `SAMDUE_TimerInterrupt-master` directory 
4. Copy whole `SAMDUE_TimerInterrupt-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**SAMDUE_TimerInterrupt** library](https://platformio.org/lib/show/11428/SAMDUE_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/11428/SAMDUE_TimerInterrupt/installation). Search for **SAMDUE_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

 1. **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

---
---

### Optional Libraries' Patches

##### Notes: These patches are totally optional and necessary only when you use the related Ethernet library and get certain error or issues.

1. If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

2. To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

3. To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

4. To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for this [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

6. **To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library**, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- For [UIPEthernet v2.0.8](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

- For [UIPEthernet v2.0.9](https://github.com/UIPEthernet/UIPEthernet)

  - [UIPEthernet.h](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.h)
  - [UIPEthernet.cpp](LibraryPatches/UIPEthernet-2.0.9/UIPEthernet.cpp)
  - [Enc28J60Network.h](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.h)
  - [Enc28J60Network.cpp](LibraryPatches/UIPEthernet-2.0.9/utility/Enc28J60Network.cpp)

7. Check if you need to install the UIPthernet patch [new SAMD core F3/F4 compatibility](https://github.com/UIPEthernet/UIPEthernet/commit/c6d6519a260166b722b9cee5dd1f0fb2682e6782) to avoid errors `#include HardwareSPI.h` on some SAMD boards (Nucleo-32 F303K8, etc.)

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using **xyz-Impl.h instead of standard xyz.cpp**, possibly creates certain `Multiple Definitions` Linker error in certain use cases. Although it's simple to just modify several lines of code, either in the library or in the application, the library is adding 2 more source directories

1. **scr_h** for new h-only files
2. **src_cpp** for standard h/cpp files

besides the standard **src** directory.

To use the **old standard cpp** way, locate this library' directory, then just 

1. **Delete the all the files in src directory.**
2. **Copy all the files in src_cpp directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

To re-use the **new h-only** way, just 

1. **Delete the all the files in src directory.**
2. **Copy the files in src_h directory into src.**
3. Close then reopen the application code in Arduino IDE, etc. to recompile from scratch.

---
---


## New from v1.0.1

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long miliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) and [**ISR_Timer_Complex_Ethernet**](examples/ISR_Timer_Complex_Ethernet) examples will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in loop(), using delay() function as an example. The elapsed time then is very unaccurate

---

## Supported Boards

- **SAM DUE**

---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

#### 1.1 Init Hardware Timer

```
// Interval in microsecs
attachDueInterrupt(TIMER1_INTERVAL_MS * 1000, TimerHandler1, "ITimer1");
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

```
void TimerHandler(void)
{
  // Doing something here inside ISR
}

#define TIMER_INTERVAL_MS        1000      // 1s = 1000ms

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
  ....
  
  // Interval in microsecs
  attachDueInterrupt(TIMER_INTERVAL_MS * 1000, TimerHandler, "ITimer");
}  
```

### 2. Using 16 ISR_based Timers from 1 Hardware Timers


#### 2.1 Init Hardware Timer and ISR-based Timer

```
// Interval in microsecs
attachDueInterrupt(TIMER1_INTERVAL_MS * 1000, TimerHandler1, "ITimer1");
```

#### 2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```
void TimerHandler(void)
{
  ISR_Timer.run();
}

#define HW_TIMER_INTERVAL_MS          1L

#define TIMER_INTERVAL_2S             2000L
#define TIMER_INTERVAL_5S             5000L
#define TIMER_INTERVAL_11S            11000L
#define TIMER_INTERVAL_101S           101000L

// In SAM DUE, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething2s()
{
  // Doing something here inside ISR
}
  
void doingSomething5s()
{
  // Doing something here inside ISR
}

void doingSomething11s()
{
  // Doing something here inside ISR
}

void doingSomething101s()
{
  // Doing something here inside ISR
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
  ....
  
  // Interval in microsecs
  attachDueInterrupt(HW_TIMER_INTERVAL_MS * 1000, TimerHandler, "ITimer");

  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  ISR_Timer.setInterval(TIMER_INTERVAL_2S, doingSomething2s);
  ISR_Timer.setInterval(TIMER_INTERVAL_5S, doingSomething5s);
  ISR_Timer.setInterval(TIMER_INTERVAL_11S, doingSomething11s);
  ISR_Timer.setInterval(TIMER_INTERVAL_101S, doingSomething101s);
}  
```

---
---

### Examples: 

 1. [Argument_None](examples/Argument_None)
 2. [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
 3. [ISR_RPM_Measure](examples/ISR_RPM_Measure)
 4. [ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet)
 5. [RPM_Measure](examples/RPM_Measure)
 6. [SwitchDebounce](examples/SwitchDebounce)
 7. [TimerInterruptTest](examples/TimerInterruptTest)
 8. [TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)


---
---

### Example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array)

```
#if !( defined(ARDUINO_SAM_DUE) || defined(__SAM3X8E__) )
  #error This code is designed to run on SAM DUE board / platform! Please check your Tools->Board setting.
#endif

// These define's must be placed at the beginning before #include "SAMDTimerInterrupt.h"
// Don't define SAMDUE_TIMER_INTERRUPT_DEBUG > 0. Only for special ISR debugging only. Can hang the system.
#define SAMDUE_TIMER_INTERRUPT_DEBUG      1

#include "SAMDUETimerInterrupt.h"
#include "SAMDUE_ISR_Timer.h"

#include <SimpleTimer.h>              // https://github.com/schinken/SimpleTimer

#ifndef LED_BUILTIN
  #define LED_BUILTIN       13
#endif

#ifndef LED_BLUE
  #define LED_BLUE          2
#endif

#ifndef LED_RED
  #define LED_RED           3
#endif

// Resolution for ISR_Timer. Smaller => more precise.
#define HW_TIMER_INTERVAL_US      100L

volatile uint32_t startMillis = 0;

// Init SAMDUE_ISR_Timer
// Each SAMDUE_ISR_Timer can service 16 different ISR-based timers
SAMDUE_ISR_Timer ISR_Timer;

#define LED_TOGGLE_INTERVAL_MS        500L

void TimerHandler(void)
{
  static bool toggle  = false;
  static bool started = false;
  static int timeRun  = 0;

  ISR_Timer.run();

  // Toggle LED every LED_TOGGLE_INTERVAL_MS = 500ms = 0.5s
  if (++timeRun == ( (LED_TOGGLE_INTERVAL_MS * 1000) / HW_TIMER_INTERVAL_US) )
  {
    timeRun = 0;

    if (!started)
    {
      started = true;
      pinMode(LED_BUILTIN, OUTPUT);
    }

    //timer interrupt toggles pin LED_BUILTIN
    digitalWrite(LED_BUILTIN, toggle);
    toggle = !toggle;
  }
}

#define NUMBER_ISR_TIMERS         16

// You can assign any interval for any timer here, in milliseconds
uint32_t TimerInterval[NUMBER_ISR_TIMERS] =
{
  1000L,  2000L,  3000L,  4000L,  5000L,  6000L,  7000L,  8000L,
  9000L, 10000L, 11000L, 12000L, 13000L, 14000L, 15000L, 16000L
};

typedef void (*irqCallback)  (void);

#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 0)
void printStatus(uint16_t index, unsigned long deltaMillis, unsigned long currentMillis)
{ 
  Serial.print(TimerInterval[index]/1000);
  Serial.print("s: Delta ms = ");
  Serial.print(deltaMillis);
  Serial.print(", ms = ");
  Serial.println(currentMillis);
}
#endif

// In SAMDUE, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething0()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 0)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(0, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething1()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(1, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething2()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(2, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething3()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(3, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething4()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(4, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething5()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(5, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething6()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(6, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething7()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(7, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething8()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(8, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething9()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(9, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething10()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(10, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

// In SAMDUE, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething11()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(11, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

// In SAMDUE, avoid doing something fancy in ISR, for example complex Serial.print with String() argument
// The pure simple Serial.prints here are just for demonstration and testing. Must be eliminate in working environment
// Or you can get this run-time error / crash
void doingSomething12()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(12, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething13()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(13, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething14()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(14, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

void doingSomething15()
{
#if (SAMDUE_TIMER_INTERRUPT_DEBUG > 1)
  static unsigned long previousMillis = startMillis;
  unsigned long currentMillis = millis();
  unsigned long deltaMillis   = currentMillis - previousMillis;
  
  printStatus(15, deltaMillis, currentMillis);
  
  previousMillis = currentMillis;
#endif
}

irqCallback irqCallbackFunc[NUMBER_ISR_TIMERS] =
{
  doingSomething0,  doingSomething1,  doingSomething2,  doingSomething3, 
  doingSomething4,  doingSomething5,  doingSomething6,  doingSomething7, 
  doingSomething8,  doingSomething9,  doingSomething10, doingSomething11,
  doingSomething12, doingSomething13, doingSomething14, doingSomething15
};

////////////////////////////////////////////////


#define SIMPLE_TIMER_MS        2000L

// Init SimpleTimer
SimpleTimer simpleTimer;

// Here is software Timer, you can do somewhat fancy stuffs without many issues.
// But always avoid
// 1. Long delay() it just doing nothing and pain-without-gain wasting CPU power.Plan and design your code / strategy ahead
// 2. Very long "do", "while", "for" loops without predetermined exit time.
void simpleTimerDoingSomething2s()
{
  static unsigned long previousMillis = startMillis;
  unsigned long currMillis = millis();
  
  Serial.print("simpleTimer2s: Dms=");
  Serial.print(SIMPLE_TIMER_MS);
  Serial.print(", actual=");
  Serial.println(currMillis - previousMillis);
  
  previousMillis = currMillis;
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
  Serial.begin(115200);
  while (!Serial);
  
  Serial.println("\nStarting ISR_16_Timers_Array on " + String(BOARD_NAME));
  Serial.println("Version : " + String(SAMDUE_TIMER_INTERRUPT_VERSION));
  Serial.println("CPU Frequency = " + String(F_CPU / 1000000) + " MHz");
  Serial.println("Timer Frequency = " + String(SystemCoreClock / 1000000) + " MHz");

  // Interval in microsecs
  attachDueInterrupt(HW_TIMER_INTERVAL_US, TimerHandler, "ITimer");
  
  // Just to demonstrate, don't use too many ISR Timers if not absolutely necessary
  // You can use up to 16 timer for each ISR_Timer
  for (int i = 0; i < NUMBER_ISR_TIMERS; i++)
  {
    ISR_Timer.setInterval(TimerInterval[i], irqCallbackFunc[i]); 
  }

  // You need this timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary.
  simpleTimer.setInterval(SIMPLE_TIMER_MS, simpleTimerDoingSomething2s);
}

#define BLOCKING_TIME_MS      11111L

void loop()
{
  // This unadvised blocking task is used to demonstrate the blocking effects onto the execution and accuracy to Software timer
  // You see the time elapse of ISR_Timer still accurate, whereas very unaccurate for Software Timer
  // The time elapse for 2000ms software timer now becomes 11111ms (BLOCKING_TIME_MS)
  // While that of ISR_Timer is still prefect.
  delay(BLOCKING_TIME_MS);

  // You need this Software timer for non-critical tasks. Avoid abusing ISR if not absolutely necessary
  // You don't need to and never call ISR_Timer.run() here in the loop(). It's already handled by ISR timer.
  simpleTimer.run();
}
```
---
---

### Debug Terminal Output Samples

1. The following is the sample terminal output when running example [ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet) on **Arduino SAM DUE** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after 10.917s !!!**. Then in loop(), it's also activated **every 3s**.

```
Starting ISR_Timer_Complex_Ethernet on SAM DUE
Version : 1.0.1
Using Timer(0) = TC0, channel = 0, IRQ = TC0_IRQn
Timer(0), us = 50000.00
ITimer attached to Timer(0)
[5] Getting IP...
[7] MAC: FE-8A-F1-EA-DE-82
_pinCS = 0
W5100 init, using SS_PIN_DEFAULT = 10, new ss_pin = 10, W5100Class::ss_pin = 10
W5100::init: W5100, SSIZE =4096
2s: Delta ms = 2000
2s: Delta ms = 2000
[7728] IP:192.168.2.134
[7728] 
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v0.6.1 on Arduino Due

[7732] BlynkArduinoClient.connect: Connecting to account.duckdns.org:8080
[7849] Ready (ping: 6ms).
IP = 192.168.2.134
2s: Delta ms = 2000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 10917
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
11s: Delta ms = 11000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
11s: Delta ms = 11000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
5s: Delta ms = 5000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
11s: Delta ms = 11000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
5s: Delta ms = 5000
11s: Delta ms = 11000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000
2s: Delta ms = 2000
2s: Delta ms = 2000
blynkDoingSomething2s: Delta programmed ms = 2000, actual = 3000

```

---

2. The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Arduino SAM DUE** to demonstrate how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on SAM DUE
Version : 1.0.1
CPU Frequency = 84 MHz
Timer Frequency = 84 MHz
Using Timer(0) = TC0, channel = 0, IRQ = TC0_IRQn
ITimer0 attached to Timer(0)
Using Timer(1) = TC0, channel = 1, IRQ = TC1_IRQn
ITimer1 attached to Timer(1)
ITimer0: millis() = 1104, delta = 1104
ITimer0: millis() = 2104, delta = 1000
ITimer0: millis() = 3104, delta = 1000
ITimer1: millis() = 3111, delta = 3111
ITimer0: millis() = 4104, delta = 1000
Stop ITimer0, millis() = 5001
ITimer1: millis() = 6111, delta = 3000
ITimer1: millis() = 9111, delta = 3000
Start ITimer0, millis() = 10002
ITimer0: millis() = 11002, delta = 1000
ITimer0: millis() = 12002, delta = 1000
ITimer1: millis() = 12111, delta = 3000
ITimer0: millis() = 13002, delta = 1000
ITimer0: millis() = 14002, delta = 1000
Stop ITimer1, millis() = 15001
ITimer0: millis() = 15002, delta = 1000
Stop ITimer0, millis() = 15003
Start ITimer0, millis() = 20004
ITimer0: millis() = 21004, delta = 1000
ITimer0: millis() = 22004, delta = 1000
ITimer0: millis() = 23004, delta = 1000
ITimer0: millis() = 24004, delta = 1000
ITimer0: millis() = 25004, delta = 1000
Stop ITimer0, millis() = 25005
Start ITimer1, millis() = 30002
Start ITimer0, millis() = 30006
ITimer0: millis() = 31006, delta = 1000
ITimer0: millis() = 32006, delta = 1000
ITimer1: millis() = 33002, delta = 3000
ITimer0: millis() = 33006, delta = 1000
ITimer0: millis() = 34006, delta = 1000
ITimer0: millis() = 35006, delta = 1000
Stop ITimer0, millis() = 35007
ITimer1: millis() = 36002, delta = 3000
ITimer1: millis() = 39002, delta = 3000
Start ITimer0, millis() = 40008
ITimer0: millis() = 41008, delta = 1000
ITimer1: millis() = 42002, delta = 3000
ITimer0: millis() = 42008, delta = 1000
ITimer0: millis() = 43008, delta = 1000
ITimer0: millis() = 44008, delta = 1000
ITimer1: millis() = 45002, delta = 3000
Stop ITimer1, millis() = 45003
ITimer0: millis() = 45008, delta = 1000
Stop ITimer0, millis() = 45009

```

---

3. The following is the sample terminal output when running example [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) on **Arduino SAM DUE** to demonstrate the accuracy and how to use 16 ISR Timers from just 1 Hardware Timer.

```
Starting ISR_16_Timers_Array on SAM DUE
Version : 1.0.1
CPU Frequency = 84 MHz
Timer Frequency = 84 MHz
Using Timer(0) = TC0, channel = 0, IRQ = TC0_IRQn
Timer(0), us = 100.00
ITimer attached to Timer(0)
1s: Delta ms = 1006, ms = 1006
1s: Delta ms = 1000, ms = 2006
1s: Delta ms = 1000, ms = 3006
1s: Delta ms = 1000, ms = 4006
1s: Delta ms = 1000, ms = 5006
1s: Delta ms = 1000, ms = 6006
1s: Delta ms = 1000, ms = 7006
1s: Delta ms = 1000, ms = 8006
1s: Delta ms = 1000, ms = 9006
1s: Delta ms = 1000, ms = 10006
1s: Delta ms = 1000, ms = 11006
simpleTimer2s: Dms=2000, actual=11118
1s: Delta ms = 1000, ms = 12006
1s: Delta ms = 1000, ms = 13006
1s: Delta ms = 1000, ms = 14006
1s: Delta ms = 1000, ms = 15006
1s: Delta ms = 1000, ms = 16006
1s: Delta ms = 1000, ms = 17006
1s: Delta ms = 1000, ms = 18006
1s: Delta ms = 1000, ms = 19006
1s: Delta ms = 1000, ms = 20006
1s: Delta ms = 1000, ms = 21006
1s: Delta ms = 1000, ms = 22006
simpleTimer2s: Dms=2000, actual=11111
1s: Delta ms = 1000, ms = 23006
1s: Delta ms = 1000, ms = 24006
1s: Delta ms = 1000, ms = 25006
1s: Delta ms = 1000, ms = 26006
1s: Delta ms = 1000, ms = 27006
1s: Delta ms = 1000, ms = 28006
1s: Delta ms = 1000, ms = 29006
1s: Delta ms = 1000, ms = 30006
1s: Delta ms = 1000, ms = 31006
1s: Delta ms = 1000, ms = 32006
1s: Delta ms = 1000, ms = 33006
simpleTimer2s: Dms=2000, actual=11111
1s: Delta ms = 1000, ms = 34006
1s: Delta ms = 1000, ms = 35006
1s: Delta ms = 1000, ms = 36006
1s: Delta ms = 1000, ms = 37006
1s: Delta ms = 1000, ms = 38006
1s: Delta ms = 1000, ms = 39006
1s: Delta ms = 1000, ms = 40006
1s: Delta ms = 1000, ms = 41006
1s: Delta ms = 1000, ms = 42006
1s: Delta ms = 1000, ms = 43006
1s: Delta ms = 1000, ms = 44006
simpleTimer2s: Dms=2000, actual=11111
1s: Delta ms = 1000, ms = 45006
1s: Delta ms = 1000, ms = 46006
1s: Delta ms = 1000, ms = 47006

```
---
---

### Releases v1.0.1

1. Permit up to 16 super-long-time, super-accurate ISR-based timers to avoid being blocked
2. Using cpp code besides Impl.h code to use if Multiple-Definition linker error3. 
3. Add complicated example [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) utilizing and demonstrating the full usage of 16 independent ISR Timers based on just 1 Hardware Timer.

#### Supported Boards

  - **Arduino SAM DUE**.

---
---

### Issues ###

Submit issues to: [SAMDUE_TimerInterrupt issues](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.


## DONE


1. Basic hardware timers for SAM DUE.
2. More hardware-initiated software-enabled timers
3. Longer time interval

---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Use some code from the [**Ivan Seidel's DueTimer Library**](https://github.com/ivanseidel/DueTimer).

<table>
  <tr>
    <td align="center"><a href="https://github.com/ivanseidel"><img src="https://github.com/ivanseidel.png" width="100px;" alt="ivanseidel"/><br /><sub><b>⭐️ Ivan Seidel</b></sub></a><br /></td>
  </tr> 
</table>

---

## Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/blob/master/LICENSE)

---

## Copyright

Copyright 2020- Khoi Hoang


