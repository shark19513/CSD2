cmake_minimum_required(VERSION 3.30)
project(circBuffer VERSION 0.0.1)

juce_add_console_app(circBuffer PRODUCT_NAME "circBuffer")
target_sources(circBuffer PRIVATE main.cpp circBuffer.cpp)
target_compile_definitions(circBuffer PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(circBuffer PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(circBuffer PRIVATE cxx_std_20)