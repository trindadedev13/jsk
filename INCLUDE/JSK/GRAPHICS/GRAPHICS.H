#ifndef JSK_GRAPHICS_GRAPHICS_H
#define JSK_GRAPHICS_GRAPHICS_H

#include <stddef.h>
#include <stdint.h>

#include "JSK/BOOT/VBE.H"

typedef struct font_t
{
        uint8_t *data;
        uint32_t width;
        uint32_t height;
        uint32_t glyph;
} Font;

uint32_t color (uint8_t, uint8_t, uint8_t);

Font *get_default_font (void);

void init_graphics (VbeModeInfo*vmi, Font *);

void set_pixel (size_t x, size_t y, uint32_t color);
uint32_t get_pixel (size_t x, size_t y);

void clear_screen (uint32_t);

void draw_char (size_t x, size_t y, uint32_t color, char ch);
void draw_char_ex (size_t x, size_t y, uint32_t color, Font *, char ch);

void draw_str (size_t x, size_t y, uint32_t color, const char *str,
               size_t len);

void draw_str_ex (size_t x, size_t y, uint32_t color, Font *, const char *str,
               size_t len);

void draw_rect (size_t x, size_t y, size_t w, size_t h, uint32_t color);

#endif
