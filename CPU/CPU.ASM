[BITS 32]

%DEFINE COM1 0x3F8

SECTION .text
        GLOBAL   CPU_OUTB
        GLOBAL   CPU_INB
        GLOBAL   CPU_PUTCHAR
        GLOBAL   CPU_ABORT

CPU_OUTB:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        MOV      AL, [EBP + 12]
        OUT      DX, AL
        
        POP      EBP

        RET

CPU_INB:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        IN       AL, DX
        
        POP      EBP

        RET


CPU_PUTCHAR:
        PUSH     EBP
        MOV      EBP, ESP

CPU_PUTCHAR_LOOP:
        MOV      DX, COM1 + 0x05
        IN       AL, DX

        AND      AL, 0x20
        CMP      AL, 0x00
        JE       CPU_PUTCHAR_LOOP

        MOV      DX, COM1
        MOV      AL, [ESP + 8]
        OUT      DX, AL
        
        POP      EBP
        
        RET

CPU_ABORT:
        CLI
        HLT
        JMP      $
