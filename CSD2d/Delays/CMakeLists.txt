cmake_minimum_required(VERSION 3.30)
project(Delays VERSION 0.0.1)

find_library(LIBLO_LIBRARY NAMES lo)
find_path(LIBLO_INCLUDE_DIR lo/lo.h)

juce_add_console_app(Delays PRODUCT_NAME "Delays")
target_sources(Delays PRIVATE
        Effect.cpp
        SubsampleDelay.cpp
)

target_compile_definitions(Delays PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="..")

target_include_directories(Delays PRIVATE ${LIBLO_INCLUDE_DIRS})

target_link_libraries(Delays PRIVATE
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

target_compile_features(Delays PRIVATE cxx_std_20)