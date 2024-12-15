cmake_minimum_required(VERSION 3.30)
project(SynthSong VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)

juce_add_console_app(SynthSong PRODUCT_NAME "SynthSong")
target_sources(SynthSong
                PRIVATE
                main.cpp
                sine.cpp
                saw.cpp
                square.cpp
                oscillator.cpp
                synth.cpp
                superSawSynth.cpp
                squareBassSynth.cpp
                tunes.cpp
                audioToFile.cpp
                )

target_compile_definitions(SynthSong
                            PRIVATE
                            JUCE_WEB_BROWSER=0
                            JUCE_USE_CURL=0
                            SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
                            )

target_link_libraries(SynthSong
        PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_processors

        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

target_compile_features(SynthSong PRIVATE cxx_std_20)