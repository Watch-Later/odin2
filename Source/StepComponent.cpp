/*
  ==============================================================================

    StepComponent.cpp
    Created: 4 May 2020 1:23:41am
    Author:  frederik_siepe

  ==============================================================================
*/

#include "StepComponent.h"
#include <JuceHeader.h>

//==============================================================================
StepComponent::StepComponent() : m_step_on("step_on", juce::DrawableButton::ButtonStyle::ImageRaw) {
	addAndMakeVisible(m_mod);
	m_mod.setSliderStyle(Slider::RotaryVerticalDrag);
	m_mod.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_mod.setNumDecimalPlacesToDisplay(3);
	m_mod.setKnobTooltip("TODO");

	addAndMakeVisible(m_transpose);
	m_transpose.setSliderStyle(Slider::RotaryVerticalDrag);
	m_transpose.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_transpose.setNumDecimalPlacesToDisplay(3);
	m_transpose.setKnobTooltip("TODO");

	addAndMakeVisible(m_step_on);
	m_step_on.setClickingTogglesState(true);
	m_step_on.setTooltip("TODO");
	m_step_on.setTriggeredOnMouseDown(true);
	m_step_on.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_step_on.onClick = [&](){
		DBG((float)m_step_on.getToggleState());
	};

	addAndMakeVisible(m_led);
	

	//TODO REMOVE
	m_mod.setRange(-1, 1);
	m_transpose.setRange(-1, 1);
}

StepComponent::~StepComponent() {
}

void StepComponent::paint(Graphics &g) {
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void StepComponent::resized() {
}

void StepComponent::setGUIBig() {
	m_led.setGUIBig();
	m_led.setTopLeftPosition(STEP_LED_POS_X, STEP_LED_POS_Y);

	juce::Image black_knob_small =
	    ImageCache::getFromMemory(BinaryData::black_knob_small_150_png, BinaryData::black_knob_small_150_pngSize);
	m_mod.setStrip(black_knob_small, N_KNOB_FRAMES);
	m_mod.setBounds(KNOB_POS_X, MOD_POS_Y, BLACK_KNOB_SMALL_SIZE_X * 1.5, BLACK_KNOB_SMALL_SIZE_Y * 1.5);

	m_transpose.setStrip(black_knob_small, N_KNOB_FRAMES);
	m_transpose.setBounds(KNOB_POS_X, TRANSPOSE_POS_Y, BLACK_KNOB_MID_SIZE_X * 1.5, BLACK_KNOB_MID_SIZE_Y * 1.5);

	juce::Image step_on_4 =
	    ImageCache::getFromMemory(BinaryData::button_arp_step_1_150_png, BinaryData::button_arp_step_1_150_pngSize);
	juce::Image step_on_2 =
	    ImageCache::getFromMemory(BinaryData::button_arp_step_2_150_png, BinaryData::button_arp_step_2_150_pngSize);
	juce::Image step_on_3 =
	    ImageCache::getFromMemory(BinaryData::button_arp_step_3_150_png, BinaryData::button_arp_step_3_150_pngSize);
	juce::Image step_on_1 =
	    ImageCache::getFromMemory(BinaryData::button_arp_step_4_150_png, BinaryData::button_arp_step_4_150_pngSize);

	juce::DrawableImage step_on_draw1;
	juce::DrawableImage step_on_draw2;
	juce::DrawableImage step_on_draw3;
	juce::DrawableImage step_on_draw4;

	step_on_draw1.setImage(step_on_1);
	step_on_draw2.setImage(step_on_2);
	step_on_draw3.setImage(step_on_3);
	step_on_draw4.setImage(step_on_4);

	m_step_on.setImages(&step_on_draw2,
	                    &step_on_draw2,
	                    &step_on_draw1,
	                    &step_on_draw1,
	                    &step_on_draw4,
	                    &step_on_draw4,
	                    &step_on_draw3,
	                    &step_on_draw3);
	m_step_on.setBounds(STEP_ON_X, STEP_ON_Y, step_on_1.getWidth(), step_on_1.getHeight());
}

void StepComponent::setGUISmall() {
}
