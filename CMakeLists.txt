cmake_minimum_required(VERSION 3.5)



project("Simple Time Library Test" C)

# Add source files directly here
set(SIMPLETIME_HEADER_FILES
        src/simpleTime/simpleTime.h
)

set(SIMPLETIME_SOURCE_FILES
        src/simpleTime/simpleTime.c
)


# Add library target
add_library(simple_time_only_lib STATIC ${SIMPLETIME_SOURCE_FILES} ${SIMPLETIME_HEADER_FILES})

# Include directories for simpleTime
target_include_directories(simple_time_only_lib PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/simpleTime
)

include(CTest)
add_subdirectory(extern)
add_subdirectory(test)
