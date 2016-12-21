/*******************************************************************************
* File Name: Common_3.h  
* Version 1.60
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PINS_Common_3_H) /* Pins Common_3_H */
#define CY_PINS_Common_3_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Common_3_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Common_3_Write(uint8 value) ;
void    Common_3_SetDriveMode(uint8 mode) ;
uint8   Common_3_ReadDataReg(void) ;
uint8   Common_3_Read(void) ;
uint8   Common_3_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Common_3_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Common_3_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Common_3_DM_RES_UP          PIN_DM_RES_UP
#define Common_3_DM_RES_DWN         PIN_DM_RES_DWN
#define Common_3_DM_OD_LO           PIN_DM_OD_LO
#define Common_3_DM_OD_HI           PIN_DM_OD_HI
#define Common_3_DM_STRONG          PIN_DM_STRONG
#define Common_3_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Common_3_MASK               Common_3__MASK
#define Common_3_SHIFT              Common_3__SHIFT
#define Common_3_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Common_3_PS                     (* (reg8 *) Common_3__PS)
/* Data Register */
#define Common_3_DR                     (* (reg8 *) Common_3__DR)
/* Port Number */
#define Common_3_PRT_NUM                (* (reg8 *) Common_3__PRT) 
/* Connect to Analog Globals */                                                  
#define Common_3_AG                     (* (reg8 *) Common_3__AG)                       
/* Analog MUX bux enable */
#define Common_3_AMUX                   (* (reg8 *) Common_3__AMUX) 
/* Bidirectional Enable */                                                        
#define Common_3_BIE                    (* (reg8 *) Common_3__BIE)
/* Bit-mask for Aliased Register Access */
#define Common_3_BIT_MASK               (* (reg8 *) Common_3__BIT_MASK)
/* Bypass Enable */
#define Common_3_BYP                    (* (reg8 *) Common_3__BYP)
/* Port wide control signals */                                                   
#define Common_3_CTL                    (* (reg8 *) Common_3__CTL)
/* Drive Modes */
#define Common_3_DM0                    (* (reg8 *) Common_3__DM0) 
#define Common_3_DM1                    (* (reg8 *) Common_3__DM1)
#define Common_3_DM2                    (* (reg8 *) Common_3__DM2) 
/* Input Buffer Disable Override */
#define Common_3_INP_DIS                (* (reg8 *) Common_3__INP_DIS)
/* LCD Common or Segment Drive */
#define Common_3_LCD_COM_SEG            (* (reg8 *) Common_3__LCD_COM_SEG)
/* Enable Segment LCD */
#define Common_3_LCD_EN                 (* (reg8 *) Common_3__LCD_EN)
/* Slew Rate Control */
#define Common_3_SLW                    (* (reg8 *) Common_3__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Common_3_PRTDSI__CAPS_SEL       (* (reg8 *) Common_3__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Common_3_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Common_3__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Common_3_PRTDSI__OE_SEL0        (* (reg8 *) Common_3__PRTDSI__OE_SEL0) 
#define Common_3_PRTDSI__OE_SEL1        (* (reg8 *) Common_3__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Common_3_PRTDSI__OUT_SEL0       (* (reg8 *) Common_3__PRTDSI__OUT_SEL0) 
#define Common_3_PRTDSI__OUT_SEL1       (* (reg8 *) Common_3__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Common_3_PRTDSI__SYNC_OUT       (* (reg8 *) Common_3__PRTDSI__SYNC_OUT) 


#if defined(Common_3__INTSTAT)  /* Interrupt Registers */

    #define Common_3_INTSTAT                (* (reg8 *) Common_3__INTSTAT)
    #define Common_3_SNAP                   (* (reg8 *) Common_3__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Common_3_H */


/* [] END OF FILE */
