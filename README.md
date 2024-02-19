# Simple Time Library for Microprocessors

This is a simple C library that provides time-related functions and structures for handling calendar time and processor time. It is designed for microcontrollers, such as Arduino.

## Overview

The `time.h` header file defines various functions and structures for working with system time on microcontrollers. It includes functions to obtain processor time, convert between different time representations, and format time values as strings. It manages time as a uint32_t, counting the seconds from midnight, January 1, 2000 (Year 2000 Epoch). This library functions for timestamps up until the year 2068 (Year 2038 Problem plus 30 years).


## Functions

In `time.h`

- `clock()`:  This function is an ISO-compliant stub. It should return the processor time used since the start of the system. If you implement this, it needs logic that takes sleep times into account.
- `difftime()`: Computes the difference between two calendar times.
- `mktime()`: Converts a `struct time` object in UTC to calendar time.
- `time()`: Returns the value read from a pointer.
- `asctime()`: Converts every `struct time` object to a string representation.
- `ctime()`: Converts a calendar time to a string representation in CET/CEST.
- `gmtime()`: Converts a calendar time value to a UTC-based `struct time` object.
- `localtime()`: Converts a calendar time value to a CET/CEST `struct time` object.
- `strftime()`: This is a stub that returns zero to fulfill ANSI/ISO 9899-1990 requirements.

String representations of time are in the format: `yyyy-mm-dd hh:mm:ss` and appended with `(CET)` or `(CEST)` if it's not a UTC time.

## Structures

- `struct time`: Represents the broken-down time with various components such as seconds, minutes, hours, day of the month, month, year, etc.

## Usage

To use this library in your C program, link the library into your build chain and include the time.h header file. The library will also work in a C++ environment, but keep in mind that Atmel warns against using C++ in the toolchain description. Example of usage: Please check out my `dwarfOS` repository.

```c
#include "time.h"
```
## Compatibility

`time.h`/`.c` works only on C compilers when `time_t` is not defined.

## Contributing

Contributions to improve or expand this library are welcome! If you find any issues or have suggestions for enhancements, feel free to open an issue or submit a pull request.

## License

This library is licensed under the MIT License. See the `LICENSE` file for details.

This `README.md` file provides an overview of the `time.h` header file, including descriptions of its functions, structures, macros, usage instructions, compatibility information, contribution guidelines, and licensing information.
