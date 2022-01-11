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
      tune("Tune", "ct"), pan("Pan", "%"), volume("Volume", "db"), mix("Mix", "%"), lowCut("Low Cut", "Hz"),
      highCut("High Cut", "db"), attackValue(Params::getState(), removeWhitespace(name) + ".attack", attack),
      decayValue(Params::getState(), removeWhitespace(name) + ".decay", decay),
      sustainValue(Params::getState(), removeWhitespace(name) + ".sustain", sustain),
      releaseValue(Params::getState(), removeWhitespace(name) + ".release", release),
      tuneValue(Params::getState(), removeWhitespace(name) + ".tune", tune),
      panValue(Params::getState(), removeWhitespace(name) + ".pan", pan),
      volumeValue(Params::getState(), removeWhitespace(name) + ".volume", volume),
      mixValue(Params::getState(), removeWhitespace(name) + ".mix", mix),
      lowCutValue(Params::getState(), removeWhitespace(name) + ".lowCut", lowCut),
      highCutValue(Params::getState(), removeWhitespace(name) + ".highCut", highCut)
{
    // wave formula

    addAndMakeVisible(&waveFormula);

    // envelope

    addAndMakeVisible(&attack);
    addAndMakeVisible(&decay);
    addAndMakeVisible(&sustain);
    addAndMakeVisible(&release);

    // sound

    addAndMakeVisible(&tune);
    addAndMakeVisible(&pan);
    addAndMakeVisible(&volume);
    addAndMakeVisible(&mix);

    // filter

    addAndMakeVisible(&lowCut);
    addAndMakeVisible(&highCut);
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

    gfx.setColour(EditorColours::Marigold);
    gfx.setFont(Font(EditorLookAndFeel::getValueMonospaceFont()));
    gfx.setFont(24.0F);

    gfx.drawText("sin(x)", lfoSize, Justification::centred);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(lfoSize.getRight(), LineThickness, lfoSize.getRight(), getHeight() - LineThickness, LineThickness);

    // draw sound label

    gfx.setColour(EditorColours::BlackCoffee.brighter());
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText("sound", soundSize.reduced(Margin * 0.5, Margin * 0.5), Justification::centredTop);

    // draw divider

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawLine(soundSize.getRight(), LineThickness, soundSize.getRight(), getHeight() - LineThickness, LineThickness);

    // draw filter label

    gfx.setColour(EditorColours::BlackCoffee.brighter());
    gfx.setFont(Font(EditorLookAndFeel::getMainFont()));
    gfx.setFont(16.0F);

    gfx.drawText("filter", filterSize.reduced(Margin * 0.5, Margin * 0.5), Justification::centredTop);
}

void OscillatorComponent::resized()
{
    nameSize = Rectangle<float>(0, 0, 60.0F, getHeight());
    waveformSize = Rectangle<float>(nameSize.getRight() + LineThickness, 0, 200.0F, getHeight());

    const auto topMargin = 18.0F;
    const auto bottomMargin = topMargin / 2;
    const auto height = getHeight() - topMargin - bottomMargin;
    const auto width = height * 0.75;

    envelopeSize = Rectangle<float>(waveformSize.getRight() + LineThickness, 0, width * 4, getHeight());

    attack.setBounds(envelopeSize.getX(), topMargin, width, height);
    decay.setBounds(attack.getRight(), topMargin, width, height);
    sustain.setBounds(decay.getRight(), topMargin, width, height);
    release.setBounds(sustain.getRight(), topMargin, width, height);

    lfoSize = Rectangle<float>(envelopeSize.getRight() + LineThickness, 0, 200.0F, getHeight());
    soundSize = Rectangle<float>(lfoSize.getRight() + LineThickness, 0, width * 4, getHeight());

    tune.setBounds(soundSize.getX(), topMargin, width, height);
    pan.setBounds(tune.getRight(), topMargin, width, height);
    volume.setBounds(pan.getRight(), topMargin, width, height);
    mix.setBounds(volume.getRight(), topMargin, width, height);

    filterSize = Rectangle<float>(soundSize.getRight() + LineThickness, 0, width * 3, getHeight());

    lowCut.setBounds(filterSize.getX(), topMargin, width, height);
    highCut.setBounds(lowCut.getRight(), topMargin, width, height);
}
