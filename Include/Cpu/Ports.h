#ifndef JSK_CPU_PORTS_H
#define JSK_CPU_PORTS_H

#include <stdint.h>

#define COM1 0x3F8

/** all these functions are implemented in assembly */
extern void JSKCpuOutb (uint32_t, uint8_t);
extern uint8_t JSKCpuInb (uint32_t);

#endif
