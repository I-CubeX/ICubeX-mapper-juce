//
//  ColourChangeButton.h
//  ICubeXMidi
//
//  Created by johnty on 2015-12-09.
//
//

#ifndef ColourChangeButton_h
#define ColourChangeButton_h
/** A TextButton that pops up a colour chooser to change its colours. */
class ColourChangeButton  : public TextButton,
public ChangeListener,
public ChangeBroadcaster
{
public:
    ColourChangeButton()
    : TextButton ("Click to change colour...")
    {
        setSize (10, 24);
        changeWidthToFitText();
        setColour(TextButton::buttonColourId, Colour(0xFFF0F0F0));
    }
    
    void clicked() override
    {
        ColourSelector* colourSelector = new ColourSelector();
        colourSelector->setName ("background");
        colourSelector->setCurrentColour (findColour (TextButton::buttonColourId));
        colourSelector->addChangeListener (this);
        colourSelector->setColour (ColourSelector::backgroundColourId, Colours::transparentBlack);
        colourSelector->setSize (300, 400);
        CallOutBox::launchAsynchronously (colourSelector, getScreenBounds(), nullptr);
    }
    
    void changeListenerCallback (ChangeBroadcaster* source) override
    {
        if (ColourSelector* cs = dynamic_cast <ColourSelector*> (source))
        {
            setGeneralColour(cs->getCurrentColour());
            sendChangeMessage(); //tell someone else we have new colour here.
        }
        
    }
    
    void setGeneralColour(Colour colour)
    {
        currCol = colour;
        setColour (TextButton::textColourOffId, colour);
        setColour (TextButton::textColourOnId, colour);
    }
    
    Colour currCol;
};

#endif /* ColourChangeButton_h */
