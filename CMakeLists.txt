cmake_minimum_required(VERSION 3.5)

project("Time Library Test" C)

include(CTest)
add_subdirectory(src)
add_subdirectory(extern)
add_subdirectory(test)
