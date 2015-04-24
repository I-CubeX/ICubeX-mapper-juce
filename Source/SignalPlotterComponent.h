/*
 ==============================================================================
 
 SignalPlotterComponent.cpp
 Created: 17 Apr 2015 6:28:44pm
 Author:  johnty
 Simple drawing class for plotting signals
 
 ==============================================================================
 */

#include "JuceHeader.h"
#include "ICubeXInteface.h"
#include <deque>

#define kNUM_PLOT_PTS 256

class SignalPlotterComponent  : public Component
{
public:
    
    
    
    SignalPlotterComponent()
    {
        myTimeElapsed = 0.0;
        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            std::deque<int> newRow;
            newRow.shrink_to_fit();
            myPlotData.push_back(newRow);
            latestVals[i] = 0.0;
        }
        SetPlotColour(0, Colours::blue);
        SetPlotColour(1, Colours::green);
    }
    
    void SetPlotColour(int idx, Colour col)
    {
        myPlotColours[idx] = col;
    }
    
    void updateSigs(int* sigArray)
    {
        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            latestVals[i] = sigArray[i];
            /*
            if (myPlotData[i].size() > kNUM_PLOT_PTS-1)
            {
                myPlotData[i].pop_front();
            }
            myPlotData[i].push_back(sigArray[i]);
            if (i==0)
            {
                //DBG(" " + String(sigArray[i])+ "size of array=" + String((int)myPlotData[i].size()));
                
            }
             */
        }
    }
    
    void drawSignals(Graphics &g)
    {
        g.setColour(juce::Colours::black);
        g.drawRect(originX-1, originY, width, height+2, 1); //minor tweaks since my plot method is kinda funny
        
        float oX = g.getClipBounds().getX();
        float oY = g.getClipBounds().getY();
        g.setOrigin(originX, originY);
        oX = g.getClipBounds().getX();
        oY = g.getClipBounds().getY();
        
        //g.setColour(juce::Colours::green);
        //g.fillRect(0, 0, width, height);

        g.setOrigin(0, height/2);
        
        //g.setColour(juce::Colours::pink);
        //g.fillRect(0, 0, width, height/2);
        
        g.drawLine(0, 0, width-1, 0);

        if (false)
        {
            g.setColour(myPlotColours[0]);
            for (int i=0; i<kNUM_PLOT_PTS; i++)
            {
                float x = (float)i/(float(kNUM_PLOT_PTS));
                float y = sin(2.0*M_PI*x);
                float dx =  x * (float)width;
                float dy =  -y*(float)height/2.0;
                g.drawLine(dx, dy, dx+1, dy+1);
            }
        }
        
        g.setColour(myPlotColours[0]);
        int j=0;
        //for (std::deque<int>::iterator it = myPlotData[0].begin(); it != myPlotData[0].end(); ++it)

        //int plotlen = myPlotData[0].size();
        
        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            float dY = i*25+10.0;//(float)height*(float)latestVals[i]/127.0 + 10.0;
            float dX = (float)i * 25;
            
            g.setColour(juce::Colours::black);
            g.fillRect(dX, 0.0, 10.0, dY);
            oX = g.getClipBounds().getX();
            oY = g.getClipBounds().getY();
            if (i==0)
                DBG("dY[0] = " + String(dY));
        }
        
        return;
        for (int i=0; i<1; i++) //just the first one for now
        {
            int j = 0;
            for (std::deque<int>::iterator it = myPlotData[i].begin(); it != myPlotData[i].end(); ++it)
            {                
                float x = (float)j/(float(kNUM_PLOT_PTS));
                float y = sin(2.0*M_PI*x);
                float dx =  x * (float)width;
                float dy =  -y*(float)height/2.0;
                
                g.drawLine(dx, dy, dx+1, dy+1);
                j++;
                oX = g.getClipBounds().getX();
                oY = g.getClipBounds().getY();
                
                
                
//                int len2 = myPlotData[0].size();
//                if ( (j==len2-1) && (i==0) )
//                {
//                    int len = myPlotData.size();
//                    int val = myPlotData[0].at(len2-1);
//                    DBG("val=" + String((int)(*it)));
//                    //g.drawRect((float)originX, (float)originY, (float)val, (float)val, 2.0);
//                    radius = val* 3;
//
//                    
//                    g.setColour(juce::Colours::pink);
//                    g.fillRect((float)originX+25, (float)originY+35,
//                               200.0, 200.0);
//                    
//                }
            }
            DBG(String(j));
            
        //DBG("\n");
    }
    
    
    
}
void setBounds(int x, int y, int w, int h)
{
    originX = x;
    originY = y;
    width = w;
    height = h;
}

private:
    int originX;
    int originY;
    int width;
    int height;
    
    int latestVals[kNUM_ICUBEX_SENSORS];

    double myTimeElapsed;
    std::vector<std::deque<int>> myPlotData;
    juce::Colour myPlotColours[kNUM_ICUBEX_SENSORS];

};
