/*
  ==============================================================================

    LFODisplayComponent.cpp
    Created: 27 Feb 2019 6:43:33pm
    Author:  frot

  ==============================================================================
*/

#include "LFODisplayComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
LFODisplayComponent::LFODisplayComponent() {
  // In your constructor, you should add any child components, and
  // initialise any special settings that your component needs.
}

LFODisplayComponent::~LFODisplayComponent() {}

void LFODisplayComponent::paint(Graphics &g) {
  g.setColour(STANDARD_DISPLAY_COLOR);
  juce::Point<int> top_left = getLocalBounds().getTopLeft();
  top_left.addXY(m_inlay+1, m_inlay);
  juce::Point<int> bottom_right = getLocalBounds().getBottomRight();
  bottom_right.addXY(-m_inlay-1, -m_inlay);

  g.fillRect(juce::Rectangle<int>(top_left, bottom_right)); // pmai

  if (m_value < m_waves.size()) {
    g.drawImageAt((m_waves[m_value]), 0, 0);
  }

  g.drawImageAt(m_panel, 0, 0);
}

void LFODisplayComponent::resized() {
  // This method is where you should set the bounds of any child
  // components that your component contains..
}

void LFODisplayComponent::addWave(juce::Image p_wave) {
  m_waves.push_back(p_wave.createCopy());
}
