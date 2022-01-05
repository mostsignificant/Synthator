########################################################################################################################
### SYNTHATOR SOURCE
########################################################################################################################

juce_add_plugin(${SYNTHATOR_PROJECT_NAME}
    # ICON_BIG ... # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    COMPANY_NAME ${SYNTHATOR_AUTHOR_DOMAIN}
    IS_SYNTH TRUE
    # NEEDS_MIDI_INPUT TRUE/FALSE # Does the plugin need midi input?
    # NEEDS_MIDI_OUTPUT TRUE/FALSE # Does the plugin need midi output?
    IS_MIDI_EFFECT FALSE
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Most
    PLUGIN_CODE Stor
    FORMATS Standalone # AU VST3
    PRODUCT_NAME ${SYNTHATOR_PROJECT_NAME})

########################################################################################################################
### SYNTHATOR HEADER, SOURCES, AND COMPILE SETTINGS
########################################################################################################################

juce_generate_juce_header(${SYNTHATOR_PROJECT_NAME})

target_sources(${SYNTHATOR_PROJECT_NAME}
    PRIVATE
        Editor.cpp
        EditorLookAndFeel.cpp
        Oscillator.cpp
        SynthProcessor.cpp
        SynthSound.cpp
        SynthVoice.cpp)

target_compile_definitions(${SYNTHATOR_PROJECT_NAME}
    PUBLIC
        JUCE_WEB_BROWSER=0 
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_compile_features(${SYNTHATOR_PROJECT_NAME} PRIVATE cxx_std_17)

########################################################################################################################
### SYNTHATOR BINARY DATA FROM RESOURCES FOLDER
########################################################################################################################

set(SYNTHATOR_BINARY_DATA "${SYNTHATOR_PROJECT_NAME}Data")

juce_add_binary_data(${SYNTHATOR_BINARY_DATA}
    SOURCES 
        ${PROJECT_SOURCE_DIR}/Resources/Fonts/Share/Share-Bold.ttf
        ${PROJECT_SOURCE_DIR}/Resources/Fonts/Share/Share-BoldItalic.ttf
        ${PROJECT_SOURCE_DIR}/Resources/Fonts/Share/Share-Italic.ttf
        ${PROJECT_SOURCE_DIR}/Resources/Fonts/Share/Share-Regular.ttf
        ${PROJECT_SOURCE_DIR}/Resources/Fonts/ShareTechMono/ShareTechMono-Regular.ttf)

########################################################################################################################
### SYNTHATOR LINK BINARY DATA AND JUCE DATA
########################################################################################################################

target_link_libraries(${SYNTHATOR_PROJECT_NAME}
    PRIVATE
        chaiscript
        ${SYNTHATOR_BINARY_DATA}
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags)
        #juce::juce_recommended_warning_flags)
