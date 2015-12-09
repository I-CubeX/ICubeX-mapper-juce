/*
 ==============================================================================
 
 ICubeMIDIComponent.h
 Created: 8 Dec 2015 1:52:03pm
 Author:  johnty
 
 ==============================================================================
 */

#ifndef ICUBEMIDICOMPONENT_H_INCLUDED
#define ICUBEMIDICOMPONENT_H_INCLUDED

#include "JuceHeader.h"
#include "ICubeXInterface/ICubeXInteface.h"

class ICubeMIDIComponent : public MidiInputCallback,
                           public ICubeXInterface,
                           public ChangeBroadcaster
{
public:
   void handleIncomingMidiMessage (MidiInput* source,
                                   const MidiMessage& message);
   void setAllSensors(bool stream_on);
   
   void setOutputPort(MidiOutput* port) {outputPort = port;}
   
protected:
   void sendSysExCmd() override;
   
private:
   MidiOutput* outputPort;   
};



#endif  // ICUBEMIDICOMPONENT_H_INCLUDED
