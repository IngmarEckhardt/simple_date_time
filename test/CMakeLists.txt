cmake_minimum_required(VERSION 3.5)

add_executable(time_c_test
        simpleTime_test.c
)

target_link_libraries(time_c_test
        simple_time_only_lib
        Unity
)

add_test(suite_1 time_c_test)