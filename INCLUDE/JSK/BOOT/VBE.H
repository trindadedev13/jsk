#ifndef JSK_BOOT_VBE_H
#define JSK_BOOT_VBE_H

#include <stdint.h>

struct VBE_MODE_INFO
{
        // mandatory info for all VBE revisions
        uint16_t attributes;
        uint8_t window_a;
        uint8_t window_b;
        uint16_t granularity;
        uint16_t window_size;
        uint16_t segment_a;
        uint16_t segment_b;
        uint32_t win_func_ptr;
        uint16_t pitch; // 0x10  bytes per scanline

        // VBE 1.2+
        uint16_t width;  // 0x12
        uint16_t height; // 0x14
        uint8_t w_char;
        uint8_t y_char;
        uint8_t planes;
        uint8_t bpp; // 0x19
        uint8_t banks;
        uint8_t memory_model;
        uint8_t bank_size;
        uint8_t image_pages;
        uint8_t reserved0;

        // direct color fields
        uint8_t red_mask;       // 0x1F
        uint8_t red_position;   // 0x20
        uint8_t green_mask;     // 0x21
        uint8_t green_position; // 0x22
        uint8_t blue_mask;      // 0x23
        uint8_t blue_position;  // 0x24
        uint8_t rsvd_mask;      // 0x25
        uint8_t rsvd_position;  // 0x26
        uint8_t direct_color_attributes;

        // VBE 2.0+
        uint32_t framebuffer; // 0x28  PhysBasePtr
        uint32_t off_screen_mem_off;
        uint16_t off_screen_mem_size;

        uint8_t reserved1[206]; // pad until 256 bytes total
} __attribute__ ((packed));

#endif