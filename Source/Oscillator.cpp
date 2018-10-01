/*
  ==============================================================================

    Oscillator.cpp
    Created: 20 Sep 2018 4:46:19pm
    Author:  Shaikat Hossain

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Oscillator.h"

//==============================================================================
Oscillator::Oscillator(Archetype_synthAudioProcessor& p) : processor(p)
{

    setSize(200,200);
    
    oscMenu.addItem("Sine",1);
    oscMenu.addItem("Saw",2);
    oscMenu.addItem("Square",3);
    addAndMakeVisible(&oscMenu);
    oscMenu.addListener(this);
    
    oscMenu.setJustificationType(Justification::centred);
    
    waveSelection = new AudioProcessorValueTreeState::ComboBoxAttachment(processor.tree,"wavetype",oscMenu);
    
}

Oscillator::~Oscillator()
{
}

void Oscillator::paint (Graphics& g)
{
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Oscillator One", titleArea, Justification::centredTop);
    
    Rectangle<float> area(25,25,150,150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);
    
}

void Oscillator::comboBoxChanged(ComboBox* box)
{
}

void Oscillator::resized()
{
  Rectangle<int> area = getLocalBounds().reduced(40);
    oscMenu.setBounds(area.removeFromTop(20));

}
