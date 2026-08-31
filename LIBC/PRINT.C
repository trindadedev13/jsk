#include <stdio.h>

#include "JSK/CPU/CPU.H"

int
putchar (int ch)
{
    CPU_PUTCHAR (ch);
}

void
puts (const char *s)
{
    while (*s)
        putchar (*s++);
    putchar ('\n');
}

void
puthex (int value)
{
    int i;
    char buf[9];

    putchar ('0');
    putchar ('x');
    for (i = 7; i >= 0; i--)
    {
        buf[i] = "0123456789ABCDEF"[value & 0xF];
        value >>= 4;
    }

    buf[8] = '\0';

    puts (buf);
}