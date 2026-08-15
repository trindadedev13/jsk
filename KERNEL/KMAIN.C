#include <stddef.h>

#include "JSK/GRAPHICS/GRAPHICS.H"

void
kernel_main (void)
{
        clear_screen ();

        draw_str (0, 0, COLOR_BLUE, "Hello!", 6);

        for (;;)
        {
        }
}
