;***************************************************************************
; FILENAME: cymem.a51
; Version 2.40
;
;  DESCRIPTION:
;    Specialized memory routines for Keil bootup. These functions accept
;    3-byte pointers, but the pointers are interpreted as absolute locations
;    rather than as Keil generic/far pointers. Interrupts should be disabled
;    while these functions are executing unless the interrupt handler is
;    aware of dual DPTRs (DPS register), extended DPTRs (DPX0/DPX1), and
;    extended register-indirect memory access (MXAX register).
;
;   C DECLARATIONS:
;    extern void cymemzero(void far *addr, unsigned short size);
;    extern void cyconfigcpy(unsigned short size, const void far *src, void far *dest) large;
;    extern void cyconfigcpycode(unsigned short size, const void code *src, void far *dest);
;    extern void cfg_write_bytes_code(const void code *table);
;    extern void cfg_write_bytes(const void far *table);
;    extern unsigned char cyread8(const void far *addr);
;    extern unsigned char cyread8_nodpx(const void far *addr);
;    extern void cywrite8(void far *addr, unsigned char value);
;    extern void cywrite8_nodpx(void far *addr, unsigned char value);
;    extern unsigned int cyread16(const void far *addr);
;    extern unsigned int cyread16_nodpx(const void far *addr);
;    extern void cywrite16(void far *addr, unsigned int value);
;    extern void cywrite16_nodpx(void far *addr, unsigned int value);
;    extern unsigned long cyread24(const void far *addr);
;    extern unsigned long cyread24_nodpx(const void far *addr);
;    extern void cywrite24(void far *addr, unsigned long value);
;    extern void cywrite24_nodpx(void far *addr, unsigned long value);
;    extern unsigned long cyread32(const void far *addr);
;    extern unsigned long cyread32_nodpx(const void far *addr);
;    extern void cywrite32(void far *addr, unsigned long value);
;    extern void cywrite32_nodpx(void far *addr, unsigned long value);
;
;*******************************************************************************
; Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;*******************************************************************************
$NOMOD51

;*******************************************************************************
;* SFRs
;*******************************************************************************
DPL0    EQU 082H
DPH0    EQU 083H
DPL1    EQU 084H
DPH1    EQU 085H
DPS     EQU 086H
DPX0    EQU 093H
DPX1    EQU 095H
P2      EQU 0A0H
MXAX    EQU 0EAH

;*******************************************************************************
;* Symbols
;*******************************************************************************
NAME CYMEM

PUBLIC _cyconfigcpy
PUBLIC ?_cyconfigcpy?BYTE
PUBLIC _cfg_write_bytes
PUBLIC _cfg_write_bytes_code
PUBLIC _cyconfigcpycode
PUBLIC _cymemzero
PUBLIC _cyread8
PUBLIC _cyread8_nodpx
PUBLIC _cywrite8
PUBLIC _cywrite8_nodpx
PUBLIC _cyread16
PUBLIC _cyread16_nodpx
PUBLIC _cywrite16
PUBLIC _cywrite16_nodpx
PUBLIC _cyread24
PUBLIC _cyread24_nodpx
PUBLIC _cywrite24
PUBLIC _cywrite24_nodpx
PUBLIC _cyread32
PUBLIC _cyread32_nodpx
PUBLIC _cywrite32
PUBLIC _cywrite32_nodpx

;*******************************************************************************
;* void cymemzero(void far *, unsigned short);
;* Zero memory in extended XDATA. Range must not cross a 64k boundary.
;* Parameters:
;* R3: Bits [23:16] of start address
;* R2: Bits [15:8] of start address
;* R1: Bits [7:0] of start address
;* R4: Bits [15:8] of size
;* R5: Bits [7:0] of size
;*******************************************************************************
?PR?CYMEMZERO?CYMEM SEGMENT CODE
RSEG ?PR?CYMEMZERO?CYMEM
_cymemzero:
    MOV A,R4
    ORL A,R5
    JZ _cymemzero_end   ; Exit if size is 0
    MOV A,R5
    JZ _cymemzero_noinc
    INC R4              ; Tweak loop count for DJNZ
_cymemzero_noinc:
    MOV DPX0,R3
    MOV DPH0,R2
    MOV DPL0,R1
    CLR A
_cymemzero_loop:
    MOVX @DPTR,A        ; Zero memory
    INC DPTR
    DJNZ R5,_cymemzero_loop
    DJNZ R4,_cymemzero_loop
_cymemzero_end:
    MOV DPX0,#0
    RET

;*******************************************************************************
;* void cyconfigcpy(unsigned short, const void far *, void far *) large;
;* Copy memory from extended XDATA to extended XDATA. Source and destination
;* ranges must not cross a 64k boundary.
;* Parameters:
;* R6: Bits [15:8] of size
;* R7: Bits [7:0] of size
;* R3: Bits [23:16] of source address
;* R2: Bits [15:8] of source address
;* R1: Bits [7:0] of source address
;* Memory parameters: see ?_cyconfigcpy?BYTE
;*******************************************************************************
?PR?_CYCONFIGCPY?CYMEM SEGMENT CODE
RSEG ?PR?_CYCONFIGCPY?CYMEM
_cyconfigcpy:
    MOV DPS,#000h           ; Select DP0
    MOV A,R7                ; Size in R6:R7 (MSB in R6)
    ORL A,R6
    JZ _cyconfigcpy_end     ; Exit if size is 0
    MOV A,R7
    JZ _cyconfigcpy_noinc
    INC R6                  ; Tweak loop count for DJNZ
_cyconfigcpy_noinc:
    MOV DPX0,#000h          ; Read destination pointer to DPX1:DPH1:DPL1
    MOV DPTR,#_cyconfigcpy_dstx
    MOVX A,@DPTR
    MOV DPX1,A
    INC DPTR
    MOVX A,@DPTR
    MOV DPH1,A
    INC DPTR
    MOVX A,@DPTR
    MOV DPL1,A
    MOV DPX0,R3             ; Source address in R3:R2:R1
    MOV DPH0,R2
    MOV DPL0,R1
_cyconfigcpy_loop:
    MOVX A,@DPTR
    INC DPTR
    INC DPS                 ; Select DP1
    MOVX @DPTR,A
    INC DPTR
    DEC DPS                 ; Select DP0
    DJNZ R7,_cyconfigcpy_loop
    DJNZ R6,_cyconfigcpy_loop
_cyconfigcpy_end:
    CLR A
    MOV DPX0,A
    MOV DPX1,A
    RET

?XD?_CYCONFIGCPY?CYMEM SEGMENT XDATA OVERLAYABLE
RSEG ?XD?_CYCONFIGCPY?CYMEM
?_cyconfigcpy?BYTE:
_cyconfigcpy_reserved: DS 5
_cyconfigcpy_dstx:     DS 1
_cyconfigcpy_dsth:     DS 1
_cyconfigcpy_dstl:     DS 1

;*******************************************************************************
;* void cyconfigcpycode(unsigned short, const void code *, void far *);
;* Copy memory from CODE to extended XDATA. Destination range must not cross a
;* 64k boundary.
;* Parameters:
;* R6: Bits [15:8] of size
;* R7: Bits [7:0] of size
;* R3: Bits [23:16] of destination address
;* R2: Bits [15:8] of destination address
;* R1: Bits [7:0] of destination address
;* R4: Bits[15:8] of source address
;* R5: Bits [7:0] of source address
;*******************************************************************************
?PR?CYCONFIGCPYCODE?CYMEM  SEGMENT CODE
RSEG ?PR?CYCONFIGCPYCODE?CYMEM
_cyconfigcpycode:
    MOV DPS,#000h           ; Select DP0
    MOV A,R7                ; Size in R6:R7 (MSB in R6)
    ORL A,R6
    JZ _cyconfigcpycode_end ; Exit if size is 0
    MOV A,R7
    JZ _cyconfigcpycode_noinc
    INC R6                  ; Tweak loop count for DJNZ
_cyconfigcpycode_noinc:
    MOV DPH0,R4             ; Source address in R4:R5
    MOV DPL0,R5
    MOV DPX1,R3             ; Destination address in R3:R2:R1
    MOV DPH1,R2
    MOV DPL1,R1
_cyconfigcpycode_loop:
    CLR A
    MOVC A,@A+DPTR
    INC DPTR
    INC DPS                 ; Select DP1
    MOVX @DPTR,A
    INC DPTR
    DEC DPS                 ; Select DP0
    DJNZ R7,_cyconfigcpycode_loop
    DJNZ R6,_cyconfigcpycode_loop
_cyconfigcpycode_end:
    CLR A
    MOV DPX1,A
    RET

;*******************************************************************************
;* void cfg_write_bytes(const void far *table);
;* R3: Bits [23:16] of pointer to start of table
;* R2: Bits [15:8] of pointer to start of table
;* R1: Bits [7:0] of pointer to start of table
;* Reads data from cfg_byte_table and writes it to memory
;* cfg_byte_table contains a byte representing the number of records, followed
;* by a sequence of records:
;* struct cfg_byte_table_record_s {
;*     unsigned char dpx;
;*     unsigned char dph;
;*     unsigned char value[];
;* };
;* Source range must not cross a 64k boundary.
;*******************************************************************************
?PR?CFG_WRITE_BYTES?CYMEM   SEGMENT CODE
RSEG ?PR?CFG_WRITE_BYTES?CYMEM
_cfg_write_bytes:
    MOV R4,MXAX                     ; Save
    MOV R5,P2
    MOV DPX0,R3                     ; Start at beginning of table
    MOV DPH0,R2
    MOV DPL0,R1
    MOVX A,@DPTR
    MOV R1,A                        ; Number of ranges
    JZ _cfg_write_bytes_end

_cfg_write_bytes_outer:
    INC DPTR
    MOVX A,@DPTR
    MOV MXAX,A                      ; Extended address byte
    INC DPTR
    MOVX A,@DPTR
    MOV P2,A                        ; High address byte
    INC DPTR
    MOVX A,@DPTR
    JZ _cfg_write_bytes_outer
    MOV R2,A                        ; Count

_cfg_write_bytes_inner:
    INC DPTR
    MOVX A,@DPTR
    MOV R0,A
    INC DPTR
    MOVX A,@DPTR
    MOVX @R0,A                      ; Write to MXAX:P2:R0
    DJNZ R2,_cfg_write_bytes_inner

    DJNZ R1,_cfg_write_bytes_outer

_cfg_write_bytes_end:
    MOV P2,R5                       ; Restore
    MOV MXAX,R4
    CLR A
    MOV DPX0,A
    RET

;*******************************************************************************
;* void cfg_write_bytes_code(const void code *table);
;* R6:R7: Pointer to cfg_byte_table
;* Reads data from cfg_byte_table and writes it to memory
;* cfg_byte_table contains a byte representing the number of records, followed
;* by a sequence of records:
;* struct cfg_byte_table_record_s {
;*     unsigned char dpx;
;*     unsigned char dph;
;*     unsigned char value[];
;* };
;*******************************************************************************
?PR?CY_WRITE_BYTES_CODE?CYMEM   SEGMENT CODE
RSEG ?PR?CY_WRITE_BYTES_CODE?CYMEM
_cfg_write_bytes_code:
    MOV R4,MXAX                     ; Save
    MOV R5,P2
    MOV DPH0,R6                     ; Start at beginning of table
    MOV DPL0,R7
    CLR A
    MOVC A,@A+DPTR
    MOV R1,A                        ; Number of ranges
    JZ _cfg_write_bytes_code_end

_cfg_write_bytes_code_outer:
    INC DPTR
    CLR A
    MOVC A,@A+DPTR                  ; Extended address byte
    MOV MXAX,A
    INC DPTR
    CLR A
    MOVC A,@A+DPTR                  ; High address byte
    MOV P2,A
    INC DPTR
    CLR A
    MOVC A,@A+DPTR                  ; Count
    JZ _cfg_write_bytes_code_outer
    MOV R2,A

_cfg_write_bytes_code_inner:
    INC DPTR
    CLR A
    MOVC A,@A+DPTR                  ; Low address byte
    MOV R0,A
    INC DPTR
    CLR A
    MOVC A,@A+DPTR                  ; Value
    MOVX @R0,A                      ; Write to MXAX:P2:R0
    DJNZ R2,_cfg_write_bytes_code_inner

    DJNZ R1,_cfg_write_bytes_code_outer

_cfg_write_bytes_code_end:
    MOV P2,R5                       ; Restore
    MOV MXAX,R4
    RET

;*******************************************************************************
;* Read a byte
;* R3:R2:R1: Address
;* Return value in R7
;*******************************************************************************
?PR?CYREAD8?CYMEM   SEGMENT CODE
RSEG ?PR?CYREAD8?CYMEM
_cyread8:
    MOV DPX0,R3
_cyread8_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOVX A,@DPTR
    MOV DPX0,#0
    MOV R7,A
    RET

;*******************************************************************************
;* Write a byte
;* R3:R2:R1: Address
;* R5: Value
;*******************************************************************************
?PR?CYWRITE8?CYMEM  SEGMENT CODE
RSEG ?PR?CYWRITE8?CYMEM
_cywrite8:
    MOV DPX0,R3
_cywrite8_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOV A,R5
    MOVX @DPTR,A
    MOV DPX0,#0
    RET

;*******************************************************************************
;* Read a little-endian 16-bit value
;* R3:R2:R1: Address
;* May not cross a 64k boundary
;* Return value in R6:R7 (big endian, R6 is MSB)
;*******************************************************************************
?PR?CYREAD16?CYMEM  SEGMENT CODE
RSEG ?PR?CYREAD16?CYMEM
_cyread16:
    MOV DPX0,R3
_cyread16_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOVX A,@DPTR
    MOV R7,A    ; LSB
    INC DPTR
    MOVX A,@DPTR
    MOV R6,A    ; MSB
    MOV DPX0,#0
    RET

;*******************************************************************************
;* Write a little-endian 16-bit value
;* R3:R2:R1: Address
;* R4:R5: Value (big endian, R4 is MSB)
;* May not cross a 64k boundary
;*******************************************************************************
?PR?CYWRITE16?CYMEM SEGMENT CODE
RSEG ?PR?CYWRITE16?CYMEM
_cywrite16:
    MOV DPX0,R3
_cywrite16_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOV A,R5    ; LSB
    MOVX @DPTR,A
    INC DPTR
    MOV A,R4    ; MSB
    MOVX @DPTR,A
    MOV DPX0,#0
    RET

;*******************************************************************************
;* Read a little-endian 24-bit value
;* R3:R2:R1: Address
;* May not cross a 64k boundary
;* Return value in R4:R5:R6:R7 (big endian, R4 is MSB, R4 always 0)
;*******************************************************************************
?PR?CYREAD24?CYMEM  SEGMENT CODE
RSEG ?PR?CYREAD24?CYMEM
_cyread24:
    MOV DPX0,R3
_cyread24_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOVX A,@DPTR
    MOV R7,A    ; LSB
    INC DPTR
    MOVX A,@DPTR
    MOV R6,A
    INC DPTR
    MOVX A,@DPTR
    MOV R5,A
    CLR A
    MOV R4,A    ; MSB
    MOV DPX0,A
    RET

;*******************************************************************************
;* Write a little-endian 24-bit value
;* R3:R2:R1: Address
;* R4:R5:R6:R7: Value (big endian, R4 is MSB, R4 ignored)
;* May not cross a 64k boundary
;*******************************************************************************
?PR?CYWRITE24?CYMEM SEGMENT CODE
RSEG ?PR?CYWRITE24?CYMEM
_cywrite24:
    MOV DPX0,R3
_cywrite24_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOV A,R7    ; LSB
    MOVX @DPTR,A
    INC DPTR
    MOV A,R6
    MOVX @DPTR,A
    INC DPTR
    MOV A,R5
    MOVX @DPTR,A
    MOV DPX0,#0
    RET

;*******************************************************************************
;* Read a little-endian 32-bit value
;* R3:R2:R1: Address
;* May not cross a 64k boundary
;* Return value in R4:R5:R6:R7 (big endian, R4 is MSB)
;*******************************************************************************
?PR?CYREAD32?CYMEM  SEGMENT CODE
RSEG ?PR?CYREAD32?CYMEM
_cyread32:
    MOV DPX0,R3
_cyread32_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOVX A,@DPTR
    MOV R7,A    ; LSB
    INC DPTR
    MOVX A,@DPTR
    MOV R6,A
    INC DPTR
    MOVX A,@DPTR
    MOV R5,A
    INC DPTR
    MOVX A,@DPTR
    MOV R4,A    ; MSB
    MOV DPX0,#0
    RET

;*******************************************************************************
;* Write a little-endian 32-bit value
;* R3:R2:R1: Address
;* R4:R5:R6:R7: Value (big endian, R4 is MSB)
;* May not cross a 64k boundary
;*******************************************************************************
?PR?CYWRITE32?CYMEM SEGMENT CODE
RSEG ?PR?CYWRITE32?CYMEM
_cywrite32:
    MOV DPX0,R3
_cywrite32_nodpx:
    MOV DPH0,R2
    MOV DPL0,R1
    MOV A,R7    ; LSB
    MOVX @DPTR,A
    INC DPTR
    MOV A,R6
    MOVX @DPTR,A
    INC DPTR
    MOV A,R5
    MOVX @DPTR,A
    INC DPTR
    MOV A,R4    ; MSB
    MOVX @DPTR,A
    MOV DPX0,#0
    RET

    END
