cmake_minimum_required(VERSION 2.8.8)

project(prefix)

add_executable(prefix_test prefix_test.c prefix.c)

set( CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_executable(prefix_test_cpp prefix.c prefix_test.cc prefix.cc)

