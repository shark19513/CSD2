cmake_minimum_required(VERSION 3.30)
project(sounding_oscillators VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

juce_add_console_app(sounding_oscillators PRODUCT_NAME "sounding_oscillators")
target_sources(sounding_oscillators PRIVATE main.cpp sine.cpp saw.cpp square.cpp)
target_compile_definitions(sounding_oscillators PRIVATE JUCE_WEB_BROWSER=0 JUCE_USE_CURL=0)

target_link_libraries(sounding_oscillators
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(sounding_oscillators PRIVATE cxx_std_20)