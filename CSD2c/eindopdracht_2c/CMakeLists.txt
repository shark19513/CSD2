cmake_minimum_required(VERSION 3.30)
project(eindopdracht_2c VERSION 0.0.1)

find_library(LIBLO_LIBRARY NAMES lo)
find_path(LIBLO_INCLUDE_DIR lo/lo.h)

juce_add_console_app(eindopdracht_2c PRODUCT_NAME "eindopdracht_2c")
target_sources(eindopdracht_2c PRIVATE main.cpp
        callback.cpp
        ValueSmoothener.cpp
        osc.cpp
        CustomOscServer.cpp
        effect.cpp
        delay.cpp
        waveshaper.cpp
        wavetableGenerator.cpp
        chorus.cpp
        BitCrusher.cpp
        Filters.h
)

target_compile_definitions(eindopdracht_2c PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(eindopdracht_2c PRIVATE ${LIBLO_INCLUDE_DIRS})

target_link_libraries(eindopdracht_2c PRIVATE
        oscillators
        audio

        juce::juce_core
        juce::juce_data_structures
        juce::juce_events

        ${LIBLO_LIBRARY}

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(eindopdracht_2c PRIVATE cxx_std_20)
