#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Boot/Multiboot.h"
#include "Boot/Vbe.h"
#include "Graphics/Graphics.h"

static void InitGraphics (VbeModeInfo *vmi)
{
    GSSurface *surface = [[GSSurface alloc] initWithVbe:vmi];
    GSFont *font = GetDefaultFont ();
    GSContext *ctx = [[GSContext alloc] initWithSurface:surface font:font];
    
    Color white = [ctx rgb:255 g:255 b:255];
    [ctx clear:white];
}

void 
JSKKernelMain (MultibootInfo *mbinfo, uint32_t magic)
{
    (void)magic;

    InitGraphics (mbinfo->vbe_mode_info);
    puthex (magic);

    for (;;)
    {
    }
}
