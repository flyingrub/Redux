#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class ReduxLookAndFeel : public LookAndFeel_V4
{
public:
	ReduxLookAndFeel();
	void drawRotarySlider(Graphics & g, int x, int y, int width, int height, float sliderPos, const float rotaryStartAngle, const float rotaryEndAngle, Slider & slider);
	~ReduxLookAndFeel();
};

