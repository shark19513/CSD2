cmake_minimum_required(VERSION 3.30)
project(Dopplinator VERSION 0.0.1)

find_library(LIBLO_LIBRARY NAMES lo)
find_path(LIBLO_INCLUDE_DIR lo/lo.h)

juce_add_console_app(Dopplinator PRODUCT_NAME "Dopplinator")
target_sources(Dopplinator PRIVATE
        main.cpp
        osc.cpp
        CustomOscServer.cpp
        CustomCallback.cpp
        Effect.cpp
        Doppler.cpp
        Delay.cpp
)

target_compile_definitions(Dopplinator PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="..")

target_include_directories(Dopplinator PRIVATE ${LIBLO_INCLUDE_DIRS})

target_link_libraries(Dopplinator PRIVATE
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

target_compile_features(Dopplinator PRIVATE cxx_std_20)