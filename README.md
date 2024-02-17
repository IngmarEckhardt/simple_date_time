# C Time Library

This is a simple C library providing time-related functions and structures for handling calendar time and processor time. It is meant for Microcontroller like arduino. 

## Overview

The `time.h` header file in C provides declarations for various functions and structures related to time manipulation. It includes functions for obtaining processor time, converting between different time representations, and formatting time values as strings. It handles the time as a uint32_t counting the second from midnight 1.1.2000 (Year 2k Epoche). This library works for timestamps until the 2068. (Year 2038 + 30 years)

The `mcuClock.h` header file in C provides declarations for functions to manage a volatile uint32_t systemTime with atomic read and write operations and is meant to work together with the time management.

## Functions and Structures

In `time.h`

- `clock()`: is a iso fulfilling stub, it should return the processor time used since start of system, if you implement this it need a logic that take sleep times into account
- `difftime()`: Computes the difference between two calendar times.
- `mktime()`: Converts a `struct tm` object in UTC to calendar time.
- `time()`: returns the value read from a pointer.
- `asctime()`: Converts every `struct tm` object to a string representation.
- `ctime()`: Converts a calendar time to a string representation in CET/CEST.
- `gmtime()`: Converts a calendar time value to a UTC-based `struct tm` object.
- `localtime()`: Converts a calendar time value to a CET/CEST `struct tm` object.
- `strftime()`: is a stub that return zero to fulfill ansi/iso 9899-1990

In `mcuClock.h` every operation is protected with storing interrupt status, disabling all Interrupts, doing the operation and restoring the interrupt status afterward.

- `set_system_time`: Initialize a systemTime Clock uint32 value
- `getSystemTime`: read the systemTime
- `tickSecond`:  increase the systemTime with 1 second. Call this for example in a interrupt-routine that is called from a counter overflow counting a clock quartz.

## Structures

- `struct tm`: Represents the broken-down time with various components such as seconds, minutes, hours, day of the month, month, year, etc.

## Folder Structure

To avoid problems with cross-platform compilation the code is separated into time.h/.c, which are highly platform-dependent and will cause compile problems in every toolchain where time_t is already declared and SimpleTime.h/.c, which is platform-independent and the unit tests will compile with every toolchain.

## Usage

To use this library in your C program, link the library into your build chain, and include the `time.h` header file. The library will also work in a cpp environment, but keep in mind Atmel warns against using Cpp in the toolchain description..

```c
#include "time.h"
