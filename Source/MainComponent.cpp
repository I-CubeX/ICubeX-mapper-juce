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
    comboBoxMidiIn->setEditableText (false);
    comboBoxMidiIn->setJustificationType (Justification::centredLeft);
    comboBoxMidiIn->setTextWhenNothingSelected (String::empty);
    comboBoxMidiIn->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBoxMidiIn->addListener (this);

    addAndMakeVisible (comboBoxMidiOut = new ComboBox ("midi out box"));
    comboBoxMidiOut->setEditableText (false);
    comboBoxMidiOut->setJustificationType (Justification::centredLeft);
    comboBoxMidiOut->setTextWhenNothingSelected (String::empty);
    comboBoxMidiOut->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBoxMidiOut->addListener (this);


    //[UserPreSize]
    myMapperInterface = new MapperInterface();
    DBG("starting mapper thread...\n");
    myMapperInterface->startThread();
    DBG("... started!\n");
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


    //[Destructor]. You can add your own custom destruction code here..
    if (myMapperInterface != NULL)
    {
        DBG("quit called from main window\n");
        myMapperInterface->stopThread(2000);
        DBG("mapperInterface thread stopped\n");
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainWindow::AddMidiIn(const juce::String &name) {
    comboBoxMidiIn->addItem(name, comboBoxMidiIn->getNumItems()+1);
}

void MainWindow::AddMidiOut(const juce::String &name) {
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
            virtualName="" explicitFocusOrder="0" pos="8 8 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <COMBOBOX name="midi out box" id="7d9929464830b002" memberName="comboBoxMidiOut"
            virtualName="" explicitFocusOrder="0" pos="8 40 150 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
