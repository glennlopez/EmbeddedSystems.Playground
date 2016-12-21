/*******************************************************************************
* File Name: LED_8.h  
* Version 2.5
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

#if !defined(CY_PINS_LED_8_H) /* Pins LED_8_H */
#define CY_PINS_LED_8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_8_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_8_Write(uint8 value) ;
void    LED_8_SetDriveMode(uint8 mode) ;
uint8   LED_8_ReadDataReg(void) ;
uint8   LED_8_Read(void) ;
uint8   LED_8_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_8_DRIVE_MODE_BITS        (3)
#define LED_8_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_8_DRIVE_MODE_BITS))
#define LED_8_DRIVE_MODE_SHIFT       (0x00u)
#define LED_8_DRIVE_MODE_MASK        (0x07u << LED_8_DRIVE_MODE_SHIFT)

#define LED_8_DM_ALG_HIZ         (0x00u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_DIG_HIZ         (0x01u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_RES_UP          (0x02u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_RES_DWN         (0x03u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_OD_LO           (0x04u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_OD_HI           (0x05u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_STRONG          (0x06u << LED_8_DRIVE_MODE_SHIFT)
#define LED_8_DM_RES_UPDWN       (0x07u << LED_8_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define LED_8_MASK               LED_8__MASK
#define LED_8_SHIFT              LED_8__SHIFT
#define LED_8_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_8_PS                     (* (reg32 *) LED_8__PS)
/* Port Configuration */
#define LED_8_PC                     (* (reg32 *) LED_8__PC)
/* Data Register */
#define LED_8_DR                     (* (reg32 *) LED_8__DR)
/* Input Buffer Disable Override */
#define LED_8_INP_DIS                (* (reg32 *) LED_8__PC2)


#if defined(LED_8__INTSTAT)  /* Interrupt Registers */

    #define LED_8_INTSTAT                (* (reg32 *) LED_8__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins LED_8_H */


/* [] END OF FILE */
