//
//  SynthVoice.h
//  Archetype_Synth
//
//  Created by Shaikat Hossain on 9/19/18.
//
//

#ifndef SynthVoice_h
#define SynthVoice_h

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"

class SynthVoice : public SynthesiserVoice
{
public:
    bool canPlaySound (SynthesiserSound* sound)
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    //===================================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition )
    {
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
    }
    //========================================================
    
    void stopNote (float velocity, bool allowTailOff)
    {
        clearCurrentNote();
    }
    
    //=========================================================
    
    void pitchWheelMoved(int newPitchWheelValue)
    {
    }
    
    //======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue )
    {
    }
    
    //=====================================================
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
    {
    }
    
    //====================================================
private:
    double level;
    double frequency;
};

#endif /* SynthVoice_h */
