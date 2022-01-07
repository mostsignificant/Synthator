#include "Editor.hpp"
#include "EditorColours.hpp"
#include "SynthProcessor.hpp"
#include "Version.hpp"

Editor::Editor(SynthProcessor &p)
    : AudioProcessorEditor(&p), processor(p), visualiser(p.getTotalNumOutputChannels()), osc1("OSC 1"), osc2("OSC 2"),
      osc3("OSC 3"), osc4("OSC 4")
{
    setLookAndFeel(&lookAndFeel);

    visualiser.setBufferSize(512);
    visualiser.setSamplesPerBlock(4);
    visualiser.setColours(Colours::white, Colours::orange);

    setSize(1200, 900);

    formulaEditor.addListener(this);
    addAndMakeVisible(&osc1);
    addAndMakeVisible(&osc2);
    addAndMakeVisible(&osc3);
    addAndMakeVisible(&osc4);
    // addAndMakeVisible(&visualiser);
}

Editor::~Editor()
{
    setLookAndFeel(nullptr);
}

void Editor::paint(Graphics &gfx)
{
    paintBackground(gfx);
    paintHeader(gfx);
}

void Editor::resized()
{
    const auto margin = 10.0F;

    osc1.setBounds(margin, 100.0F, getWidth() - 2 * margin, 100.0F);
    osc2.setBounds(margin, 200.0F, getWidth() - 2 * margin, 100.0F);
    osc3.setBounds(margin, 300.0F, getWidth() - 2 * margin, 100.0F);
    osc4.setBounds(margin, 400.0F, getWidth() - 2 * margin, 100.0F);
}

void Editor::textEditorTextChanged(TextEditor &editor)
{
    if (&editor == &formulaEditor)
    {
        processor.onFormulaChanged(formulaEditor.getText());
    }
}

void Editor::pushBuffer(const AudioBuffer<float> &buffer)
{
    visualiser.pushBuffer(buffer);
}

void Editor::paintBackground(Graphics &gfx)
{
    const auto gradient =
        ColourGradient(EditorColours::BlackCoffee, 0, 0, EditorColours::RaisinBlack, 0, getHeight(), false);
    gfx.setGradientFill(gradient);
    gfx.fillRect(0, 0, getWidth(), getHeight());
}

void Editor::paintHeader(Graphics &gfx)
{
    const auto height = 75;

    // draw header background

    gfx.setColour(EditorColours::RaisinBlack);
    gfx.fillRect(0, 0, getWidth(), height);

    // draw synthator text

    gfx.setFont(Font(EditorLookAndFeel::getValueRegularFont()));
    gfx.setFont(36.0F);
    gfx.setColour(EditorColours::ParadisePink);
    gfx.drawFittedText("Synthator", Rectangle<int>(getWidth() - height * 3, 0, height * 3, height),
                       Justification::centred, 1);

    // draw version number

    gfx.setFont(Font(EditorLookAndFeel::getLabelFont()));
    gfx.setFont(12.0F);
    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawFittedText(SYNTHATOR_VERSION, Rectangle<int>(getWidth() - height * 3, 0, height * 3, height),
                       Justification::centredBottom, 1);
}
