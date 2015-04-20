/*
  ==============================================================================

    SignalPlotterComponent.cpp
    Created: 17 Apr 2015 6:28:44pm
    Author:  johnty
   based mostly on the GraphicsDemo from the JUCE main demo project

  ==============================================================================
*/

#include "JuceHeader.h"

class SignalPlotterComponent  : public Component
{
public:
    void drawSignals(Graphics &g)
    {
        g.drawRect(originX, originY, width, height, 3);

        g.drawLine(0, 0, 200, 200);
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
};