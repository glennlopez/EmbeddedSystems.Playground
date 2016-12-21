/*******************************************************************************
* File Name: PSoC3_8051.h
* Version 2.40
*
*  Description:
*   8051 register definitions for the PSoC3 family of parts.
*
*  Note:
*
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/


#if !defined(__PSoC3_8051_H__)
#define __PSoC3_8051_H__

#include <cyfitter.h>

sfr SFRPRT0DR       = 0x80;

sfr SP              = 0x81;
sfr DPL             = 0x82;
sfr DPH             = 0x83;
sfr DPL1            = 0x84;
sfr DPH1            = 0x85;
sfr DPS             = 0x86;

sfr SFRPRT0PS       = 0x89;
sfr SFRPRT0SEL      = 0x8A;
sfr SFRPRT1DR       = 0x90;
sfr SFRPRT1PS       = 0x91;

sfr DPX             = 0x93;
sfr DPX1            = 0x95;

sfr SFRPRT2DR       = 0x98;
sfr SFRPRT2PS       = 0x99;
sfr SFRPRT2SEL      = 0x9A;

sfr P2AX            = 0xA0;
#if (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 || \
     CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
sfr CPUCLK_DIV      = 0xA1;
#endif
sfr SFRPRT1SEL      = 0xA2;

sfr IE              = 0xA8;
sbit EA             = IE^7;

sfr SFRPRT3DR       = 0xB0;
sfr SFRPRT3PS       = 0xB1;
sfr SFRPRT3SEL      = 0xB2;
sfr SFRPRT4DR       = 0xC0;
sfr SFRPRT4PS       = 0xC1;
sfr SFRPRT4SEL      = 0xC2;
sfr SFRPRT5DR       = 0xC8;
sfr SFRPRT5PS       = 0xC9;
sfr SFRPRT5SEL      = 0xCA;

sfr PSW             = 0xD0;
sbit P              = PSW^0;
sbit F1             = PSW^1;
sbit OV             = PSW^2;
sbit RS0            = PSW^3;
sbit RS1            = PSW^4;
sbit F0             = PSW^5;
sbit AC             = PSW^6;
sbit CY             = PSW^7;

sfr SFRPRT6DR       = 0xD8;
sfr SFRPRT6PS       = 0xD9;
sfr SFRPRT6SEL      = 0xDA;

sfr ACC             = 0xE0;

sfr SFRPRT12DR      = 0xE8;
sfr SFRPRT12PS      = 0xE9;
sfr MXAX            = 0xEA;

sfr B               = 0xF0;

sfr SFRPRT12SEL     = 0xF2;
sfr SFRPRT15DR      = 0xF8;
sfr SFRPRT15PS      = 0xF9;
sfr SFRPRT15SEL     = 0xFA;



/* __PSoC3_8051_H__ */
#endif
