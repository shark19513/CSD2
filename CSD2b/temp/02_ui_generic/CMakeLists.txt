cmake_minimum_required(VERSION 3.20)
project(02_ui_generic LANGUAGES CXX)

add_executable(anotherExample main.cpp)
target_compile_features(example PRIVATE cxx_std_20)