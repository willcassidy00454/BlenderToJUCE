/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BlenderToJUCEAudioProcessor::BlenderToJUCEAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), parameters(*this, nullptr, juce::Identifier ("BlenderToJUCE"),
                                 {
                           std::make_unique<juce::AudioParameterFloat> (juce::ParameterID {"drive", 1},      // parameter ID
                                                                        "Drive",      // parameter name
                                                                        1.0f,      // minimum value
                                                                        10.0f,       // maximum value
                                                                        1.0f),       // default value
                       })
#endif
{
    drive_parameter_value_ = parameters.getRawParameterValue("drive");
}

BlenderToJUCEAudioProcessor::~BlenderToJUCEAudioProcessor()
{
}

//==============================================================================
const juce::String BlenderToJUCEAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BlenderToJUCEAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BlenderToJUCEAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool BlenderToJUCEAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double BlenderToJUCEAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BlenderToJUCEAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BlenderToJUCEAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BlenderToJUCEAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String BlenderToJUCEAudioProcessor::getProgramName (int index)
{
    return {};
}

void BlenderToJUCEAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void BlenderToJUCEAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void BlenderToJUCEAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BlenderToJUCEAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void BlenderToJUCEAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channel_index = 0; channel_index < totalNumInputChannels; ++channel_index)
    {
        for (int sample_index = 0; sample_index < buffer.getNumSamples(); ++sample_index)
        {
            auto input_sample = buffer.getSample(channel_index, sample_index);
            auto saturated_sample = tanh(*drive_parameter_value_ * input_sample);
            
            buffer.setSample(channel_index, sample_index, saturated_sample);
        }
    }
}

//==============================================================================
bool BlenderToJUCEAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* BlenderToJUCEAudioProcessor::createEditor()
{
    return new BlenderToJUCEAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BlenderToJUCEAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void BlenderToJUCEAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BlenderToJUCEAudioProcessor();
}
