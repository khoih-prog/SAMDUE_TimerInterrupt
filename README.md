# SAMDUE_TimerInterrupt Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/SAMDUE_TimerInterrupt.svg?)](https://www.ardu-badge.com/SAMDUE_TimerInterrupt)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SAMDUE_TimerInterrupt.svg)](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SAMDUE_TimerInterrupt.svg)](http://github.com/khoih-prog/SAMDUE_TimerInterrupt/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-SAMDUE_TimerInterrupt/count.svg" title="SAMDUE_TimerInterrupt Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-SAMDUE_TimerInterrupt/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Important Change from v1.3.0](#Important-Change-from-v130)
* [Why do we need this SAMDUE_TimerInterrupt library](#why-do-we-need-this-samdue_timerinterrupt-library)
  * [Features](#features)
  * [Why using ISR-based Hardware Timer Interrupt is better](#why-using-isr-based-hardware-timer-interrupt-is-better)
  * [Currently supported Boards](#currently-supported-boards)
  * [Important Notes about ISR](#important-notes-about-isr)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Arduino SAM DUE boards](#1-for-arduino-sam-due-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [New from v1.0.1](#new-from-v101)
* [Usage](#usage)
  * [1. Using only Hardware Timer directly](#1-using-only-hardware-timer-directly)
    * [1.1 Init Hardware Timer](#11-init-hardware-timer)
    * [1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function](#12-set-hardware-timer-interval-and-attach-timer-interrupt-handler-function)
  * [2. Using 16 ISR_based Timers from 1 Hardware Timer](#2-using-16-isr_based-timers-from-1-hardware-timer)
    * [2.1 Init Hardware Timer and ISR-based Timer](#21-init-hardware-timer-and-isr-based-timer)
    * [2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions](#22-set-hardware-timer-interval-and-attach-timer-interrupt-handler-functions)
* [Examples](#examples)
  * [  1. Argument_None](examples/Argument_None)
  * [  2. ISR_16_Timers_Array](examples/ISR_16_Timers_Array)
  * [  3. ISR_RPM_Measure](examples/ISR_RPM_Measure)
  * [  4. ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet)
  * [  5. RPM_Measure](examples/RPM_Measure)
  * [  6. SwitchDebounce](examples/SwitchDebounce)
  * [  7. TimerInterruptTest](examples/TimerInterruptTest)
  * [  8. TimerInterruptLEDDemo](examples/TimerInterruptLEDDemo)
  * [  9. **Change_Interval**](examples/Change_Interval)
  * [ 10. **ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex)
  * [ 11. **multiFileProject**](examples/multiFileProject) **New**
* [Example ISR_16_Timers_Array_Complex](#example-isr_16_timers_array_complex)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. ISR_Timer_Complex_Ethernet on Arduino SAM DUE](#1-isr_timer_complex_ethernet-on-arduino-sam-due)
  * [2. TimerInterruptTest on Arduino SAM DUE](#2-timerinterrupttest-on-arduino-sam-due)
  * [3. ISR_16_Timers_Array on Arduino SAM DUE](#3-isr_16_timers_array-on-arduino-sam-due)
  * [4. Change_Interval on Arduino SAM DUE](#4-change_interval-on-arduino-sam-due)
  * [5. ISR_16_Timers_Array_Complex on Arduino SAM DUE](#5-isr_16_timers_array_complex-on-arduino-sam-due)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Important Change from v1.3.0

Please have a look at [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)

### Why do we need this [SAMDUE_TimerInterrupt library](https://github.com/khoih-prog/SAMDUE_TimerInterrupt)

### Features

This library enables you to use Interrupt from Hardware Timers on an SAM-DUE-based board.

As **Hardware Timers are rare, and very precious assets** of any board, this library now enables you to use up to **16 ISR-based Timers, while consuming only 1 Hardware Timer**. Timers' interval is very long (**ulong millisecs**).

Now with these new **16 ISR-based timers**, the maximum interval is **practically unlimited** (limited only by unsigned long milliseconds) while **the accuracy is nearly perfect** compared to software timers. 

The most important feature is they're ISR-based timers. Therefore, their executions are **not blocked by bad-behaving functions / tasks**. This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_Timer_Complex**](examples/ISR_Timer_Complex) example will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.

Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.

You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in `loop()`, using delay() function as an example. The elapsed time then is very unaccurate

### Why using ISR-based Hardware Timer Interrupt is better

Imagine you have a system with a **mission-critical** function, measuring water level and control the sump pump or doing something much more important. You normally use a software timer to poll, or even place the function in `loop()`. But what if another function is **blocking** the `loop()` or `setup()`.

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use a Hardware Timer with **Interrupt** to call your function.

These hardware timers, using interrupt, still work even if other functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software timers using `millis()` or `micros()`. That's necessary if you need to measure some data requiring better accuracy.

Functions using normal software timers, relying on `loop()` and calling `millis()`, won't work if the `loop()` or `setup()` is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.

The catch is **your function is now part of an ISR (Interrupt Service Routine), and must be lean / mean, and follow certain rules.** More to read on:

[**HOWTO Attach Interrupt**](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)

---

### Currently supported Boards

  - **Arduino SAM DUE**.

---

### Important Notes about ISR

1. Inside the attached function, **delay() won’t work and the value returned by `millis()` will not increment.** Serial data received while in the function may be lost. You should declare as **volatile any variables that you modify within the attached function.**

2. Typically global variables are used to pass data between an ISR and the main program. To make sure variables shared between an ISR and the main program are updated correctly, declare them as volatile.

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards
 3. [`Blynk library 1.0.1+`](https://github.com/blynkkk/blynk-library/releases). [![Latest release](https://img.shields.io/github/release/blynkkk/blynk-library.svg)](https://github.com/blynkkk/blynk-library/releases/latest/) to use with certain example.
 4. To use with certain example, depending on which Ethernet card you're using:
   - [`Ethernet library v2.0.0+`](https://github.com/arduino-libraries/Ethernet) for W5100, W5200 and W5500.  [![GitHub release](https://img.shields.io/github/release/arduino-libraries/Ethernet.svg)](https://github.com/arduino-libraries/Ethernet/releases/latest)
   - [`EthernetLarge library v2.0.0+`](https://github.com/OPEnSLab-OSU/EthernetLarge) for W5100, W5200 and W5500.
   - [`Ethernet2 library v1.0.4+`](https://github.com/khoih-prog/Ethernet2) for W5500. [![GitHub release](https://img.shields.io/github/release/adafruit/Ethernet2.svg)](https://github.com/adafruit/Ethernet2/releases/latest)
   - [`Ethernet3 library v1.5.5+`](https://github.com/sstaub/Ethernet3) for W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip. [![GitHub release](https://img.shields.io/github/release/sstaub/Ethernet3.svg)](https://github.com/sstaub/Ethernet3/releases/latest)
   - [`EthernetENC library v2.0.2+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest). **New and Better**
   - [`UIPEthernet library v2.0.11+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
 5. To use with certain example
   - [`SimpleTimer library`](https://github.com/jfturcot/SimpleTimer) for [ISR_16_Timers_Array](examples/ISR_16_Timers_Array) and [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) examples.
   
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
3. Install [**SAMDUE_TimerInterrupt** library](https://platformio.org/lib/show/11467/SAMDUE_TimerInterrupt) or [**SAMDUE_TimerInterrupt** library](https://platformio.org/lib/show/11428/SAMDUE_TimerInterrupt) by using [Library Manager](https://platformio.org/lib/show/11467/SAMDUE_TimerInterrupt/installation). Search for **SAMDUE_TimerInterrupt** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

---
---

### Libraries' Patches

#### Notes: These patches are totally optional and necessary only when you use the related Ethernet library and get certain error or issues.

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)


#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.12/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)


---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include these `.hpp` files

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "SAMDUETimerInterrupt.hpp"   //https://github.com/khoih-prog/SAMDUE_TimerInterrupt

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "SAMDUE_ISR_Timer.hpp"        //https://github.com/khoih-prog/SAMDUE_TimerInterrupt
```

in many files. But be sure to use the following `.h` files **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "SAMDUETimerInterrupt.h"     //https://github.com/khoih-prog/SAMDUE_TimerInterrupt

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "SAMDUE_ISR_Timer.h"          //https://github.com/khoih-prog/SAMDUE_TimerInterrupt
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

---
---


## New from v1.0.1

Now with these new `16 ISR-based timers` (while consuming only **1 hardware timer**), the maximum interval is practically unlimited (limited only by unsigned long milliseconds). The accuracy is nearly perfect compared to software timers. The most important feature is they're ISR-based timers Therefore, their executions are not blocked by bad-behaving functions / tasks.
This important feature is absolutely necessary for mission-critical tasks. 

The [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) and [**ISR_Timer_Complex_Ethernet**](examples/ISR_Timer_Complex_Ethernet) examples will demonstrate the nearly perfect accuracy compared to software timers by printing the actual elapsed millisecs of each type of timers.
Being ISR-based timers, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet and Blynk services. You can also have many `(up to 16)` timers to use.
This non-being-blocked important feature is absolutely necessary for mission-critical tasks. 
You'll see blynkTimer Software is blocked while system is connecting to WiFi / Internet / Blynk, as well as by blocking task 
in `loop()`, using delay() function as an example. The elapsed time then is very unaccurate

---
---

## Usage

Before using any Timer, you have to make sure the Timer has not been used by any other purpose.

### 1. Using only Hardware Timer directly

#### 1.1 Init Hardware Timer

```cpp
// Interval in microsecs
attachDueInterrupt(TIMER1_INTERVAL_MS * 1000, TimerHandler1, "ITimer1");
```

#### 1.2 Set Hardware Timer Interval and attach Timer Interrupt Handler function

```cpp
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

### 2. Using 16 ISR_based Timers from 1 Hardware Timer


#### 2.1 Init Hardware Timer and ISR-based Timer

```cpp
// Interval in microsecs
attachDueInterrupt(TIMER1_INTERVAL_MS * 1000, TimerHandler1, "ITimer1");
```

#### 2.2 Set Hardware Timer Interval and attach Timer Interrupt Handler functions

```cpp
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
 9. [**Change_Interval**](examples/Change_Interval). New
10. [**ISR_16_Timers_Array_Complex**](examples/ISR_16_Timers_Array_Complex).
11. [**multiFileProject**](examples/multiFileProject) **New**

---
---

### Example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex)

https://github.com/khoih-prog/SAMDUE_TimerInterrupt/blob/34fbcaf186b6b4e116df6d73dba55f5534cf53a9/examples/ISR_16_Timers_Array_Complex/ISR_16_Timers_Array_Complex.ino#L35-L367


---
---

### Debug Terminal Output Samples

### 1. ISR_Timer_Complex_Ethernet on Arduino SAM DUE

The following is the sample terminal output when running example [ISR_Timer_Complex_Ethernet](examples/ISR_Timer_Complex_Ethernet) on **Arduino SAM DUE** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy**.  The ISR timer is **programmed for 2s, is activated exactly after 2.000s !!!**

While software timer, **programmed for 2s, is activated after 10.917s !!!**. Then in `loop()`, it's also activated **every 3s**.

```
Starting ISR_Timer_Complex_Ethernet on SAM DUE
SAMDUE_TimerInterrupt v1.3.0
CPU Frequency = 84 MHz
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

### 2. TimerInterruptTest on Arduino SAM DUE

The following is the sample terminal output when running example [**TimerInterruptTest**](examples/TimerInterruptTest) on **Arduino SAM DUE** to demonstrate how to start/stop Hardware Timers.

```
Starting TimerInterruptTest on SAM DUE
SAMDUE_TimerInterrupt v1.3.0
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

### 3. ISR_16_Timers_Array on Arduino SAM DUE

The following is the sample terminal output when running example [**ISR_16_Timers_Array**](examples/ISR_16_Timers_Array) on **Arduino SAM DUE** to demonstrate the accuracy and how to use 16 ISR Timers from just 1 Hardware Timer.

```
Starting ISR_16_Timers_Array on SAM DUE
SAMDUE_TimerInterrupt v1.3.0
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

### 4. Change_Interval on Arduino SAM DUE

The following is the sample terminal output when running example [Change_Interval](examples/Change_Interval) to demonstrate how to change Timer Interval on-the-fly

```
Starting Change_Interval on SAM DUE
SAMDUE_TimerInterrupt v1.3.0
CPU Frequency = 84 MHz
Timer Frequency = 84 MHz
Using Timer(0) = TC0, channel = 0, IRQ = TC0_IRQn
ITimer0 attached to Timer(0)
Using Timer(1) = TC0, channel = 1, IRQ = TC1_IRQn
ITimer1 attached to Timer(1)
Time = 10001, Timer0Count = 19, Timer1Count = 9
Time = 20002, Timer0Count = 39, Timer1Count = 19
ITimer0 attached to Timer(0)
ITimer1 attached to Timer(1)
Changing Interval, Timer0 = 1000,  Timer1 = 2000
Time = 30003, Timer0Count = 49, Timer1Count = 24
Time = 40004, Timer0Count = 59, Timer1Count = 29
ITimer0 attached to Timer(0)
ITimer1 attached to Timer(1)
Changing Interval, Timer0 = 500,  Timer1 = 1000
Time = 50005, Timer0Count = 79, Timer1Count = 39
Time = 60006, Timer0Count = 99, Timer1Count = 49
ITimer0 attached to Timer(0)
ITimer1 attached to Timer(1)
Changing Interval, Timer0 = 1000,  Timer1 = 2000
Time = 70007, Timer0Count = 109, Timer1Count = 54
Time = 80008, Timer0Count = 119, Timer1Count = 59
ITimer0 attached to Timer(0)
ITimer1 attached to Timer(1)
Changing Interval, Timer0 = 500,  Timer1 = 1000
Time = 90009, Timer0Count = 139, Timer1Count = 69
```

---

### 5. ISR_16_Timers_Array_Complex on Arduino SAM DUE

The following is the sample terminal output when running new example [ISR_16_Timers_Array_Complex](examples/ISR_16_Timers_Array_Complex) on **Arduino SAM DUE** to demonstrate the accuracy of ISR Hardware Timer, **especially when system is very busy or blocked**. The 16 independent ISR timers are **programmed to be activated repetitively after certain intervals, is activated exactly after that programmed interval !!!**

While software timer, **programmed for 2s, is activated after 10.000s in `loop()`!!!**.

In this example, 16 independent ISR Timers are used, yet utilized just one Hardware Timer. The Timer Intervals and Function Pointers are stored in arrays to facilitate the code modification.

```
Starting ISR_16_Timers_Array_Complex on SAM DUE
SAMDUE_TimerInterrupt v1.3.0
CPU Frequency = 84 MHz
Timer Frequency = 84 MHz
Using Timer(0) = TC0, channel = 0, IRQ = TC0_IRQn
ITimer attached to Timer(0)
SimpleTimer : 2, ms = 10009, Dms : 10000
Timer : 0, programmed : 5000, actual : 5007
Timer : 1, programmed : 10000, actual : 0
Timer : 2, programmed : 15000, actual : 0
Timer : 3, programmed : 20000, actual : 0
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
SimpleTimer : 2, ms = 20061, Dms : 10052
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15007
Timer : 3, programmed : 20000, actual : 20007
Timer : 4, programmed : 25000, actual : 0
Timer : 5, programmed : 30000, actual : 0
Timer : 6, programmed : 35000, actual : 0
Timer : 7, programmed : 40000, actual : 0
Timer : 8, programmed : 45000, actual : 0
Timer : 9, programmed : 50000, actual : 0
Timer : 10, programmed : 55000, actual : 0
Timer : 11, programmed : 60000, actual : 0
Timer : 12, programmed : 65000, actual : 0
Timer : 13, programmed : 70000, actual : 0
Timer : 14, programmed : 75000, actual : 0
Timer : 15, programmed : 80000, actual : 0
...
SimpleTimer : 2, ms = 140731, Dms : 10057
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75007
Timer : 15, programmed : 80000, actual : 80007
SimpleTimer : 2, ms = 150788, Dms : 10057
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75000
Timer : 15, programmed : 80000, actual : 80007
SimpleTimer : 2, ms = 160845, Dms : 10057
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75000
Timer : 15, programmed : 80000, actual : 80000
SimpleTimer : 2, ms = 170902, Dms : 10057
Timer : 0, programmed : 5000, actual : 5000
Timer : 1, programmed : 10000, actual : 10000
Timer : 2, programmed : 15000, actual : 15000
Timer : 3, programmed : 20000, actual : 20000
Timer : 4, programmed : 25000, actual : 25000
Timer : 5, programmed : 30000, actual : 30000
Timer : 6, programmed : 35000, actual : 35000
Timer : 7, programmed : 40000, actual : 40000
Timer : 8, programmed : 45000, actual : 45000
Timer : 9, programmed : 50000, actual : 50000
Timer : 10, programmed : 55000, actual : 55000
Timer : 11, programmed : 60000, actual : 60000
Timer : 12, programmed : 65000, actual : 65000
Timer : 13, programmed : 70000, actual : 70000
Timer : 14, programmed : 75000, actual : 75000
Timer : 15, programmed : 80000, actual : 80000

```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level (_TIMERINTERRUPT_LOGLEVEL_) from 0 to 4

```cpp
// These define's must be placed at the beginning before #include "SAMDUE_TimerInterrupt.h"
// _TIMERINTERRUPT_LOGLEVEL_ from 0 to 4
// Don't define _TIMERINTERRUPT_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [SAMDUE_TimerInterrupt issues](https://github.com/khoih-prog/SAMDUE_TimerInterrupt/issues)

---

## TO DO

1. Search for bug and improvement.


## DONE


1. Basic hardware timers for SAM DUE.
2. More hardware-initiated software-enabled timers
3. Longer time interval
4. Similar features for remaining Arduino boards such as ESP32, ESP8266, STM32, nRF52, mbed-nRF52, Teensy, etc.
5. Add Table of Contents
6. Fix `multiple-definitions` linker error
7. Optimize library code by using `reference-passing` instead of `value-passing`

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


