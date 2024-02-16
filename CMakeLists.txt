cmake_minimum_required(VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
set(TARGET_CPU ATmega328P)

project(simple-date-time CXX C)

add_compile_definitions("__AVR_${TARGET_CPU}__")

add_link_options(-Wl,--print-memory-usage )

# Specify your source files here
set(SOURCE_FILES
        src/mcuClock.c
        src/time.c
)

# Define the executable target and link it with source files
add_executable(simple-date-time ${SOURCE_FILES})

# Add compiler options
target_compile_options(simple-date-time PRIVATE
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