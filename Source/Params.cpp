#include "Params.hpp"
#include "SynthProcessor.hpp"

std::unique_ptr<AudioProcessorValueTreeState> Params::state;

void Params::init(SynthProcessor &processor)
{
    std::vector<std::unique_ptr<RangedAudioParameter>> params;

    params.push_back(std::make_unique<AudioParameterFloat>("osc1.attack", "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>("osc2.attack", "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>("osc3.attack", "attack", 0.0f, 10.0f, 0.1f));
    params.push_back(std::make_unique<AudioParameterFloat>("osc4.attack", "attack", 0.0f, 10.0f, 0.1f));

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

auto Params::getRawParameterValue(StringRef parameterID) -> std::atomic<float> *
{
    return state->getRawParameterValue(parameterID);
}
