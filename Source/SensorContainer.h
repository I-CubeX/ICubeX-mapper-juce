/*
  ==============================================================================

    SensorContainer.h
    Created: 16 Dec 2015 11:53:07am
    Author:  johnty
 
    container class for holding sensor values

  ==============================================================================
*/

#ifndef SENSORCONTAINER_H_INCLUDED
#define SENSORCONTAINER_H_INCLUDED

#include "JuceHeader.h"

class SensorContainer : public ChangeBroadcaster
{
public:
    SensorContainer(int size = 1);

    //updates an individual value (not, since it will trigger a change, probably better to use the bulk update function
    void update(float val, int idx, bool emitChange = true);
    
    void update(float* vals, int size, bool emitChange = true);
    
    int getSize() { return numSensors; }
    
    float* getSensorData() { return sensorData; }
    
private:
    //TODO: find suitable data structure for this.
    float* sensorData;
    int numSensors;
};




#endif  // SENSORCONTAINER_H_INCLUDED
