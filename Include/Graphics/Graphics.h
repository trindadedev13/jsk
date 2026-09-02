#pragma once

#include <stdint.h>

typedef uint32_t Color;
typedef Color Pixel;

#ifdef __OBJC__

#include <Foundation/Foundation.h>

@class GSSurface;
@class GSContext;
@class GSFont;

#include "Boot/Vbe.h"
#include "Graphics/Context.h"
#include "Graphics/Font.h"
#include "Graphics/Surface.h"

#endif

GSFont *get_default_font (void);

void init_graphics (VbeModeInfo *vmi, GSFont *font);