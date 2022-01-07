#pragma once

#include <JuceHeader.h>
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
    static auto getRawParameterValue(StringRef parameterID) -> std::atomic<float> *;

private:
    static std::unique_ptr<AudioProcessorValueTreeState> state;
};
