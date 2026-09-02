; THIS CODE ISN'T WORKING
; I SUSPECT IT'S BECAUSE OF THE CALL & RET.
; WHEN YOU CALL THE ENTER_PROTECTED_MODE, YOU'RE AT 16BIT
; AND PUSHES A 2BYTE ADDR, BUT AT RET, YOU'RE IN 32BIT
; SO, IT TRIES TO POP 4 BYTES INSTEAD OF 4.
; THE SAME GOES FOR ENTER_REAL_MODE

[BITS 32]

SECTION .data
        SAVED_ESP:
                DD       0x00
        RGDTDESC:
                DW       0x00
                DD       0x00

SECTION .text
        EXTERN  GDTR
        GLOBAL  ENTER_REAL_MODE
        GLOBAL  ENTER_PROTECTED_MODE

ENTER_REAL_MODE:
        CLI                       ; DISABLE INTERRUPTS
        MOV      [SAVED_ESP], ESP ; SAVE ESP
        JMP      CODE_SEG16:.PM16  ;

[BITS 16]
.PM16:
        MOV      AX, DATA_SEG16
        MOV      DS, AX
        MOV      ES, AX
        MOV      FS, AX
        MOV      GS, AX
        MOV      SS, AX

        MOV      EAX, cr0
        AND      EAX, 0xFFFFFFFE
        MOV      CR0, EAX

        JMP      0x0000:.RM16 ; FAR JUMP

.RM16:
        XOR      AX, AX
        MOV      DS, AX
        MOV      ES, AX
        MOV      SS, AX
        MOV      SP, [SAVED_ESP]

        STI
        RET

[BITS 16]
ENTER_PROTECTED_MODE:
        CLI

        LGDT     [GDTR]

        MOV      EAX, CR0
        OR       EAX, 0x01
        MOV      CR0, EAX

        JMP      CODE_SEG32:.PM32

.PM32:
        MOV      AX, DATA_SEG32
        MOV      DS, AX
        MOV      ES, AX
        MOV      FS, AX
        MOV      GS, AX
        MOV      SS, AX

        MOV      ESP, [SAVED_ESP] ; RESTORE STACK

        STI
        RET

%INCLUDE "JSK/BOOT/GDT.INC"
