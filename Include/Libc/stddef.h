#ifndef JSK_LIBC_STDDEF_H
#define JSK_LIBC_STDDEF_H

#define NULL (0)

/** Attribute Macros */
#if __has_attribute(always_inline)
#define ALWAYS_INLINE __attribute((always_inline))
#else
#define ALWAYS_INLINE
#endif

#if __has_attribute(unused)
#define UNUSED __attribute((unused))
#else
#define UNUSED
#endif

typedef unsigned int size_t;
typedef int ssize_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;

#endif
