cmake_minimum_required(VERSION 2.8.8)
project(w0rdcr4ck)

set( CMAKE_CXX_FLAGS "-Wall -std=c++14" )

add_executable(w0rdcr4ck ws.hpp ws.cc args.cc "prefix/prefix.c" "prefix/prefix.cc")

