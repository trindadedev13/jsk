[BITS 32]

SECTION .text
        GLOBAL   _START
        GLOBAL   __cxa_pure_virtual

        EXTERN   __init_array_start
        EXTERN   __init_array_end
        EXTERN   kernel_main

        ; CALL CPP CONSTRUCTORS
        ; WE AREN'T USING C++ RIGHT NOW
        ; BUT THIS MAKES EASIER TO USE IN FUTURE
_START:
        MOV      EBX, __init_array_start
        MOV      EBP, __init_array_end
        CMP      EBX, EBP
        JE       .END 
.LOOP:
        CALL     [EBX]    ; CALL CTOR (*CTOR)()
        ADD      EBX, 4   ; ADVANCES 4 BYTE (NEXT POINTER)
        CMP      EBX, EBP
        JNE      .LOOP    ; IF NOT EQUAL END, CONTINUE 

        
.END:
        CALL     kernel_main
        JMP      $

__cxa_pure_virtual:
        JMP      $
