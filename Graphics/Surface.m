#import "Graphics/Graphics.h"

#include <stdint.h>
#include <stddef.h>

#include "Boot/Vbe.h"

@implementation GSSurface

- (id)initWithPixels:(void *)pixels width:(size_t)width height:(size_t)height pitch:(size_t)pitch  bitsPerPixel:(uint8_t)bpp redPosition:(uint8_t)redPos greenPosition: (uint8_t)greenPos bluePosition: (uint8_t)bluePos
{
    self = [super init];
    if (self)
    {
        _pixels = pixels;
        _width = width;
        _height = height;
        _pitch = pitch;
        _bpp = bpp;
        _redPos = redPos;
        _greenPos = greenPos;
        _bluePos = bluePos;
    }
    return self;
}

- (id)initWithVbe:(VbeModeInfo *)vmi
{
    return [self initWithPixels:(void *)vmi->framebuffer width:vmi->width height:vmi->height pitch:vmi->pitch bitsPerPixel: vmi->bpp redPosition:vmi->red_position greenPosition:vmi->green_position bluePosition:vmi->blue_position];
}

- (void *)pixels {return _pixels; }
- (size_t)width { return _width; }
- (size_t)height { return _height; };
- (size_t)pitch { return _pitch; }
- (uint8_t)bitsPerPixel { return _bpp; }
- (uint8_t)redPosition { return _redPos; } 
- (uint8_t)greenPosition { return _greenPos; }
- (uint8_t)bluePosition { return _bluePos; }

- (Color)rgb:(uint8_t)r g:(uint8_t)g b:(uint8_t)b
{
    return ((uint32_t)r << _redPos) |
           ((uint32_t)g   << _greenPos) |
           ((uint32_t)b   << _bluePos);
}

- (void)setPixelAtX:(size_t)x y:(size_t)y color:(Color)color
{
    if (x >= _width || y >= _height)
        return;

    Pixel *f = (Pixel *)_pixels;
    f[x + y * (_pitch + 4)] = color;
}

- (Pixel)getPixelAtX:(size_t)x y:(size_t)y
{
    Pixel *f = (Pixel *)_pixels;
    return f[x+y*(_pitch+4)];
}

@end


