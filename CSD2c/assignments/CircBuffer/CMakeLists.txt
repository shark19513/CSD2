cmake_minimum_required(VERSION 3.30)
project(CircBuffer VERSION 0.0.1)

juce_add_console_app(CircBuffer PRODUCT_NAME "CircBuffer")
target_sources(CircBuffer PRIVATE main.cpp CircBuffer.cpp)
target_compile_definitions(CircBuffer PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(CircBuffer PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(CircBuffer PRIVATE cxx_std_20)