;-------------------------------------------------------------------------------
; FILENAME: CyBootAsmKeil.a51
; Version 2.40
;
;  DESCRIPTION:
;    Assembly routines for Keil A51.
;
;-------------------------------------------------------------------------------
; Copyright 2010-2011, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;-------------------------------------------------------------------------------

$NOMOD51
$INCLUDE (cyfitterkeil.inc)
$INCLUDE (PSoC3_8051.inc)

NAME CYBOOTASMKEIL


;-------------------------------------------------------------------------------
; CyDelayCycles
;-------------------------------------------------------------------------------
; 
; Summary:
;   Delays for at least the given number of cycles.
;
; Parameters:
;   count: number of cycles (R4:R7, MSB in R4)
;
; Return:
;   void.
;
; Destroys:
;   R0, R3, R4, R5, R6, R7
;-------------------------------------------------------------------------------
; void CyDelayCycles(uint32 count);
PUBLIC _CyDelayCycles
?PR?CYDELAYCYCLES?CYBOOTASMKEIL SEGMENT CODE PAGE    ; Align to 256-byte boundary
RSEG ?PR?CYDELAYCYCLES?CYBOOTASMKEIL
_CyDelayCycles:                     ; cycles bytes
    MOV A, R4                       ;   1   1
    ORL A, R5                       ;   1   1
    ORL A, R6                       ;   1   1
    JNZ _CyDelayCycles_32           ;   4   2   If the delay is small, use non-cache-dependent loop
    MOV R0, #-4                     ;   2   2   4 cycles per iteration
    MOV A, R7                       ;   1   1
    ADD A, #-23                     ;   2   2   (8-byte boundary) Subtract overhead
    JNC _CyDelayCycles_done         ;   3   2
_CyDelayCycles_loop8:
    ADD A, R0                       ;   1   1
    JC _CyDelayCycles_loop8         ;   3   2
_CyDelayCycles_done:
    RET                             ;   4   1

    NOP                             ;   1   1   (8-byte boundary) alignment
    NOP                             ;   1   1
_CyDelayCycles_32:
IF CYDEV_INSTRUCT_CACHE_ENABLED <> 0
    MOV R3, #-15                    ;   2   2   15 CPU cycles per iteration for instructions
    MOV R0, #-38                    ;   2   2   Overhead
    NOP                             ;   1   1   alignment
    NOP                             ;   1   1
ELSE
    MOV R0, #-59                    ;   2   2   Overhead (60+8*FLASH_CYCLES)
    MOV DPTR, #CYREG_CACHE_CR       ;   3   3   Get wait states
    MOVX A, @DPTR                   ;   2+  1
    SWAP A                          ;   1   1   (8-byte boundary)
    RR A                            ;   1   1
    RR A                            ;   1   1
    ANL A, #03h                     ;   2   2
    MOV DPTR, #cy_flash_cycles      ;   3   3
    MOVC A, @A+DPTR                 ;   5+  1   (8-byte boundary) Get number of wait states
    ADD A, ACC                      ;   2   2   2 reads per iteration
    ADD A, #15                      ;   2   2   15 CPU cycles per iteration for instructions
    CPL A                           ;   1   1   Negate
    INC A                           ;   1   1
    MOV R3, A                       ;   1   1
ENDIF

    MOV A, R7                       ;   1   1   (8-byte boundary) Subtract overhead
    ADD A, R0                       ;   1   1
    MOV R7, A                       ;   1   1
    MOV R0, #0FFh                   ;   2   2
    MOV A, R6                       ;   1   1
    ADDC A, R0                      ;   1   1
    MOV R6, A                       ;   1   1
    MOV A, R5                       ;   1   1   (8-byte boundary)
    ADDC A, R0                      ;   1   1
    MOV R5, A                       ;   1   1
    MOV A, R4                       ;   1   1
    ADDC A, R0                      ;   1   1
    MOV R4, A                       ;   1   1
    JNC _CyDelayCycles_done         ;   3   2
_CyDelayCycles_loop32:
    MOV A, R7                       ;   1   1   (8-byte boundary)
    ADD A, R3                       ;   1   1
    MOV R7, A                       ;   1   1
    MOV A, R6                       ;   1   1
    ADDC A, R0                      ;   1   1
    MOV R6, A                       ;   1   1
    MOV A, R5                       ;   1   1
    ADDC A, R0                      ;   1   1
    MOV R5, A                       ;   1   1   (8-byte boundary)
    MOV A, R4                       ;   1   1
    ADDC A, R0                      ;   1   1
    MOV R4, A                       ;   1   1
    JC _CyDelayCycles_loop32        ;   3   2
    RET                             ;   1   1

cy_flash_cycles:
IF CYDEV_CHIP_REVISION_USED <= CYDEV_CHIP_REVISION_3A_ES2
    DB 6, 3, 4, 5
ELSE
    DB 5, 2, 3, 4
ENDIF


;-------------------------------------------------------------------------------
; CyDelayUs
;-------------------------------------------------------------------------------
;
; Summary:
;   Delays for at least the given number of microseconds.
;
; Parameters:
;   microseconds: delay in microseconds (R6:R7, MSB in R6)
;
; Return:
;   void.
;
; Destroys:
;   R0, R1, R2, R3, R4, R5, R6, R7
;
;-------------------------------------------------------------------------------
; void CyDelayUs(uint16 microseconds);
EXTERN XDATA:BYTE (cydelay_freq_mhz)
PUBLIC _CyDelayUs
?PR?CYDELAYUS?CYBOOTASMKEIL SEGMENT CODE DWORD    ; Align to 4-byte boundary
RSEG ?PR?CYDELAYUS?CYBOOTASMKEIL
_CyDelayUs:                   ; cycles bytes
    MOV A, R6                 ;    1    1
    MOV R2, A                 ;    1    1
    MOV DPTR, #cydelay_freq_mhz    ;    3    3    R5:R6:R7 = R2:R7 * cydelay_freq_mhz
    MOVX A, @DPTR             ;    2+    1
    MOV R0, A                 ;    1    1    Save cydelay_freq_mhz
    MOV B, R7                 ;    2    2
    MUL AB                    ;    2    1    A * LSB
    MOV R7, A                 ;    1    1    product LSB
    MOV R6, B                 ;    3    2    product MSB
    MOV A, R0                 ;    1    1    cydelay_freq_mhz
    MOV B, R2                 ;    3    3
    MUL AB                    ;    2    1    A * MSB
    ADD A, R6                 ;    1    1
    MOV R6, A                 ;    1    1    product LSB
    MOV A, B                  ;    2    2    product MSB
    ADDC A, #0                ;    2    2    carry
    MOV R5, A                 ;    1    1
    MOV A, R7                 ;    1    1
    ADD A, #-55               ;    2    2    Subtract estimated overhead
    MOV R7, A                 ;    1    1
    MOV R0, #0FFh             ;    2    2
    MOV A, R6                 ;    1    1
    ADDC A, R0                ;    1    1
    MOV R6, A                 ;    1    1
    MOV A, R5                 ;    1    1
    ADDC A, R0                ;    1    1
    MOV R5, A                 ;    1    1
    CLR A                     ;    1    1
    ADDC A, R0                ;    1    1
    MOV R4, A                 ;    1    1
    JNC _CyDelayUs_done       ;    3    2    Overhead exceeds requested delay
    LJMP _CyDelayCycles       ;    4    3
_CyDelayUs_done:
    RET


;-------------------------------------------------------------------------------
; Function Name: CyEnterCriticalSection
;-------------------------------------------------------------------------------
; Summary:
;   Enters a critical section and disables interrupts.
;   Implementation of CyEnterCriticalSection manipulates the IRQ enable bit with 
;   interrupts still enabled. The test and set of the interrupt bits is not atomic; 
;   this is true for both PSoC3 and PSoC5. 
;   Therefore, to avoid corrupting processor state, 
;   it must be the policy that all interrupt routines restore the 
;   interrupt enable bits as they were found on entry.
;   
; Parameters:
;   void.
;
; Return:
;   Returns a value containing two bits.
;     bit 0: 1 if interrupts were enabled before CyEnterCriticalSection was
;            called.
;     bit 1: 1 if IRQ generation was disabled before CyEnterCriticalSection was
;            called.
;
;-------------------------------------------------------------------------------
; uint8 CyEnterCriticalSection(void);
PUBLIC CyEnterCriticalSection
?PR?CYENTERCRITICALSECTION?CYBOOTASMKEIL SEGMENT CODE
RSEG ?PR?CYENTERCRITICALSECTION?CYBOOTASMKEIL
CyEnterCriticalSection:
IF CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A AND CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A AND CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3
    MOV DPTR, #CYDEV_INTC_CSR_EN
    MOVX A, @DPTR
    MOV R0, A
    ORL A, #02h                             ; Disable IRQ generation
    MOVX @DPTR, A
    MOV A, R0
    ANL A, #02h
    MOV R7, A                               ; Save IRQ generation state
ELSE
    MOV R7, #00h
ENDIF
    JBC EA, CyEnterCriticalSection_ret1     ; Test and clear interrupt enable
    RET
CyEnterCriticalSection_ret1:
    MOV A, #01h
    ORL A, R7                               ; Save interrupt enable state
    MOV R7, A
    RET


;-------------------------------------------------------------------------------
; Function Name: CyExitCriticalSection
;-------------------------------------------------------------------------------
; Summary:
;   Ends a critical section, re-enabling interrupts if they were enabled before
;   entering the critical section.
;   Implementation of CyEnterCriticalSection manipulates the IRQ enable bit with 
;   interrupts still enabled. The test and set of the interrupt bits is not atomic; 
;   this is true for both PSoC3 and PSoC5. 
;   Therefore, to avoid corrupting processor state, 
;   it must be the policy that all interrupt routines restore the 
;   interrupt enable bits as they were found on entry.
;   
; Parameters:
;   savedIntrStatus: Should be the value that was returned from
;     CyEnterCriticalSection.
;     bit 0: 1 if interrupts were enabled before CyExitCriticalSection was
;            called.
;     bit 1: 1 if IRQ generation was disabled before CyExitCriticalSection was
;            called.
;
; Return:
;   void.
;
;-------------------------------------------------------------------------------
; void CyExitCriticalSection(uint8 savedIntrStatus);
PUBLIC _CyExitCriticalSection
?PR?CYEXITCRITICALSECTION?CYBOOTASMKEIL SEGMENT CODE
RSEG ?PR?CYEXITCRITICALSECTION?CYBOOTASMKEIL
_CyExitCriticalSection:
    MOV A, R7
    ANL A, #01h
    JZ _CyExitCriticalSection_disable       ; Restore interrupt enable state
    SETB EA
    SJMP _CyExitCriticalSection_IrqGen
_CyExitCriticalSection_disable:
    CLR EA
_CyExitCriticalSection_IrqGen:
IF CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A AND CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A AND CYDEV_CHIP_REVISION_USED >= CYDEV_CHIP_REVISION_3A_ES3
    MOV A, R7
    ANL A, #02h
    MOV R7, A
    MOV DPTR, #CYDEV_INTC_CSR_EN
    MOVX A, @DPTR
    ANL A, #NOT 02h
    ORL A, R7                               ; Restore IRQ generation state
    MOVX @DPTR, A
ENDIF
    RET

;-------------------------------------------------------------------------------
; Function Name: _CyDelay
;-------------------------------------------------------------------------------
; Summary:
;   Added to support backward compatibility, CyDelay function which is non-reentrant.
;
?PR?_CyDelay?CYBOOTASMKEIL  SEGMENT CODE
    
; Extern declaration of reentrant CyDelay function
EXTRN    CODE (_?CyDelay)

; Export our non-reentrant CyDelay symbol
PUBLIC    _CyDelay

; Create _CyDelay function for binary compatibility with shipping iAP kit
RSEG  ?PR?_CyDelay?CYBOOTASMKEIL
_CyDelay:
    USING    0
    ; Have same calling conventions, args in R4-R7.
    LCALL    _?CyDelay
    RET

    END


;[] END OF FILE
