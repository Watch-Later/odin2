/*
  ==============================================================================

    WaveformSelectorComponent.h
    Created: 1 Mar 2019 6:48:53pm
    Author:  frot

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GlobalIncludes.h"
#include "GlasDisplay.h"
#include <map>

#define N_SUBMENUS 5
//==============================================================================
/*
 */
class WaveformSelectorComponent : public Component
{
public:
  WaveformSelectorComponent(bool p_buttons_right);
  ~WaveformSelectorComponent();

  void paint(Graphics &) override;
  void resized() override;

  void setTooltip(const String p_text){
    m_display.setTooltip(p_text);
  }

  void setColor(juce::Colour p_color)
  {
    m_display.setColor(p_color);
  }

  void addWave(int p_index, std::string p_name)
  {
    m_menu.addItem(p_index, p_name);
    m_menu_map.insert(std::pair<int, std::string>(p_index, p_name));
    m_inc_map.insert(std::pair<int, int>(p_index, p_index + 1));
    m_dec_map.insert(std::pair<int, int>(p_index, p_index - 1));
  }

  void addWaveToSubmenu(int p_index, std::string p_name, int p_submenu)
  {
    if (p_submenu >= 0 && p_submenu < N_SUBMENUS)
    {
      m_submenu[p_submenu].addItem(p_index, p_name);
      m_menu_map.insert(std::pair<int, std::string>(p_index, p_name));
      m_inc_map.insert(std::pair<int, int>(p_index, p_index + 1));
      m_dec_map.insert(std::pair<int, int>(p_index, p_index - 1));
    }
  }

  void applySubmenu(int p_submenu, const std::string &p_name){
    if (p_submenu >= 0 && p_submenu < N_SUBMENUS)
    {
      m_menu.addSubMenu(p_name, m_submenu[p_submenu]);
    }
  }

  void setIncrementValue(int p_index, int p_next_value)
  {
    auto it = m_inc_map.find(p_index);
    if (it != m_inc_map.end())
    {
      m_inc_map.erase(it);
    }
    m_inc_map.insert(std::pair<int, int>(p_index, p_next_value));
  }

  void setDecrementValue(int p_index, int p_next_value)
  {
    auto it = m_dec_map.find(p_index);
    if (it != m_dec_map.end())
    {
      m_dec_map.erase(it);
    }
    m_dec_map.insert(std::pair<int, int>(p_index, p_next_value));
  }

  void setValue(int p_value)
  {
    auto it = m_menu_map.find(p_value);
    if (it != m_menu_map.end())
    {
      m_display.setText(it->second);
      m_value = p_value;
    }
  }

private:
  void increment()
  {
    auto it = m_inc_map.find(m_value);
    if (it != m_inc_map.end())
    {
      setValue(it->second);
    }
  }

  void decrement()
  {
    auto it = m_dec_map.find(m_value);
    if (it != m_dec_map.end())
    {
      setValue(it->second);
    }
  }

  GlasDisplay m_display;
  juce::PopupMenu m_menu;
  juce::PopupMenu m_submenu[N_SUBMENUS];
  std::map<int, std::string> m_menu_map; //to get string names from menu indices
  std::map<int, int> m_inc_map;          //which value to go to on increment()
  std::map<int, int> m_dec_map;          //which value to go to on decrement()

  juce::DrawableButton m_up;
  juce::DrawableButton m_down;

  int m_value = 0;
  bool m_buttons_right;
  int m_display_width;
  OdinMenuFeels m_menu_feels;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformSelectorComponent)
};
