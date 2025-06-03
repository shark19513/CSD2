project(nyoomPlugin VERSION 0.0.1)

juce_add_plugin(nyoomPlugin
        VERSION 0.0.1
        # ICON_BIG ...
        # ICON_SMALL ...
        COMPANY_NAME SonicShark
        # IS_SYNTH TRUE/FALSE
        # NEEDS_MIDI_INPUT TRUE/FALSE
        # NEEDS_MIDI_OUTPUT TRUE/FALSE
        # IS_MIDI_EFFECT TRUE/FALSE
        # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE
        # COPY_PLUGIN_AFTER_BUILD TRUE/FALSE
        PLUGIN_MANUFACTURER_CODE Shrk
        PLUGIN_CODE shNy

        FORMATS AU VST3 Standalone
        PRODUCT_NAME "nyoom")

target_sources(nyoomPlugin
        PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp
        Effect.cpp
        Delay.cpp
        Doppler.cpp
)

target_link_libraries(nyoomPlugin
        PRIVATE
        audio
        juce::juce_audio_utils
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)