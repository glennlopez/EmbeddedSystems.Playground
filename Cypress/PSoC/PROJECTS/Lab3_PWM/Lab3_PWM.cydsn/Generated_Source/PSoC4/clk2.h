/*******************************************************************************
* File Name: clk2.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_clk2_H)
#define CY_CLOCK_clk2_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void clk2_StartEx(uint32 alignClkDiv);
#define clk2_Start() \
    clk2_StartEx(clk2__PA_DIV_ID)

#else

void clk2_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void clk2_Stop(void);

void clk2_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 clk2_GetDividerRegister(void);
uint8  clk2_GetFractionalDividerRegister(void);

#define clk2_Enable()                         clk2_Start()
#define clk2_Disable()                        clk2_Stop()
#define clk2_SetDividerRegister(clkDivider, reset)  \
    clk2_SetFractionalDividerRegister((clkDivider), 0u)
#define clk2_SetDivider(clkDivider)           clk2_SetDividerRegister((clkDivider), 1u)
#define clk2_SetDividerValue(clkDivider)      clk2_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define clk2_DIV_ID     clk2__DIV_ID

#define clk2_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define clk2_CTRL_REG   (*(reg32 *)clk2__CTRL_REGISTER)
#define clk2_DIV_REG    (*(reg32 *)clk2__DIV_REGISTER)

#define clk2_CMD_DIV_SHIFT          (0u)
#define clk2_CMD_PA_DIV_SHIFT       (8u)
#define clk2_CMD_DISABLE_SHIFT      (30u)
#define clk2_CMD_ENABLE_SHIFT       (31u)

#define clk2_CMD_DISABLE_MASK       ((uint32)((uint32)1u << clk2_CMD_DISABLE_SHIFT))
#define clk2_CMD_ENABLE_MASK        ((uint32)((uint32)1u << clk2_CMD_ENABLE_SHIFT))

#define clk2_DIV_FRAC_MASK  (0x000000F8u)
#define clk2_DIV_FRAC_SHIFT (3u)
#define clk2_DIV_INT_MASK   (0xFFFFFF00u)
#define clk2_DIV_INT_SHIFT  (8u)

#else 

#define clk2_DIV_REG        (*(reg32 *)clk2__REGISTER)
#define clk2_ENABLE_REG     clk2_DIV_REG
#define clk2_DIV_FRAC_MASK  clk2__FRAC_MASK
#define clk2_DIV_FRAC_SHIFT (16u)
#define clk2_DIV_INT_MASK   clk2__DIVIDER_MASK
#define clk2_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_clk2_H) */

/* [] END OF FILE */
