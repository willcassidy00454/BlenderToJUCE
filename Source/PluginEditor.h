/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookAndFeel.h"

//==============================================================================
/**
*/
class BlenderToJUCEAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BlenderToJUCEAudioProcessorEditor (BlenderToJUCEAudioProcessor&, juce::AudioProcessorValueTreeState& apvts);
    ~BlenderToJUCEAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void SetBoundsFromBlender (juce::Slider &slider, double min_x, double min_y, double max_x, double max_y);
    
    BlenderToJUCEAudioProcessor& processor_;
    juce::AudioProcessorValueTreeState& parameters_;
    
    CustomLookAndFeel custom_look_and_feel_;
    
    juce::Slider drive_slider;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drive_parameter_attachment_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlenderToJUCEAudioProcessorEditor)
};
