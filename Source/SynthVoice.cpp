#include "SynthVoice.hpp"

#include "SynthProcessor.hpp"
#include "SynthSound.hpp"

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
    return dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    osc1.reset();
    envelope.reset();

    const dsp::ProcessSpec spec{sampleRate, static_cast<uint32>(samplesPerBlock),
                                static_cast<uint32>(outputChannels)};

    osc1.prepare(spec);
    envelope.setParameters(ADSR::Parameters{0.1f, 0.1f, 1.0f, 0.1f});
    envelope.setSampleRate(spec.sampleRate);
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                           int currentPitchWheelPosition)
{
    const auto frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    osc1.get<OscillatorIndex>().setFrequency(frequency);
    osc1.get<OscillatorIndex>().setLevel(velocity);

    envelope.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    envelope.noteOff();

    if (!allowTailOff || !envelope.isActive())
        clearCurrentNote();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}

void SynthVoice::renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    if (!isVoiceActive())
        return;

    buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    buffer.clear();

    dsp::AudioBlock<float> audioblock{buffer};
    osc1.process(dsp::ProcessContextReplacing<float>{audioblock});

    envelope.applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());

    for (auto channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, buffer, channel, 0, numSamples);

        if (!envelope.isActive())
            clearCurrentNote();
    }
}

void SynthVoice::setFormula(String formula)
{
    osc1.get<OscillatorIndex>().setFormula(formula);
}