/*******************************************************************************
* File Name: LED_F.h  
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

#if !defined(CY_PINS_LED_F_H) /* Pins LED_F_H */
#define CY_PINS_LED_F_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_F_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_F_Write(uint8 value) ;
void    LED_F_SetDriveMode(uint8 mode) ;
uint8   LED_F_ReadDataReg(void) ;
uint8   LED_F_Read(void) ;
uint8   LED_F_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_F_DRIVE_MODE_BITS        (3)
#define LED_F_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_F_DRIVE_MODE_BITS))

#define LED_F_DM_ALG_HIZ         (0x00u)
#define LED_F_DM_DIG_HIZ         (0x01u)
#define LED_F_DM_RES_UP          (0x02u)
#define LED_F_DM_RES_DWN         (0x03u)
#define LED_F_DM_OD_LO           (0x04u)
#define LED_F_DM_OD_HI           (0x05u)
#define LED_F_DM_STRONG          (0x06u)
#define LED_F_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_F_MASK               LED_F__MASK
#define LED_F_SHIFT              LED_F__SHIFT
#define LED_F_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_F_PS                     (* (reg32 *) LED_F__PS)
/* Port Configuration */
#define LED_F_PC                     (* (reg32 *) LED_F__PC)
/* Data Register */
#define LED_F_DR                     (* (reg32 *) LED_F__DR)
/* Input Buffer Disable Override */
#define LED_F_INP_DIS                (* (reg32 *) LED_F__PC2)


#if defined(LED_F__INTSTAT)  /* Interrupt Registers */

    #define LED_F_INTSTAT                (* (reg32 *) LED_F__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_F_DRIVE_MODE_SHIFT       (0x00u)
#define LED_F_DRIVE_MODE_MASK        (0x07u << LED_F_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_F_H */


/* [] END OF FILE */
