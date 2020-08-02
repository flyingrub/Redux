/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ReduxLookAndFeel.h"

using namespace juce;

//==============================================================================
/**
*/
class ReduxAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ReduxAudioProcessorEditor (ReduxAudioProcessor&);
    ~ReduxAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ReduxAudioProcessor& processor;
	ReduxLookAndFeel look;

	Label downsampleLabel, bitReductionLabel, mixLabel;
	Slider downsampleSlider;
	Slider bitReductionSlider;
	Slider mixSlider;
	AudioProcessorValueTreeState::SliderAttachment downsampleAttachment;
	AudioProcessorValueTreeState::SliderAttachment bitReductionAttachment;
	AudioProcessorValueTreeState::SliderAttachment mixAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReduxAudioProcessorEditor)
};
