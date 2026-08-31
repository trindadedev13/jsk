#ifndef JSK_LIBC_STRING_H
#define JSK_LIBC_STRING_H

#include <stddef.h>

size_t strlen (const char *);
int strcmp (const char *, const char *);
char *strdup (const char *);
char *strcpy (char *dst, const char *src);

void *memcpy (void *dst, const void *src, size_t n);
void *memset (void *s, int c, size_t n);

#endif
