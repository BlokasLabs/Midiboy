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
