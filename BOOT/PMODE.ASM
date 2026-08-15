[BITS 32]

PMODE:
        MOV      AX, DATA_SEG

        ; SETUP DATA (with GDT)
        MOV      DS, AX
        MOV      ES, AX
        MOV      FS, AX
        MOV      GS, AX

        ; SETUP x86 STACK
        MOV      EBP, 0x90000
        MOV      ESP, EBP
        MOV      SS,  AX

        JMP      KERNEL
