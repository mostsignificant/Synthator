#include "Params.hpp"
#include "SynthProcessor.hpp"

std::unique_ptr<AudioProcessorValueTreeState> Params::state;

namespace
{

const std::array OscillatorAttackParamIDs = {
    "osc1.attack",
    "osc2.attack",
    "osc3.attack",
    "osc4.attack",
};

const std::array OscillatorDecayParamIDs = {
    "osc1.decay",
    "osc2.decay",
    "osc3.decay",
    "osc4.decay",
};

const std::array OscillatorSustainParamIDs = {
    "osc1.sustain",
    "osc2.sustain",
    "osc3.sustain",
    "osc4.sustain",
};

const std::array OscillatorReleaseParamIDs = {
    "osc1.release",
    "osc2.release",
    "osc3.release",
    "osc4.release",
};

const std::array OscillatorMixParamIDs = {
    "osc1.mix",
    "osc2.mix",
    "osc3.mix",
    "osc4.mix",
};

} // namespace

void Params::init(SynthProcessor &processor)
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorAttackParamIDs[0], "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorAttackParamIDs[1], "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorAttackParamIDs[2], "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorAttackParamIDs[3], "attack", 0.0f, 10.0f, 0.1f));

    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorDecayParamIDs[0], "decay", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorDecayParamIDs[1], "decay", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorDecayParamIDs[2], "decay", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorDecayParamIDs[3], "decay", 0.0f, 10.0f, 0.1f));

    params.push_back(std::make_unique<AudioParameterInt>(OscillatorSustainParamIDs[0], "sustain", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorSustainParamIDs[1], "sustain", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorSustainParamIDs[2], "sustain", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorSustainParamIDs[3], "sustain", 0, 100, 100));

    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorReleaseParamIDs[0], "release", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorReleaseParamIDs[1], "release", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorReleaseParamIDs[2], "release", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>(OscillatorReleaseParamIDs[3], "release", 0.0f, 10.0f, 0.1f));

    params.push_back(std::make_unique<AudioParameterInt>(OscillatorMixParamIDs[0], "mix", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorMixParamIDs[1], "mix", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorMixParamIDs[2], "mix", 0, 100, 100));
    params.push_back(std::make_unique<AudioParameterInt>(OscillatorMixParamIDs[3], "mix", 0, 100, 100));

    state = std::make_unique<AudioProcessorValueTreeState>(
        processor, nullptr, "Params", AudioProcessorValueTreeState::ParameterLayout(params.begin(), params.end()));
}

void Params::deinit()
{
    state.reset(nullptr);
}

auto Params::getState() -> AudioProcessorValueTreeState &
{
    return *state;
}

auto Params::getEnvelopeValues(const size_t i) -> ADSR::Parameters
{
    return {*state->getRawParameterValue(OscillatorAttackParamIDs[i]),
            *state->getRawParameterValue(OscillatorDecayParamIDs[i]),
            *state->getRawParameterValue(OscillatorSustainParamIDs[i]) / 100.0F,
            *state->getRawParameterValue(OscillatorReleaseParamIDs[i])};
}

auto Params::getMixValue(std::size_t i) -> float
{
    return *state->getRawParameterValue(OscillatorMixParamIDs[i]) / 100.0F;
}