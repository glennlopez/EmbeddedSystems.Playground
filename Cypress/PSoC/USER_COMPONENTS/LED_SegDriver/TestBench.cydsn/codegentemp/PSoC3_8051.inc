;*******************************************************************************
; FILENAME: PSoC3_8051.inc 
; Version 2.40
;
;  DESCRIPTION:
;    8051 register definitions for the PSoC3 family of parts.
;
;   NOTE:
;    
;
;
;*******************************************************************************
; Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
; You may use this file only in accordance with the license, terms, conditions, 
; disclaimers, and limitations in the end user license agreement accompanying 
; the software package with which this file was provided.
;*******************************************************************************

#if !defined(PSoC3_8051_INC)
#define PSoC3_8051_INC

$INCLUDE (cyfitterkeil.inc)

SFRPRT0DR       DATA 080H

SP              DATA 081H
DPL             DATA 082H
DPH             DATA 083H
DPL1            DATA 084H
DPH1            DATA 085H
DPS             DATA 086H

SFRPRT0PS       DATA 089H
SFRPRT0SEL      DATA 08AH
SFRPRT1DR       DATA 090H
SFRPRT1PS       DATA 091H

DPX             DATA 093H
DPX1            DATA 095H

SFRPRT2DR       DATA 098H
SFRPRT2PS       DATA 099H
SFRPRT2SEL      DATA 09AH

P2AX            DATA 0A0H
IF (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 OR \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
CPUCLK_DIV      DATA 0A1H
ENDIF
SFRPRT1SEL      DATA 0A2H

IE              DATA 0A8H
  EA            BIT 0A8H+7H

SFRPRT3DR       DATA 0B0H
SFRPRT3PS       DATA 0B1H
SFRPRT3SEL      DATA 0B2H
SFRPRT4DR       DATA 0C0H
SFRPRT4PS       DATA 0C1H
SFRPRT4SEL      DATA 0C2H
SFRPRT5DR       DATA 0C8H
SFRPRT5PS       DATA 0C9H
SFRPRT5SEL      DATA 0CAH

PSW             DATA 0D0H
  P             BIT 0D0H+0H
  F1            BIT 0D0H+1H
  OV            BIT 0D0H+2H
  RS0           BIT 0D0H+3H
  RS1           BIT 0D0H+4H
  F0            BIT 0D0H+5H
  AC            BIT 0D0H+6H
  CY            BIT 0D0H+7H

SFRPRT6DR       DATA 0D8H
SFRPRT6PS       DATA 0D9H
SFRPRT6SEL      DATA 0DAH

ACC             DATA 0E0H

SFRPRT12DR      DATA 0E8H
SFRPRT12PS      DATA 0E9H
MXAX            DATA 0EAH

B               DATA 0F0H

SFRPRT12SEL     DATA 0F2H
SFRPRT15DR      DATA 0F8H
SFRPRT15PS      DATA 0F9H
SFRPRT15SEL     DATA 0FAH

; PSoC3_8051_INC
#endif
