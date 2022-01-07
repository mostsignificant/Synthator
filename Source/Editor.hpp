#pragma once

#include "EditorLookAndFeel.hpp"
#include "OscillatorComponent.hpp"
#include <JuceHeader.h>

class SynthProcessor;

class Editor : public AudioProcessorEditor, public TextEditor::Listener
{
public:
    Editor(SynthProcessor &);
    ~Editor();

    void paint(Graphics &) override final;
    void resized() override final;

    void textEditorTextChanged(TextEditor &) override final;

    void pushBuffer(const AudioBuffer<float> &);

private:
    SynthProcessor &processor;
    EditorLookAndFeel lookAndFeel;

    TextEditor formulaEditor;
    AudioVisualiserComponent visualiser;
    OscillatorComponent osc1;
    OscillatorComponent osc2;
    OscillatorComponent osc3;
    OscillatorComponent osc4;

    void paintBackground(Graphics &);
    void paintHeader(Graphics &);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor)
};
