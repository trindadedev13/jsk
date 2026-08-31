#include "string.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

size_t
strlen (const char *s)
{
    size_t i = 0;

    if (!s)
        return NULL;

    while (*s++)
    {
        i++;
    };
    return i;
}

int
strcmp (const char *a, const char *b)
{
    if (!a || !b)
        return NULL;

    while (*a && (*a == *b))
    {
        a++;
        b++;
    }
    return *(uint8_t *)a - *(uint8_t *)b;
}

char *
strcpy (char *dst, const char *src)
{
    if (!dst || !src)
        return NULL;

    while (*src)
    {
        *dst++ = *src++;
    }
    return dst;
}

char *
strdup (const char *src)
{
    size_t len = strlen (src);
    char *dst = (char *)malloc (len + 1);
    strcpy (dst, src);
    dst[len] = '\0';
    return dst;
}

void *
memset (void *s, int c, size_t n)
{
    uint8_t *dst = (uint8_t *)s;
    while (n--)
    {
        *dst++ = c;
    }
    return s;
}

void *
memcpy (void *dst, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    if (!dst || !src)
        return NULL;

    while (n--)
    {
        *d++ = *s++;
    }

    return dst;
}
