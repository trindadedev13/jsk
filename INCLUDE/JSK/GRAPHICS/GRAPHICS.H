#ifndef JSK_GRAPHICS_GRAPHICS_H
#define JSK_GRAPHICS_GRAPHICS_H

#include <stddef.h>
#include <stdint.h>

#include "JSK/GRAPHICS/FONT.H"

#define VESA_WIDTH 640
#define VESA_HEIGHT 480
#define VESA_MEMORY 0xFD000000UL

static uint8_t *vesa_fb = (uint8_t *)VESA_MEMORY;

enum
{
        COLOR_BLACK = 0x00,
        COLOR_DARK_BLUE,
        COLOR_DARK_GREEN,
        COLOR_DARK_CYAN,
        COLOR_DARK_RED,
        COLOR_DARK_MAGENTA,
        COLOR_BROWN,
        COLOR_LIGHT_GRAY,
        COLOR_DARK_GRAY,
        COLOR_BLUE,
        COLOR_GREEN,
        COLOR_CYAN,
        COLOR_RED,
        COLOR_MAGENTA,
        COLOR_YELLOW,
        COLOR_WHITE
};

static __attribute__ ((unused)) void
set_pixel (size_t x, size_t y, uint8_t color)
{
        vesa_fb[y * VESA_WIDTH + x] = color;
}

static __attribute__ ((unused)) uint8_t
get_pixel (size_t x, size_t y)
{
        return vesa_fb[y * VESA_WIDTH + x];
}

void clear_screen (void);

void draw_bitmap (size_t x, size_t y, const uint8_t *bitmap, uint8_t color);
void draw_char (size_t x, size_t y, uint8_t color, char ch);

void draw_str (size_t x, size_t y, uint8_t color, const char *str, size_t len);

#endif
