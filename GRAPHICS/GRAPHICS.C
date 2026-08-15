#include "JSK/GRAPHICS/GRAPHICS.H"

#include <stddef.h>

void
clear_screen (void)
{
        size_t x;
        size_t y;

        for (y = 0; y < VESA_HEIGHT; ++y)
        {
                for (x = 0; x < VESA_WIDTH; ++x)
                {
                        set_pixel (x, y, COLOR_BLACK);
                }
        }
}

void
draw_bitmap (size_t x, size_t y, const uint8_t *bitmap, uint8_t color)
{
        size_t cx;
        size_t cy;

        for (cy = 0; cy < FONT_HEIGHT; ++cy)
        {
                for (cx = 0; cx < FONT_WIDTH; ++cx)
                {
                        if (bitmap[cy] & (1u << (FONT_WIDTH - 1 - cx)))
                        {
                                set_pixel (x + cx, y + cy, color);
                        }
                }
        }
}

void
draw_char (size_t x, size_t y, uint8_t color, char ch)
{
        const uint8_t *bitmap;

        bitmap = FONT + ((unsigned char)ch * FONT_HEIGHT);

        draw_bitmap (x, y, bitmap, color);
}

void
draw_str (size_t x, size_t y, uint8_t color, const char *str, size_t len)
{
        size_t i;
        size_t font_x;

        font_x = x;

        for (i = 0; i < len; ++i)
        {
                draw_char (font_x, y, color, str[i]);
                font_x += FONT_WIDTH;
        }
}
