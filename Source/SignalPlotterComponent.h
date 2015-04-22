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
            if (i==0)
            {
                //DBG(" " + String(sigArray[i])+ "size of array=" + String((int)myPlotData[i].size()));
                
            }
        }
        int len = myPlotData.size();
        int len2 = myPlotData[0].size();
        int val = myPlotData[0].at(len2-1);
        //DBG("\n");
    }
    
    void drawSignals(Graphics &g)
    {
        //g.drawRect(originX, originY, width, height, 3);
        
        g.setOrigin(originX, originY);
        g.setColour(juce::Colours::green);
        g.fillRect(0, 0, width, height);

        g.setOrigin(0, height/2);
        g.setColour(juce::Colours::pink);
        g.fillRect(0, 0, width, height/2);
        
        g.setColour(juce::Colours::black);
        g.drawLine(0, 0, width, 0);

        g.setColour(juce::Colours::red);
        for (int i=0; i<kNUM_PLOT_PTS; i++)
        {
            float x = (float)i/(float(kNUM_PLOT_PTS));
            float y = sin(2.0*M_PI*x);
            float dx =  x * (float)width;
            float dy =  -y*(float)height/2.0;
            g.drawLine(dx, dy, dx+1, dy+1);
        }
        
        float radius = 50.0;
        float drawOriginX = originX;
        float drawOriginY = originY+height;
        for (int i=0; i<1; i++) //just the first one for now
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
                //g.drawLine(x0, y0, x0+1, y0+1);
                //g.drawLine(drawOriginX+dx, drawOriginY-y0, 1, 1);
                //DBG(String(x0) + " " + String(y0));
                
                //g.drawRect((float)originX, (float)originY, a, (float)height, 3.0);
                
                int len2 = myPlotData[0].size();
                if ( (j==len2-1) && (i==0) )
                {
                    int len = myPlotData.size();
                    int val = myPlotData[0].at(len2-1);
                    DBG("val=" + String((int)(*it)));
                    //g.drawRect((float)originX, (float)originY, (float)val, (float)val, 2.0);
                    radius = val* 3;

                    
                    g.setColour(juce::Colours::pink);
                    g.fillRect((float)originX+25, (float)originY+35,
                               200.0, 200.0);
                    
                }
            j++;
            
        }
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

double myTimeElapsed;
std::vector<std::deque<int>> myPlotData;
juce::Colour myPlotColours[kNUM_ICUBEX_SENSORS];

};
