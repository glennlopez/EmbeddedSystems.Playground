;*******************************************************************************
; FILENAME: KeilStart.a51
; Version 3.20
;
;  DESCRIPTION:
;   Bootup Code for PSoC3 chips using the Keil toolchain.
;
;*******************************************************************************
; Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;*******************************************************************************

;* We will supply our own register definitions.
$NOMOD51

;* PSoC Register definitions.
$INCLUDE (PSoC3_8051.inc)
$INCLUDE (cydevicekeil_trm.inc)

;* Application-specific definitions.
$INCLUDE (cyfitterkeil.inc)

EXTERN XDATA:BYTE (CyResetStatus)

ZERO_REG        EQU     CYREG_PHUB_CFGMEM23_CFG1
SIZEOF_IDATA    EQU     100h

_CyResetStatus  EQU     CYDEV_SRAM_SIZE - 1 ;Keeps track of the RESET_SRO status across induced reset
_CyResetInduced EQU     CYDEV_SRAM_SIZE - 2 ;Keeps track of whether we manually induced a reset

IBPSTACK        EQU     0
XBPSTACK        EQU     1
XBPSTACKTOP     EQU     CYDEV_SRAM_SIZE - 3 ;Keep in mind additional variables declared above
PBPSTACK        EQU     0

?C?XPAGE1SFR    DATA    093h
?C?XPAGE1RST    EQU     0

;*******************************************************************************
;* Placement.
;*******************************************************************************
                NAME    ?C_STARTUP

?C_C51STARTUP   SEGMENT   CODE
?STACK          SEGMENT   IDATA

                RSEG    ?STACK
                DS      1 ; Declare some data so the assembler will keep the labeled segment.

                EXTRN CODE (?C_START)
                EXTRN CODE (cyfitter_cfg)

IF DMA_CHANNELS_USED__MASK0 <> 0
                ;* Only necessary if the design contains a DMA component.
                EXTRN CODE (CyDmacConfigure)
ENDIF

IF CYDEV_BOOTLOADER_ENABLE <> 0
                EXTRN CODE (CyBtldr_CheckLaunch)
ENDIF

                PUBLIC  ?C_STARTUP, ?C?XPAGE1SFR, ?C?XPAGE1RST
                PUBLIC  STARTUP1   ; include STARTUP1 for bootloader

;*******************************************************************************
;* Reset vector.
;*******************************************************************************

                CSEG    AT      0
?C_STARTUP:
       ljmp     STARTUP1                            ; 3 bytes

;*******************************************************************************
;* Aligned routines
;*******************************************************************************

       ; The following routines require alignment to avoid crossing an 8-byte
       ; boundary in an inner loop.

       ; dma_wait
       ; Arguments:
       ; R6:R7  Address of BASIC_STATUS
       ; Waits for the CHAIN_ACTIVE bit to be cleared by the DMA controller.
       nop                                          ; 1 byte
       PUBLIC   _dma_wait
_dma_wait:
       mov      DPL, R7                             ; 2 bytes
       mov      DPH, R6                             ; 2 bytes
       ; The loop needs to be aligned to an 8-byte boundary
_dma_wait_loop:
       movx     A, @DPTR                            ; 1 byte
       anl      A, #01h                             ; 2 bytes   CHAIN_ACTIVE
       nop                                          ; 1 byte
       nop                                          ; 1 byte
       nop                                          ; 1 byte
       jnz      _dma_wait_loop                      ; 2 bytes
       ret                                          ; 1 byte

       ; clear_idata
       ; Arguments: None
       ; Writes zeros to IDATA.
       ; This code should not be called because it overwrites the call stack.
clear_idata:
       mov      R0, #SIZEOF_IDATA - 1               ; 2 bytes
       clr      A                                   ; 1 byte
       ; The loop needs to be aligned to a 4-byte boundary
clear_idata_loop:
       mov      @R0, A                              ; 1 byte
       djnz     R0, clear_idata_loop                ; 2 bytes
       ljmp     clear_idata_done                    ; 3 bytes

;*******************************************************************************
;* Startup entry Point.
;*******************************************************************************
                RSEG    ?C_C51STARTUP
STARTUP1:

       mov      ?C?XPAGE1SFR, #?C?XPAGE1RST         ; Set XDATA page
       mov      R0, #000                            ; Set by debugger when attached to indicate not to perform reset

IF CYDEV_DEBUGGING_ENABLE <> 0
       mov      DPH, #HIGH (CYDEV_DEBUG_ENABLE_REGISTER)
       mov      DPL, #LOW (CYDEV_DEBUG_ENABLE_REGISTER)
       movx     A, @DPTR
       orl      A, #CYDEV_DEBUG_ENABLE_MASK
       movx     @DPTR, A
       nop
       debugEnabled:
ENDIF


IF (CYDEV_CHIP_REVISION_USED > CYDEV_CHIP_REVISION_3A_ES2)
  IF (CYDEV_PROJ_TYPE <> CYDEV_PROJ_TYPE_LOADABLE)
           ; Handle case where Software Reset is needed in order to ensure NVLs have been setup properly on TO5
           ; R0 - Used to indicate Debugger Attached
           ; R1 - Used to hold CYREG_MLOGIC_REV_ID value
           ; R2 - Used to hold CYREG_RESET_SR0 value (saved in CyResetStatus after clear RAM), 
           ;      also used by cybtldrhelper.a51
           
           mov      DPTR, #CYREG_MLOGIC_REV_ID
           movx     A, @DPTR
           mov      R1, A
           mov      DPTR, #CYREG_RESET_SR0
           movx     A, @DPTR
           mov      R2, A
           cjne     R1, #003h, PERFORM_STARTUP    ; Only reset on TO5 (rev=3)
           anl      A, #020h
           cjne     A, #000h, RESTORE_RESET_DATA  ; If software reset, jump 
           cjne     R0, #000h, PERFORM_STARTUP    ; Set by debugger when attached
        PERFORM_SW_RESET:
           mov      A, R2                         ; Save the Reset information
           mov      DPTR, #_CyResetStatus
           movx     @DPTR, A
           mov      A, #001h
           mov      DPTR, #_CyResetInduced
           movx     @DPTR, A
           mov      DPTR, #CYREG_RESET_CR2        ; Perform the Reset
           movx     @DPTR, A
        RESTORE_RESET_DATA:                       ; Restore original Reset data
           mov      DPTR, #_CyResetInduced
           movx     A, @DPTR
           jz       PERFORM_STARTUP
           mov      DPTR, #_CyResetStatus
           movx     A, @DPTR
           mov      R2, A                         ; R2 used after SRAM clear, do not use!!!
        PERFORM_STARTUP:
  ENDIF
ENDIF


       mov      DPTR, #CYREG_CACHE_CR

IF (CYDEV_CONFIGURATION_IMOENABLED <> 0)
       mov      A, #(03h SHL 6)                     ; FLASH_CYCLES = 3 (3 cycles, up to 67MHz)
ELSE
       mov      A, #(01h SHL 6)                     ; FLASH_CYCLES = 1 (1 cycle, up to 22MHz)
ENDIF

       movx     @DPTR, A
       mov      sp, #?STACK-1                       ; Set the stack pointer.

IF CYDEV_BOOTLOADER_ENABLE <> 0
       ;* check if need to start loadable application, bootloaders always do this check first so
       ;* that the device does not get configured before we launch the user application which
       ;* has its own unique configuration
       lcall    CyBtldr_CheckLaunch
Btldr_NoLaunch:
ENDIF

IF (CYDEV_CONFIGURATION_CLEAR_SRAM <> 0)
  IF (CYDEV_CONFIGURATION_DMA == 0)

       ;* Clear SRAM using CPU
       mov      DPTR, #CYDEV_SRAM_BASE
       mov      R0, #LOW (CYDEV_SRAM_SIZE)
       mov      R1, #HIGH (CYDEV_SRAM_SIZE)
       clr      A
    INIT_SRAM:
       movx     @DPTR, A
       inc      DPTR
       djnz     R0, INIT_SRAM
       djnz     R1, INIT_SRAM                       ; Assumes CYDEV_SRAM_SIZE is at least 256 bytes

  ELSE
  
       ;* Clear SRAM using DMA
       mov      DPTR, #ZERO_REG
       clr      A
       movx     @DPTR, A
       inc      DPTR
       movx     @DPTR, A
       inc      DPTR
       movx     @DPTR, A
       inc      DPTR
       movx     @DPTR, A
       mov      DPTR, #CYREG_PHUB_CH0_BASIC_CFG
       movx     @DPTR, A                            ; Make sure channel is disabled
       mov      DPTR, #(CYREG_PHUB_CH0_BASIC_STATUS + 1)
       movx     @DPTR, A                            ; Initial TD 0
       mov      DPTR, #CYREG_PHUB_CH1_BASIC_CFG
       movx     @DPTR, A                            ; Disable channel

       ;* CFGMEM0 Setup
       mov      DPTR, #CYREG_PHUB_CFGMEM0_CFG0
       mov      A, #010h                            ; burstcnt
       movx     @DPTR, A
       mov      DPTR, #CYREG_PHUB_CFGMEM0_CFG1
       clr      A
       movx     @DPTR, A                            ; src_base_adr low
       inc      DPTR
       movx     @DPTR, A                            ; src_base_adr high
       inc      DPTR
       movx     @DPTR, A                            ; dst_base_adr low
       inc      DPTR
       movx     @DPTR, A                            ; dst_base_adr high


       ;* TD configuration
       mov      DPTR, #CYREG_PHUB_TDMEM0_ORIG_TD0
       mov      R0, #000h                           ; R0 tracks next TD
    SETUP_TD:
       inc      R0
       mov      A, #000h
       movx     @DPTR, A                            ; Set TD count (lower byte)
       inc      DPTR
       mov      A, #08h
       movx     @DPTR, A                            ; Set TD count (upper byte)
       mov      A, R0
       cjne     R0, #((CYDEV_SRAM_SIZE + 2047) / 2048), SETUP_ADDR
       mov      A, #0FFh
    SETUP_ADDR:
       inc      DPTR
       movx     @DPTR, A                            ; Set Next TD
       inc      DPTR
       mov      A, #022h                            ; auto_exec_next, inc_dst_adr
       movx     @DPTR, A                            ; Set TD Configuration

       inc      DPTR
       mov      A, #LOW ZERO_REG
       movx     @DPTR, A                            ; Set Source Addr Low
       inc      DPTR
       mov      A, #HIGH ZERO_REG
       movx     @DPTR, A                            ; Set Source Addr High
       inc      DPTR
       clr      A
       movx     @DPTR, A                            ; Set Destination Addr Low
       inc      DPTR
       mov      A, R0
       dec      A
       mov      B, #008h
       mul      AB
       movx     @DPTR, A                            ; Set Destination Addr High
       inc      DPTR
       cjne     R0, #((CYDEV_SRAM_SIZE + 2047) / 2048), SETUP_TD
       

       ;* Start DMA
       mov      DPTR, #CYREG_PHUB_CH0_BASIC_CFG
       mov      A, #01h
       movx     @DPTR, A
       mov      DPTR, #CYREG_PHUB_CH0_ACTION
       movx     @DPTR, A
  ENDIF
ENDIF

IF (CYDEV_CHIP_MEMBER_USED == CYDEV_CHIP_MEMBER_3A AND CYDEV_ECC_ENABLE <> 0)
       ;* Workaround for an issue that could cause a false ECC interrupt at startup
       mov      DPTR, #CYREG_CACHE_INT_LOG3
       movx     A, @DPTR                            ; clear CACHE_INT_LOG3 (clear on read)
       mov      DPTR, #CYREG_CACHE_INT_LOG4
       movx     A, @DPTR                            ; clear CACHE_INT_LOG4 (clear on read)
       mov      DPTR, #CYREG_INTC_CLR_PD0
       mov      A, #02h
       movx     @DPTR, A                            ; clear interrupt 1
ENDIF


IF ((CYDEV_CONFIGURATION_CLEAR_SRAM <> 0) AND (CYDEV_CONFIGURATION_DMA <> 0))
       ;* Wait for DMA to finish
       mov      R6, #HIGH CYREG_PHUB_CH0_BASIC_STATUS
       mov      R7, #LOW CYREG_PHUB_CH0_BASIC_STATUS
       lcall    _dma_wait
       mov      DPTR, #CYREG_PHUB_CH0_BASIC_CFG
       movx     @DPTR, A                            ; Disable channel
ENDIF


       ; Save the RESET_SR0 register in the CyResetStatus variable
       mov      A, R2                       ; R2 set prior to SRAM clearing
       mov      DPTR, #CyResetStatus
       movx     @DPTR, A
       

       ;* Clear idata.
       ljmp     clear_idata
clear_idata_done:

IF IBPSTACK <> 0
       EXTRN DATA (?C_IBP)

       ;* ?C_IBP acts as a base pointer to the reentrant stack for the SMALL model.
       mov      ?C_IBP, #LOW IBPSTACKTOP
ENDIF

IF XBPSTACK <> 0
       EXTRN DATA (?C_XBP)

       ;* ?C_XBP acts as a base pointer to the reentrant stack for the LARGE model.
       mov      ?C_XBP, #HIGH XBPSTACKTOP
       mov      ?C_XBP+1, #LOW XBPSTACKTOP
ENDIF

IF PBPSTACK <> 0
       EXTRN DATA (?C_PBP)

       ;* ?C_XBP acts as a base pointer to the reentrant stack for the COMPACT model.
       mov      ?C_PBP, #LOW PBPSTACKTOP
ENDIF

       ;* Initialize the configuration registers.
       lcall    cyfitter_cfg

IF DMA_CHANNELS_USED__MASK0 <> 0

       ;* Setup DMA - only necessary if the design contains a DMA component.
       lcall    CyDmacConfigure

ENDIF

       ;* Jump to Keil's variable initialization and then main.
       ljmp     ?C_START

;*******************************************************************************
;* End of startup code.
;*******************************************************************************

       END
