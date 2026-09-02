[BITS 32]

%DEFINE COM1 0x3F8

SECTION .text
        GLOBAL   JSKCpuOutb
        GLOBAL   JSKCpuInb
        GLOBAL   JSKCpuPutChar
        GLOBAL   JSKCpuAbort

JSKCpuOutb:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        MOV      AL, [EBP + 12]
        OUT      DX, AL
        
        POP      EBP

        RET

JSKCpuInb:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        IN       AL, DX
        
        POP      EBP

        RET


JSKCpuPutChar:
        PUSH     EBP
        MOV      EBP, ESP

JSKCpuPutCharLoop:
        MOV      DX, COM1 + 0x05
        IN       AL, DX

        AND      AL, 0x20
        CMP      AL, 0x00
        JE       JSKCpuPutCharLoop

        MOV      DX, COM1
        MOV      AL, [ESP + 8]
        OUT      DX, AL
        
        POP      EBP
        
        RET

JSKCpuAbort:
        CLI
        HLT
        JMP      $
