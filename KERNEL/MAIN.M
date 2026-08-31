#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "OBJC/OBJC.H"

#include "JSK/BOOT/MULTIBOOT.H"
#include "JSK/BOOT/VBE.H"
#include "JSK/CPU/CPU.H"
#include "JSK/GRAPHICS/GRAPHICS.H"

#define sputc CPU_PUTCHAR
#define DRAW_STR(x, y, color, s) draw_str (x, y, color, s, strlen (s))

@interface People : Object
{
    char *_name;
}

- (id)init:(const char *)name;
- (void)dealloc;
- (void)sayHi;
@end

@implementation People

- (id)init:(const char *)name
{
    self = [super init];
    if (self)
        _name = strdup(name);
    return self;
}

- (void)dealloc
{
    printf ("dealloc\n");
    free(_name);
    [super dealloc];
}

- (void)sayHi
{
    if (_name) printf("Hi %s!\n", _name);
}

- (const char *)name
{
    return _name;
}

- (void)setName:(const char *)name
{
    if (_name) free (_name);
    _name = strdup (name);
}

@end

static void test()
{
    @autoreleasepool
    {
        People *p = [[[People alloc] init: "Aquiles Trindade"] autorelease];
        [p sayHi];
    }
}

void
kernel_main (MultibootInfo *mbinfo, uint32_t magic)
{
    (void)magic;

    init_graphics (mbinfo->vbe_mode_info, NULL);
    clear_screen (color(0,0,255));

    test();

    for (;;)
    {
    }
}
