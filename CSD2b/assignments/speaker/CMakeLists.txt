cmake_minimum_required(VERSION 3.29)
project(3_speaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(3_speaker
    main.cpp
        speaker.h
        speaker.cpp
        tweeter.cpp
        tweeter.h
        woofer.cpp
        woofer.h)
