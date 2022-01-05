#pragma once

#include <JuceHeader.h>
#include "EditorLookAndFeel.hpp"

class SynthProcessor;

class Editor : public AudioProcessorEditor, public TextEditor::Listener
{
public:
    Editor (SynthProcessor&);
    ~Editor();
    
    void paint (Graphics&) override final;
    void resized() override final;
    
    void textEditorTextChanged (TextEditor&) override final;

    void pushBuffer (const AudioBuffer<float>&);

private:
    SynthProcessor& processor;
    EditorLookAndFeel lookAndFeel;
    
    TextEditor formulaEditor;
    AudioVisualiserComponent visualiser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Editor)
};
