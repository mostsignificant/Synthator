#include "OscillatorComponent.hpp"
#include "EditorColours.hpp"
#include "EditorLookAndFeel.hpp"
#include "Params.hpp"

namespace
{

auto underscorify(String text) -> String
{
    return text.replace(" ", "_");
}

} // namespace

OscillatorComponent::OscillatorComponent(String name)
    : name(name), attack("ATT", "sec"), decay("DEC", "sec"), sustain("SUS", "%"), release("REL", "sec"),
      attackValue(Params::getState(), underscorify(name) + "_ATTACK", attack),
      decayValue(Params::getState(), underscorify(name) + "_DECAY", decay),
      sustainValue(Params::getState(), underscorify(name) + "_SUSTAIN", sustain),
      releaseValue(Params::getState(), underscorify(name) + "_RELEASE", release)
{
    addAndMakeVisible(&attack);
    addAndMakeVisible(&decay);
    addAndMakeVisible(&sustain);
    addAndMakeVisible(&release);
}

void OscillatorComponent::paint(Graphics &gfx)
{
    const auto cornerSize = 10.0F;
    const auto lineThickness = 2.0F;
    const auto background =
        Rectangle<float>(lineThickness, lineThickness, getWidth() - 2 * lineThickness, getHeight() - 2 * lineThickness);
    const auto margin = 10.0F;

    // draw background and outline

    gfx.setColour(EditorColours::RaisinBlack.withAlpha(0.25F));
    gfx.fillRoundedRectangle(background, cornerSize);

    gfx.setColour(EditorColours::BlackCoffee);
    gfx.drawRoundedRectangle(background, cornerSize, lineThickness);

    // draw oscillator name label

    const auto labelSize = Rectangle<float>(margin, 0.0F, 50.0F, getHeight());

    gfx.setColour(EditorColours::ParadisePink);
    gfx.setFont(Font(EditorLookAndFeel::getLabelFont()));
    gfx.setFont(16.0F);

    gfx.drawText(name, labelSize, Justification::centred);
}

void OscillatorComponent::resized()
{
    attack.setBounds(75.0F, 0.0F, 75.0F, 75.0F);
    decay.setBounds(150.0F, 0.0F, 75.0F, 75.0F);
    sustain.setBounds(225.0F, 0.0F, 75.0F, 75.0F);
    release.setBounds(300.0F, 0.0F, 75.0F, 75.0F);
}
