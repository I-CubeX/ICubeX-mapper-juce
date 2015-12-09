/*
 ==============================================================================
 
 ICubeMIDIComponent.cpp
 Created: 8 Dec 2015 1:52:03pm
 Author:  johnty
 
 ==============================================================================
 */

#include "ICubeMIDIComponent.h"

void ICubeMIDIComponent::setAllSensors(bool stream_on)
{
    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        SendStream(stream_on, i);
    }
    
}

void ICubeMIDIComponent::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message)
{
    if (message.isSysEx())
    {    //note: our parser expects a "full" sysex
        // message, so we need to put back 0xF0 header and 0xF7 footer bytes!
        std::vector<unsigned char> data;
        data.reserve(message.getSysExDataSize()+2);
        data.insert(data.begin(), 0xF0);
        for (int i=0; i<message.getSysExDataSize(); i++)
        {
            data.insert(data.end(), message.getSysExData()[i]);
            //DBG(String((unsigned int)(message.getSysExData()[i]))+ " ");
        }
        data.insert(data.end(), 0xF7);
        ParseSysEx(data);
        sendChangeMessage();
        
    }
}

void ICubeMIDIComponent::sendSysExCmd()
{
    std::vector<unsigned char> sendBuff = getSysExBuffer();
    unsigned char* ptrData = new unsigned char[sendBuff.size()];
    for (int i=0; i<sendBuff.size(); i++) {
        ptrData[i] = sendBuff.at(i);
    }
    //   DBG("size of data =" + String((int)sendBuff.size()));
    MidiMessage msg(ptrData, sendBuff.size()); //living dangerously
    if (outputPort != nullptr)
        outputPort->sendMessageNow(msg);
    else
        DBG("warning: no MIDI out attached to ICubeX Interface!");
}