#ifndef JSK_LIBC_STDLIB
#define JSK_LIBC_STDLIB

#include <stddef.h>

void *malloc (size_t size);
void free (void *ptr);
void *realloc (void *ptr, size_t newsize);
void *calloc (size_t count, size_t size);

[[noreturn]] void abort (void);

#endif
