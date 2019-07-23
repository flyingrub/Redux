/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ReduxAudioProcessorEditor::ReduxAudioProcessorEditor (ReduxAudioProcessor& p)
    : AudioProcessorEditor (&p)
	, processor (p)
	, downsampleAttachment(p.state, "downSample", downsampleSlider)
	, bitReductionAttachment(p.state, "bitReduction", bitReductionSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 100);

	downsampleSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);
	downsampleSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(downsampleSlider);

	bitReductionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 0, 0);
	bitReductionSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(bitReductionSlider);
}

ReduxAudioProcessorEditor::~ReduxAudioProcessorEditor()
{
}

//==============================================================================
void ReduxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void ReduxAudioProcessorEditor::resized()
{
	auto bounds = getLocalBounds();
	downsampleSlider.setBounds(bounds.removeFromLeft(getWidth() / 2));
	bitReductionSlider.setBounds(bounds);
}
