/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReduxAudioProcessor::ReduxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
    , state(*this, nullptr)
    , nextSampleToTake({0,0})
    , previousSample({0,0})
#endif
{
    addParameter(downsample = new AudioParameterFloat("downSample", "DownSample", NormalisableRange<float>(0.0f, 200.0f), 5.0f));
    addParameter(bitReduction = new AudioParameterInt("bitReduction", "BitReduction", 1, 32, 8));
    addParameter(mix = new AudioParameterFloat("mix", "Mix", NormalisableRange<float>(0.0f, 1.0f), 1.f));
}

ReduxAudioProcessor::~ReduxAudioProcessor()
{
}

//==============================================================================
const String ReduxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ReduxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ReduxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ReduxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ReduxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ReduxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ReduxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ReduxAudioProcessor::setCurrentProgram (int index)
{
}

const String ReduxAudioProcessor::getProgramName (int index)
{
    return {};
}

void ReduxAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ReduxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < 2; i++)
    {
        nextSampleToTake[i] = 0;
        previousSample[i] = 0;
    }
}

void ReduxAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ReduxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ReduxAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    auto numSamples = buffer.getNumSamples();


    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        int bitReduction = downsample->get();
        float mixValue = mix->get();

        for (auto i = 0; i < numSamples; ++i)
        {
            auto in = channelData[i];
            float out = in;
            if (nextSampleToTake[channel] < 1)
            {
                previousSample[channel] = in;
                nextSampleToTake[channel] = downsample->get();
            }
            out = previousSample[channel];

            // REDUCE BIT DEPTH ::::: source : https://github.com/theaudioprogrammer/bitcrusherDemo/blob/master/Source/PluginProcessor.cpp#L309
            float totalQLevels = powf(2, bitReduction);
            float val = out;
            float remainder = fmodf(val, 1 / totalQLevels);

            // Quantize ...
            out = val - remainder;

            channelData[i] = in * (1 - mixValue) + out * mixValue;
            nextSampleToTake[channel]--;
        }
    }
}

//==============================================================================
bool ReduxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ReduxAudioProcessor::createEditor()
{
    return new ReduxAudioProcessorEditor (*this);
}

//==============================================================================
void ReduxAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // Store an xml representation of our state.
    std::unique_ptr<XmlElement> xmlState(state.copyState().createXml());

    if (xmlState.get() != nullptr)
        copyXmlToBinary(*xmlState, destData);
}

void ReduxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // Restore our plug-in's state from the xml representation stored in the above
         // method.
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        state.replaceState(ValueTree::fromXml(*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ReduxAudioProcessor();
}
