cmake_minimum_required(VERSION 2.8.8)
project(ws)

set( CMAKE_CXX_FLAGS "-Wall -std=c++11" )

add_executable(w0rdcr4ck ws.cc args.cc "prefix/prefix.c" "prefix/prefix.cc")

