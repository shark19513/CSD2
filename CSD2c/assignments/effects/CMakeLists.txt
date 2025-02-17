cmake_minimum_required(VERSION 3.30)
project(effects VERSION 0.0.1)

juce_add_console_app(effects PRODUCT_NAME "effects")
target_sources(effects PRIVATE main.cpp callback.cpp effect.cpp delay.cpp tremolo.cpp waveshaper.cpp)
target_compile_definitions(effects PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(effects PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(effects PRIVATE cxx_std_20)