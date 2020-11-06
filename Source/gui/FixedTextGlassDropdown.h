/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#pragma once

#include "GlassDropdown.h"

/**
 * @brief The same as a GlassDropdown, but always displays a static text.
 */
class FixedTextGlassDropdown : public GlassDropdown {
public:
	FixedTextGlassDropdown(const std::string &p_fixed_text);
	~FixedTextGlassDropdown() {
	}

	virtual void paint(Graphics &) override;

protected:
	std::string m_fixed_text;
};