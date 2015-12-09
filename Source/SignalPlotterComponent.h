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
#include <deque>

#define kNUM_PLOT_PTS 1024
#define kSAMPLES_PER_PIXEL 4

#define NUM_PLOTS kNUM_ICUBEX_SENSORS


class SignalPlotterComponent  : public CustomAudioVisualiserComponent
{
public:
    
    AudioSampleBuffer* buff;
    
    SignalPlotterComponent() : CustomAudioVisualiserComponent(NUM_PLOTS)
    {
        val = 0.5;
        clear();
        setBufferSize(kNUM_PLOT_PTS);
        setSamplesPerBlock(kSAMPLES_PER_PIXEL);
        setRepaintRate(60);
        
        buff = new AudioSampleBuffer(NUM_PLOTS, kSAMPLES_PER_PIXEL);
        
        for (int i=0; i< NUM_PLOTS; i++)
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
        for (int i=0; i<NUM_PLOTS; i++)
        {
            latestVals[i] = sigArray[i];
        }
        
    }
    
    void fillDrawBuffer()
    {
        buff->clear();
        
        float vals[NUM_PLOTS];
        for (int i=0; i<NUM_PLOTS; i++)
        {
            float val = 1.9*(((float) latestVals[i] / 127.0) - 0.5);
            if (val > 1.0) val = 1.0;
            if (val < -1.0) val = -1.0;
            //if (i==0)
            //   DBG("val[0] = " + String::formatted("%2.2f", val));
            
            vals[i] = val;
            for (int j=0; j<kSAMPLES_PER_PIXEL; j++)
            {
                if (j<=kSAMPLES_PER_PIXEL/2)
                    buff->addSample(i, j, vals[i]);
                else
                    buff->addSample(i, j, vals[i]+0.05);
                //addPlotVal(val);
            }
        }
        pushBuffer(*buff);
    }
    
    //test fn: adds a single plot point to all plots
    void addPlotVal(float val)
    {
        AudioSampleBuffer* buff = new AudioSampleBuffer(NUM_PLOTS, 1);
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
        
        //DBG("timerCallback");
        fillDrawBuffer();
        repaint();
        
        
        //      float sign = 1.0;
        //      for (int i=0; i<100; i++)
        //      {
        //         val += sign*1.0/50;
        //         addPlotVal(val);
        //         if (val >= .5)
        //            sign = -1.0;
        //         if (val <= -0.5)
        //            sign = 1.0;
        //      }
        //      repaint();
        //      return;
        
        
        
        repaint();
    }
    
    void paint (Graphics& g) override
    {
        CustomAudioVisualiserComponent::paint(g);
        //      g.fillAll (myBgColour);
        //
        //      Rectangle<float> r (getLocalBounds().toFloat());
        //      const float channelHeight = r.getHeight() / channels.size();
        //
        //
        //      for (int i = 0; i < channels.size(); ++i)
        //      {
        //         g.setColour (myPlotColours[i]);
        //
        //         const ChannelInfo& c = *channels.getUnchecked(i);
        //
        //         paintChannel (g, r.removeFromTop (channelHeight),
        //                       c.levels.begin(), c.levels.size(), c.nextSample);
        //      }
    }
    
    
    ~SignalPlotterComponent()
    {
        delete buff;
    }
    
private:
    
    int latestVals[kNUM_ICUBEX_SENSORS];
    
    double myTimeElapsed;
    std::vector<std::deque<int>> myPlotData;
    juce::Colour myPlotColours[kNUM_ICUBEX_SENSORS];
    juce::Colour myBgColour;
    float val;
    
};

#endif //define _SIGNALPLOTTERCOMPONENT_H_