/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

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
	
	Slider downsampleSlider;
	Slider bitReductionSlider;
	AudioProcessorValueTreeState::SliderAttachment downsampleAttachment;
	AudioProcessorValueTreeState::SliderAttachment bitReductionAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReduxAudioProcessorEditor)
};
