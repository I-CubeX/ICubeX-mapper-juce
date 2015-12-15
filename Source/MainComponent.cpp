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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainWindow::MainWindow ()
{
    //[Constructor_pre] You can add your own custom stuff here..


    sigColours[0] = Colours::blue;
    sigColours[1] = Colours::green;
    sigColours[2] = Colours::blueviolet;
    sigColours[3] = Colours::cornflowerblue;
    sigColours[4] = Colour(0xff2ab483);
    sigColours[5] = Colours::brown;
    sigColours[6] = Colour (0xffe81dd5);
    sigColours[7] = Colour (0xffeeeeee);

    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        sensorValues[i] = 0;
    }


    //[/Constructor_pre]

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

    addAndMakeVisible (toggleButtonSensors = new ToggleButton ("sensors toggle button"));
    toggleButtonSensors->setTooltip (TRANS("toggle sensors here"));
    toggleButtonSensors->setButtonText (TRANS("sensors active"));
    toggleButtonSensors->addListener (this);

    addAndMakeVisible (textButtonAutoConnect = new TextButton ("auto connect button"));
    textButtonAutoConnect->setTooltip (TRANS("automatically try connect to ICubeX port"));
    textButtonAutoConnect->setButtonText (TRANS("Auto Connect"));
    textButtonAutoConnect->addListener (this);

    addAndMakeVisible (labelSensor1 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor1->setFont (Font (15.00f, Font::plain));
    labelSensor1->setJustificationType (Justification::centredLeft);
    labelSensor1->setEditable (false, false, false);
    labelSensor1->setColour (Label::textColourId, Colours::blue);
    labelSensor1->setColour (TextEditor::textColourId, Colours::black);
    labelSensor1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor2 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor2->setFont (Font (15.00f, Font::plain));
    labelSensor2->setJustificationType (Justification::centredLeft);
    labelSensor2->setEditable (false, false, false);
    labelSensor2->setColour (Label::textColourId, Colours::green);
    labelSensor2->setColour (TextEditor::textColourId, Colours::black);
    labelSensor2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor3 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor3->setFont (Font (15.00f, Font::plain));
    labelSensor3->setJustificationType (Justification::centredLeft);
    labelSensor3->setEditable (false, false, false);
    labelSensor3->setColour (Label::textColourId, Colours::blueviolet);
    labelSensor3->setColour (TextEditor::textColourId, Colours::black);
    labelSensor3->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor4 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor4->setFont (Font (15.00f, Font::plain));
    labelSensor4->setJustificationType (Justification::centredLeft);
    labelSensor4->setEditable (false, false, false);
    labelSensor4->setColour (Label::textColourId, Colours::cornflowerblue);
    labelSensor4->setColour (TextEditor::textColourId, Colours::black);
    labelSensor4->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor5 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor5->setFont (Font (15.00f, Font::plain));
    labelSensor5->setJustificationType (Justification::centredLeft);
    labelSensor5->setEditable (false, false, false);
    labelSensor5->setColour (Label::textColourId, Colour (0xff2ab483));
    labelSensor5->setColour (TextEditor::textColourId, Colours::black);
    labelSensor5->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor6 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor6->setFont (Font (15.00f, Font::plain));
    labelSensor6->setJustificationType (Justification::centredLeft);
    labelSensor6->setEditable (false, false, false);
    labelSensor6->setColour (Label::textColourId, Colours::brown);
    labelSensor6->setColour (TextEditor::textColourId, Colours::black);
    labelSensor6->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor7 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor7->setFont (Font (15.00f, Font::plain));
    labelSensor7->setJustificationType (Justification::centredLeft);
    labelSensor7->setEditable (false, false, false);
    labelSensor7->setColour (Label::textColourId, Colour (0xffe81dd5));
    labelSensor7->setColour (TextEditor::textColourId, Colours::black);
    labelSensor7->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (labelSensor8 = new Label ("new label",
                                                 TRANS("sensor")));
    labelSensor8->setFont (Font (15.00f, Font::plain));
    labelSensor8->setJustificationType (Justification::centredLeft);
    labelSensor8->setEditable (false, false, false);
    labelSensor8->setColour (TextEditor::textColourId, Colours::black);
    labelSensor8->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButtonSelAll = new TextButton ("select all btn"));
    textButtonSelAll->setTooltip (TRANS("select all channels"));
    textButtonSelAll->setButtonText (TRANS("Select All"));
    textButtonSelAll->setConnectedEdges (Button::ConnectedOnRight);
    textButtonSelAll->addListener (this);

    addAndMakeVisible (labelSensorProps = new Label ("new label",
                                                     TRANS("Sensor Properties")));
    labelSensorProps->setFont (Font (14.00f, Font::plain));
    labelSensorProps->setJustificationType (Justification::centredLeft);
    labelSensorProps->setEditable (false, false, false);
    labelSensorProps->setColour (Label::backgroundColourId, Colour (0x8d808080));
    labelSensorProps->setColour (TextEditor::textColourId, Colours::black);
    labelSensorProps->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (textButtonSelNone = new TextButton ("select none  btn"));
    textButtonSelNone->setTooltip (TRANS("select no channels"));
    textButtonSelNone->setButtonText (TRANS("Select None"));
    textButtonSelNone->setConnectedEdges (Button::ConnectedOnLeft);
    textButtonSelNone->addListener (this);

    addAndMakeVisible (textButtonPop = new TextButton ("button popout"));
    textButtonPop->setButtonText (TRANS("Plot"));
    textButtonPop->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    textButtonPop->addListener (this);


    //[UserPreSize]

    //hardcoded from GUI (in future we should dynamically all the things)
    // the array is more like how we should be accessing things, so this bit
    // is a translation towards that kind of structure

    //the labels above were from before, made statically via the GUI builder.
    // below we replace them with buttons in their place, which allows
    // colour changing. this is all sandboxy stuff, so probably shouldn't
    // be used by anyone else in this state...

    sigLabels[0] = labelSensor1.get();
    sigLabels[1] = labelSensor2.get();
    sigLabels[2] = labelSensor3.get();
    sigLabels[3] = labelSensor4.get();
    sigLabels[4] = labelSensor5.get();
    sigLabels[5] = labelSensor6.get();
    sigLabels[6] = labelSensor7.get();
    sigLabels[7] = labelSensor8.get();

    //init device manager
    myDeviceManager = new AudioDeviceManager();
    myDeviceManager->initialise(2, 2, 0, true, String::empty, 0);
    currentPortName = "none";

    //init ICubeX Component
    myICubeX = new ICubeMIDIComponent();
    myICubeX->addChangeListener(this);

    //init SigPlotter
    mySigPlotter = new SignalPlotterComponent();
    mySigPlotter->setColours(Colours::black, Colours::green);
    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        mySigPlotter->setChColour(sigColours[i], i);
    }
    mySigPlotter->addChangeListener(this);
    addAndMakeVisible(mySigPlotter);
    
    //init popup plotter
    
    bool native = true;
    mySumPlotterWind = new PopoutPlottingWindow("Signal Average", Colour(0xFAAAAAAAAA), DocumentWindow::allButtons);
    
    Rectangle<int> area (0, 0, 400, 200);
    const RectanglePlacement placement ((native ? RectanglePlacement::xLeft : RectanglePlacement::xRight)
                                        + RectanglePlacement::yTop + RectanglePlacement::doNotResize);
    Rectangle<int> result (placement.appliedTo (area, Desktop::getInstance().getDisplays().getMainDisplay().userArea.reduced (20)));
    mySumPlotterWind->setBounds (result);
    mySumPlotterWind->setResizable (true, ! native);
    mySumPlotterWind->setUsingNativeTitleBar (native);
    mySumPlotterWind->setVisible(true);

    mySigSumPlotter = new SignalPlotterComponent(1);
    mySigSumPlotter->setColours(Colours::black, Colours::cyan);
    //TODO: for some reason, don't set the auto resize
    // feature otherwise initalizes with assertion fault
    mySumPlotterWind->setContentOwned(mySigSumPlotter, false);
    mySumPlotterWind->setVisible(false);

    //start mapper interface
    myMapperInterface = new MapperInterface();
    DBG("starting mapper thread...\n");
    myMapperInterface->startThread();
    DBG("... started!\n");

    //colour for plots
    //NamedValueSet props = labelSensor1->getProperties();
    //Colour* col = (Colour*)props.getVarPointerAt(Label::textColourId);
    //mySigPlotter->SetPlotColour(0, *col);

    //other init stuff here
    RefreshPorts();

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..

    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        //here we do the switcharoo, adding our "dynamic"
        //components in the place where we placed the "static" labels
        // from the GUI builder in Pro/Introjucer

        mySensorBtns[i] = new ColourChangeButton();
        mySensorBtns[i]->setButtonText(sigLabels[i]->getText());
        mySensorBtns[i]->setBounds(sigLabels[i]->getBounds());
        mySensorBtns[i]->setGeneralColour(sigColours[i]);
        addAndMakeVisible(mySensorBtns[i]);

        //hide the old labels.
        sigLabels[i]->setVisible(false);

        //register button for colour changes
        mySensorBtns[i]->addChangeListener(this);

    }

    //[/Constructor]
}

MainWindow::~MainWindow()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //stop digitizer

    myICubeX->setAllSensors(false);

    //[/Destructor_pre]

    comboBoxMidiIn = nullptr;
    comboBoxMidiOut = nullptr;
    textButtonRefreshPorts = nullptr;
    toggleButtonSensors = nullptr;
    textButtonAutoConnect = nullptr;
    labelSensor1 = nullptr;
    labelSensor2 = nullptr;
    labelSensor3 = nullptr;
    labelSensor4 = nullptr;
    labelSensor5 = nullptr;
    labelSensor6 = nullptr;
    labelSensor7 = nullptr;
    labelSensor8 = nullptr;
    textButtonSelAll = nullptr;
    labelSensorProps = nullptr;
    textButtonSelNone = nullptr;
    textButtonPop = nullptr;


    //[Destructor]. You can add your own custom destruction code here..


    if (myMapperInterface != NULL)
    {
        DBG("quit called from main window\n");
        myMapperInterface->stopThread(2000);
        DBG("mapperInterface thread stopped\n");
        //delete myMapperInterface;
    }
    myDeviceManager = nullptr;
    //[/Destructor]
}

//==============================================================================
void MainWindow::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //draw sigPlotter
    //[/UserPaint]
}

void MainWindow::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    comboBoxMidiIn->setBounds (8, 8, 150, 24);
    comboBoxMidiOut->setBounds (8, 40, 150, 24);
    textButtonRefreshPorts->setBounds (168, 8, 95, 24);
    toggleButtonSensors->setBounds (24, 136, 150, 24);
    textButtonAutoConnect->setBounds (168, 40, 95, 24);
    labelSensor1->setBounds (8, 82, 64, 24);
    labelSensor2->setBounds (72, 82, 64, 24);
    labelSensor3->setBounds (136, 82, 64, 24);
    labelSensor4->setBounds (200, 82, 64, 24);
    labelSensor5->setBounds (8, 106, 64, 24);
    labelSensor6->setBounds (72, 106, 64, 24);
    labelSensor7->setBounds (136, 106, 64, 24);
    labelSensor8->setBounds (200, 106, 64, 24);
    textButtonSelAll->setBounds (8, 160, 95, 24);
    labelSensorProps->setBounds (16, 184, 248, 184);
    textButtonSelNone->setBounds (184, 160, 95, 24);
    textButtonPop->setBounds (104, 160, 79, 24);
    //[UserResized] Add your own custom resize handling here..
    mySigPlotter->setBounds(300, 5, getWidth()-305, getHeight()-15);
    //mySigPlotter->setColours(juce::Colour::fromRGB(0, 0, 0), juce::Colour::fromRGB(0, 255, 0));
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
        SelectMidiIn(idx);
        //[/UserComboBoxCode_comboBoxMidiIn]
    }
    else if (comboBoxThatHasChanged == comboBoxMidiOut)
    {
        //[UserComboBoxCode_comboBoxMidiOut] -- add your combo box handling code here..
        int idx = comboBoxMidiOut->getSelectedItemIndex();
        SelectMidiOut(idx);
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
    else if (buttonThatWasClicked == toggleButtonSensors)
    {
        //[UserButtonCode_toggleButtonSensors] -- add your button handler code here..
        bool stream = toggleButtonSensors->getToggleState();
        myICubeX->setAllSensors(stream);
        //[/UserButtonCode_toggleButtonSensors]
    }
    else if (buttonThatWasClicked == textButtonAutoConnect)
    {
        //[UserButtonCode_textButtonAutoConnect] -- add your button handler code here..
        //[/UserButtonCode_textButtonAutoConnect]
    }
    else if (buttonThatWasClicked == textButtonSelAll)
    {
        //[UserButtonCode_textButtonSelAll] -- add your button handler code here..
        mySigPlotter->setSelectAllChannels(true);
        //[/UserButtonCode_textButtonSelAll]
    }
    else if (buttonThatWasClicked == textButtonSelNone)
    {
        //[UserButtonCode_textButtonSelNone] -- add your button handler code here..
        mySigPlotter->setSelectAllChannels(false);
        //[/UserButtonCode_textButtonSelNone]
    }
    else if (buttonThatWasClicked == textButtonPop)
    {
        //[UserButtonCode_textButtonPop] -- add your button handler code here..
        popSumPlotter();
        //[/UserButtonCode_textButtonPop]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void MainWindow::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    if (source == myICubeX)
    {
        updateSensorVals();
        updateLabels();
    }
    else if (source == mySigPlotter) {
        updateAnalysisWindow();

    }

    else
    {
        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            if (source == mySensorBtns[i])
            {
                sigColours[i] = mySensorBtns[i]->currCol;
                mySigPlotter->setChColour(sigColours[i], i);
                return;
            }
        }
    }
}

void MainWindow::RefreshPorts()
{
    comboBoxMidiIn->clear();
    comboBoxMidiOut->clear();
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

void MainWindow::SelectMidiIn(int idx)
{
    const StringArray list(MidiInput::getDevices());
    const String newInput(list[idx]);

    if (! myDeviceManager->isMidiInputEnabled(newInput)) {
        myDeviceManager->setMidiInputEnabled(newInput, true);
        myDeviceManager->addMidiInputCallback(newInput, myICubeX);
        currentPortName = newInput;

    }

    DBG("added midi input callback to " + newInput + "\n");
}

void MainWindow::SelectMidiOut(int idx)
{
    const StringArray list(MidiOutput::getDevices());
    const String newOutput(list[idx]);

    myDeviceManager->setDefaultMidiOutput(newOutput);
    myICubeX->setOutputPort(myDeviceManager->getDefaultMidiOutput());
    myICubeX->SendSetMode(false);
    myICubeX->SendReset();

    DBG("selected midi out " + newOutput);
}

void MainWindow::updateSensorVals()
{
    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        sensorValues[i] = myICubeX->my_digitizer_state_.GetSensorValState(i);
    }
    //this is some needless array/vector data conversion right here
    std::vector<int> newVec(sensorValues, sensorValues+kNUM_ICUBEX_SENSORS);
    myMapperInterface->updateVals(newVec);
    mySigPlotter->updateSigs(sensorValues);

    updateAnalysisWindow();

}

void MainWindow::updateLabels()
{
    MessageManagerLock mml;
    if (mml.lockWasGained()) {

        for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
        {
            mySensorBtns[i]->setButtonText(String(sensorValues[i]));
        }
        /*
         labelSensor1->setText(String(sensorValues[0]), dontSendNotification);
         labelSensor2->setText(String(sensorValues[1]), dontSendNotification);
         labelSensor3->setText(String(sensorValues[2]), dontSendNotification);
         labelSensor4->setText(String(sensorValues[3]), dontSendNotification);
         labelSensor5->setText(String(sensorValues[4]), dontSendNotification);
         labelSensor6->setText(String(sensorValues[5]), dontSendNotification);
         labelSensor7->setText(String(sensorValues[6]), dontSendNotification);
         labelSensor8->setText(String(sensorValues[7]), dontSendNotification);
         */
    }
}

void MainWindow::updateAnalysisWindow()
{
    String s;

    //TODO: this kind of behaviour should be modularized
    int numSelected = 0;
    float sum = 0;

    s << "ch selected = ";
    for (int i=0; i<kNUM_ICUBEX_SENSORS; i++)
    {
        if (mySigPlotter->isChannelSelected(i))
        {
            numSelected++;
            //TODO: see, we have yet another copy
            // of the sensor Values, but when was this synced?
            //   ... we shouldn't need to care if we had a dedicated
            //       model of the sensor values that handles it!!!
            sum+= sensorValues[i];
            s <<String(i) << " ";
        }
        
        //and here we do some combination, which further shows the
        // necessity of a modular system...
        if ( (mySumPlotterWind->isVisible()) && (numSelected>=1) ) //don't divide by 0
        {
            //TODO another interesting consequence:
            // this plotter "window" class should probably
            // be decoupled from the plotting data
            // to be consistent with MVC...
            int val = sum/numSelected; //rounding, blah blah
            mySigSumPlotter->updateSigs(&val);
        }
    }

    s <<"\nSum = " << String(sum);


    labelSensorProps->setText(s, NotificationType::dontSendNotification);
}

void MainWindow::popSumPlotter()
{
    mySumPlotterWind->setVisible (!mySumPlotterWind->isVisible());
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Introjucer information section --

    This is where the Introjucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainWindow" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams=""
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="0" initialWidth="600" initialHeight="400">
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
              virtualName="" explicitFocusOrder="0" pos="168 8 95 24" tooltip="refresh MIDI ports"
              buttonText="Refresh Ports" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="sensors toggle button" id="3771bf04353d3be1" memberName="toggleButtonSensors"
                virtualName="" explicitFocusOrder="0" pos="24 136 150 24" tooltip="toggle sensors here"
                buttonText="sensors active" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TEXTBUTTON name="auto connect button" id="b54ab90f08d157a3" memberName="textButtonAutoConnect"
              virtualName="" explicitFocusOrder="0" pos="168 40 95 24" tooltip="automatically try connect to ICubeX port"
              buttonText="Auto Connect" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="96fa6019cd20e93" memberName="labelSensor1"
         virtualName="" explicitFocusOrder="0" pos="8 82 64 24" textCol="ff0000ff"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="e3902ee2234690f9" memberName="labelSensor2"
         virtualName="" explicitFocusOrder="0" pos="72 82 64 24" textCol="ff008000"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="4d2ec8bc35a78fda" memberName="labelSensor3"
         virtualName="" explicitFocusOrder="0" pos="136 82 64 24" textCol="ff8a2be2"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="ef80babd10d6f897" memberName="labelSensor4"
         virtualName="" explicitFocusOrder="0" pos="200 82 64 24" textCol="ff6495ed"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="705c5368a7bf0b51" memberName="labelSensor5"
         virtualName="" explicitFocusOrder="0" pos="8 106 64 24" textCol="ff2ab483"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c3939c3b937756aa" memberName="labelSensor6"
         virtualName="" explicitFocusOrder="0" pos="72 106 64 24" textCol="ffa52a2a"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="5af2718dd3fc93d7" memberName="labelSensor7"
         virtualName="" explicitFocusOrder="0" pos="136 106 64 24" textCol="ffe81dd5"
         edTextCol="ff000000" edBkgCol="0" labelText="sensor" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="539233305d9aeeb5" memberName="labelSensor8"
         virtualName="" explicitFocusOrder="0" pos="200 106 64 24" edTextCol="ff000000"
         edBkgCol="0" labelText="sensor" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="select all btn" id="c34bcd55767c897b" memberName="textButtonSelAll"
              virtualName="" explicitFocusOrder="0" pos="8 160 95 24" tooltip="select all channels"
              buttonText="Select All" connectedEdges="2" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="new label" id="99641d49f60a64e3" memberName="labelSensorProps"
         virtualName="" explicitFocusOrder="0" pos="16 184 248 184" bkgCol="8d808080"
         edTextCol="ff000000" edBkgCol="0" labelText="Sensor Properties"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="14" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="select none  btn" id="a6becec1dde3e99d" memberName="textButtonSelNone"
              virtualName="" explicitFocusOrder="0" pos="184 160 95 24" tooltip="select no channels"
              buttonText="Select None" connectedEdges="1" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="button popout" id="1b705cb3ad30856f" memberName="textButtonPop"
              virtualName="" explicitFocusOrder="0" pos="104 160 79 24" buttonText="Plot"
              connectedEdges="3" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
