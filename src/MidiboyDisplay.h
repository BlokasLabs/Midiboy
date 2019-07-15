/*
 * Midiboy Core Library.
 * Copyright (C) 2019  Vilniaus Blokas UAB, https://blokas.io/midiboy
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2 of the
 * License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef MIDIBOY_DISPLAY_H
#define MIDIBOY_DISPLAY_H

#include <stdint.h>

// MidiboyDisplay implements basic drawing operations for a 128x64 screen.
// The drawing operations work with vertical blocks of 1x8 pixels at a time,
// so the Y coordinate in the API is for the vertical block to use, it must be
// in range [0;7]. For example, 3 is for vertical block of pixels in lines [24;31].
//
// If the drawing operation exceeds 128 pixel width, it will get wrapped automatically
// to the beginning of the next vertical block.
//
// Given the memory layout of vertical blocks, it is optimal to align the graphics
// to fit within the 8 line block, otherwise, updating multiple pages would be necessary.
// This class is meant to provide a basic interface for a display with this kind of layout,
// a more advanced class that reuses the provided interfaces could be built on top, to
// provide freeform graphics API.
class MidiboyDisplay
{
public:
	void begin();

	// Set the position to draw at, x should be a value within [0;127] range, and y_8 should be in range [0;7] - see MidiboyDisplay overview for an explanation.
	// Scroll should be set first, before calling this function.
	void setDrawPosition(uint8_t x, uint8_t y_8);
	uint8_t getDrawPositionX() const;
	uint8_t getDrawPositionY_8() const;

	// The line argument can be any value between [0;63]. Recommended to scroll by 8 lines (single vertical block), unless you handle updating inter-block drawing and offsetting data yourself.
	void setVerticalScroll(uint8_t line);
	void addVerticalScroll(int8_t delta);
	uint8_t getVerticalScroll() const;

	// Draw n x 8 pixels of empty (inverse = false) or filled (inverse = true) space at current drawing position, repeated n times.
	void drawSpace(uint16_t n, bool inverse);

	// Draw same 1 x 8 pixels at current drawing position, repeated n times.
	void drawBits(uint8_t pixels_1x8, uint16_t n, bool inverse);

	// Draw n x 8 pixels at current drawing position.
	void drawBitmap(const void *data, uint16_t n, bool inverse);

	// Same as drawBitmap, but for use with const PROGMEM data.
	void drawBitmap_P(const void *data, uint16_t n, bool inverse);

	// Clear the screen. Resets scroll to 0 and draw position to 0, 0.
	void clearScreen();
};

#endif // MIDIBOY_DISPLAY_H
