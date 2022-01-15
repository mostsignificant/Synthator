#pragma once

#include "chaiscript/chaiscript.hpp"
#include <JuceHeader.h>

class Oscillator : public dsp::Oscillator<float>
{
public:
    Oscillator();

    void setFormula(String formula);

private:
    chaiscript::ChaiScript chai;
    String formula;
    float var = 0.0;

    void initChaiscript();
    void initOscillator();
};
