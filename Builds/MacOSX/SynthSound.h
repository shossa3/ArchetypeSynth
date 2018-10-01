/*
 ==============================================================================
 
 SynthSound.h
 Created: 19 Sep 2018 12:10:27pm
 Author:  Shaikat Hossain
 
 ==============================================================================
 */

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SynthSound : public SynthesiserSound
{
public:
    bool    appliesToNote(int /*midiNoteNumber*/)
    {
        return true;
    }
    
    bool    appliesToChannel(int /*midiChannel*/)
    {
        return true;
    }
    
};
