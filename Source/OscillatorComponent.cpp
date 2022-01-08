#include "OscillatorComponent.hpp"
#include "EditorColours.hpp"
#include "EditorLookAndFeel.hpp"
#include "Params.hpp"

namespace
{

const auto CornerSize = 10.0F;
const auto LineThickness = 2.0F;
const auto Margin = 10.0F;

auto removeWhitespace(String text) -> String
{
    return text.replace(" ", "");
}

} // namespace

OscillatorComponent::OscillatorComponent(String name)
    : name(name), attack("ATT", "sec"), decay("DEC", "sec"), sustain("SUS", "%"), release("REL", "sec"),
      attackValue(Params::getState(), removeWhitespace(name) + ".attack", attack),
      decayValue(Params::getState(), removeWhitespace(name) + ".decay", decay),
      sustainValue(Params::getState(), removeWhitespace(name) + ".sustain", sustain),
      releaseValue(Params::getState(), removeWhitespace(name) + ".release", release)
{
    // wave formula

    addAndMakeVisible(&waveFormula);

    // envelope

    addAndMakeVisible(&attack);
    addAndMakeVisible(&decay);
    addAndMakeVisible(&sustain);
    addAndMakeVisible(&release);
}

void OscillatorComponent::paint(Graphics &gfx)
{
    const auto background =
        Rectangle<float>(LineThickness, LineThickness, getWidth() - 2 * LineThickness, getHeight() - 2 * LineThickness);

    // draw background and outline

    gfx.setColour(EditorColours::RaisinBlack.withAlpha(0.25F));
    gfx.fillRoundedRectangle(background, CornerSize);

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawRoundedRectangle(background, CornerSize, LineThickness);

    // draw oscillator name label

    const auto nameLabelSize = Rectangle<float>(LineThickness, 0.0F, 75.0F, getHeight());

    gfx.setColour(EditorColours::ParadisePink);
    gfx.setFont(Font(EditorLookAndFeel::getLabelFont()));
    gfx.setFont(16.0F);

    gfx.drawText(name, nameLabelSize, Justification::centred);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(nameLabelSize.getWidth(), LineThickness, nameLabelSize.getWidth(), getHeight() - LineThickness,
                 LineThickness);

    // draw wave formula label

    const auto waveformLabelSize = nameLabelSize + Point<float>(nameLabelSize.getWidth(), 0);

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.setFont(Font(EditorLookAndFeel::getLabelFont()));
    gfx.setFont(16.0F);

    gfx.drawText("Waveform", waveformLabelSize, Justification::centredTop);
}

void OscillatorComponent::resized()
{

    waveFormula.setBounds(50.0F, 0.0F, 75.0F, 75.0F);

    attack.setBounds(175.0F, 0.0F, 75.0F, 75.0F);
    decay.setBounds(250.0F, 0.0F, 75.0F, 75.0F);
    sustain.setBounds(325.0F, 0.0F, 75.0F, 75.0F);
    release.setBounds(400.0F, 0.0F, 75.0F, 75.0F);
}
