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
            myPlotData.push_back(newRow);
        }
    }
    
    void SetPlotColour(int idx, Colour col)
    {
        myPlotColours[idx] = col;
    }
    
    void updateSigs(int* sigArray)
    {
        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            if (myPlotData[i].size() > kNUM_PLOT_PTS-1)
            {
                myPlotData[i].pop_front();
            }
            myPlotData[i].push_back(sigArray[i]);
            //DBG(" " + String(sigArray[i]));
        }
        //DBG("\n");
    }
    
    void drawSignals(Graphics &g)
    {
        g.drawRect(originX, originY, width, height, 3);

        float drawOriginX = originX;
        float drawOriginY = originY+height;
        for (int i=0; i<2; i++) //just the first one for now
        {
            int j = 1;
            for (std::deque<int>::iterator it = myPlotData[i].begin(); it != myPlotData[i].end(); ++it)
            {
                float x0;
                float y0;
                float dx = (float)width/(float)kNUM_PLOT_PTS;
                x0 = drawOriginX+j*dx;
                y0 = drawOriginY- (float) (int)(*it) * height / 127.0;
                //g.setColour(myPlotColours[i]);
                g.drawEllipse(x0, y0, 20, 20, 5);
                //g.drawLine(x0, y0, x0+1, y0+1);
                //g.drawLine(drawOriginX+dx, drawOriginY-y0, 1, 1);
                j++;
                DBG(String(x0) + " " + String(y0));
                float a = y0;
                g.drawRect((float)originX, (float)originY, a, (float)height, 3.0);

            }
            DBG("\n");
        }
        g.drawEllipse(50, 50, 200, 200, 5);
        
        
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
    
    double myTimeElapsed;
    std::vector<std::deque<int>> myPlotData;
    juce::Colour myPlotColours[kNUM_ICUBEX_SENSORS];
    
};