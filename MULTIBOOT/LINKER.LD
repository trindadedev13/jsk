OUTPUT_FORMAT(elf32-i386)
ENTRY(_KERNEL_BOOT_START)

SECTIONS
{
    . = 0x100000;

    .multiboot ALIGN(4K) :
    {
        KEEP(*(.multiboot))
    }
    
    .text ALIGN(4K) :
    {
        *(.text)
    }

    .rodata ALIGN(4K) :
    {
        *(.rodata)
    }

    .data ALIGN(4K) :
    {
        *(.data)
    }

    .bss ALIGN(4K) :
    {
        *(COMMON)
        *(.bss)
    }

    .stack ALIGN(16) :
    {
        *(stackBottom)
        *(stackTop)
    }
}