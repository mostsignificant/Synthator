#include "SynthVoice.hpp"

#include "Params.hpp"
#include "SynthProcessor.hpp"
#include "SynthSound.hpp"

bool SynthVoice::canPlaySound(SynthesiserSound *sound)
{
    return dynamic_cast<SynthSound *>(sound) != nullptr;
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    const dsp::ProcessSpec spec{sampleRate, static_cast<uint32>(samplesPerBlock), static_cast<uint32>(outputChannels)};

    for (auto &&chain : chains)
    {
        chain.reset();
        chain.prepare(spec);
    }

    for (auto i = 0; i < envelopes.size(); ++i)
    {
        envelopes[i].reset();
        envelopes[i].setParameters(Params::getEnvelopeValues(i));
        envelopes[i].setSampleRate(spec.sampleRate);
    }
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound,
                           int currentPitchWheelPosition)
{
    const auto frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);

    for (auto &&chain : chains)
    {
        chain.get<OscillatorIndex>().setFrequency(frequency);
        chain.get<OscillatorIndex>().setLevel(velocity);
    }

    for (auto &&envelope : envelopes)
    {
        envelope.noteOn();
    }
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    for (auto &&envelope : envelopes)
    {
        envelope.noteOff();
    }

    const auto envelopeActive =
        std::any_of(envelopes.begin(), envelopes.end(), [](const auto &envelope) { return envelope.isActive(); });

    if (!allowTailOff || !envelopeActive)
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

    for (auto i = 0; i < envelopes.size(); ++i)
    {
        envelopes[i].setParameters(Params::getEnvelopeValues(i));
    }

    buffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    buffer.clear();

    dsp::AudioBlock<float> audioblock{buffer};

    for (auto i = 0; i < chains.size(); ++i)
    {
        chains[i].process(dsp::ProcessContextReplacing<float>{audioblock});
        envelopes[i].applyEnvelopeToBuffer(buffer, 0, buffer.getNumSamples());
    }

    const auto envelopeActive =
        std::any_of(envelopes.begin(), envelopes.end(), [](const auto &envelope) { return envelope.isActive(); });

    for (auto channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, buffer, channel, 0, numSamples);

        if (!envelopeActive)
            clearCurrentNote();
    }
}

void SynthVoice::setFormula(String formula)
{
    // @todo
    // osc1.get<OscillatorIndex>().setFormula(formula);
}