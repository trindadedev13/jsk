#include "Graphics/Graphics.h"

#include <stddef.h>
#include <stdint.h>

@implementation GSContext

- (id)initWithSurface:(GSSurface *)surface font:(GSFont *)font
{
    self = [super init];
    if (self)
    {
        _surface = surface;
        _font = font;
    }
    return self;
}

- (GSSurface *)surface { return _surface; }
- (GSFont *)font { return _font; };

- (void)setFont: (GSFont *)font
{
    if (font)
        _font = font;
}

- (Color)rgb:(uint8_t)r g:(uint8_t)g b:(uint8_t)b
{
    return [_surface rgb:r g:g b:b];
}

- (void)clear:(Color)color
{
     size_t width = [_surface width];
     size_t height = [_surface height];
     for (size_t y = 0; y < height; y++)
        for (size_t x = 0; x < width; x++)
            [_surface setPixelAtX:x y:y color:color];
}

- (void)setPixelAtX: (size_t)x y:(size_t)y color:(Color)color
{
    [_surface setPixelAtX:x y:y color:color];
}


- (Color)getPixelAtX: (size_t)x y:(size_t)y
{
    return [_surface getPixelAtX:x y:y];
}

- (void)drawChar: (char)ch x:(size_t)x y:(size_t)y color:(Color)color
{
    [self drawChar:ch x:x y:y color:color font:_font];
}

- (void)drawChar: (char)ch x:(size_t)x y:(size_t)y color:(Color)color font:(GSFont *)font
{
    uint8_t *data = [font data];
    size_t width = [font width];
    size_t height = [font height];
    size_t bytes_per_row = [font bytesPerRow];
    size_t glyph_size = [font glyphSize];
    uint8_t *bitmap = data + ((unsigned char)ch * glyph_size);
    for (size_t cy = 0; cy < height; cy++)
        for (size_t cx = 0; cx < width; cx++)
        {
            size_t byte = cx = 8;
            size_t bit = 7 - (cx & 8);
            if (bitmap[cy * bytes_per_row + byte] & (1 << bit))
            {
                [_surface setPixelAtX:x+cx y:y+cy color:color];
            }
        }
}

- (void)drawString: (const char *)str x:(size_t)x y:(size_t)y color:(Color)color len:(size_t)len
{
    [self drawString:str x:x y:y color:color font:_font len:len];
}

- (void)drawString: (const char *)str x:(size_t)x y:(size_t)y color:(Color)color font: (GSFont *)font len: (size_t)len
{
    size_t font_w = [font width];
    size_t cx = x;
    for (size_t i = 0; i < len; i++)
    {
        [self drawChar:str[i] x:cx y:y color:color];
        cx += font_w;
    }
}

- (void)drawRectX: (size_t)x y:(size_t)y w:(size_t)w h:(size_t)h color:(Color)color
{
    for (size_t cy = y; cy < y + h; cy++)
        for (size_t cx = x; cx < x + h; cx++)
            [_surface setPixelAtX:cx y:y color:color];
}


@end
