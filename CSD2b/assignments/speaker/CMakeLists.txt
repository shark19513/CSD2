cmake_minimum_required(VERSION 3.29)
project(speaker)

set(CMAKE_CXX_STANDARD 14)

add_executable(speaker
    main.cpp
        speaker.h
        speaker.cpp
        tweeter.h
        tweeter.cpp
        woofer.h
        woofer.cpp
        driver.h)
