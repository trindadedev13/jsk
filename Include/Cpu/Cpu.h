#ifndef JSK_CPU_H
#define JSK_CPU_H

#include <stdint.h>

#define COM1 0x3F8

/** put char in COM1 */
extern void JSKCpuPutChar (uint8_t);

[[noreturn]] extern void JSKCpuAbort (void);

#endif
