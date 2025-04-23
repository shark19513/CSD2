cmake_minimum_required(VERSION 3.30)
project(FakeDoppler VERSION 0.0.1)

juce_add_console_app(FakeDoppler PRODUCT_NAME "FakeDoppler")
target_sources(FakeDoppler PRIVATE
        main.cpp
        CustomCallback.cpp
)

target_compile_definitions(FakeDoppler PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="..")

target_link_libraries(FakeDoppler PRIVATE
        oscillators
        audio

        juce::juce_core
        juce::juce_data_structures
        juce::juce_events

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(FakeDoppler PRIVATE cxx_std_20)