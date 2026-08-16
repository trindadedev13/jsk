#include "JSK/GRAPHICS/GRAPHICS.H"

#include <stddef.h>
#include <stdint.h>

#include "JSK/BOOT/VBE.H"

struct VBE_MODE_INFO *video = NULL;

void
init_graphics (struct VBE_MODE_INFO *vmi)
{
        video = vmi;
}

void
set_pixel (size_t x, size_t y, uint32_t color)
{
        uint32_t *fb = (uint32_t *)video->framebuffer;
        fb[y * (video->pitch / 4) + x] = color;
}

uint8_t
get_pixel (size_t x, size_t y)
{
        uint32_t *fb = (uint32_t *)video->framebuffer;
        return fb[y * (video->pitch / 4) + x];
}

void
clear_screen (uint32_t color)
{
        size_t y, x;
        for (y = 0; y < video->height; ++y)
                for (x = 0; x < video->width; ++x)
                        set_pixel (x, y, color);
}

void
draw_char (size_t x, size_t y, uint32_t color, char ch)
{
}

void
draw_str (size_t x, size_t y, uint32_t color, const char *str, size_t len)
{
}

void
draw_rect (size_t x, size_t y, size_t w, size_t h, uint32_t color)
{
        size_t cx, cy;
        for (cy = y; cy < y + h; ++cy)
        {
                for (cx = x; cx < x + w; ++cx)
                {
                        set_pixel (cx, cy, color);
                }
        }
}
