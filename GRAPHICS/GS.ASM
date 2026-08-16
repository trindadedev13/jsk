; THIS CODE DOESN'T WORK
; BECAUSE BIOS/MODE.ASM DOESN'T WORK ALSO
; SEE BIOS/MODE.ASM HEADER.

[BITS 32]

SECTION .text
        GLOBAL   TTOUT
        GLOBAL   RPIXEL
        GLOBAL   WPIXEL
        GLOBAL   SETCURPOS

        EXTERN   ENTER_REAL_MODE
        EXTERN   ENTER_PROTECTED_MODE

; TELETYPE OUTPUT
TTOUT:
        PUSH     EBP
        MOV      EBP, ESP

        CALL     ENTER_REAL_MODE

        MOV      AH, 0x0E
        MOV      AL, [EBP+4] ; CHAR
        MOV      BL, [EBP+8] ; COLOR
        INT      0x10

        CALL     ENTER_PROTECTED_MODE

        POP      EBP

        RET

; READ PIXEL
RPIXEL:
        PUSH     EBP
        MOV      EBP, ESP

        CALL     ENTER_REAL_MODE

        MOV      AH, 0x0E
        MOV      AL, [EBP+4] ; X
        MOV      DX, [EBP+8] ; Y
        INT      0x10
        
        CALL     ENTER_PROTECTED_MODE

        MOV      EAX, AL

        POP      EBP
        RET

; WRITE PIXEL
WPIXEL:
        PUSH     EBP
        MOV      EBP, ESP

        CALL     ENTER_REAL_MODE

        MOV      AH, 0x0E
        MOV      CX, [EBP+4] ; Y
        MOV      DX, [EBP+8] ; Y
        MOV      AL, [EBP+16] ; COLOR
        INT      0x10

        CALL     ENTER_PROTECTED_MODE

        POP      EBP
        RET

; SET CURSOR POS
SETCURPOS:
        PUSH     EBP
        MOV      EBP, ESP

        CALL     ENTER_REAL_MODE

        MOV      AH, 0x02
        MOV      DH, [EBP+4] ; X
        MOV      DL, [EBP+8] ; Y
        INT      0x10

        CALL     ENTER_PROTECTED_MODE

        POP      EBP
