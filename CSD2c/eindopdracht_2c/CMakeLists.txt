cmake_minimum_required(VERSION 3.30)
project(eindopdracht_2c VERSION 0.0.1)

juce_add_console_app(eindopdracht_2c PRODUCT_NAME "eindopdracht_2c")
target_sources(eindopdracht_2c PRIVATE main.cpp
        callback.cpp
        effect.cpp
        StereoEffect.cpp
        delay.cpp
        waveshaper.cpp
        wavetableGenerator.cpp
        chorus.cpp
        StereoChorus.cpp
        )

target_compile_definitions(eindopdracht_2c PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(eindopdracht_2c PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(eindopdracht_2c PRIVATE cxx_std_20)