/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BlenderToJUCEAudioProcessorEditor::BlenderToJUCEAudioProcessorEditor (BlenderToJUCEAudioProcessor& p, juce::AudioProcessorValueTreeState& apvts)
    : AudioProcessorEditor (&p), processor_ (p), parameters_(apvts)
{
    setSize (1920 / 2, 1080 / 2);
    
    drive_slider.setName ("Drive");
//    drive_slider.setLookAndFeel (&custom_look_and_feel_);
    drive_slider.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    drive_slider.setTextBoxStyle (juce::Slider::NoTextBox, false, 60, 20);
    
    drive_parameter_attachment_.reset (new juce::AudioProcessorValueTreeState::SliderAttachment (parameters_, "drive", drive_slider));
    
    addAndMakeVisible (drive_slider);
}

BlenderToJUCEAudioProcessorEditor::~BlenderToJUCEAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void BlenderToJUCEAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void BlenderToJUCEAudioProcessorEditor::resized()
{
    juce::Rectangle<int> slider_bounds = {50, 50, 100, 100};
    drive_slider.setBounds(slider_bounds);
}

void BlenderToJUCEAudioProcessorEditor::SetBoundsFromBlender (juce::Slider &slider,
                                                              double min_x,
                                                              double min_y,
                                                              double max_x,
                                                              double max_y)
{
    auto x_fraction = min_x;
    auto y_fraction = 1.0 - max_y;
    auto width_fraction = max_x - min_x;
    auto height_fraction = max_y - min_y;
    
    auto editor_width = double(getWidth());
    auto editor_height = double(getHeight());
    
    juce::Rectangle<double> bounds {x_fraction * editor_width,
                                    y_fraction * editor_height,
                                    width_fraction * editor_width,
                                    height_fraction * editor_height};

    slider.setBounds(bounds.toNearestInt());
}
