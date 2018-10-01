/*
  ==============================================================================

    Oscillator.h
    Created: 20 Sep 2018 4:46:19pm
    Author:  Shaikat Hossain

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Oscillator    : public Component,
private ComboBox::Listener
{
public:
    Oscillator(Archetype_synthAudioProcessor&);
    ~Oscillator();

    void paint (Graphics&) override;
    void resized() override;
    void comboBoxChanged(ComboBox*) override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
    ComboBox oscMenu;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;
  
    Archetype_synthAudioProcessor& processor;
};
