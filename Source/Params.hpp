#pragma once

#include <JuceHeader.h>
#include <cstddef>
#include <memory>

class SynthProcessor;

class Params
{
public:
    Params(Params &&) = delete;
    Params(const Params &) = delete;
    auto operator=(Params &&) -> Params & = delete;
    auto operator=(const Params &) -> Params & = delete;

    static void init(SynthProcessor &processor);
    static void deinit();

    static auto getState() -> AudioProcessorValueTreeState &;

    static auto getEnvelopeValues(std::size_t i) -> ADSR::Parameters;
    static auto getMixValue(std::size_t i) -> float;

private:
    static std::unique_ptr<AudioProcessorValueTreeState> state;
};
