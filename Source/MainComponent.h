/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 4.0.2

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

#ifndef __JUCE_HEADER_8B807C0970EF2CF1__
#define __JUCE_HEADER_8B807C0970EF2CF1__

//[Headers]     -- You can add your own extra header files here --
#include "JuceHeader.h"
#include "MapperInterface.h"
#include "ICubeMIDIComponent.h"
#include "ICubeXInterface/ICubeXInteface.h"
#include "ColourChangeButton.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
 An auto-generated component, created by the Introjucer.

 Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainWindow  : public Component,
                    public ChangeListener,
                    public ComboBoxListener,
                    public ButtonListener
{
public:
    //==============================================================================
    MainWindow ();
    ~MainWindow();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
   void RefreshPorts();
   void AddMidiIn(const String& name);
   void AddMidiOut(const String& name);

   void changeListenerCallback(ChangeBroadcaster* source) ;

   static AudioDeviceManager& getSharedAudioDeviceManager();
   void SelectMidiIn(int idx);
   void SelectMidiOut(int idx);

   void updateLabels();
   void updateSensorVals();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);
    void buttonClicked (Button* buttonThatWasClicked);



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
   ScopedPointer<MapperInterface> myMapperInterface;
   ScopedPointer<AudioDeviceManager> myDeviceManager;
   ScopedPointer<ICubeMIDIComponent> myICubeX;
   ScopedPointer<SignalPlotterComponent> mySigPlotter;
   String currentPortName;
   int sensorValues[kNUM_ICUBEX_SENSORS];
   juce::Colour sigColours[kNUM_ICUBEX_SENSORS];
   Label* sigLabels[kNUM_ICUBEX_SENSORS];
   ScopedPointer<ColourChangeButton> mySensorBtns[kNUM_ICUBEX_SENSORS];

    //[/UserVariables]

    //==============================================================================
    ScopedPointer<ComboBox> comboBoxMidiIn;
    ScopedPointer<ComboBox> comboBoxMidiOut;
    ScopedPointer<TextButton> textButtonRefreshPorts;
    ScopedPointer<ToggleButton> toggleButtonSensors;
    ScopedPointer<TextButton> textButtonAutoConnect;
    ScopedPointer<Label> labelSensor1;
    ScopedPointer<Label> labelSensor2;
    ScopedPointer<Label> labelSensor3;
    ScopedPointer<Label> labelSensor4;
    ScopedPointer<Label> labelSensor5;
    ScopedPointer<Label> labelSensor6;
    ScopedPointer<Label> labelSensor7;
    ScopedPointer<Label> labelSensor8;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

#endif   // __JUCE_HEADER_8B807C0970EF2CF1__
