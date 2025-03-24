#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider (juce::Graphics & g,
                           int x,
                           int y,
                           int width,
                           int height,
                           float sliderPos,
                           float rotaryStartAngle,
                           float rotaryEndAngle,
                           juce::Slider & slider) override;
private:
};
