cmake_minimum_required(VERSION 3.29)
project(instrument_class)

set(CMAKE_CXX_STANDARD 20)

add_executable(instrument_class main.cpp
        instrument.cpp
        instrument.h)
