/*******************************************************************************
* File Name: LED_Refresh_Clock.h
* Version 1.60
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_CLOCK_LED_Refresh_Clock_H)
#define CY_CLOCK_LED_Refresh_Clock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void LED_Refresh_Clock_Start(void) ;
void LED_Refresh_Clock_Stop(void) ;

#if(!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2) && \
	!(CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC5 && \
	CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_5A_ES1))
void LED_Refresh_Clock_StopBlock(void) ;
#endif

void LED_Refresh_Clock_StandbyPower(uint8 state) ;
void LED_Refresh_Clock_SetDividerRegister(uint16 clkDivider, uint8 reset) ;
uint16 LED_Refresh_Clock_GetDividerRegister(void) ;
void LED_Refresh_Clock_SetModeRegister(uint8 modeBitMask) ;
void LED_Refresh_Clock_ClearModeRegister(uint8 modeBitMask) ;
uint8 LED_Refresh_Clock_GetModeRegister(void) ;
void LED_Refresh_Clock_SetSourceRegister(uint8 clkSource) ;
uint8 LED_Refresh_Clock_GetSourceRegister(void) ;
#if defined(LED_Refresh_Clock__CFG3)
void LED_Refresh_Clock_SetPhaseRegister(uint8 clkPhase) ;
uint8 LED_Refresh_Clock_GetPhaseRegister(void) ;
#endif

#define LED_Refresh_Clock_Enable()                       LED_Refresh_Clock_Start()
#define LED_Refresh_Clock_Disable()                      LED_Refresh_Clock_Stop()
#define LED_Refresh_Clock_SetDivider(clkDivider)         LED_Refresh_Clock_SetDividerRegister(clkDivider, 1)
#define LED_Refresh_Clock_SetDividerValue(clkDivider)    LED_Refresh_Clock_SetDividerRegister((clkDivider) - 1, 1)
#define LED_Refresh_Clock_SetMode(clkMode)               LED_Refresh_Clock_SetModeRegister(clkMode)
#define LED_Refresh_Clock_SetSource(clkSource)           LED_Refresh_Clock_SetSourceRegister(clkSource)
#if defined(LED_Refresh_Clock__CFG3)
#define LED_Refresh_Clock_SetPhase(clkPhase)             LED_Refresh_Clock_SetPhaseRegister(clkPhase)
#define LED_Refresh_Clock_SetPhaseValue(clkPhase)        LED_Refresh_Clock_SetPhaseRegister((clkPhase) + 1)
#endif


/***************************************
*           API Constants
***************************************/

/* Constants SetPhase(), clkPhase parameter. Only valid for PSoC 3 ES2 and earlier. See datasheet for details. */
#if CYDEV_CHIP_FAMILY_USED == CYDEV_CHIP_FAMILY_PSOC3 && \
   (CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES1 || \
    CYDEV_CHIP_REVISION_USED == CYDEV_CHIP_REVISION_3A_ES2)
#define CYCLK_2_5NS             0x01 /* 2.5 ns delay. */
#define CYCLK_3_5NS             0x02 /* 3.5 ns delay. */
#define CYCLK_4_5NS             0x03 /* 4.5 ns delay. */
#define CYCLK_5_5NS             0x04 /* 5.5 ns delay. */
#define CYCLK_6_5NS             0x05 /* 6.5 ns delay. */
#define CYCLK_7_5NS             0x06 /* 7.5 ns delay. */
#define CYCLK_8_5NS             0x07 /* 8.5 ns delay. */
#define CYCLK_9_5NS             0x08 /* 9.5 ns delay. */
#define CYCLK_10_5NS            0x09 /* 10.5 ns delay. */
#define CYCLK_11_5NS            0x0A /* 11.5 ns delay. */
#define CYCLK_12_5NS            0x0B /* 12.5 ns delay. */
#endif


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define LED_Refresh_Clock_CLKEN              (* (reg8 *) LED_Refresh_Clock__PM_ACT_CFG)
#define LED_Refresh_Clock_CLKEN_PTR          ((reg8 *) LED_Refresh_Clock__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define LED_Refresh_Clock_CLKSTBY            (* (reg8 *) LED_Refresh_Clock__PM_STBY_CFG)
#define LED_Refresh_Clock_CLKSTBY_PTR        ((reg8 *) LED_Refresh_Clock__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define LED_Refresh_Clock_DIV_LSB            (* (reg8 *) LED_Refresh_Clock__CFG0)
#define LED_Refresh_Clock_DIV_LSB_PTR        ((reg8 *) LED_Refresh_Clock__CFG0)
#define LED_Refresh_Clock_DIV_PTR            ((reg16 *) LED_Refresh_Clock__CFG0)

/* Clock MSB divider configuration register. */
#define LED_Refresh_Clock_DIV_MSB            (* (reg8 *) LED_Refresh_Clock__CFG1)
#define LED_Refresh_Clock_DIV_MSB_PTR        ((reg8 *) LED_Refresh_Clock__CFG1)

/* Mode and source configuration register */
#define LED_Refresh_Clock_MOD_SRC            (* (reg8 *) LED_Refresh_Clock__CFG2)
#define LED_Refresh_Clock_MOD_SRC_PTR        ((reg8 *) LED_Refresh_Clock__CFG2)

#if defined(LED_Refresh_Clock__CFG3)
/* Analog clock phase configuration register */
#define LED_Refresh_Clock_PHASE              (* (reg8 *) LED_Refresh_Clock__CFG3)
#define LED_Refresh_Clock_PHASE_PTR          ((reg8 *) LED_Refresh_Clock__CFG3)
#endif


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define LED_Refresh_Clock_CLKEN_MASK         LED_Refresh_Clock__PM_ACT_MSK
#define LED_Refresh_Clock_CLKSTBY_MASK       LED_Refresh_Clock__PM_STBY_MSK

/* CFG2 field masks */
#define LED_Refresh_Clock_SRC_SEL_MSK        LED_Refresh_Clock__CFG2_SRC_SEL_MASK
#define LED_Refresh_Clock_MODE_MASK          (~(LED_Refresh_Clock_SRC_SEL_MSK))

#if defined(LED_Refresh_Clock__CFG3)
/* CFG3 phase mask */
#define LED_Refresh_Clock_PHASE_MASK         LED_Refresh_Clock__CFG3_PHASE_DLY_MASK
#endif

#endif /* CY_CLOCK_LED_Refresh_Clock_H */


/* [] END OF FILE */
