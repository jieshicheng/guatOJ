cmake_minimum_required(VERSION 3.7)
project(guatOJ)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp compiler.cpp compiler.h lib/OJlib.cpp lib/OJlib.h compare.cpp compare.h single_pipe.cpp single_pipe.h)
add_executable(guatOJ ${SOURCE_FILES})