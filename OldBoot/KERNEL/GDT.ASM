[BITS 16]

GLOBAL  GDTR
GLOBAL  GDT_SETUP

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

[SECTION .data]
GDT:
        ; NOT USED
        GDT_NULL:
                DQ       0x00

        ; CODE SEG
        GDT_CODE:
                DW       0xFFFF    ; LIMIT LOW
                DW       0x00      ; BASE LOW
                DB       0x00      ; BASE MID
                DB       10011010b ; ACCESS : PRESENT, RING0, CODE, EXEC/READ
                DB       11001111b ; FLAGS : 4K GRANULARITY + 32BIT
                DB       0x00      ; BASE HIGH

        GDT_DATA:
                DW      0xFFFF
                DW      0x00
                DB      0x00
                DB      10010010b ; ACCESS : PRESENT, RING0, DATA, READ/WRITE
                DB      11001111b ; FLAGS : 4K GRANULARITY + 32BIT
                DB      0x00

        GDT_CODE16:
                DW      0xFFFF
                DW      0x00
                DB      0x00
                DB      10011010b
                DB      00001111b
                DB      0x00

        GDT_DATA16:
                DW      0xFFFF
                DW      0x00
                DB      0x00
                DB      10010010b
                DB      00001111b
                DB      0x00

        

; GDT STRUCT, TO STORE ADDR AND LIMIT
GDTR:
        DW      GDTR - GDT - 1
        DD      GDT
