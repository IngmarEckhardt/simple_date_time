cmake_minimum_required(VERSION 3.5)
set(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
project("Simple Time Library" C)
#adjust to your cpu
set(TARGET_CPU ATmega328P)
add_compile_definitions("__AVR_${TARGET_CPU}__")

# adjust -B to your cpu
set(CUSTOM_COMPILE_OPTIONS
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

add_compile_options(${CUSTOM_COMPILE_OPTIONS})

project(simple-date-time-lib CXX C)

set(HEADER_FILES
        time.h
        simpleTime/mcuClock.h
        simpleTime/simpleTime.h
        )

set(SOURCE_FILES
        time.c
        simpleTime/mcuClock.c
        simpleTime/simpleTime.c
        )

add_library(time_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(time_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)