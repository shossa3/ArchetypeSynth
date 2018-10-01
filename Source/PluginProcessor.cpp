/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Archetype_synthAudioProcessor::Archetype_synthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
attackTime(0.1f),
tree(*this,nullptr)
#endif
{

    dsp::ProcessSpec spec{};
    spec.numChannels=2;
    spec.maximumBlockSize=512;
    spec.sampleRate=48000;
    
    
    NormalisableRange<float> attackParam(0.1f, 5000.0f);
    NormalisableRange<float> decayParam(0.1f, 2000.0f);
    NormalisableRange<float> sustainParam(0.0f, 1.0f);
    NormalisableRange<float> releaseParam(0.1f, 5000.0f);
    
    tree.createAndAddParameter("attack", "Attack", "attack", attackParam, 0.1f, nullptr, nullptr);
    tree.createAndAddParameter("decay", "Decay", "decay", decayParam, 1.0f, nullptr, nullptr);
    tree.createAndAddParameter("sustain", "Sustain", "sustain", sustainParam, 0.8f, nullptr, nullptr);
    tree.createAndAddParameter("release", "Release", "release", releaseParam, 0.1f, nullptr, nullptr);
    
    
    NormalisableRange<float> wavetypeParam(0,2); 
    tree.createAndAddParameter("wavetype", "WaveType", "wavetype", wavetypeParam, 0, nullptr, nullptr);
    
    NormalisableRange<float> filterVal(20.0f,10000.0f);
    NormalisableRange<float> resVal(1,5);
    NormalisableRange<float> filterTypeVal(0,2);

    
    tree.createAndAddParameter("filterCutoff", "FilterCutoff", "filterCutoff", filterVal, 400.0f, nullptr, nullptr);
    tree.createAndAddParameter("filterRes", "FilterRes", "filterRes", resVal, 1, nullptr, nullptr);
    tree.createAndAddParameter("filterType", "FilterType", "filterType", filterTypeVal, 0, nullptr, nullptr);

    
    tree.state = ValueTree("My Plugin ValueTree");
    
    
    mySynth.clearVoices();
    for (int i=0;i<5;i++)
    {
        mySynth.addVoice(new SynthVoice(spec));
       // mySynth.addVoice(new SynthVoice());

    }
    
    mySynth.clearSounds();
    mySynth.addSound(new SynthSound);
    
}

Archetype_synthAudioProcessor::~Archetype_synthAudioProcessor()
{
}

//==============================================================================
const String Archetype_synthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Archetype_synthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}


bool Archetype_synthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Archetype_synthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Archetype_synthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Archetype_synthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Archetype_synthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Archetype_synthAudioProcessor::setCurrentProgram (int index)
{
}

const String Archetype_synthAudioProcessor::getProgramName (int index)
{
    return {};
}

void Archetype_synthAudioProcessor::changeProgramName (int index, const String& newName)
{
}

void Archetype_synthAudioProcessor::process (dsp::ProcessContextReplacing<float> context)
{
    //do your dsp processing and output here
    stateVariableFilter.process(context);
}

void Archetype_synthAudioProcessor::updateParameters()
{
    //be sure to update params for your dsp here
    updateFilter();
}


//==============================================================================
void Archetype_synthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
    
    
    dsp::ProcessSpec spec;
    spec.sampleRate = lastSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
}


void Archetype_synthAudioProcessor::updateFilter()
{
    int menuChoice = *tree.getRawParameterValue("filterType");
    float cutoff = *tree.getRawParameterValue("filterCutoff");
    float res = *tree.getRawParameterValue("filterRes");
    

    if (menuChoice == 0)
        
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
    }
    if (menuChoice == 1)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
    }
    if (menuChoice == 2)
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
    }
    else
    {
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency(lastSampleRate, cutoff, res);
        
    }
    
}

void Archetype_synthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Archetype_synthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void Archetype_synthAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{

    juce::MidiBuffer::Iterator iterator(midiMessages);
    MidiMessage m;
    int samplePos;
    
    while( iterator.getNextEvent(m,samplePos))
    {
        DBG( m.getDescription() );
    }
    
    for (int i=0;i<mySynth.getNumVoices();i++)
    {
        if ((myVoice = dynamic_cast<SynthVoice*>(mySynth.getVoice(i))))
        {
            myVoice->getEnvelopeParams(tree.getRawParameterValue("attack"),
                                       tree.getRawParameterValue("decay"),
                                       tree.getRawParameterValue("sustain"),
                                       tree.getRawParameterValue("release"));
            
            myVoice->getOscType(tree.getRawParameterValue("wavetype"));
            
            myVoice->getFilterParams(tree.getRawParameterValue("filterType"),
                                     tree.getRawParameterValue("filterCutoff"),
                                     tree.getRawParameterValue("filterRes"));
        }
    }
    
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
 
}

//==============================================================================
bool Archetype_synthAudioProcessor::hasEditor() const
{
    return true;
}

AudioProcessorEditor* Archetype_synthAudioProcessor::createEditor()
{
    return new Archetype_synthAudioProcessorEditor (*this);
}

//==============================================================================
void Archetype_synthAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Archetype_synthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Archetype_synthAudioProcessor();
}
