#ifndef JSK_BOOT_MULTIBOOT_H
#define JSK_BOOT_MULTIBOOT_H

#include <stdint.h>

#include "JSK/BOOT/VBE.H"

struct MB_AOUT_SYM_TABLE
{
        uint32_t tab_size;
        uint32_t str_size;
        uint32_t addr;
        uint32_t reserved;
} __attribute__ ((packed));

struct MB_ELF_SECTION_HEADER_TABLE
{
        uint32_t num;
        uint32_t size;
        uint32_t addr;
        uint32_t shndx;
} __attribute__ ((packed));

struct MB_MODULE
{
        uint32_t mod_start;
        uint32_t mod_end;
        uint32_t str;
        uint32_t reserved;
} __attribute__ ((packed));

struct MB_INFO
{
        uint32_t flags;
        uint32_t mem_lower;
        uint32_t mem_upper;
        uint32_t boot_device;

        uint32_t cmdline;
        uint32_t mods_count;
        uint32_t mods_addr;

        union
        {
                struct MB_AOUT_SYM_TABLE aout_sym;
                struct MB_ELF_SECTION_HEADER_TABLE elf_sec;
        } u;

        uint32_t mmap_length;
        uint32_t mmap_addr;

        uint32_t drives_length;
        uint32_t drives_addr;

        uint32_t config_table;
        uint32_t boot_loader_name;

        uint32_t apm_table;

        uint32_t vbe_control_info;
        uint32_t vbe_mode_info;
        uint16_t vbe_mode;
        uint16_t vbe_interface_seg;
        uint16_t vbe_interface_off;
        uint16_t vbe_interface_len;
} __attribute__ ((packed));

struct MB_MMAP_ENTRY
{
        uint32_t size;
        uint32_t addr_low;
        uint32_t addr_high;
        uint32_t len_low;
        uint32_t len_high;
#define MULTIBOOT_MEMORY_AVAILABLE 1
#define MULTIBOOT_MEMORY_RESERVED 2
#define MULTIBOOT_MEMORY_ACPI_RECLAIMABLE 3
#define MULTIBOOT_MEMORY_NVS 4
#define MULTIBOOT_MEMORY_BADRAM 5
        uint32_t type;
} __attribute__ ((packed));

#endif
