[BITS 16]
[ORG  0x7C00]

%DEFINE KERNEL 0x7E00

BMAIN:
        ; CLEAR FLAGS
        CLI
        CLD

        ; SETUP DATA
        XOR      AX, AX
        MOV      DS, AX
        MOV      ES, AX

        ; SETUP STACK
        MOV      SP, 0x7C00 ; OVERWRITE BOOT
        MOV      SS, AX     ; ZERO

        STI                 ; ENABLE INTERRUPTS

        CALL     READ_SECTORS

        ; INITS VBE, THE VIDEOINFO STRUCT ADDR IS AT EAX
        CALL     VBE_INIT

        MOV      SI, STARTING_KERNEL
        CALL     PRINT

        JMP      0x0000:KERNEL

READ_SECTORS:
        ; COUNTER
        MOV      CX, 10

.LOOP:
        PUSH     CX

        ; READ EXTENDED SECTORS
        MOV      AH, 0x42
        MOV      SI, DAP
        INT      0x13

        ; MODIFY DAP
        ADD      DWORD[DAP+8], 127
        ADD      WORD [DAP+6], 0xFE0

        POP      CX

        LOOP     .LOOP

        RET

ALIGN 4

;  DISK ADDR PACKET
DAP:
        DB       0x10        ; DAP     BYTE [DAP+0]
        DB       0x00        ; UNUSED  BYTE [DAP+1]
        DW       0x7F        ; SECTORS BYTE [DAP+2]
        DW       0x0000      ; SEGMENT BYTE [DAP+3]
        DW       KERNEL >> 4 ; OFFSET  WORD [DAP+6]
        DQ       1           ; LBA     WORF [DAP+8]

STARTING_KERNEL:
        DB       'Starting Kernel...'
        DB       0x00

%INCLUDE "BIOS/VIDEO.ASM"

TIMES   510 - ($ - $$) DB 0x00
DW      0xAA55
