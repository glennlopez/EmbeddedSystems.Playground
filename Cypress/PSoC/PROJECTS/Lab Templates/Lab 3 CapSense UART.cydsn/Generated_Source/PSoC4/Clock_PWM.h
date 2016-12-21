/*******************************************************************************
* File Name: Clock_PWM.h
* Version 2.0
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

#if !defined(CY_CLOCK_Clock_PWM_H)
#define CY_CLOCK_Clock_PWM_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void Clock_PWM_Start(void);
void Clock_PWM_Stop(void);

void Clock_PWM_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_PWM_GetDividerRegister(void);
uint8  Clock_PWM_GetFractionalDividerRegister(void);

#define Clock_PWM_Enable()                         Clock_PWM_Start()
#define Clock_PWM_Disable()                        Clock_PWM_Stop()
#define Clock_PWM_SetDividerRegister(clkDivider, reset)  \
                        Clock_PWM_SetFractionalDividerRegister((clkDivider), 0)
#define Clock_PWM_SetDivider(clkDivider)           Clock_PWM_SetDividerRegister((clkDivider), 1)
#define Clock_PWM_SetDividerValue(clkDivider)      Clock_PWM_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define Clock_PWM_DIV_REG    (*(reg32 *)Clock_PWM__REGISTER)
#define Clock_PWM_ENABLE_REG Clock_PWM_DIV_REG

#endif /* !defined(CY_CLOCK_Clock_PWM_H) */

/* [] END OF FILE */
