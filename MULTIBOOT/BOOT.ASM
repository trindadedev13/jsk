MBOOT_PAGE_ALIGN EQU 1 << 0
MBOOT_MEM_INFO   EQU 1 << 1
MBOOT_USE_GFX    EQU 1 << 2

MBOOT_MAGIC      EQU 0x1BADB002
MBOOT_FLAGS      EQU MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_USE_GFX
MBOOT_CHECKSUM   EQU -(MBOOT_MAGIC + MBOOT_FLAGS)

SECTION .multiboot
        align    4
        DD       MBOOT_MAGIC
        DD       MBOOT_FLAGS
        DD       MBOOT_CHECKSUM
        DD       0x00, 0x00, 0x00, 0x00, 0x00

        DD       0x01
        DD       1280
        DD       720
        DD       32

align 16

SECTION .text
        GLOBAL   _KERNEL_BOOT_START
        EXTERN   _KERNEL_START

_KERNEL_BOOT_START:
        PUSH     EAX
        PUSH     EBX

        XOR      EBP, EBP

        CALL     _KERNEL_START

HALT:
        HLT
        JMP      HALT

SECTION .bss
        align    16
