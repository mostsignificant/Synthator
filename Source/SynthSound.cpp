#include "SynthSound.hpp"

bool SynthSound::appliesToNote (int midiNoteNumber)
{
    return true;
}

bool SynthSound::appliesToChannel (int midiChannel)
{
    return true;
}
