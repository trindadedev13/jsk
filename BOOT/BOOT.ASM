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
        MOV      SP, 0x7C00
        MOV      SS, AX

        STI

        ; SETUP VESA (640x480 8bpp)
        MOV     AX, 0x4F02
        MOV     BX, 0x4103
        INT     0x10

        CALL     READ_SECTORS
        CALL     GDT_SETUP

        JMP      CODE_SEG:PMODE

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

%INCLUDE "BOOT/GDT.ASM"
%INCLUDE "BOOT/PMODE.ASM"

TIMES   510 - ($ - $$) DB 0x00
DW      0xAA55
