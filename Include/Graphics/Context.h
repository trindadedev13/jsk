#pragma once

#include <stdint.h>
#include <stddef.h>

#include "Boot/Vbe.h"

@interface GSContext : NSObject {
@private
    GSSurface *_surface;
    GSFont *_font;
}

- (id)initWithSurface:(GSSurface *)surface font:(GSFont *)font;

- (GSSurface *)surface;
- (GSFont *)font;

- (void)setFont: (GSFont *)font;

- (Color)rgb:(uint8_t)r g:(uint8_t)g b:(uint8_t)b;

- (void)clear:(Color)color;

- (void)setPixelAtX: (size_t)x y:(size_t)y color:(Color)color;
- (Color)getPixelAtX: (size_t)x y:(size_t)y;

- (void)drawChar: (char)ch x:(size_t)x y:(size_t)y color:(Color)color;
- (void)drawChar: (char)ch x:(size_t)x y:(size_t)y color:(Color)color font:(GSFont *)font;

- (void)drawString: (const char *)str x:(size_t)x y:(size_t)y color:(Color)color len: (size_t)len;

- (void)drawString: (const char *)str x:(size_t)x y:(size_t)y color:(Color)color font:(GSFont *)font len: (size_t)len;

- (void)drawRectX: (size_t)x y:(size_t)y w:(size_t)w h:(size_t)h color:(Color)color;

@end
