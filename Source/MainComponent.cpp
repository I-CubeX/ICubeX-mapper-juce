/*
  ==============================================================================

  This is an automatically generated GUI class created by the Introjucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Introjucer version: 3.1.0

  ------------------------------------------------------------------------------

  The Introjucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-13 by Raw Material Software Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow ()
{
    addAndMakeVisible (comboBoxMidiIn = new ComboBox ("midi in box"));
    comboBoxMidiIn->setTooltip (TRANS("list of MIDI inputs"));
    comboBoxMidiIn->setEditableText (false);
    comboBoxMidiIn->setJustificationType (Justification::centredLeft);
    comboBoxMidiIn->setTextWhenNothingSelected (TRANS("select input"));
    comboBoxMidiIn->setTextWhenNoChoicesAvailable (TRANS("(no ports available)"));
    comboBoxMidiIn->addListener (this);

    addAndMakeVisible (comboBoxMidiOut = new ComboBox ("midi out box"));
    comboBoxMidiOut->setTooltip (TRANS("list of MIDI outputs"));
    comboBoxMidiOut->setEditableText (false);
    comboBoxMidiOut->setJustificationType (Justification::centredLeft);
    comboBoxMidiOut->setTextWhenNothingSelected (TRANS("select output"));
    comboBoxMidiOut->setTextWhenNoChoicesAvailable (TRANS("(no ports available)"));
    comboBoxMidiOut->addListener (this);

    addAndMakeVisible (textButtonRefreshPorts = new TextButton ("refresh port btn"));
    textButtonRefreshPorts->setTooltip (TRANS("refresh MIDI ports"));
    textButtonRefreshPorts->setButtonText (TRANS("Refresh Ports"));
    textButtonRefreshPorts->addListener (this);


    //[UserPreSize]
    
    //start mapper interface
    myMapperInterface = new MapperInterface();
    DBG("starting mapper thread...\n");
    myMapperInterface->startThread();
    DBG("... started!\n");
    
    //other init stuff here
    RefreshPorts();
    
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    comboBoxMidiIn = nullptr;
    comboBoxMidiOut = nullptr;
    textButtonRefreshPorts = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    if (myMapperInterface != NULL)
    {
        DBG("quit called from main window\n");
        myMapperInterface->stopThread(2000);
        DBG("mapperInterface thread stopped\n");
        //delete myMapperInterface;
    }
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainWindow::resized()
{
    comboBoxMidiIn->setBounds (8, 8, 150, 24);
    comboBoxMidiOut->setBounds (8, 40, 150, 24);
    textButtonRefreshPorts->setBounds (168, 24, 95, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainWindow::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBoxMidiIn)
    {
        //[UserComboBoxCode_comboBoxMidiIn] -- add your combo box handling code here..
        int idx = comboBoxMidiIn->getSelectedItemIndex();
        myMidiIn = MidiInput::openDevice(idx, NULL);
        //[/UserComboBoxCode_comboBoxMidiIn]
    }
    else if (comboBoxThatHasChanged == comboBoxMidiOut)
    {
        //[UserComboBoxCode_comboBoxMidiOut] -- add your combo box handling code here..
        //[/UserComboBoxCode_comboBoxMidiOut]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void MainWindow::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == textButtonRefreshPorts)
    {
        //[UserButtonCode_textButtonRefreshPorts] -- add your button handler code here..
        
        RefreshPorts();
        
        //[/UserButtonCode_textButtonRefreshPorts]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainWindow::RefreshPorts()
{
    for (int i=0; i<MidiInput::getDevices().size(); i++)
    {
        AddMidiIn(MidiInput::getDevices()[i]);
    }
    for (int i=0; i<MidiOutput::getDevices().size(); i++)
    {
        AddMidiOut(MidiOutput::getDevices()[i]);
    }
}

void MainWindow::AddMidiIn(const juce::String &name)
{
    comboBoxMidiIn->addItem(name, comboBoxMidiIn->getNumItems()+1);
}

void MainWindow::AddMidiOut(const juce::String &name)
{
    comboBoxMidiOut->addItem(name, comboBoxMidiOut->getNumItems()+1);

}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <COMBOBOX name="midi in box" id="6d56b5526b211a0b" memberName="comboBoxMidiIn"
            virtualName="" explicitFocusOrder="0" pos="8 8 150 24" tooltip="list of MIDI inputs"
            editable="0" layout="33" items="" textWhenNonSelected="select input"
            textWhenNoItems="(no ports available)"/>
  <COMBOBOX name="midi out box" id="7d9929464830b002" memberName="comboBoxMidiOut"
            virtualName="" explicitFocusOrder="0" pos="8 40 150 24" tooltip="list of MIDI outputs"
            editable="0" layout="33" items="" textWhenNonSelected="select output"
            textWhenNoItems="(no ports available)"/>
  <TEXTBUTTON name="refresh port btn" id="9393238952627389" memberName="textButtonRefreshPorts"
              virtualName="" explicitFocusOrder="0" pos="168 24 95 24" tooltip="refresh MIDI ports"
              buttonText="Refresh Ports" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
