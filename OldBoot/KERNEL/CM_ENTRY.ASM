[BITS 16]

SECTION .text
        GLOBAL   _KERNEL_START

        GLOBAL   __cxa_pure_virtual ; FALLBACK OF C++ VIRTUAL FUNCTIONS

        ; GLOBAL OBJECTS C++ CONSTRUCTOR ARRAY
        EXTERN   __init_array_start
        EXTERN   __init_array_end

        EXTERN   kernel_main ; FROM KERNEL/MAIN.C
        EXTERN   GDTR        ; FROM KERNEL/GDT.ASM
        EXTERN   GDT_SETUP   ; FROM KERNEL/GDT.ASM
        EXTERN   PRINT       ; FROM BIOS/VIDEO.ASM

_KERNEL_START:
        ; SETUP GDT
        PUSH     EAX ; SAVE VBE_MODE_INFO STRUCT
        
        MOV      SI, M_GDT_SETUP
        CALL     PRINT

        CALL     GDT_SETUP
        ; DEBUG

        POP      EAX

        JMP      CODE_SEG32:.PM32

[BITS 32]
.PM32:
        MOV      EBX, EAX ; SAVE THE VBE_MODE_INFO AGAIN
        MOV      AX, DATA_SEG32
        MOV      DS, AX
        MOV      ES, AX
        MOV      FS, AX
        MOV      GS, AX
        MOV      SS, AX

        MOV      EBP, 0x90000
        MOV      ESP, EBP

        MOV      EAX, EBX ; RESTORE VBE_MODE_INFO IN EAX AGAIN
        JMP      INIT_ARRAYS

        ; CALL CPP CONSTRUCTORS
        ; WE AREN'T USING C++ RIGHT NOW
        ; BUT THIS MAKES EASIER TO USE IN FUTURE
INIT_ARRAYS:
        MOV      EBX, __init_array_start
        MOV      EBP, __init_array_end
        CMP      EBX, EBP
        JE       INIT_ARRAYS.END
INIT_ARRAYS.LOOP:
        CALL     [EBX]            ; CALL CTOR (*CTOR)()
        ADD      EBX, 4           ; ADVANCES 4 BYTE (NEXT POINTER)
        CMP      EBX, EBP
        JNE      INIT_ARRAYS.LOOP ; IF NOT EQUAL END, CONTINUE 

INIT_ARRAYS.END:
        PUSH     EAX         ; PUSH EAX AS FIRST ARG (CDECL)
        CALL     kernel_main
        ADD      ESP, 4      ; CLEAN FRAME
        JMP      $

__cxa_pure_virtual:
        JMP      $

; STRINGS
M_GDT_SETUP:
        DB       "Callling GDT_SETUP..."
        DB       0x00

%INCLUDE "JSK/BOOT/GDT.INC"
