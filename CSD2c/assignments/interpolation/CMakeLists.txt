cmake_minimum_required(VERSION 3.30)
project(interpolation VERSION 0.0.1)

juce_add_console_app(interpolation PRODUCT_NAME "interpolation")
target_sources(interpolation PRIVATE main.cpp interpolation.cpp interpolation.h)
target_compile_definitions(interpolation PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(interpolation PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(interpolation PRIVATE cxx_std_20)