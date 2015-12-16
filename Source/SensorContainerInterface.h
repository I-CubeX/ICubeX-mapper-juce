/*
  ==============================================================================

    SensorContainerInterface.h
    Created: 16 Dec 2015 12:40:44pm
    Author:  johnty
 
    Interface class for objects that need to interact with the SensorContainer
     class. Uses the ChangeBroadcaster/Listener mechanism for synchronization
     but also allows polled access to the data

  ==============================================================================
*/

#ifndef SENSORCONTAINERINTERFACE_H_INCLUDED
#define SENSORCONTAINERINTERFACE_H_INCLUDED

#include "SensorContainer.h"

class SensorContainerInterface
{
public:
    //virtual void triggerChanged() = 0;
    
    //!links to data holding structure
    void setContainer(SensorContainer* cont) {container = cont;}
    
    //!adds change listener
    //void addSubscriber(ChangeListener* sub) { this->addChangeListener(sub); }
    
    //!returns the data container for polled access
    SensorContainer* getSensorContainer() {return container;}
    
private:
    SensorContainer* container;
    
};



#endif  // SENSORCONTAINERINTERFACE_H_INCLUDED
