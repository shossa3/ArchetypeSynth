/*
  ==============================================================================

    SynthVoice.h
    Created: 19 Sep 2018 12:10:38pm
    Author:  Shaikat Hossain

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

class SynthVoice : public SynthesiserVoice
{
public:
    
    SynthVoice(const juce::dsp::ProcessSpec& spec)
    {
        tempBlock = juce::dsp::AudioBlock<float> (heapBlock, spec.numChannels, spec.maximumBlockSize);
        processorChain.prepare (spec);
        lfo.initialise ([] (float x) { return std::sin(x); }, 128);
        lfo.prepare ({ spec.sampleRate / lfoUpdateRate, spec.maximumBlockSize, spec.numChannels });
    
    };
    ~SynthVoice(){};
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SynthSound*>(sound) != nullptr;
    }
    
    void getEnvelopeParams (float* attack, float* decay, float* sustain, float* release)
    {
        env1.setAttack(double(*attack));
        env1.setDecay(double(*decay));
        env1.setSustain(double(*sustain));
        env1.setRelease(double(*release));
    
    }
    
    double setEnvelope()
    {
        return env1.adsr(setOscType(), env1.trigger);
    }
    
    
    void setEnvelopeBlock()
    {
        
        for (int sample = 0; sample < numSamples; sample++)
        {
            
            for (int channel=0; channel < outputBuffer.getNumChannels(); ++channel)
            {
            //    outputBuffer.addSample(channel, outputBuffer.startSample, env1.adsr(outputBuffer.getSample(channel, sample), env1.trigger));
                
            }
            
        }
        
    }

    
    void getOscType(float* selection)
    {
        theWave = *selection;
        setOscType();
    }
    
    
    
    double setOscType ()
    {
        if (theWave == 0)
        {
            auto& osc = processorChain.get<oscIndex>();
            
            osc.initialise ([] (float x)
                            {
                                return std::sin(x);
                            }, 128);
            
            return osc1.sinewave(frequency);
        }
        if (theWave == 1)
        {
            auto& osc = processorChain.get<oscIndex>();
            
            osc.initialise ([] (float x)
                            {
                                return jmap (x, float (-MathConstants<double>::pi), float (MathConstants<double>::pi), float (-1), float (1));
                            }, 2);
            
            return osc1.saw(frequency);
        }
        if (theWave == 2)
        {
            auto& osc = processorChain.get<oscIndex>();
            
            osc.initialise ([] (float x)
                            {
                                return jmap (x, float (-MathConstants<double>::pi), float (MathConstants<double>::pi), float (1), float (1));
                            }, 2);

            return osc1.square(frequency);
        }
        else
        {
            auto& osc = processorChain.get<oscIndex>();
            
            osc.initialise ([] (float x)
                            {
                                return std::sin(x);
                            }, 128);
            
            return osc1.sinewave(frequency);
        }
    }
    
    void setFrequency (float newValue, bool force = false)
    {
        auto& osc = processorChain.template get<oscIndex>();
        osc.setFrequency (newValue, force);
        
    }
 
    //==============================================================================
    void reset() noexcept
    {
        processorChain.reset();
    }
    
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        processorChain.process (context);
    }
    
    //==============================================================================
    void prepare (const juce::dsp::ProcessSpec& spec)
    {

    }
    
    
    void setLevel (float newValue)
    {
        auto& gain = processorChain.template get<gainIndex>();
        gain.setGainLinear (newValue);
    }
    
    void getFilterParams (float* filterType, float* filterCutoff, float* filterRes)
    {

        filterChoice = *filterType;
        cutoff = *filterCutoff;
        resonance = *filterRes;
        
        
    }
    
    double setFilter()
    {
        if (menuChoice==0)
        {

        
            return filter1.lores(setEnvelope(),  cutoff, resonance);
        
        }
        
        if (menuChoice==1)
        {

            
            return filter1.hires(setEnvelope(), cutoff, resonance);
            
        }
        
        
        if (menuChoice==2)
        {

            
            return filter1.bandpass(setEnvelope(),  cutoff, resonance);
            
        }
        else {

            return filter1.lores(setEnvelope(),  cutoff, resonance);
        }
    }
    
    
    //===================================================
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition ) override
    {
        env1.trigger = 1;
        level = velocity;
        frequency = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
        std::cout << midiNoteNumber << std::endl;
        
        /*
        dsp::ProcessSpec spec;
        spec.numChannels=2;
        spec.maximumBlockSize=512;
        spec.sampleRate=48000;
        processorChain.prepare (spec);
        */
         processorChain.get<oscIndex>().setFrequency (frequency, true);
        setLevel (velocity);
    }
//========================================================
    
    void stopNote (float velocity, bool allowTailOff) override
    {
        DBG( "*****stop note****");
        env1.trigger=0;
        allowTailOff = false;
//        if (velocity==0)
//        {
//            clearCurrentNote();
//            processorChain.reset();
//        }
        processorChain.reset();

    }
    
//=========================================================
    
    void pitchWheelMoved(int newPitchWheelValue) override
    {
    }
    
//======================================================
    
    void controllerMoved (int controllerNumber, int newControllerValue ) override
    {
    }
    
  
        
//=====================================================
    
    void renderNextBlock (AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override
    {
        auto sampleRate = getSampleRate();
        
        
        auto output = tempBlock.getSubBlock (0, (size_t) numSamples);
        output.clear();
        for (size_t pos = 0; pos < numSamples;)
        {
            auto max = jmin (static_cast<size_t> (numSamples - pos), lfoUpdateCounter);
            auto block = output.getSubBlock (pos, max);
            juce::dsp::ProcessContextReplacing<float> context (block);
            processorChain.process (context);
            
            pos += max;
           
            lfoUpdateCounter -= max;
            if (lfoUpdateCounter == 0)
            {
                lfoUpdateCounter = lfoUpdateRate;
                auto lfoOut = lfo.processSample (0.0f);                                // [5]
            }
        }
        juce::dsp::AudioBlock<float> (outputBuffer)
        .getSubBlock ((size_t) startSample, (size_t) numSamples)
        .add (tempBlock);
       
    }
    
        juce::dsp::AudioBlock<float> outputBuffer;

        int   numSamples = 512;
        
//====================================================
private:
    double level;
    double frequency;
    float lastSampleRate;
    maxiOsc osc1;
    maxiEnv env1;
    maxiFilter filter1;
    int theWave;
    static constexpr size_t lfoUpdateRate = 100;
    size_t lfoUpdateCounter = lfoUpdateRate;
    juce::dsp::Oscillator<float> lfo;
        
        
        
    int filterChoice;
    float cutoff;
    float resonance;
        
    int menuChoice;
    int cutoff2;
    int res;

        enum
        {
            oscIndex,
            gainIndex
        };
        
        
        dsp::ProcessorChain<juce::dsp::Oscillator<float>, juce::dsp::Gain<float>> processorChain;
        juce::HeapBlock<char> heapBlock;
        juce::dsp::AudioBlock<float> tempBlock;

};

      
