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
	, mixAttachment(p.state, "mix", mixSlider)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 100);
	setLookAndFeel(&look);

	downsampleLabel.setText("Downsample", dontSendNotification);
	downsampleLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(downsampleLabel);

	bitReductionLabel.setText("Bit Reduction", dontSendNotification);
	bitReductionLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(bitReductionLabel);

	mixLabel.setText("Mix", dontSendNotification);
	mixLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mixLabel);

	look.setColour(Label::ColourIds::textColourId, Colour(0xFF000000));
	look.setColour(Slider::ColourIds::thumbColourId, Colour(0xFF2C2C2C));
	look.setColour(Slider::ColourIds::rotarySliderFillColourId, Colour(0xFF6DD7FE));
	look.setColour(Slider::ColourIds::rotarySliderOutlineColourId, Colour(0xFF2C2C2C));
	look.setColour(Slider::ColourIds::textBoxTextColourId, Colour(0xFF000000));
	look.setColour(Slider::ColourIds::textBoxOutlineColourId, Colour(0x00FFFFFF));

	downsampleSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 15);
	downsampleSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(downsampleSlider);

	bitReductionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 15);
	bitReductionSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(bitReductionSlider);

	mixSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 80, 15);
	mixSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	addAndMakeVisible(mixSlider);
}

ReduxAudioProcessorEditor::~ReduxAudioProcessorEditor()
{
}

//==============================================================================
void ReduxAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colour(0xFF878787));
}

void ReduxAudioProcessorEditor::resized()
{
	auto bounds = getLocalBounds();
	bounds.reduce(0, 8);
	int width = getWidth() / 3;

	auto textBounds = bounds.removeFromTop(15);
	downsampleLabel.setBounds(textBounds.removeFromLeft(width));
	bitReductionLabel.setBounds(textBounds.removeFromLeft(width));
	mixLabel.setBounds(textBounds);

	downsampleSlider.setBounds(bounds.removeFromLeft(width));
	bitReductionSlider.setBounds(bounds.removeFromLeft(width));
	mixSlider.setBounds(bounds);
}
