/*
  ==============================================================================

    Envelope.h
    Created: 21 Sep 2018 11:21:05am
    Author:  Shaikat Hossain

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class Envelope    : public Component
{
public:
    Envelope(Archetype_synthAudioProcessor&);
    ~Envelope();

    void paint (Graphics&) override;
    void resized() override;


private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Envelope)
    Archetype_synthAudioProcessor& processor;
    
     Slider attackSlider;
     Slider decaySlider;
     Slider sustainSlider;
     Slider releaseSlider;
     ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> attackVal;
     ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> decayVal;
     ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> sustainVal;
     ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> releaseVal;
     
     
};
