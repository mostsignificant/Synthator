#include "OscillatorComponent.hpp"
#include "EditorColours.hpp"
#include "EditorLookAndFeel.hpp"
#include "Params.hpp"

namespace
{

const auto CornerSize = 10.0F;
const auto LineThickness = 3.0F;
const auto Margin = 10.0F;

auto removeWhitespace(String text) -> String
{
    return text.replace(" ", "");
}

} // namespace

OscillatorComponent::OscillatorComponent(String name)
    : name(name), attack("Attack", "s"), decay("Decay", "s"), sustain("Sustain", "%"), release("Release", "s"),
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

    gfx.setColour(EditorColours::ParadisePink);
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText(name, nameSize, Justification::centred);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(nameSize.getRight(), LineThickness, nameSize.getRight(), getHeight() - LineThickness, LineThickness);

    // draw wave formula

    gfx.setColour(EditorColours::BlackCoffee.brighter());
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText("waveform", waveformSize.reduced(Margin * 0.5, Margin * 0.5), Justification::centredTop);

    gfx.setColour(EditorColours::Platinum);
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(12.0F);

    gfx.drawText("edit", waveformSize.reduced(Margin * 0.5, Margin * 0.5), Justification::topRight);
    gfx.drawText("+", waveformSize.reduced(Margin * 0.5, Margin * 0.5), Justification::topLeft);

    gfx.setColour(EditorColours::Marigold);
    gfx.setFont(Font(EditorLookAndFeel::getValueMonospaceFont()));
    gfx.setFont(24.0F);

    gfx.drawText("sin(x)", waveformSize, Justification::centred);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(waveformSize.getRight(), LineThickness, waveformSize.getRight(), getHeight() - LineThickness,
                 LineThickness);

    // draw envelope label

    gfx.setColour(EditorColours::BlackCoffee.brighter());
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText("envelope", envelopeSize.reduced(Margin * 0.5, Margin * 0.5), Justification::centredTop);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(envelopeSize.getRight(), LineThickness, envelopeSize.getRight(), getHeight() - LineThickness,
                 LineThickness);

    // draw lfo formula

    gfx.setColour(EditorColours::BlackCoffee.brighter());
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText("lfo", lfoSize.reduced(Margin * 0.5, Margin * 0.5), Justification::centredTop);

    gfx.setColour(EditorColours::Platinum);
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(12.0F);

    gfx.drawText("edit", lfoSize.reduced(Margin * 0.5, Margin * 0.5), Justification::topRight);
    gfx.drawText("+", lfoSize.reduced(Margin * 0.5, Margin * 0.5), Justification::topLeft);

    gfx.setColour(EditorColours::Marigold);
    gfx.setFont(Font(EditorLookAndFeel::getValueMonospaceFont()));
    gfx.setFont(24.0F);

    gfx.drawText("sin(x)", lfoSize, Justification::centred);
}

void OscillatorComponent::resized()
{
    nameSize = Rectangle<float>(0, 0, 60.0F, getHeight());
    waveformSize = Rectangle<float>(nameSize.getRight(), 0, 200.0F, getHeight());

    const auto topMargin = 18.0F;
    const auto bottomMargin = topMargin / 2;
    const auto size = getHeight() - topMargin - bottomMargin;

    envelopeSize = Rectangle<float>(waveformSize.getRight(), 0, size * 4, getHeight());

    attack.setBounds(envelopeSize.getX(), topMargin, size, size);
    decay.setBounds(attack.getRight(), topMargin, size, size);
    sustain.setBounds(decay.getRight(), topMargin, size, size);
    release.setBounds(sustain.getRight(), topMargin, size, size);

    lfoSize = Rectangle<float>(envelopeSize.getRight(), 0, 200.0F, getHeight());
}
