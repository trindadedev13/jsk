[BITS 32]

%DEFINE COM1 0x3F8

SECTION .text
        GLOBAL   CpuOutb
        GLOBAL   CpuInb
        GLOBAL   CpuPutChar
        GLOBAL   CpuAbort

CpuOutb:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        MOV      AL, [EBP + 12]
        OUT      DX, AL
        
        POP      EBP

        RET

CpuInb:
        PUSH     EBP
        MOV      EBP, ESP

        MOV      DX, [EBP + 8]
        IN       AL, DX
        
        POP      EBP

        RET


CpuPutChar:
        PUSH     EBP
        MOV      EBP, ESP

CpuPutCharLoop:
        MOV      DX, COM1 + 0x05
        IN       AL, DX

        AND      AL, 0x20
        CMP      AL, 0x00
        JE       CpuPutCharLoop

        MOV      DX, COM1
        MOV      AL, [ESP + 8]
        OUT      DX, AL
        
        POP      EBP
        
        RET

CpuAbort:
        CLI
        HLT
        JMP      $
