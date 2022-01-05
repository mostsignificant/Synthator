#pragma once

#include <JuceHeader.h>

class SynthSound : public SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override final;
    bool appliesToChannel (int midiChannel) override final;
};
