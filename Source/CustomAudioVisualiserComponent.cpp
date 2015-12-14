/*
 ==============================================================================
 
 This file is part of the JUCE library.
 Copyright (c) 2015 - ROLI Ltd.
 
 Permission is granted to use this software under the terms of either:
 a) the GPL v2 (or any later version)
 b) the Affero GPL v3
 
 Details of these licenses can be found at: www.gnu.org/licenses
 
 JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 
 ------------------------------------------------------------------------------
 
 To release a closed-source product which uses JUCE, commercial licenses are
 available: visit www.juce.com for more information.
 
 ==============================================================================
 */
#include "CustomAudioVisualiserComponent.h"
//using namespace juce;

struct CustomAudioVisualiserComponent::ChannelInfo
{
    ChannelInfo (CustomAudioVisualiserComponent& o, int bufferSize)
    : owner (o), nextSample (0), subSample (0)
    {
        setBufferSize (bufferSize);
        clear();
        isChSelected = false;
    }
    
    void clear() noexcept
    {
        for (int i = 0; i < levels.size(); ++i)
        {
            levels.getReference(i) = Range<float>();
        }
        
        value = Range<float>();
        subSample = 0;
    }
    
    void pushSamples (const float* inputSamples, const int num) noexcept
    {
        for (int i = 0; i < num; ++i)
        {
            pushSample (inputSamples[i]);
        }
    }
    
    void pushSample (const float newSample) noexcept
    {
        if (--subSample <= 0)
        {
            nextSample %= levels.size();
            levels.getReference (nextSample++) = value;
            subSample = owner.getSamplesPerBlock();
            value = Range<float> (newSample, newSample);
        }
        else
        {
            value = value.getUnionWith (newSample);
        }
    }
    
    void setBufferSize (int newSize)
    {
        levels.removeRange (newSize, levels.size());
        levels.insertMultiple (-1, Range<float>(), newSize - levels.size());
        
        if (nextSample >= newSize)
            nextSample = 0;
    }
    //TODO: see if it makes sense to use the Selectable class in JUCE
    void setChSelected(bool selected) { isChSelected = selected;}
    bool getIsChSelected() const {return isChSelected;}
    
    CustomAudioVisualiserComponent& owner;
    Array<Range<float> > levels;
    Range<float> value;
    int nextSample, subSample;
    
    bool isChSelected;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelInfo)
};


//==============================================================================
CustomAudioVisualiserComponent::CustomAudioVisualiserComponent (const int initialNumChannels) : numSamples (1024),
inputSamplesPerBlock (256),
    backgroundColour (Colours::black),
    fgColour(Colours::red),
    drawGrid(true)
{
    setOpaque (true);
    setNumChannels (initialNumChannels);
    setRepaintRate (60);
    drawOffset = 0.0;
}

CustomAudioVisualiserComponent::~CustomAudioVisualiserComponent()
{
    
}

void CustomAudioVisualiserComponent::setNumChannels (const int numChannels)
{
    channels.clear();
    waveformColours.clear();
    for (int i = 0; i < numChannels; ++i) {
        channels.add(new ChannelInfo (*this, numSamples));
        //default to fgColour;
        waveformColours.add(new Colour(fgColour));
    }
}

void CustomAudioVisualiserComponent::setBufferSize (int newNumSamples)
{
    numSamples = newNumSamples;
    
    for (int i = 0; i < channels.size(); ++i)
        channels.getUnchecked(i)->setBufferSize (newNumSamples);
}

void CustomAudioVisualiserComponent::clear()
{
    for (int i = 0; i < channels.size(); ++i)
        channels.getUnchecked(i)->clear();
}

void CustomAudioVisualiserComponent::pushBuffer (const float** d, int numChannels, int num)
{
    numChannels = jmin (numChannels, (int)channels.size());
    
    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSamples (d[i], num);
}

void CustomAudioVisualiserComponent::pushBuffer (const AudioSampleBuffer& buffer)
{
    pushBuffer (buffer.getArrayOfReadPointers(),
                buffer.getNumChannels(),
                buffer.getNumSamples());
}

void CustomAudioVisualiserComponent::pushBuffer (const AudioSourceChannelInfo& buffer)
{
    const int numChannels = jmin (buffer.buffer->getNumChannels(), (int)channels.size());
    
    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSamples (buffer.buffer->getReadPointer (i, buffer.startSample),buffer.numSamples);
}

void CustomAudioVisualiserComponent::pushSample (const float* d, int numChannels)
{
    numChannels = jmin (numChannels, channels.size());
    
    for (int i = 0; i < numChannels; ++i)
        channels.getUnchecked(i)->pushSample (d[i]);
}

void CustomAudioVisualiserComponent::setSamplesPerBlock (int newSamplesPerPixel) noexcept
{
    inputSamplesPerBlock = newSamplesPerPixel;
}

void CustomAudioVisualiserComponent::setRepaintRate (int frequencyInHz)
{
    startTimerHz (frequencyInHz);
}

void CustomAudioVisualiserComponent::timerCallback()
{
    repaint();
}

void CustomAudioVisualiserComponent::setColours (Colour bk, Colour fg, Colour grd) noexcept
{
    backgroundColour = bk;
    gridColour = grd;
    for (int i=0; i<channels.size(); i++)
    {
        *waveformColours.getUnchecked(i) = fg;
    }
    repaint();
}

void CustomAudioVisualiserComponent::setChColour(Colour colour, int channel)
{
    *waveformColours.getUnchecked(channel) = colour;
}

void CustomAudioVisualiserComponent::paint (Graphics& g)
{
    g.fillAll (backgroundColour);
    
    Rectangle<float> r (getLocalBounds().toFloat());
    
    g.setColour(gridColour);
    
    
    for (int i=0; i<numSamples/60 + 1; i++)
    {
        //drawOffset-= 1.0/60.0; //this is not a good way to keep track of time
        
        if (drawOffset < -(float)numSamples/60.0) {
            drawOffset = 0.0;  //wrap the moving grid point around
            DBG("blip");
            DBG(String(r.getWidth()));
        }
        float dx = r.getWidth()*(60.0/(float)numSamples);
        g.drawLine(i*dx+drawOffset, 0, i*dx+drawOffset, r.getHeight());
    }
    
    const float channelHeight = r.getHeight() / channels.size();
    
    
    
    for (int i = 0; i < channels.size(); ++i)
    {

        
        const ChannelInfo& c = *channels.getUnchecked(i);

        //draw horizontal grid for channel
        g.setColour(gridColour);
        g.drawLine(0, channelHeight*(i+1), r.getWidth(), channelHeight*(i+1));
        
        
        //draw a channel
        g.setColour (*waveformColours.getUnchecked(i));
        
        paintChannel (g, r.removeFromTop (channelHeight),
                      c.levels.begin(), c.levels.size(), c.nextSample);
        
        //draw "selection" around channel if selected
        if (c.getIsChSelected())
        {
            g.setColour(Colour(0xAA00FF00));
            g.drawRect(0.0, (float)i*channelHeight, r.getWidth(), channelHeight, channelHeight/25.0);
        }
    }
}

void CustomAudioVisualiserComponent::getChannelAsPath (Path& path, const Range<float>* levels, int numLevels, int nextSample)
{
    path.preallocateSpace (4 * numLevels + 8);
    
    for (int i = 0; i < numLevels; ++i)
    {
        const float level = -(levels[(nextSample + i) % numLevels].getEnd());
        
        if (i == 0)
            path.startNewSubPath (0.0f, level);
        else
            path.lineTo ((float) i, level);
    }
    
    for (int i = numLevels; --i >= 0;)
        path.lineTo ((float) i, -(levels[(nextSample + i) % numLevels].getStart()));
    
    path.closeSubPath();
}

void CustomAudioVisualiserComponent::paintChannel (Graphics& g, Rectangle<float> area,
                                                   const Range<float>* levels, int numLevels, int nextSample)
{
    Path p;
    getChannelAsPath (p, levels, numLevels, nextSample);
    
    g.fillPath (p, AffineTransform::fromTargetPoints (0.0f, -1.0f,               area.getX(), area.getY(),
                                                      0.0f, 1.0f,                area.getX(), area.getBottom(),
                                                      (float) numLevels, -1.0f,  area.getRight(), area.getY()));
}

void CustomAudioVisualiserComponent::mouseDown(const juce::MouseEvent &event)
{
    String s;
    s << "mouseDown @ " << String((int)event.getMouseDownPosition().getX())
      <<" "  << String((int)event.getMouseDownPosition().getY())<<"\n";
    DBG(s);
    
    // calculate where we've clicked in relation to channels
    // TODO: don't do this in the overlapped plotting case.
    Rectangle<float> r (getLocalBounds().toFloat());
    const float channelHeight = r.getHeight() / channels.size();
    
    s.clear();
    for (int i = 0; i < channels.size(); ++i)
    {
        if ( (event.getMouseDownY() < channelHeight*(i+1)) &&
               (event.getMouseDownY() > channelHeight*i) )
        {
            //we can do something else for right click
            if (event.mods.isLeftButtonDown()) {
                bool selected = !channels[i]->getIsChSelected(); //do a toggle
                channels[i]->setChSelected(selected);
                s <<"ch " << String(i) << " selected = " << String(selected)<<"\n";
                DBG(s);
                
                break; //we can only click on one thing at a time
            }
        }
    }
    
    
}
