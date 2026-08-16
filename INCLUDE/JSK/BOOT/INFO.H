#ifndef JSK_BOOT_INFO_H
#define JSK_BOOT_INFO_H

#include <stdint.h>

struct __attribute__((packed)) BOOT_INFO
{
    uint32_t vbe_mode_info;
};

#endif
