#include "JSK/GRAPHICS/GRAPHICS.H"

#include <stddef.h>
#include <stdint.h>

#include "JSK/BOOT/VBE.H"

typedef struct graphics_context_t
{
    VbeModeInfo *vbe;
    Font *font;
} GraphicsContext;

GraphicsContext ctx;

// Default font
extern int S1_FONT_WIDTH;
extern int S1_FONT_HEIGHT;
extern int S1_FONT_GLYPH;
extern uint8_t S1_FONT[];

void
init_graphics (VbeModeInfo *vmi, Font *font)
{
    ctx.vbe = vmi;
    ctx.font = font;
    if (!ctx.font)
        ctx.font = get_default_font ();
}

uint32_t
color (uint8_t r, uint8_t g, uint8_t b)
{
    return (((uint32_t)r << ctx.vbe->red_position)
            | ((uint32_t)g << ctx.vbe->green_position)
            | ((uint32_t)b << ctx.vbe->blue_position));
}

Font *
get_default_font (void)
{
    static Font f;
    f.data = S1_FONT;
    f.width = S1_FONT_WIDTH;
    f.height = S1_FONT_HEIGHT;
    f.glyph = S1_FONT_GLYPH;
    return &f;
}

void
set_pixel (size_t x, size_t y, uint32_t color)
{
    uint32_t *fb = (uint32_t *)ctx.vbe->framebuffer;
    fb[x + (y * ctx.vbe->pitch / 4)] = color;
}

uint32_t
get_pixel (size_t x, size_t y)
{
    uint32_t *fb = (uint32_t *)ctx.vbe->framebuffer;
    return fb[x + (y * ctx.vbe->pitch / 4)];
}

void
clear_screen (uint32_t color)
{
    size_t y, x;
    for (y = 0; y < ctx.vbe->height; ++y)
        for (x = 0; x < ctx.vbe->width; ++x)
            set_pixel (x, y, color);
}

void
draw_char (size_t x, size_t y, uint32_t color, char ch)
{
    draw_char_ex (x, y, color, ctx.font, ch);
}

#define BYTES_PER_ROW(font) (((font)->width + 7) / 8)
#define GLYPH_SIZE(font) (BYTES_PER_ROW (font) * (font)->height)
void
draw_char_ex (size_t x, size_t y, uint32_t color, Font *font, char ch)
{
    size_t cy, cx;
    uint8_t *bm = font->data + (unsigned char)ch * GLYPH_SIZE (font);

    for (cy = 0; cy < font->height; ++cy)
    {
        for (cx = 0; cx < font->width; ++cx)
        {
            int byte = cx / 8;
            int bit = 7 - (cx % 8);
            if (bm[cy * BYTES_PER_ROW (font) + byte] & (1 << bit))
                set_pixel (x + cx, y + cy, color);
        }
    }
}

void
draw_str (size_t x, size_t y, uint32_t color, const char *str, size_t len)
{
    draw_str_ex (x, y, color, ctx.font, str, len);
}

void
draw_str_ex (size_t x, size_t y, uint32_t color, Font *font, const char *str,
             size_t len)
{
    size_t i;
    size_t cx = x;
    for (i = 0; i < len; i++)
    {
        char ch = str[i];
        draw_char_ex (cx, y, color, font, ch);
        cx += font->width;
    }
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
