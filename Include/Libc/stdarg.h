#ifndef JSK_LIBC_STDARG_H
#define JSK_LIBC_STDARG_H

typedef char *va_list;

#define __va_align(n) \
    (((n) + sizeof(int) - 1) & ~(sizeof(int) - 1))

#define va_start(ap, last) \
    ((ap) = (va_list)((char *)&(last) + __va_align(sizeof(last))))

#define va_arg(ap, type) \
    (*(type *)((ap += __va_align(sizeof(type))) - __va_align(sizeof(type))))

#define va_end(ap) \
    ((ap) = (va_list)0)

#endif