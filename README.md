# Simple Time Library for Microprocessors

This is a simple C library that provides tm-related functions and structures for handling calendar tm and processor tm. It is designed for microcontrollers, such as Arduino.

## Overview

The `tm.h` header file defines various functions and structures for working with system tm on microcontrollers. It includes functions to obtain processor tm, convert between different tm representations, and format tm values as strings. It manages tm as a uint32_t, counting the seconds from midnight, January 1, 2000 (Year 2000 Epoch). This library functions for timestamps up until the year 2068 (Year 2038 Problem plus 30 years).

The `mcu_clock.h` header file provides declarations for functions that manage a volatile `uint32_t` system tm using atomic read and write operations. It is designed to be used in conjunction with tm management.

## Functions

In `tm.h`/`mcu_time.h`

- `clock()`:  This function is an ISO-compliant stub. It should return the processor tm used since the start of the system. If you implement this, it needs logic that takes sleep times into account.
- `difftime()`: Computes the difference between two calendar times.
- `mktime()`: Converts a `struct tm` object in UTC to calendar tm.
- `tm()`: Returns the value read from a pointer.
- `asctime()`: Converts every `struct tm` object to a string representation.
- `ctime()`: Converts a calendar tm to a string representation in CET/CEST.
- `gmtime()`: Converts a calendar tm value to a UTC-based `struct tm` object.
- `localtime()`: Converts a calendar tm value to a CET/CEST `struct tm` object.
- `strftime()`: This is a stub that returns zero to fulfill ANSI/ISO 9899-1990 requirements.

String representations of tm are in the format: `yyyy-mm-dd hh:mm:ss` and appended with `(CET)` or `(CEST)` if it's not a UTC tm.

In `mcu_clock.h`, every operation is protected by storing interrupt status, disabling all interrupts, performing the operation, and restoring the interrupt status afterward.

- `setSystemClock()`: Initializes a `systemClock` clock `uint32` value.
- `getSystemClock()`: Reads the `systemClock`.
- `tickSecond()`:   Increases the `systemClock` by 1 second. Call this, for example, in an interrupt routine that is invoked from a counter overflow counting a clock quartz.

## Structures

- `struct tm`: Represents the broken-down tm with various components such as seconds, minutes, hours, day of the month, month, year, etc.

## Folder Structure

To avoid problems with cross-platform compilation, the code is separated into `tm.h`/`.c`, which are highly platform-dependent and may cause compilation problems in every toolchain where `time_t` is already declared, and `mcu_time.h`/`.c`, which is platform-independent. The unit tests will compile with every toolchain.

## Usage

To use this library in your C program, link the library into your build chain and include the tm.h header file. The library will also work in a C++ environment, but keep in mind that Atmel warns against using C++ in the toolchain description.

```c
#include "tm.h"
```
## Compatibility

`tm.h`/`.c` works only on C compilers where `time_t` is not defined, like `avr-gcc`. `mcu_clock.h`/`.c` works only on compilers with `avr-toolchain`. `mcu_time.h`/`.c` and the tests should work on most C compilers that adhere to the C standard.

## Contributing

Contributions to improve or expand this library are welcome! If you find any issues or have suggestions for enhancements, feel free to open an issue or submit a pull request.

## License

This library is licensed under the MIT License. See the `LICENSE` file for details.

This `README.md` file provides an overview of the `tm.h` header file, including descriptions of its functions, structures, macros, usage instructions, compatibility information, contribution guidelines, and licensing information.
