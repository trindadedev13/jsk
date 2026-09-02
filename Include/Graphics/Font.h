#pragma once

#include <stddef.h>
#include <stdint.h>

@interface GSFont : NSObject {
@private
    uint8_t *_data;
    size_t _width;
    size_t _height;
    size_t _glyphCount;
}

- (id)initWithData:(uint8_t *)data width:(size_t)width height:(size_t)height glyphCount:(size_t)glyphCount;

- (uint8_t *)data;
- (size_t)width;
- (size_t)height;
- (size_t)glyphCount;
- (size_t)bytesPerRow;
- (size_t)glyphSize;

GSFont *GetDefaultFont (void);

@end
