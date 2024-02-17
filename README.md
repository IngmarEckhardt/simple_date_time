# Microcontroller Time Library

This is a simple C library that provides time-related functions and structures for handling calendar time and processor time. It is intended for use with microcontrollers, such as Arduino.

## Overview

The `mcu_time.h` header file defines various functions and structures for working with system time. It includes functions for obtaining processor time, converting between different time representations, and formatting time values as strings.

The `mcu_clock.h` header file in C includes declarations for functions that manage a volatile uint32_t system time with atomic read and write operations. It is designed to work in conjunction with time management.

## Functions and Structures

### `mcu_time.h`

- `clock()`: Returns the processor time used by the program.
- `difftime()`: Computes the difference between two calendar times.
- `mktime()`: Converts a `struct tm` object in UTC to calendar time.
- `time()`: returns the value read from a pointer.
- `asctime()`: Converts every `struct tm` object to a string representation.
- `ctime()`: Converts a calendar time to a string representation in CET/CEST.
- `gmtime()`: Converts a calendar time value to a UTC-based `struct tm` object.
- `localtime()`: Converts a calendar time value to a CET/CEST `struct tm` object.
- `strftime()`: is a stub that return zero to fulfill ansi/iso 9899-1990

### `mcu_clock.h`

In `mcu_clock.h`, every operation is secured by storing the interrupt status, disabling all interrupts, performing the operation, and then restoring the interrupt status afterward.

- `set_system_time`: Initialize a system time Clock uint32 value
- `get_system_time`: read the system time
- `tick_second`:  increase the system time by one second. This can be done, for example, in an interrupt routine that is triggered by a counter overflow counting from a quartz clock.

## Structures

- `struct tm`: Represents the broken-down time with various components such as seconds, minutes, hours, day of the month, month, year, etc.

## Folder Structure

To avoid problems with cross-platform compilation the code is separated into time.h/.c, which are highly platform-dependent and will cause compile problems in every toolchain where time_t is already declared and SimpleTime.h/.c, which is platform-independent and the unit tests will compile with every toolchain.

## Usage

To use this library in your C program, link the library into your build chain, and include the `time.h` header file. The library will also work in a cpp environment, but keep in mind Atmel warns against using Cpp in the toolchain description..

```c
