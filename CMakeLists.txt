#Name: William Parlan
#Assignment: Homework 3
#Description: Cmake instructions to generate executables

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(hw8test hw8_tests.cpp)
target_link_libraries(hw8test ${GTEST_LIBRARIES} pthread)

# create performance executable
add_executable(hw8perf hw8_perf.cpp)