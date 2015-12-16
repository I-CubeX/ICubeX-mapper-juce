/*
 ==============================================================================
 
 SignalPlotterComponent.cpp
 Created: 17 Apr 2015 6:28:44pm
 Author:  johnty
 Simple drawing class for plotting signals
 
 ==============================================================================
 */

#ifndef _SIGNALPLOTTERCOMPONENT_H_
#define _SIGNALPLOTTERCOMPONENT_H_

#include "ICubeXInterface/ICubeXInteface.h"
#include "JuceHeader.h"
#include "CustomAudioVisualiserComponent.h"
#include "SensorContainerInterface.h"
#include <deque>

#define kNUM_PLOT_PTS 1024
#define kSAMPLES_PER_PIXEL 4
#define kOVER_DRAW 1

#define NUM_PLOTS kNUM_ICUBEX_SENSORS


class SignalPlotterComponent  : public CustomAudioVisualiserComponent, public SensorContainerInterface, public ChangeListener
{
public:
    
    AudioSampleBuffer* buff;
    
    SignalPlotterComponent(int plots = NUM_PLOTS, bool sync = false) : CustomAudioVisualiserComponent(plots)
    {
        numPlots = plots;
        isSynced = sync;
        val = 0.5;
        clear();
        setBufferSize(kNUM_PLOT_PTS);
        setSamplesPerBlock(kSAMPLES_PER_PIXEL);
        setRepaintRate(60); //TODO: sync related stuff 
        pixels_per_second = 60*kOVER_DRAW;

        DBG(String(pixels_per_second));
        
        
        buff = new AudioSampleBuffer(numPlots, kSAMPLES_PER_PIXEL*kOVER_DRAW);
        
        for (int i=0; i< numPlots; i++)
        {
            latestVals[i] = 0.0;
        }
    }
    
    void SetBgColour(Colour col)
    {
        myBgColour = col;
    }
    void SetPlotColour(int idx, Colour col)
    {
        myPlotColours[idx] = col;
    }
    
    void updateSigs(int* sigArray)
    {
        for (int i=0; i<numPlots; i++)
        {
            latestVals[i] = sigArray[i];
        }
        
    }
    
    //this is a synchronized draw update!
    void changeListenerCallback(ChangeBroadcaster* source)
    {
        SensorContainer* container = getSensorContainer();
        if ( container != nullptr)
        {
            for (int i=0; i<container->getSize(); i++)
            {
                latestVals[i] = container->getSensorData()[i];
            }
        }
        fillDrawBuffer();
        repaint();
    }

    void triggerChanged();
    
    void fillDrawBuffer()
    {
        buff->clear();
        
        float vals[numPlots];
        for (int i=0; i<numPlots; i++)
        {
            float val = 1.9*(((float) latestVals[i] / 127.0) - 0.5);
            if (val > 1.0) val = 1.0;
            if (val < -1.0) val = -1.0;
            //if (i==0)
            //   DBG("val[0] = " + String::formatted("%2.2f", val));
            
            vals[i] = val;
            for (int j=0; j<kSAMPLES_PER_PIXEL*kOVER_DRAW; j++)
            {
                if (j<=kSAMPLES_PER_PIXEL*kOVER_DRAW/2)
                    buff->addSample(i, j, vals[i]);
                else
                    buff->addSample(i, j, vals[i]+0.05); //Note2self: not a good way to get "line thickness"...
                //addPlotVal(val);
            }
        }
        pushBuffer(*buff);
    }
    
    //test fn: adds a single plot point to all plots
    void addPlotVal(float val)
    {
        AudioSampleBuffer* buff = new AudioSampleBuffer(numPlots, 1);
        buff->clear();
        float* vals = new float[2];
        buff->addSample(0, 0, val);
        buff->addSample(1, 0, 0.5-val);
        buff->addSample(2, 0, 1.5*val);
        buff->addSample(3, 0, 1.5*(0.5-val));
        buff->addSample(4, 0, val);
        buff->addSample(5, 0, -val);
        buff->addSample(6, 0, 0.5*val);
        pushBuffer(*buff);
        delete buff;
        
        
        //vals[0] = val;
        //vals[1] = 0.5 - val;
        //pushSample(vals, 2);
    }
    
    void timerCallback()
    {
        //if not synced by data, we want to manually fill
        // the draw buffer and repaint on timer
        if (!isSynced)
        {
            fillDrawBuffer();
            repaint();
        }
}
    
    void paint (Graphics& g) override
    {
        CustomAudioVisualiserComponent::paint(g);
    }
    
    
    ~SignalPlotterComponent()
    {
        delete buff;
    }
    
private:
    
    int numPlots;
    bool isSynced;
    
    //TODO these arrays should have dynamic length
    // depending on init.
    int latestVals[kNUM_ICUBEX_SENSORS];
    
    double myTimeElapsed;
    std::vector<std::deque<int>> myPlotData;
    juce::Colour myPlotColours[kNUM_ICUBEX_SENSORS];
    juce::Colour myBgColour;
    float val;
    
    float pixels_per_second;
    
};

#endif //define _SIGNALPLOTTERCOMPONENT_H_