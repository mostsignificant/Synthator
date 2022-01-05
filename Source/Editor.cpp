#include "Editor.hpp"
#include "SynthProcessor.hpp"

Editor::Editor (SynthProcessor& p)
    : AudioProcessorEditor (&p), processor (p), visualiser(p.getTotalNumOutputChannels())
{
    setLookAndFeel(&lookAndFeel);
    
    visualiser.setBufferSize(512);
    visualiser.setSamplesPerBlock(4);
    visualiser.setColours(Colours::white, Colours::orange);
    
    setSize (1024, 768);
    
    formulaEditor.addListener(this);
    addAndMakeVisible (&formulaEditor);
    addAndMakeVisible (&visualiser);
}

Editor::~Editor()
{
    setLookAndFeel(nullptr);
}

void Editor::paint (Graphics& g)
{
    g.setFont (Font (lookAndFeel.getCustomFont()));
    g.setFont (20.0f);
    
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);

    g.drawRoundedRectangle (Rectangle<float>(5, 5, getWidth() - 10, getHeight() - 10), 5, 2);
    
    g.setColour (Colours::black);
    g.drawFittedText ("FORMULATOR", Rectangle<int>(0, 10, getWidth(), 20), Justification::centred, false);
}

void Editor::resized()
{
    visualiser.setBounds (20, 40, getWidth() - 40, 100);
    formulaEditor.setBounds (20, 140, getWidth() - 40, 24);
    
    formulaEditor.setFont (Font (lookAndFeel.getCustomFont()));
    formulaEditor.setBorder (BorderSize<int>(1, 1, 1, 1));
}

void Editor::textEditorTextChanged (TextEditor& editor)
{
    if (&editor == &formulaEditor)
    {
        processor.onFormulaChanged (formulaEditor.getText());
    }
}

void Editor::pushBuffer (const AudioBuffer<float> &buffer)
{
    visualiser.pushBuffer (buffer);
}
