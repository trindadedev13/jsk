#ifndef JSK_LIBC_STDINT_H
#define JSK_LIBC_STDINT_H

#ifndef SIZE_MAX
#define SIZE_MAX ((size_t)-1)
#endif

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;

typedef unsigned int uint32_t;
typedef int int32_t;

typedef long long intmax_t;
typedef int ptrdiff_t;

#endif
