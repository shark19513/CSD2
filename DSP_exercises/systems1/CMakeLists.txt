cmake_minimum_required(VERSION 3.30)
project(systems1 VERSION 0.0.1)

juce_add_console_app(systems1 PRODUCT_NAME "systems1")
target_sources(systems1 PRIVATE main.cpp)
target_compile_definitions(systems1 PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(systems1 PRIVATE
        oscillators
        audio

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(systems1 PRIVATE cxx_std_20)