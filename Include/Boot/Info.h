#ifndef JSK_BOOT_INFO_H
#define JSK_BOOT_INFO_H

#include <stdint.h>

typedef struct boot_info_t
{
    uint32_t vbe_mode_info;
} __attribute__((packed)) BootInfo;

#endif
