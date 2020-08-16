#include "PatchBrowserSelector.h"
#include <JuceHeader.h>

PatchBrowserSelector::PatchBrowserSelector(File::TypesOfFileToFind p_file_or_dir,
                                           String p_left_button,
                                           String p_mid_button,
                                           String p_right_button) :
    m_file_or_dir(p_file_or_dir) {

	m_scroll_bar.reportMouseDrag = [&](float p_delta_y) {
		if (fabs(m_available_scroll_height - m_scroll_bar_height) >= 1) {
			m_scroll_position = (p_delta_y * m_max_scroll_position) / (m_available_scroll_height - m_scroll_bar_height);

			enforceScrollLimits();
			positionEntries();
			repaint();
		}
	};

	m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_RENAME, "Rename");
	m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_DELETE, "Delete");
	m_menu.setLookAndFeel(&m_menu_feels);

	addChildComponent(m_input_field);
	m_input_field.setAlwaysOnTop(true);

	if (p_left_button != "") {
		addAndMakeVisible(m_left_button);
		m_left_button.setButtonText(p_left_button);
		m_show_left_button = true;
		m_left_button.setLookAndFeel(&m_button_feels);
		m_left_button.setAlwaysOnTop(true);
		m_left_button.onClick = [&]() { onImport(getDirectory()); };
	}
	if (p_mid_button != "") {
		addAndMakeVisible(m_mid_button);
		m_mid_button.setButtonText(p_mid_button);
		m_show_mid_button = true;
		m_mid_button.setLookAndFeel(&m_button_feels);
		m_mid_button.setAlwaysOnTop(true);
		m_mid_button.onClick = [&]() { onExport(getDirectory()); };
	}
	addAndMakeVisible(m_right_button);
	m_right_button.setButtonText(p_right_button);
	m_right_button.setLookAndFeel(&m_button_feels);
	m_right_button.setAlwaysOnTop(true);
	m_right_button.onClick = [&]() {
		if (m_input_field_active) {
			applyInputField();
		} else {
			//resetInputFieldAndShow();
			showInputField();
		}
	};

	//m_input_field.onFocusLost = [&]() { hideInputField(); };
	m_input_field.setColour(TextEditor::ColourIds::backgroundColourId, PATCH_BROWSER_INPUT_FIELD_BACKGROUND_COLOR);
	m_input_field.onEscapeKey = [&]() { hideInputField(); };
	m_input_field.onReturnKey = [&]() { applyInputField(); };

	addAndMakeVisible(m_scroll_bar);
	m_scroll_bar.setAlwaysOnTop(true);
}

PatchBrowserSelector::~PatchBrowserSelector() {
	m_menu.setLookAndFeel(nullptr);

	m_left_button.setLookAndFeel(nullptr);
	m_mid_button.setLookAndFeel(nullptr);
	m_right_button.setLookAndFeel(nullptr);
}

void PatchBrowserSelector::paint(Graphics &g) {
	g.fillAll(MODMATRIX_COLOR); // clear the background
	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1); // draw an outline around the component

#define WARNING_COLOR ODIN_BLUE

	switch (m_directory_status) {
	case DirectoryStatus::Nonexistent: {
		g.setColour(WARNING_COLOR);
		float font_size = m_GUI_big ? 17.f : 13.f;
		float inlay_x   = m_GUI_big ? WARNING_INLAY_X_150 : WARNING_INLAY_X_100;
		float offset_y  = m_GUI_big ? WARNING_OFFSET_Y_150 : WARNING_OFFSET_Y_100;
		g.setFont(font_size);
		g.drawMultiLineText(
		    m_nonexistent_text, inlay_x, font_size + offset_y, getWidth() - 2 * inlay_x, Justification::centred, 5.f);
	} break;

	case DirectoryStatus::Empty: {
		g.setColour(WARNING_COLOR);
		float font_size = m_GUI_big ? 17.f : 13.f;
		float inlay_x   = m_GUI_big ? WARNING_INLAY_X_150 : WARNING_INLAY_X_100;
		float offset_y  = m_GUI_big ? WARNING_OFFSET_Y_150 : WARNING_OFFSET_Y_100;
		g.setFont(font_size);
		g.drawMultiLineText(
		    m_empty_text, inlay_x, font_size + offset_y, getWidth() - 2 * inlay_x, Justification::centred, 5.f);
	} break;
	}
}

void PatchBrowserSelector::applyInputField() {

	if (m_input_field.getText().isEmpty()) {
		AlertWindow::showMessageBox(AlertWindow::AlertIconType::WarningIcon,
		                            "No name provided!",
		                            "Please enter a name into the text field!",
		                            "Jeeez, okay...");
	} else {
		onCreateNewFile(getDirectory() + File::getSeparatorString() + m_input_field.getText());
		m_input_field_active = false;
		hideInputField();
	}
}

void PatchBrowserSelector::resetInputFieldAndShow() {
	m_input_field.clear();
	m_input_field.setVisible(true);
	m_input_field.grabKeyboardFocus();
	m_input_field_active = true;
}

void PatchBrowserSelector::showInputField() {
	m_input_field.setVisible(true);
	m_input_field.grabKeyboardFocus();
	m_input_field_active = true;
}

void PatchBrowserSelector::hideInputField() {
	m_input_field.setVisible(false);
	m_input_field_active = false;
}

void PatchBrowserSelector::setGUIBig() {
	m_GUI_big = true;

	m_menu_feels.setWidth(200);
	m_menu_feels.setFontSize(18);
	m_button_feels.setButtonFontSize(17.f);

	m_left_button.setBounds(0, getHeight() - BUTTON_HEIGHT_BROWSER_150, getWidth() / 3, BUTTON_HEIGHT_BROWSER_150);
	m_mid_button.setBounds(
	    getWidth() / 3, getHeight() - BUTTON_HEIGHT_BROWSER_150, getWidth() / 3, BUTTON_HEIGHT_BROWSER_150);
	m_right_button.setBounds(
	    getWidth() * 2 / 3, getHeight() - BUTTON_HEIGHT_BROWSER_150, getWidth() / 3, BUTTON_HEIGHT_BROWSER_150);

	m_input_field.setBounds(0, getHeight() - BUTTON_HEIGHT_BROWSER_150, getWidth() / 3 * 2, BUTTON_HEIGHT_BROWSER_150);
	m_input_field.setFont(Font(17.f));

	regenerateContent();
	resetScrollPosition();
	positionEntries();
}

void PatchBrowserSelector::setGUISmall() {
	m_GUI_big = false;

	m_menu_feels.setWidth(170.f);
	m_menu_feels.setFontSize(16.f);
	m_button_feels.setButtonFontSize(14.f);

	m_left_button.setBounds(0,
	                        BROWSER_SIZE_Y - BUTTON_HEIGHT_BROWSER - 2 * BROWSER_INLAY_Y - 2,
	                        getWidth() / 3,
	                        BUTTON_HEIGHT_BROWSER + BROWSER_INLAY_Y - 4);

	m_mid_button.setBounds(getWidth() / 3,
	                       BROWSER_SIZE_Y - BUTTON_HEIGHT_BROWSER - 2 * BROWSER_INLAY_Y - 2,
	                       getWidth() / 3,
	                       BUTTON_HEIGHT_BROWSER + BROWSER_INLAY_Y - 4);
	m_right_button.setBounds(getWidth() * 2 / 3,
	                         BROWSER_SIZE_Y - BUTTON_HEIGHT_BROWSER - 2 * BROWSER_INLAY_Y - 2,
	                         getWidth() / 3,
	                         BUTTON_HEIGHT_BROWSER + BROWSER_INLAY_Y - 4);

	m_input_field.setBounds(0,
	                        BROWSER_SIZE_Y - BUTTON_HEIGHT_BROWSER - 2 * BROWSER_INLAY_Y - 2,
	                        getWidth() / 3 * 2,
	                        BUTTON_HEIGHT_BROWSER + BROWSER_INLAY_Y - 4);
	m_input_field.setFont(Font(17.f));

	regenerateContent();
	resetScrollPosition();
	positionEntries();
}

void PatchBrowserSelector::setWildCard(String p_wildcard) {
	m_wildcard = p_wildcard;
}

void PatchBrowserSelector::setDirectory(String p_absolute_path) {

	m_absolute_path = p_absolute_path;

	DBG("Set path to " + m_absolute_path);

	resetScrollPosition();
	regenerateContent();

	bool exists = File(p_absolute_path).isDirectory();
	showButtons(exists);

	if (m_copy_move_enabled) {
		recreatePopupMenu();
	}
}

void PatchBrowserSelector::recreatePopupMenu() {
	m_menu.clear();
	m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_RENAME, "Rename");
	m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_DELETE, "Delete");

	File file(m_absolute_path);
	if (file.exists()) {
		PopupMenu m_move_menu;
		PopupMenu m_copy_menu;

		auto parent = file.getParentDirectory();

		auto siblings = parent.findChildFiles(File::TypesOfFileToFind::findDirectories, false);
		siblings.sort(m_file_comparator);

		String current_dir = file.getFileName();
		m_copy_move_map.clear();

		for (int i = 0; i < siblings.size(); ++i) {
			if (siblings[i].getFileName() != current_dir) {
				m_move_menu.addItem(PATCH_BROWSER_MENU_MOVE_OFFSET + i, siblings[i].getFileName());
				m_copy_menu.addItem(PATCH_BROWSER_MENU_COPY_OFFSET + i, siblings[i].getFileName());

				m_copy_move_map.insert(std::make_pair(i, siblings[i].getFileName()));
			}
		}

		if (m_move_menu.getNumItems() > 0) {
			m_menu.addSubMenu("Move to " + m_copy_target_name, m_move_menu);
			m_menu.addSubMenu("Copy to " + m_copy_target_name, m_copy_menu);
		} else {
			m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_RENAME, "Move to " + m_copy_target_name, false);
			m_menu.addItem(PATCH_BROWSER_MENU_ENTRY_RENAME, "Copy to " + m_copy_target_name, false);
		}
		DBG("---");
	}
}

String PatchBrowserSelector::getCopyFileString(int p_popupmenu_index) {
	return getCopyMoveMap(p_popupmenu_index - PATCH_BROWSER_MENU_COPY_OFFSET);
}

String PatchBrowserSelector::getMoveFileString(int p_popupmenu_index) {
	return getCopyMoveMap(p_popupmenu_index - PATCH_BROWSER_MENU_MOVE_OFFSET);
}

String PatchBrowserSelector::getCopyMoveMap(int p_index) {

	auto it = m_copy_move_map.find(p_index);
	if (it != m_copy_move_map.end()) {
		return it->second;
	}
	return "";
}

void PatchBrowserSelector::checkDirectoryStatus() {
	if (!File(m_absolute_path).isDirectory()) {
		m_directory_status = DirectoryStatus::Nonexistent;
	} else if (m_entries.size() == 0) {
		m_directory_status = DirectoryStatus::Empty;
	} else {
		m_directory_status = DirectoryStatus::Ok;
	}
}

void PatchBrowserSelector::showButtons(bool p_show) {
	m_right_button.setVisible(p_show);
}

void PatchBrowserSelector::regenerateContent() {
	generateContent();
	repaint();
}

void PatchBrowserSelector::generateContent() {

	removeAllChildren();
	m_entries.clear();

	//add the buttons again
	if (m_show_left_button) {
		addAndMakeVisible(m_left_button);
	}
	if (m_show_mid_button) {
		addAndMakeVisible(m_mid_button);
	}
	addAndMakeVisible(m_right_button);
	addChildComponent(m_input_field);

	File current_dir(m_absolute_path);
	if (current_dir.isDirectory()) {

		Array<File> file_array = current_dir.findChildFiles(m_file_or_dir, false, m_wildcard);
		if (file_array.size() > 0) {

			file_array.sort(m_file_comparator);

			for (int file_index = 0; file_index < file_array.size(); ++file_index) {
				m_entries.push_back(std::make_unique<BrowserEntry>(
				    file_array[file_index].getFileName().dropLastCharacters((int)m_wildcard.length() - 1), m_GUI_big));
				if (m_pass_active_element_to_parent) {
					m_entries[m_entries.size() - 1]->enablePassActiveNameToParent(true);
					m_entries[m_entries.size() - 1]->passActiveNameToParent = [&](String p_name) {
						m_input_field.setText(p_name);
					};
				}
				String return_string               = file_array[file_index].getFileName();
				m_entries[file_index]->onLeftClick = [&, return_string]() {
					//DBG(return_string + " was clicked!");
					passValueToPatchBrowser(return_string);
					unhighlightAllEntries();
				};
				m_entries[file_index]->onRightClick = [&, return_string, file_index]() {
					int selected = m_menu.show();

					if (selected == PATCH_BROWSER_MENU_ENTRY_DELETE) {
						passDeleteToPatchBrowser(return_string);
					} else if (selected == PATCH_BROWSER_MENU_ENTRY_RENAME) {
						m_entries[file_index]->showRenameEditor();
					} else if (selected >= PATCH_BROWSER_MENU_MOVE_OFFSET &&
					           selected < PATCH_BROWSER_MENU_COPY_OFFSET) {
						onMove(m_entries[file_index]->getText(), getMoveFileString(selected));
					} else if (selected >= PATCH_BROWSER_MENU_COPY_OFFSET) {
						onCopy(m_entries[file_index]->getText(), getCopyFileString(selected));
					}
				};
				m_entries[file_index]->applyRenaming = [&](String p_old_name, String p_new_name) {
					applyRenamingSelector(getDirectory(), p_old_name, p_new_name);
				};
			}

			for (int entry = 0; entry < m_entries.size(); ++entry) {
				addAndMakeVisible(*(m_entries[entry].get()));
			}

			positionEntries();

			//show scrollbar only if needed
			if (fabs(m_available_scroll_height - m_scroll_bar_height) >= 1) {
				addAndMakeVisible(m_scroll_bar);
			}

		} else {
			//no files in current dir
		}
	} else {
		//no dir??? whatever, open filebrowser
	}

	checkDirectoryStatus();
}

void PatchBrowserSelector::positionEntries() {
	int entry_height = m_GUI_big ? ENTRY_HEIGHT_150 : ENTRY_HEIGHT_100;
	for (int entry = 0; entry < m_entries.size(); ++entry) {
		m_entries[entry]->setBoundsWithInputField(
		    0, m_scroll_position + entry_height * entry, getWidth(), entry_height);
	}

	auto scroll_bar_width = m_GUI_big ? SCROLL_BAR_WIDTH_150 : SCROLL_BAR_WIDTH_100;

	m_available_scroll_height = getHeight() - entry_height;
	m_scroll_bar_height       = m_available_scroll_height * getHeight() / (m_entries.size() * entry_height);
	m_scroll_bar_height =
	    m_scroll_bar_height > m_available_scroll_height ? m_available_scroll_height : m_scroll_bar_height;

	m_max_scroll_position = (m_entries.size() + 1) * entry_height -
	                        getHeight(); // + 1 because we leave 1 space at the bottom for the buttons
	m_scroll_bar_position =
	    -m_scroll_position / m_max_scroll_position * (m_available_scroll_height - m_scroll_bar_height);

	m_scroll_bar.setBounds(getWidth() - scroll_bar_width, m_scroll_bar_position, scroll_bar_width, m_scroll_bar_height);
}

void PatchBrowserSelector::resetScrollPosition() {
	m_scroll_position = 0.f;
}

void PatchBrowserSelector::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {

	if (m_GUI_big) {
		m_scroll_position += wheel.deltaY * MOUSE_WHEEL_FACTOR_PATCH_BROWSER_150;
	} else {
		m_scroll_position += wheel.deltaY * MOUSE_WHEEL_FACTOR_PATCH_BROWSER_100;
	}

	enforceScrollLimits();

	Component::mouseWheelMove(event, wheel);

	positionEntries();
	repaint();
}

void PatchBrowserSelector::enforceScrollLimits() {
	m_scroll_position       = m_scroll_position > 0.f ? 0.f : m_scroll_position;
	int entry_height_single = m_GUI_big ? ENTRY_HEIGHT_150 : ENTRY_HEIGHT_100;
	float entry_height      = m_entries.size() * entry_height_single;

	float bottom      = entry_height + m_scroll_position;
	int button_height = m_GUI_big ? BUTTON_HEIGHT_BROWSER_150 : BUTTON_HEIGHT_BROWSER;
	if (bottom < getHeight() - button_height) {
		m_scroll_position -= (bottom - getHeight() + button_height);
		m_scroll_position = m_scroll_position > 0.f ? 0.f : m_scroll_position;
	}
}

String PatchBrowserSelector::getDirectory() {
	return m_absolute_path;
}

String PatchBrowserSelector::getFirstSubDirectoryAndHighlightIt() {
	resetScrollPosition();
	if (m_entries.size() > 0) {
		m_entries[0]->setEntryActive(true);
		return getDirectory() + File::getSeparatorString() + m_entries[0]->getText();
		//repaint();
	} else {
		return "";
	}
}

String PatchBrowserSelector::getSubDirectoryAndHighlightItFromName(String p_name) {

	File file(p_name);
	String name = file.getFileNameWithoutExtension();

	unhighlightAllEntries();

	for (int entry = 0; entry < m_entries.size(); ++entry) {
		if (m_entries[entry]->getText() == name) {
			m_entries[entry]->setEntryActive(true);

			int entry_height_single = m_GUI_big ? ENTRY_HEIGHT_150 : ENTRY_HEIGHT_100;
			float entry_position    = entry * entry_height_single;
			m_scroll_position       = -entry_position + getHeight() / 2.f;

			enforceScrollLimits();
			positionEntries();

			return getDirectory() + File::getSeparatorString() + m_entries[entry]->getText();
			//repaint();
		}
	}

	//fallback if none was found
	return getFirstSubDirectoryAndHighlightIt();
}

void PatchBrowserSelector::unhighlightAllEntries() {
	for (int entry = 0; entry < m_entries.size(); ++entry) {
		m_entries[entry]->setEntryActive(false);
	}
}

void PatchBrowserSelector::setButtonTooltips(String p_left, String p_mid, String p_right) {
	m_left_button.setTooltip(p_left);
	m_mid_button.setTooltip(p_mid);
	m_right_button.setTooltip(p_right);
}

void PatchBrowserSelector::setWarningTexts(String p_empty, String p_nonexistent) {
	m_empty_text       = p_empty;
	m_nonexistent_text = p_nonexistent;
}

void PatchBrowserSelector::setCopyTargetName(String p_name) {
	m_copy_target_name = p_name;
}

void PatchBrowserSelector::setCopyMoveEnabled(bool p_enabled) {
	m_copy_move_enabled = p_enabled;
}

void PatchBrowserSelector::enablePassActiveNameToParent(bool p_enable) {
	m_pass_active_element_to_parent = p_enable;
}

// void PatchBrowserSelector::focusLost(FocusChangeType p_cause){
// 	//this doesnt do anything?
// 	DBG("FOCUS LOST!!");
// 	//hideInputField();
// 	Component::focusLost(p_cause);
// }