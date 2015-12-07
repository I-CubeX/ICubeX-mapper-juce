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
#include <deque>

#define kNUM_PLOT_PTS 1024
#define kSAMPLES_PER_PIXEL 32

#define NUM_PLOTS kNUM_ICUBEX_SENSORS


class SignalPlotterComponent  : public AudioVisualiserComponent
{
public:
   
   AudioSampleBuffer* buff;
   
   SignalPlotterComponent() : AudioVisualiserComponent(NUM_PLOTS)
   {
      clear();
      setBufferSize(kNUM_PLOT_PTS);
      setSamplesPerBlock(kSAMPLES_PER_PIXEL);
      buff = new AudioSampleBuffer(NUM_PLOTS, kNUM_PLOT_PTS);
   }
   
   
   void SetPlotColour(int idx, Colour col)
   {
      myPlotColours[idx] = col;
   }
   
   void updateSigs(int* sigArray)
   {

      buff->clear();
      
      //TODO: don't new it every time
      
      for (int i=0; i<NUM_PLOTS; i++)
      {
         float val = 2.0*(((float) sigArray[i] / 127.0) - 0.5);
         if (val > 1.0) val = 1.0;
         if (val < -1.0) val = -1.0;
         DBG("val = " + String::formatted("%2.2f", val));
         
         //val = 0.0;
         for (int j=0; j<kSAMPLES_PER_PIXEL; j++)
         {
            
            buff->addSample(i, j, val);
            //this->pushSample(&val, i);
            
         }
      }
      this->pushBuffer(*buff);
      
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
   
};

#endif //define _SIGNALPLOTTERCOMPONENT_H_