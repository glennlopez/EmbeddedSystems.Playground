/*******************************************************************************
* File Name: LED_B.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED_B_H) /* Pins LED_B_H */
#define CY_PINS_LED_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_B_Write(uint8 value) ;
void    LED_B_SetDriveMode(uint8 mode) ;
uint8   LED_B_ReadDataReg(void) ;
uint8   LED_B_Read(void) ;
uint8   LED_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_B_DRIVE_MODE_BITS        (3)
#define LED_B_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_B_DRIVE_MODE_BITS))

#define LED_B_DM_ALG_HIZ         (0x00u)
#define LED_B_DM_DIG_HIZ         (0x01u)
#define LED_B_DM_RES_UP          (0x02u)
#define LED_B_DM_RES_DWN         (0x03u)
#define LED_B_DM_OD_LO           (0x04u)
#define LED_B_DM_OD_HI           (0x05u)
#define LED_B_DM_STRONG          (0x06u)
#define LED_B_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_B_MASK               LED_B__MASK
#define LED_B_SHIFT              LED_B__SHIFT
#define LED_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_B_PS                     (* (reg32 *) LED_B__PS)
/* Port Configuration */
#define LED_B_PC                     (* (reg32 *) LED_B__PC)
/* Data Register */
#define LED_B_DR                     (* (reg32 *) LED_B__DR)
/* Input Buffer Disable Override */
#define LED_B_INP_DIS                (* (reg32 *) LED_B__PC2)


#if defined(LED_B__INTSTAT)  /* Interrupt Registers */

    #define LED_B_INTSTAT                (* (reg32 *) LED_B__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_B_DRIVE_MODE_SHIFT       (0x00u)
#define LED_B_DRIVE_MODE_MASK        (0x07u << LED_B_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_B_H */


/* [] END OF FILE */
