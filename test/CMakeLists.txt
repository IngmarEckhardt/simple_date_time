cmake_minimum_required(VERSION 3.5)
project("Simple Time Library Test" C)

# Unity
set(EXTERN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../extern")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../src")

add_subdirectory(${EXTERN_DIR} extern_build)


set(SIMPLETIME_HEADER_FILES
        ${SRC_DIR}/simpleTime/simpleTime.h
)

set(SIMPLETIME_SOURCE_FILES
        ${SRC_DIR}/simpleTime/simpleTime.c
)
add_library(simple_time_only_lib STATIC ${SIMPLETIME_SOURCE_FILES} ${SIMPLETIME_HEADER_FILES})

target_include_directories(simple_time_only_lib PUBLIC
        ${SRC_DIR}/simpleTime/
)

add_executable(time_c_test
        simpleTime_test.c
        simpleTime_test.h
)

target_link_libraries(time_c_test
        simple_time_only_lib
        Unity
)

include(CTest)
add_test(suite_1 time_c_test)