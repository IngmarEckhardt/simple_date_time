cmake_minimum_required(VERSION 3.5)

add_executable(time_c_test
        time_test.c
)

target_link_libraries(time_c_test
        src
        Unity
)

add_test(suite_1 time_c_test)