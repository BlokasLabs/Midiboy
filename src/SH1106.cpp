/*
 * Midichords - Midiboy Note To Chord sketch
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

#include "SH1106.h"

#include <pins_arduino.h>
#include <avr/pgmspace.h>

#include <SPI.h>
#include <stdint.h>

class Transaction
{
public:
	inline Transaction()
	{
		const SPISettings spiSettings(10000000, MSBFIRST, SPI_MODE0);
		digitalWrite(PIN_SPI_SS, LOW);
		SPI.beginTransaction(spiSettings);
	}

	inline ~Transaction()
	{
		digitalWrite(PIN_SPI_SS, HIGH);
		SPI.endTransaction();
	}
};

static uint8_t g_scroll;
static uint8_t g_x;
static uint8_t g_y_8;

// SH1106 does not wrap automatically, we do it in software. This function must not be called within an already opened Transaction.
static void nextPage()
{
	sh1106_set_position(0, g_y_8+1);
}

void sh1106_init()
{
	g_scroll = 0;
	g_x = 0;
	g_y_8 = 0;

	pinMode(PIN_SPI_SS, OUTPUT);
	pinMode(PIN_LCD_DC, OUTPUT);
	pinMode(PIN_LCD_RESET, OUTPUT);

	SPI.begin();

	sh1106_reset();
}

enum Mode
{
	COMMAND,
	DATA
};

inline static void sh1106_mode(Mode mode)
{
	digitalWrite(PIN_LCD_DC, mode == DATA);
}

inline static void sh1106_send(uint8_t byte)
{
	SPI.transfer(byte);
}

inline static void sh1106_set_scroll_line(uint8_t line)
{
	sh1106_send(0x40 | (line & 0x3f));
}

inline static void sh1106_set_column_address(uint8_t address)
{
	sh1106_send(address & 0x0f);
	sh1106_send(0x10 | (address >> 4));
}

inline static void sh1106_set_page_address(uint8_t address)
{
	sh1106_send(0xb0  | (address & 0x07));
}

inline static void sh1106_set_contrast_reg(uint8_t volume) // A.K.A. PM 
{
	sh1106_send(0x81);
	sh1106_send(volume);
}

inline static void sh1106_set_all_pixels_on(bool on)
{
	sh1106_send(0xa4 | (on ? 1 : 0));
}

inline static void sh1106_set_inverse_display(bool on)
{
	sh1106_send(0xa6 | (on ? 1 : 0));
}

inline static void sh1106_set_display_enable(bool on)
{
	sh1106_send(0xae | (on ? 1 : 0));
}

inline static void sh1106_set_mirror_x(bool on)
{
	sh1106_send(0xa0 | (on ? 1 : 0));
}

inline static void sh1106_set_mirror_y(bool on)
{
	sh1106_send(0xc0 | (on ? 0x08 : 0));
}

inline static void sh1106_nop()
{
	sh1106_send(0xe3);
}

void sh1106_reset()
{
	digitalWrite(PIN_LCD_RESET, LOW);
	delay(1);
	digitalWrite(PIN_LCD_RESET, HIGH);
	delay(5);

	g_scroll = 0;

	{
		Transaction t;

		sh1106_mode(COMMAND);
		sh1106_set_display_enable(false);
		sh1106_set_scroll_line(0);
		sh1106_set_mirror_x(true);
		sh1106_set_mirror_y(false);
		sh1106_set_contrast_reg(0xff);
	}

	sh1106_clear();

	{
		Transaction t;
		sh1106_mode(COMMAND);
		sh1106_set_display_enable(true);
	}
}

void sh1106_clear()
{
	sh1106_mode(DATA);
	Transaction t;

	for (int j=0; j<8; ++j)
	{
		sh1106_mode(COMMAND);
		sh1106_set_column_address(2);
		sh1106_set_page_address(j);

		sh1106_mode(DATA);
		for (int i=0; i<128; ++i)
		{
			sh1106_send(0);
		}
	}

	sh1106_set_scroll(0);
	sh1106_set_position(0, 0);
}

void sh1106_set_scroll(uint8_t line)
{
	g_scroll = line & 0x3f;
	sh1106_mode(COMMAND);
	Transaction t;
	sh1106_set_scroll_line(g_scroll);
}

void sh1106_add_scroll(int8_t delta)
{
	sh1106_set_scroll(g_scroll + delta);
}

uint8_t sh1106_get_scroll()
{
	return g_scroll;
}

void sh1106_set_position(uint8_t x, uint8_t y_8)
{
	x &= 0x7f;
	y_8 &= 7;
	g_x = x;
	g_y_8 = y_8;

	sh1106_mode(COMMAND);
	Transaction t;
	sh1106_set_column_address(x+2);
	sh1106_set_page_address((g_scroll >> 3) + y_8);
}

uint8_t sh1106_get_x()
{
	return g_x;
}

uint8_t sh1106_get_y_8()
{
	return g_y_8;
}

void sh1106_draw_space(uint8_t pixels_1x8, uint16_t n, bool inverse)
{
	uint8_t byte = !inverse ? pixels_1x8 : ~pixels_1x8;
	while (n != 0)
	{
		{
			sh1106_mode(DATA);
			Transaction t;
			uint8_t remaining = min(n, 128 - g_x);
			g_x += remaining;
			n -= remaining;
			while (remaining-- != 0)
			{
				sh1106_send(byte);
			}
		}

		if (g_x == 128)
			nextPage();
	}
}

void sh1106_draw_bitmap(const void *data, uint16_t n, bool inverse)
{
	const uint8_t *p = (const uint8_t*)data;
	if (!inverse)
	{
		while (n != 0)
		{
			{
				sh1106_mode(DATA);
				Transaction t;
				uint8_t remaining = min(n, 128 - g_x);
				g_x += remaining;
				n -= remaining;
				while (remaining-- != 0)
				{
					sh1106_send(*p++);
				}
			}

			if (g_x == 128)
				nextPage();
		}
	}
	else
	{
		while (n != 0)
		{
			{
				sh1106_mode(DATA);
				Transaction t;
				uint8_t remaining = min(n, 128 - g_x);
				g_x += remaining;
				n -= remaining;
				while (remaining-- != 0)
				{
					sh1106_send(~(*p++));
				}
			}

			if (g_x == 128)
				nextPage();
		}
	}
}

void sh1106_draw_progmem_bitmap(const void *data, uint16_t n, bool inverse)
{
	sh1106_mode(DATA);
	Transaction t;
	const uint8_t *p = (const uint8_t *)data;
	if (!inverse)
	{
		while (n != 0)
		{
			{
				sh1106_mode(DATA);
				Transaction t;
				uint8_t remaining = min(n, 128 - g_x);
				g_x += remaining;
				n -= remaining;
				while (remaining-- != 0)
				{
					uint8_t byte = pgm_read_byte(p++);
					sh1106_send(byte);
				}
			}

			if (g_x == 128)
				nextPage();
		}
	}
	else
	{
		while (n != 0)
		{
			{
				sh1106_mode(DATA);
				Transaction t;
				uint8_t remaining = min(n, 128 - g_x);
				g_x += remaining;
				n -= remaining;
				while (remaining-- != 0)
				{
					uint8_t byte = pgm_read_byte(p++);
					sh1106_send(~byte);
				}
			}

			if (g_x == 128)
				nextPage();
		}
	}
}

void sh1106_set_contrast(uint8_t contrast)
{
	sh1106_mode(COMMAND);
	Transaction t;
	sh1106_set_contrast_reg(contrast);
}
