cmake_minimum_required(VERSION 3.5)

# configuration
set(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_C_STANDARD 99)

# specific to CPU
set(TARGET_CPU ATmega328P)
add_compile_definitions("__AVR_${TARGET_CPU}__")
add_definitions(-D_TIME_T_DEFINED)
add_definitions(-DTIME_H)
set(CMAKE_C_COMPILER_TARGET "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/gcc/dev/atmega328p")

# directories
set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/extern/")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

# naming, versioning
set(NAME "Simple-Date-Time")
set(VERSION "0.3.0")
set(PROJECT ${NAME}_${VERSION})
project(${PROJECT} C)

# initialize extern modules, has to be after declaration of the project
add_subdirectory(${EXTERN_DIR} extern_build)

# Define NDEBUG for release builds
# add_compile_definitions(-DNDEBUG)

# Include AVR-GCC specific header
include_directories("C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/ATmega_DFP/1.7.374/include")

# AVR specific compiler options
set(AVR_COMPILE_OPTIONS
        -x c
        -funsigned-char
        -funsigned-bitfields
        -O2
        -ffunction-sections
        -fdata-sections
        -fpack-struct
        -fshort-enums
        -Wall
        -c
        -MD
        -MP
        -MF "$(@:%.o=%.d)"
        -MT "$(@:%.o=%.d)"
        -MT "$(@:%.o=%.o)"
)
add_compile_options(${AVR_COMPILE_OPTIONS})

# Add linker flags for AVR
set(AVR_LINKER_FLAGS
        -Wl,--gc-sections
)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${AVR_LINKER_FLAGS}")

set(HEADER_FILES
        ${SRC_DIR}mcu_clock.h
        ${SRC_DIR}time.h
)

set(SOURCE_FILES
        ${SRC_DIR}mcu_clock.c
        ${SRC_DIR}time.c
)

add_library(time_lib STATIC ${SOURCE_FILES})

target_include_directories(time_lib PUBLIC
        ${SRC_DIR}
)



add_library(simple_time_test STATIC ${SRC_DIR}time.c)

target_include_directories(simple_time_test PUBLIC
       ${SRC_DIR}
)

add_executable(Test_Time
        test/mcu_time_test.c
        test/mcu_time_test.h
)

target_link_libraries(Test_Time
        simple_time_test
        Unity
)

include(CTest)
add_test(testTimeFile Test_Time)