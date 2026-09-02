#ifndef JSK_LIBC_STDIO_H
#define JSK_LIBC_STDIO_H

#include <stdarg.h>
#include <stddef.h>

void puts (const char *s);
void puthex (int value);
int putchar (int ch);

int printf (const char *format, ...);
int sprintf (char *buffer, const char *format, ...);
int snprintf (char *buffer, size_t count, const char *format, ...);
int vsnprintf (char *buffer, size_t count, const char *format, va_list va);
int vprintf (const char *format, va_list va);
int fctprintf (void (*out) (char character, void *arg), void *arg,
               const char *format, ...);

#endif
