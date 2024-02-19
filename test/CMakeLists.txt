cmake_minimum_required(VERSION 3.5)
project("Simple Time Library Test" C)

# Unity
set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../extern")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src/")

add_subdirectory(${EXTERN_DIR} extern_build)

set(SIMPLETIME_SOURCE_FILES
        ${SRC_DIR}mcu_time.c
)
add_library(simple_time_only_lib STATIC ${SIMPLETIME_SOURCE_FILES})

target_include_directories(simple_time_only_lib PUBLIC
       ${SRC_DIR}
)

add_executable(mcu_t_test
        mcu_time_test.c
        mcu_time_test.h
)

target_link_libraries(mcu_t_test
        simple_time_only_lib
        Unity
)

include(CTest)
add_test(suite_1 mcu_t_test)