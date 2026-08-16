#ifndef JSK_GRAPHICS_GRAPHICS_H
#define JSK_GRAPHICS_GRAPHICS_H

#include <stddef.h>
#include <stdint.h>

#include "JSK/BOOT/VBE.H"

void init_graphics (struct VBE_MODE_INFO *vmi);

void set_pixel (size_t x, size_t y, uint32_t color);
uint8_t get_pixel (size_t x, size_t y);

void clear_screen (uint32_t);

void draw_char (size_t x, size_t y, uint32_t color, char ch);
void draw_str (size_t x, size_t y, uint32_t color, const char *str,
               size_t len);
void draw_rect (size_t x, size_t y, size_t w, size_t h, uint32_t color);

#endif
