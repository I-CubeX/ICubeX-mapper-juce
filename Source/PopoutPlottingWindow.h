/*
  ==============================================================================

    PopoutPlottingWindow.h
    Created: 15 Dec 2015 12:07:13pm
    Author:  johnty

  ==============================================================================
*/

#ifndef POPOUTPLOTTINGWINDOW_H_INCLUDED
#define POPOUTPLOTTINGWINDOW_H_INCLUDED

#include "JuceHeader.h"
#include "CustomAudioVisualiserComponent.h"

class PopoutPlottingWindow: public DocumentWindow
{
public:
    PopoutPlottingWindow(String title, Colour col, int btns) : DocumentWindow(title, col, btns)
    {
        
    };
    void closeButtonPressed()
    {
        //since its supposed exist throughout the lifetime
        // of the app, simply hide it on close.
        setVisible(false);
    }
    
    
    //TODO: should have plot colour settings, etc.
    
private:

    
};


#endif  // POPOUTPLOTTINGWINDOW_H_INCLUDED
