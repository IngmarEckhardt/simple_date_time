cmake_minimum_required(VERSION 3.5)
project(simple-date-time-lib C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)

#adjust to your cpu
set(TARGET_CPU ATmega328P)

set(HEADER_FILES
        time.h
        mcuClock.h
        )

set(SOURCE_FILES
        time.c
        mcuClock.c
        )

add_link_options(-Wl,--print-memory-usage )

add_library(time_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_compile_definitions("__AVR_${TARGET_CPU}__")

target_compile_options(time_lib PRIVATE
        -x c
        -funsigned-char
        -funsigned-bitfields
        -DNDEBUG
        -I "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include"
        -O2
        -ffunction-sections
        -fdata-sections
        -fpack-struct
        -fshort-enums
        -Wall
        -B "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328p"
        -c
        -std=gnu99
        -MD
        -MP
        -MF "$(@:%.o=%.d)"
        -MT "$(@:%.o=%.d)"
        -MT "$(@:%.o=%.o)"
)
