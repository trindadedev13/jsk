#pragma once

#include <stddef.h>
#include <stdint.h>

@interface GSSurface : NSObject {
@private
    void *_pixels;
    size_t _width;
    size_t _height;
    size_t _pitch;
    size_t _bpp;

    uint8_t _redPos, _greenPos, _bluePos;
}

- (id)initWithPixels:(void *)pixels width:(size_t)width height:(size_t)height pitch:(size_t)pitch bitsPerPixel:(uint8_t)bpp redPosition:(uint8_t)redPos greenPosition: (uint8_t)greenPos bluePosition: (uint8_t)bluePos;
- (id)initWithVbe:(VbeModeInfo *)vmi;

- (void *)pixels; 
- (size_t)width;
- (size_t)height;
- (size_t)pitch;
- (uint8_t)bitsPerPixel;
- (uint8_t)redPosition;
- (uint8_t)greenPosition;
- (uint8_t)bluePosition;

- (Color)rgb:(uint8_t)r g:(uint8_t)g b:(uint8_t)b;

- (void)setPixelAtX:(size_t)x y:(size_t)y color:(Color)color;

- (Pixel)getPixelAtX:(size_t)x y:(size_t)y;

@end