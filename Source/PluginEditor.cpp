/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Archetype_synthAudioProcessorEditor::Archetype_synthAudioProcessorEditor (Archetype_synthAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), oscGUI(p), envGUI(p), filterGui(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 200);
    
    addAndMakeVisible(&oscGUI);
    addAndMakeVisible(&envGUI);
    addAndMakeVisible(&filterGui);

}

Archetype_synthAudioProcessorEditor::~Archetype_synthAudioProcessorEditor()
{
}


//==============================================================================
void Archetype_synthAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    Rectangle<int> a{0,0,10,10};
    Rectangle<int> b{30,30,40,40};
    
    a = a.withTrimmedTop(5);
    b.withY(6);
    
    g.setColour(Colours::red);
    g.fillRect(a);
    g.setColour(Colours::green);
    g.fillRect(b);
    
}

void Archetype_synthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    Rectangle<int> area = getLocalBounds();
    
    const int componentWidth = 200;
    const int componentHeight = 200;
    
    oscGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    filterGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    envGUI.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
    

}
