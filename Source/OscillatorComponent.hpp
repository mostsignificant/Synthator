#pragma once

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

    TextEditor waveFormula;
    TextEditor lfoFormula;

    AudioProcessorValueTreeState::SliderAttachment attackValue;
    AudioProcessorValueTreeState::SliderAttachment decayValue;
    AudioProcessorValueTreeState::SliderAttachment sustainValue;
    AudioProcessorValueTreeState::SliderAttachment releaseValue;

    Rectangle<float> nameSize;
    Rectangle<float> waveformSize;
    Rectangle<float> envelopeSize;
    Rectangle<float> lfoSize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorComponent)
};
