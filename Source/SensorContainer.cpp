/*
  ==============================================================================

    SensorContainer.cpp
    Created: 16 Dec 2015 11:53:07am
    Author:  johnty

  ==============================================================================
*/

#include "SensorContainer.h"

SensorContainer::SensorContainer(int size)
{
    sensorData = new float[size];
    numSensors = size;
}

void SensorContainer::update(float val, int idx, bool emitChange)
{
    jassert(numSensors>=idx);
    
    sensorData[idx] = val;
    if (emitChange)
        sendChangeMessage();
}

void SensorContainer::update(float* vals, int size, bool emitChange)
{
    jassert(numSensors>= size);
    
    for (int i=0; i<size; i++)
    {
        sensorData[i] =  vals[i]; //in this case, memcpy?
    }
    
    if (emitChange)
        sendChangeMessage();
}