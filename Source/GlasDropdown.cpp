/*
  ==============================================================================

    GlasDropdown.cpp
    Created: 25 Feb 2019 11:24:02pm
    Author:  frot

  ==============================================================================
*/

#include "GlasDropdown.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
GlasDropdown::GlasDropdown() {
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
  setLookAndFeel(&m_menu_feels);
}

GlasDropdown::~GlasDropdown() {
  setLookAndFeel(nullptr);
}

void GlasDropdown::paint(Graphics &g) {
  //Font bfont (juce::Font (Typeface::createSystemTypefaceFor (BinaryData::bfont_ttf  ,
    //                                                            BinaryData::bfont_ttfSize)));

  g.setColour(m_color);
  juce::Point<int> top_left = getLocalBounds().getTopLeft();
  top_left.addXY(m_inlay+1,m_inlay);
  juce::Point<int> bottom_right = getLocalBounds().getBottomRight();
  bottom_right.addXY(-m_inlay-1,-m_inlay); 
  g.fillRect(
      juce::Rectangle<int>(top_left, bottom_right)); // 

  g.setColour(Colours::white);

  //if(getSelectedId() == 1 && m_grey_first_element){
  //  g.setColour(Colours::grey);
  //}

  //g.setFont(bfont);
  g.setFont(12.0f);
  g.drawText(getText(), getLocalBounds(), Justification::centred,
             true); // draw some placeholder text

  g.drawImageAt(m_glaspanel, 0, 0);
}

void GlasDropdown::resized() {
  // This method is where you should set the bounds of any child
  // components that your component contains..
}
