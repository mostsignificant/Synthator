#pragma once

#include <JuceHeader.h>
#include "Oscillator.hpp"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void prepareToPlay (double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void setFormula (String formula);
  
private:
    AudioBuffer<float> buffer;
    
    enum {
      OscillatorIndex
    };
    dsp::ProcessorChain<Oscillator> chain;
    ADSR envelope;
};
