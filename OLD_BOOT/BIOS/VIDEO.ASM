[BITS 16]

%DEFINE VBE_INFO     0x7000
%DEFINE VBE_MODEINFO 0x7200
%DEFINE VIDEOINFO    0x7400

%DEFINE WSCREEN      1280
%DEFINE HSCREEN      720
%DEFINE BPPSCREEN    32

GLOBAL  PRINT

PRINT:
        MOV      AH, 0x0E
        MOV      BL, 0x0F

.PRINT_LOOP:
        MOV      AL, [SI]
        CMP      AL, 0
        JE       .PRINT_DONE

        INT      0x10
        INC      SI
        JMP      .PRINT_LOOP

.PRINT_DONE:
        RET

VBE_INIT:
        ; GET VBE CONTROLLER INFO
        MOV      AX, 0x4F00
        MOV      DI, VBE_INFO
        MOV      DWORD [ES:DI], 'VBE2'
        INT      0x10

        CMP      AX, 0x004F
        JNE      .VBE_ERROR

        ; FIND A MODE MATCHING WSCREEN x HSCREEN x BPPSCREEN
        CALL     FIND_MODE

        CMP      WORD [FOUND_MODE], 0x00
        JE       .VBE_ERROR

        ; SET VBE MODE (FOUND_MODE ALREADY HAS THE LFB BIT SET)
        MOV      AX, 0x4F02
        MOV      BX, WORD [FOUND_MODE]
        INT      0x10

        CMP      AX, 0x004F
        JNE      .VBE_ERROR

        MOV      EAX, VBE_MODEINFO

        RET

.VBE_ERROR:
        MOV      SI, M_VBE_FAILED
        CALL     PRINT
        CLI
        HLT

; ---------------------------------------------------------
; FIND_MODE
; WALKS THE VBE MODE LIST (POINTED BY VBE_INFO+0x0E, FAR PTR)
; LOOKING FOR WSCREEN x HSCREEN x BPPSCREEN WITH LFB SUPPORT.
; RESULT: WORD [FOUND_MODE] = MODE NUMBER (WITH 0x4000 LFB BIT
;         SET) OR 0 IF NOT FOUND.
; ---------------------------------------------------------
FIND_MODE:
        MOV      SI, WORD [VBE_INFO+0x0E] ; MODE LIST OFFSET
        MOV      AX, WORD [VBE_INFO+0x10] ; MODE LIST SEGMENT
        MOV      FS, AX

.LOOP:
        MOV      CX, WORD [FS:SI]         ; CURRENT MODE NUMBER
        CMP      CX, 0xFFFF               ; END OF LIST?
        JE       .NOT_FOUND

        PUSH     SI
        PUSH     FS

        MOV      AX, 0x4F01
        MOV      DI, VBE_MODEINFO
        INT      0x10

        POP      FS
        POP      SI

        CMP      AX, 0x004F
        JNE      .SKIP

        ; CHECK XRESOLUTION
        MOV      AX, WORD [VBE_MODEINFO+0x12]
        CMP      AX, WSCREEN
        JNE      .SKIP

        ; CHECK YRESOLUTION
        MOV      AX, WORD [VBE_MODEINFO+0x14]
        CMP      AX, HSCREEN
        JNE      .SKIP

        ; CHECK BITSPERPIXEL
        MOV      AL, BYTE [VBE_MODEINFO+0x19]
        CMP      AL, BPPSCREEN
        JNE      .SKIP

        ; CHECK LINEAR FRAME BUFFER SUPPORT (ATTR BIT 7)
        MOV      AX, WORD [VBE_MODEINFO+0x00]
        TEST     AX, 0x80
        JZ       .SKIP

        ; FOUND: SET LFB BIT FOR THE SET-MODE CALL
        OR       CX, 0x4000
        MOV      WORD [FOUND_MODE], CX
        RET

.SKIP:
        ADD      SI, 0x02
        JMP      .LOOP

.NOT_FOUND:
        MOV      WORD [FOUND_MODE], 0x00
        MOV      SI, M_NOT_FOUND
        CALL     PRINT
        RET

FOUND_MODE:
        DW       0x00

M_VBE_FAILED:
        DB       "FAILED TO INIT VBE"
        DB       0x00

M_NOT_FOUND:
        DB       "REQUIRED MODE NOT FOUND"
        DB       0x00