OUTPUT_FORMAT ("binary")
ENTRY (_START)

SECTIONS
{
        /** kernel start addr */
        . = 0x7E00;

        .text :
        {
                *(.text._START)
                *(.text*)
        }

        .rodata :
        {
                *(.rodata*)
        }

        .init_array :
        {
                __init_array_start = .;
                KEEP(*(SORT(.init_array.*)))
                KEEP(*(.init_array))
                __init_array_end = .;
        }

        .data :
        {
                *(.data*)
        }

        .bss :
        {
                *(.bss*)
                *(COMMON)
        }

        kernel_end = .;
}
