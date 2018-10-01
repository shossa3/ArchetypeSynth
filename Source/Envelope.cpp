/*
  ==============================================================================

    Envelope.cpp
    Created: 21 Sep 2018 11:21:05am
    Author:  Shaikat Hossain

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Envelope.h"

//==============================================================================
Envelope::Envelope(Archetype_synthAudioProcessor& p) : processor(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    
    setSize(200,200);
    
     attackSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     attackSlider.setRange(0.1f, 5000.0f);
     attackSlider.setValue(0.1f);
     // attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
     addAndMakeVisible(&attackSlider);
     
     decaySlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     decaySlider.setRange(0.1f, 2000.0f);
     decaySlider.setValue(1.0f);
     // attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
     addAndMakeVisible(&decaySlider);
     
     sustainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     sustainSlider.setRange(0.1f, 1.0f);
     sustainSlider.setValue(0.8f);
     // attackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 20.0, 10.0);
     addAndMakeVisible(&sustainSlider);
     
     releaseSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
     releaseSlider.setRange(0.1f,5000.0f);
     releaseSlider.setValue(0.8f);
     addAndMakeVisible(&releaseSlider);
     
     attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"attack",attackSlider);
     decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"decay",decaySlider);
     sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"sustain",sustainSlider);
     releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"release",releaseSlider);
     
     

}

Envelope::~Envelope()
{
}

void Envelope::paint (Graphics& g)
{

    Rectangle<int> titleArea (0,10, getWidth(),20);
    
    g.fillAll(Colours::black);
    g.setColour(Colours::white);
    g.drawText("Envelope", titleArea, Justification::centredTop);
    
    g.drawText("A",53,150,20,20,Justification::centredTop);
    g.drawText("D",77,150,20,20,Justification::centredTop);
    g.drawText("S",103,150,20,20,Justification::centredTop);
    g.drawText("R",128,150,20,20,Justification::centredTop);
    
    Rectangle<float> area(25,25,150,150);
    
    g.setColour(Colours::yellow);
    g.drawRoundedRectangle(area,20.0f,2.0f);
}

void Envelope::resized()
{
    Rectangle<int> area = getLocalBounds().reduced(50);
    
    int sliderWidth = 25;
    int sliderHeight = 175;
    
    attackSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    
    decaySlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    
    sustainSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    
    releaseSlider.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(sliderHeight).withTrimmedTop(10));
    
    
}



