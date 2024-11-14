cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 14)

project(Assignment_3)

add_subdirectory(timer)

add_executable(timer_test
    main.cpp)

target_link_libraries(timer_test PRIVATE timer)
