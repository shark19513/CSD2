cmake_minimum_required(VERSION 3.20)
project(03_enum_choices LANGUAGES CXX)

add_executable(yetAnotherExample  main.cpp
                        synth.cpp
                        uiUtilities.cpp
                        )

target_compile_features(example PRIVATE cxx_std_20)