/*
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

#ifndef MIDIBOY_FONTS_H
#define MIDIBOY_FONTS_H

#include <avr/pgmspace.h>

#include <stdint.h>

// Declares a Font class with WIDTH, HEIGHT, SIZE and DATA_P constants. Should be placed used header (.h) files.
#define MIDIBOY_DECLARE_FONT(FontClass, w, h, bytes) \
	class FontClass \
	{ \
	public: \
		static const uint8_t WIDTH = w;            /* Width of a character. */ \
		static const uint8_t HEIGHT = h;           /* Height of a character. */ \
		static const uint16_t SIZE = bytes;        /* Size in bytes. */ \
		static const PROGMEM uint8_t DATA_P[SIZE]; /* P stands for PROGMEM, used a reminder that the data needs to be read using pgm_read_* APIs from avr/pgmspace.h. */ \
	}

// Defines the Font data. Should be used in C++ (.cpp) files.
#define MIDIBOY_DEFINE_FONT(FontClass) \
	const PROGMEM uint8_t FontClass::DATA_P[FontClass::SIZE] =

// Built-in fonts.
MIDIBOY_DECLARE_FONT(FONT_MICRO, 3, 5, 288); // 3x5 Font data based on X11 micro which is available as Public Domain font: https://github.com/olikraus/u8g2/wiki/fntgrpx11#micro, https://cgit.freedesktop.org/xorg/font/micro-misc/tree/COPYING
MIDIBOY_DECLARE_FONT(FONT_5X7,   5, 7, 475); // 5x7 Font data based on X11 5x7 font which is available as Public Domain font: https://gitlab.freedesktop.org/xorg/font/misc-misc, https://gitlab.freedesktop.org/xorg/font/misc-misc/blob/master/COPYING

#endif // MIDIBOY_FONTS_H
