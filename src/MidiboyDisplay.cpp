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

#include "MidiboyDisplay.h"

#include "SH1106.h"

void MidiboyDisplay::begin()
{
	sh1106_init();
}

void MidiboyDisplay::setDrawPosition(uint8_t x, uint8_t y_8)
{
	sh1106_set_position(x, y_8);
}

uint8_t MidiboyDisplay::getDrawPositionX() const
{
	return sh1106_get_x();
}

uint8_t MidiboyDisplay::getDrawPositionY_8() const
{
	return sh1106_get_y_8();
}

void MidiboyDisplay::setVerticalScroll(uint8_t line)
{
	sh1106_set_scroll(line);
}

void MidiboyDisplay::addVerticalScroll(int8_t delta)
{
	sh1106_add_scroll(delta);
}

uint8_t MidiboyDisplay::getVerticalScroll() const
{
	return sh1106_get_scroll();
}

void MidiboyDisplay::drawSpace(uint16_t n, bool inverse)
{
	sh1106_draw_bits(0x00, n, inverse);
}

void MidiboyDisplay::drawBits(uint8_t pixels_1x8, uint16_t n, bool inverse)
{
	sh1106_draw_bits(pixels_1x8, n, inverse);
}

void MidiboyDisplay::drawBitmap(const void * data, uint16_t n, bool inverse)
{
	sh1106_draw_bitmap(data, n, inverse);
}

void MidiboyDisplay::drawBitmap_P(const void * data, uint16_t n, bool inverse)
{
	sh1106_draw_progmem_bitmap(data, n, inverse);
}

void MidiboyDisplay::clearScreen()
{
	sh1106_clear();
}
