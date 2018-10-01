/*
  ==============================================================================

    Filter.h
    Created: 22 Sep 2018 1:15:06am
    Author:  Shaikat Hossain

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter    : public Component
{
public:
    Filter(Archetype_synthAudioProcessor&);
    ~Filter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
    Slider filterCutoff;
    Slider filterRes;
    ComboBox filterMenu;
    

    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> filterVal;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> resVal;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeVal;

    
    Archetype_synthAudioProcessor& processor; 
};
