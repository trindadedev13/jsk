[BITS 16]

GDT_SETUP:
        ; DISABLE INTERRUPTS
        CLI

        ; LOAD GDT ADDR
        LGDT     [GDTR]

        ; ENABLE PROTECTED MODE
        MOV      EAX, CR0
        OR       EAX, 0x01
        MOV      CR0, EAX

        RET

GDT:
        ; NOT USED
        GDT_NULL:
                DD       0x00
                DD       0x00

        ; CODE SEG
        GDT_CODE:
                ; SEG LIMIT
                DW       0xFFFF
                
                ; BASE
                DW       0x00
                DB       0x00
                
                ; EXECUTABLE, R/W, CODE SEG (1001 1010b)
                DB      0x9A
                
                ; ADDITIONAL ATTRS
                DB      0xCF
                
                ; RESERVED
                DB      0x00

        GDT_DATA:
                ; SEG LIMIT
                DW      0xFFFF
                
                ; BASE
                DW      0x00
                DB      0x00

                ; SPECIFIES DATA SEG
                DB      0x92

                ; ADDITIONAL ATTRS
                DB      0xCF

                ; RESERVED
                DB      0x00

; GDT STRUCT, TO STORE ADDR AND LIMIT
GDTR:
        DW      GDTR - GDT - 1
        DD      GDT

; CODE SEG
CODE_SEG EQU GDT_CODE - GDT
DATA_SEG EQU GDT_DATA - GDT
