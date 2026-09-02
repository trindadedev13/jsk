#import "Graphics/Graphics.h"

#include <stddef.h>
#include <stdint.h>

@implementation GSFont

- (id)initWithData:(uint8_t *)data width:(size_t)width height:(size_t)height glyphCount:(size_t)glyphCount
{
    self = [super init];
    if (self)
    {
        _data = data;
        _width = width;
        _height = height;
        _glyphCount = glyphCount;
    }
    return self;
}

- (uint8_t *)data { return _data; }
- (size_t)width { return _width; }
- (size_t)height { return _height; }
- (size_t)glyphCount { return _glyphCount; }
- (size_t)bytesPerRow { return (_width + 7) / 8; }
- (size_t)glyphSize { return [self bytesPerRow] * _height; };

@end

extern int S1_FONT_WIDTH;
extern int S1_FONT_HEIGHT;
extern int S1_FONT_GLYPH;
extern uint8_t S1_FONT[];

GSFont *GetDefaultFont (void)
{
    static GSFont *font = nil;
    if (!font) font = [[GSFont alloc] initWithData:S1_FONT width:S1_FONT_WIDTH height:S1_FONT_HEIGHT glyphCount:S1_FONT_GLYPH];
    return font;
}
