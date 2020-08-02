#include "ReduxLookAndFeel.h"

void ReduxLookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
	const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
	auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
	auto fill = slider.findColour(Slider::rotarySliderFillColourId);

	auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

	auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
	auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
	auto lineW = jmin(3.0f, radius * 0.5f);
	auto arcRadius = radius - lineW * 0.5f;

	Path backgroundArc;
	backgroundArc.addCentredArc(bounds.getCentreX(),
		bounds.getCentreY(),
		arcRadius,
		arcRadius,
		0.0f,
		rotaryStartAngle,
		rotaryEndAngle,
		true);

	g.setColour(outline);
	g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));

	if (slider.isEnabled())
	{
		Path valueArc;
		valueArc.addCentredArc(bounds.getCentreX(),
			bounds.getCentreY(),
			arcRadius,
			arcRadius,
			0.0f,
			rotaryStartAngle,
			toAngle,
			true);

		g.setColour(fill);
		g.strokePath(valueArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::butt));
	}

	Point<float> start(bounds.getCentreX(), bounds.getCentreY());
	Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
		bounds.getCentreY() + arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));
	Path indicator = Path();
	indicator.addLineSegment({ start, thumbPoint }, 1);

	g.setColour(slider.findColour(Slider::thumbColourId));
	g.strokePath(indicator, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));

}