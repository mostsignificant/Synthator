#pragma once

#include <JuceHeader.h>
#include "chaiscript/chaiscript.hpp"

class Oscillator
{
public:
    Oscillator();
    
    void prepare (const dsp::ProcessSpec &spec);
    void process (const dsp::ProcessContextReplacing<float> &context) noexcept;
    void reset() noexcept;
    void setFormula (String formula);
    void setFrequency (float frequency);
    void setLevel (float level);

private:
    chaiscript::ChaiScript chai;
    String formula;
    float var = 0.0;
    
    enum {
        OscillatorIndex,
        GainIndex
    };
    dsp::ProcessorChain<dsp::Oscillator<float>, dsp::Gain<float>> chain;
    
    void initChaiscript();
    void initOscillator();
};
