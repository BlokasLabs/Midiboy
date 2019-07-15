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

#ifndef SH1106_H
#define SH1106_H

#include <stdint.h>

void sh1106_init();

// Called by init automatically.
void sh1106_reset();
void sh1106_clear();

void sh1106_set_scroll(uint8_t line);
void sh1106_add_scroll(int8_t delta);
uint8_t sh1106_get_scroll();

void sh1106_set_position(uint8_t x, uint8_t y_8); // Y is in count of 8 pixels. Scroll should be set before calling this function.
uint8_t sh1106_get_x();
uint8_t sh1106_get_y_8();

void sh1106_draw_bits(uint8_t pixels_1x8, uint16_t n, bool inverse); // n x 8 vertical line.
void sh1106_draw_bitmap(const void *data, uint16_t n, bool inverse); // Draw n x 8 pixels.
void sh1106_draw_progmem_bitmap(const void *data, uint16_t n, bool inverse); // Draw n x 8 pixels from PROGMEM memory.

void sh1106_set_contrast(uint8_t contrast);

#endif // SH1106_H
