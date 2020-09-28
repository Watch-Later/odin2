#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define FX_BUTTON_OFFSET 61

class DragButton : public juce::DrawableButton {
public:
	DragButton(const String &buttonName,
	           ButtonStyle buttonStyle,
	           juce::ComponentBoundsConstrainer *constrainer,
	           std::string p_name) :
	    juce::DrawableButton(buttonName, buttonStyle) {
		m_constrainer = constrainer;
		m_button_name = p_name;
	}

	bool isInRangeDrag(float p_low, int p_check, float p_high) {
		return ((p_check >= p_low) && (p_check <= p_high));
	}
	void mouseDrag(const MouseEvent &event) override {
		juce::DrawableButton::mouseDrag(event);
		m_dragger.dragComponent(this, event, m_constrainer);
		//DBG(getX());
		float GUI_factor = m_GUI_big ? 1.5f : 1.f;

		if (isInRangeDrag(
		        0 * (float)FX_BUTTON_OFFSET * GUI_factor, getX(), 0.5f * FX_BUTTON_OFFSET * GUI_factor)) {
			lambdaMouseDrag(0);
			return;
		}

		if (isInRangeDrag(0.5f * (float)FX_BUTTON_OFFSET * GUI_factor, getX(), 1.5f * FX_BUTTON_OFFSET*
		    GUI_factor) ) {
			lambdaMouseDrag(1);
			return;
		}

		if (isInRangeDrag(1.5f * FX_BUTTON_OFFSET * GUI_factor, getX(), 2.5f * FX_BUTTON_OFFSET * GUI_factor)) {
			lambdaMouseDrag(2);
			return;
		}

		if (isInRangeDrag(2.5f * FX_BUTTON_OFFSET * GUI_factor, getX(), 3.f * FX_BUTTON_OFFSET* GUI_factor)) {
			lambdaMouseDrag(3);
			return;
		}
	}

	void mouseDown(const MouseEvent &event) override {
		juce::DrawableButton::mouseDown(event);
		setAlwaysOnTop(true);
		m_dragger.startDraggingComponent(this, event);
		lambdaMouseDown();
	}

	void mouseUp(const MouseEvent &event) override {
		juce::DrawableButton::mouseUp(event);
		setAlwaysOnTop(false);
		lambdaMouseUp();
	}

	// std::function lambdaMouseDown;
	std::function<void(int)> lambdaMouseDrag;
	std::function<void()> lambdaMouseUp;
	std::function<void()> lambdaMouseDown;

	void setGUIBig() {
		m_GUI_big = true;
	}
	void setGUISmall() {
		m_GUI_big = false;
	}

private:
	bool m_GUI_big = false;

	std::string m_button_name;
	juce::ComponentDragger m_dragger;
	juce::ComponentBoundsConstrainer *m_constrainer;
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DragButton)
};