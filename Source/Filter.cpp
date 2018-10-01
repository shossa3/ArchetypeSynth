/*
  ==============================================================================

    Filter.cpp
    Created: 22 Sep 2018 1:15:06am
    Author:  Shaikat Hossain

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Filter.h"

//==============================================================================
Filter::Filter(Archetype_synthAudioProcessor& p): processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    setSize(200, 200);
    
    
    
    filterMenu.setJustificationType(Justification::centred);
    filterMenu.addItem("Low Pass", 1);
    filterMenu.addItem("Band Pass", 2);
    filterMenu.addItem("High Pass", 3);
    addAndMakeVisible(&filterMenu);
    
    filterCutoff.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterCutoff.setRange(20.0f, 20000.0f);
    filterCutoff.setValue(600.0f);
    filterCutoff.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterCutoff.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterCutoff);
    
    filterRes.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    filterRes.setRange(1.0f, 5.0f);
    filterRes.setValue(2.0f);
    filterRes.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
    filterRes.setPopupDisplayEnabled(true, true, this);
    addAndMakeVisible(&filterRes);
    
    filterVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "cutoff", filterCutoff);
    
    resVal = new AudioProcessorValueTreeState::SliderAttachment (processor.tree, "resonance", filterRes);
    
    filterTypeVal = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree, "filterMenu", filterMenu);
    
 //   filterCutoff.setSkewFactorFromMidPoint(1000.0f);
    
}

Filter::~Filter()
{
}

void Filter::paint (Graphics& g)
{
    
    Rectangle<int> titleArea (0,10,getWidth(),20);
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("filter",titleArea,Justification::centredTop);
    
    Rectangle<float> area(25,25,150,150);
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void Filter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Rectangle<int> area = getLocalBounds().reduced(40);
    filterMenu.setBounds(area.removeFromTop(20));
    filterCutoff.setBounds(30, 100, 70, 70);
    filterRes.setBounds(100, 100, 70, 70);
}
