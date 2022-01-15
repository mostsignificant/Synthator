#include "SynthProcessor.hpp"
#include "Editor.hpp"
#include "Params.hpp"
#include "SynthSound.hpp"
#include "SynthVoice.hpp"

SynthProcessor::SynthProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
                         .withInput("Input", AudioChannelSet::stereo(), true)
#endif
                         .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
      )
#endif
{
    synth.addSound(new SynthSound());

    for (int i = 0; i < 8; i++)
    {
        synth.addVoice(new SynthVoice());
    }
}

const String SynthProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool SynthProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool SynthProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double SynthProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthProcessor::getNumPrograms()
{
    return 1; // NB: some hosts don't cope very well if you tell them there are 0 programs,
              // so this should be at least 1, even if you're not really implementing programs.
}

int SynthProcessor::getCurrentProgram()
{
    return 0;
}

void SynthProcessor::setCurrentProgram(int index)
{
}

const String SynthProcessor::getProgramName(int index)
{
    return {};
}

void SynthProcessor::changeProgramName(int index, const String &newName)
{
}

void SynthProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    Params::init(*this);

    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice *>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void SynthProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthProcessor::isBusesLayoutSupported(const BusesLayout &layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

void SynthProcessor::processBlock(AudioBuffer<float> &buffer, MidiBuffer &midiMessages)
{
    ScopedNoDenormals noDenormals;

    for (auto channel = getTotalNumInputChannels(); channel < getTotalNumOutputChannels(); ++channel)
        buffer.clear(channel, 0, buffer.getNumSamples());

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    if (auto editor = dynamic_cast<Editor *>(getActiveEditor()))
        editor->pushBuffer(buffer);
}

bool SynthProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor *SynthProcessor::createEditor()
{
    auto *editor = new Editor(*this);
    if (wrapperType == wrapperType_Standalone)
    {
        if (TopLevelWindow::getNumTopLevelWindows() == 1)
        {
            auto *window = TopLevelWindow::getTopLevelWindow(0);
            // window->setUsingNativeTitleBar(true);
        }
    }
    return editor;
}

void SynthProcessor::getStateInformation(MemoryBlock &destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthProcessor::setStateInformation(const void *data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SynthProcessor::onFormulaChanged(String formula)
{
    for (auto i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto *voice = dynamic_cast<SynthVoice *>(synth.getVoice(i)))
        {
            voice->setFormula(formula);
        }
    }
}

void SynthProcessor::onFormulaException(String)
{
}

AudioProcessor *JUCE_CALLTYPE createPluginFilter()
{
    return new SynthProcessor();
}
