# Simple Time Library for Microprocessors

This is a simple C library that provides time-related functions and structures for handling calendar time and processor time. It is designed for microcontrollers, such as Arduino.

## Overview

The `time.h` header file defines various functions and structures for working with system time on microcontrollers. It includes functions to obtain processor time, convert between different time representations, and format time values as strings. It manages time as a uint32_t, counting the seconds from midnight, January 1, 2000 (Year 2000 Epoch). This library functions for timestamps up until the year 2068 (Year 2038 Problem plus 30 years).

The `mcuClock.h` header file provides declarations for functions that manage a volatile `uint32_t` system time using atomic read and write operations. It is designed to be used in conjunction with time management.

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

String representations of time are in the format: yyyy-mm-dd hh:mm:ss and appended (CET) or (CEST) if it's not a UTC time.

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

```
## Compatibility

Time.h/.c works only on C compilers where time_t is not defined, like the avr-gcc, mcuClock.h/.c only on compiler with avr-toolchain. Mcu_time.h/.c and the tests should work on most C compilers that adhere to the C standard.

## Contributing

Contributions to improve or expand this library are welcome! If you find any issues or have suggestions for enhancements, feel free to open an issue or submit a pull request.

## License

This library is licensed under the MIT License. See the LICENSE file for details.

This README.md file provides an overview of the `time.h` header file, including descriptions of its functions, structures, macros, usage instructions, compatibility information, contribution guidelines, and licensing information.
