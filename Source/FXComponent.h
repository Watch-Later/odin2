/*
  ==============================================================================

    FXComponent.h
    Created: 27 Feb 2019 12:02:15am
    Author:  frot

  ==============================================================================
*/

#pragma once

#include "GlobalIncludes.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "Knob.h"

#define AMOUNT_POS_X 103
#define AMOUNT_POS_Y 43
#define FREQ_POS_X 31
#define FREQ_POS_Y 17
#define DRY_WET_POS_X 175
#define DRY_WET_POS_Y (FREQ_POS_Y)
#define FX_SYNC_POS_X 37
#define FX_SYNC_POS_Y 79
#define FX_RESET_POS_X 176
#define FX_RESET_POS_Y FX_SYNC_POS_Y

#define FX_FREQ_MIN 0.05
#define FX_FREQ_MAX 20
#define FX_FREQ_MID 0.8
#define FX_FREQ_DEFAULT 1
#define FX_AMOUNT_DEFAULT 0.3

#define FX_DRYWET_DEFAULT 1


//==============================================================================
/*
*/
class FXComponent    : public Component
{
public:
    FXComponent();
    ~FXComponent();

    void paint (Graphics&) override;
    void resized() override;
    void setImage(juce::Image p_background){
      m_background = p_background;
    }
    
private:

    Knob m_freq;
    Knob m_amount;
    Knob m_dry_wet;

    juce::DrawableButton m_sync;
    juce::DrawableButton m_reset;
    

    juce::Image m_background;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FXComponent)
};
