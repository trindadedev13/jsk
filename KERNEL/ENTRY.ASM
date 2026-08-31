[BITS 32]

SECTION .text
        GLOBAL   _KERNEL_START

        GLOBAL   __cxa_pure_virtual ; FALLBACK OF C++ VIRTUAL FUNCTIONS

        ; GLOBAL OBJECTS C++ CONSTRUCTOR ARRAY
        EXTERN   __init_array_start
        EXTERN   __init_array_end

        EXTERN   kernel_main ; FROM KERNEL/MAIN.C

_KERNEL_START:
        MOV      ESI, [ESP + 4] ; SAVE MULTIBOOT INFO
        MOV      EDI, [ESP + 8] ; SAVE MAGIC NUMBER

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
        PUSH     EDI
        PUSH     ESI
        CALL     kernel_main
        ADD      ESP, 8      ; CLEAR FRAME
        JMP      $

__cxa_pure_virtual:
        JMP      $
