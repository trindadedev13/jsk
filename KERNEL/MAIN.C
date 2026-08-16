#include <stddef.h>
#include <stdint.h>

#include "JSK/BOOT/MULTIBOOT.H"
#include "JSK/GRAPHICS/GRAPHICS.H"

void
kernel_main (struct MB_INFO *mbinfo, uint32_t magic)
{
        (void)magic;
        init_graphics ((struct VBE_MODE_INFO *)mbinfo->vbe_mode_info);

        clear_screen (0x00FF0000);

        draw_char (0, 0, 0x06, 'A');

        // draw_str (0, 0, COLOR_BLUE, "Hello!", 6);

        draw_rect (0, 0, 200, 100, 0x07);

        for (;;)
        {
        }
}
