#pragma once

#include "FormulaButton.hpp"
#include "Knob.hpp"
#include <JuceHeader.h>

class OscillatorComponent : public Component
{
public:
    OscillatorComponent(String name);

    void paint(Graphics &) override;
    void resized() override;

private:
    String name;

    Knob attack;
    Knob decay;
    Knob sustain;
    Knob release;

    Knob tune;
    Knob pan;
    Knob volume;
    Knob mix;

    Knob lowCut;
    Knob highCut;

    FormulaButton waveformButton;
    FormulaButton lfoButton;

    AudioProcessorValueTreeState::SliderAttachment attackValue;
    AudioProcessorValueTreeState::SliderAttachment decayValue;
    AudioProcessorValueTreeState::SliderAttachment sustainValue;
    AudioProcessorValueTreeState::SliderAttachment releaseValue;

    AudioProcessorValueTreeState::SliderAttachment tuneValue;
    AudioProcessorValueTreeState::SliderAttachment panValue;
    AudioProcessorValueTreeState::SliderAttachment volumeValue;
    AudioProcessorValueTreeState::SliderAttachment mixValue;

    AudioProcessorValueTreeState::SliderAttachment lowCutValue;
    AudioProcessorValueTreeState::SliderAttachment highCutValue;

    Rectangle<float> nameSize;
    Rectangle<float> waveformSize;
    Rectangle<float> envelopeSize;
    Rectangle<float> lfoSize;
    Rectangle<float> soundSize;
    Rectangle<float> filterSize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorComponent)
};
