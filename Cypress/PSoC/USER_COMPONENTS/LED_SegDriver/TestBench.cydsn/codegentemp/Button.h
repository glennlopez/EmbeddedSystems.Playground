/*******************************************************************************
* File Name: Button.h  
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

#if !defined(CY_PINS_Button_H) /* Pins Button_H */
#define CY_PINS_Button_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Button_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Button_Write(uint8 value) ;
void    Button_SetDriveMode(uint8 mode) ;
uint8   Button_ReadDataReg(void) ;
uint8   Button_Read(void) ;
uint8   Button_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Button_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Button_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Button_DM_RES_UP          PIN_DM_RES_UP
#define Button_DM_RES_DWN         PIN_DM_RES_DWN
#define Button_DM_OD_LO           PIN_DM_OD_LO
#define Button_DM_OD_HI           PIN_DM_OD_HI
#define Button_DM_STRONG          PIN_DM_STRONG
#define Button_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Button_MASK               Button__MASK
#define Button_SHIFT              Button__SHIFT
#define Button_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Button_PS                     (* (reg8 *) Button__PS)
/* Data Register */
#define Button_DR                     (* (reg8 *) Button__DR)
/* Port Number */
#define Button_PRT_NUM                (* (reg8 *) Button__PRT) 
/* Connect to Analog Globals */                                                  
#define Button_AG                     (* (reg8 *) Button__AG)                       
/* Analog MUX bux enable */
#define Button_AMUX                   (* (reg8 *) Button__AMUX) 
/* Bidirectional Enable */                                                        
#define Button_BIE                    (* (reg8 *) Button__BIE)
/* Bit-mask for Aliased Register Access */
#define Button_BIT_MASK               (* (reg8 *) Button__BIT_MASK)
/* Bypass Enable */
#define Button_BYP                    (* (reg8 *) Button__BYP)
/* Port wide control signals */                                                   
#define Button_CTL                    (* (reg8 *) Button__CTL)
/* Drive Modes */
#define Button_DM0                    (* (reg8 *) Button__DM0) 
#define Button_DM1                    (* (reg8 *) Button__DM1)
#define Button_DM2                    (* (reg8 *) Button__DM2) 
/* Input Buffer Disable Override */
#define Button_INP_DIS                (* (reg8 *) Button__INP_DIS)
/* LCD Common or Segment Drive */
#define Button_LCD_COM_SEG            (* (reg8 *) Button__LCD_COM_SEG)
/* Enable Segment LCD */
#define Button_LCD_EN                 (* (reg8 *) Button__LCD_EN)
/* Slew Rate Control */
#define Button_SLW                    (* (reg8 *) Button__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Button_PRTDSI__CAPS_SEL       (* (reg8 *) Button__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Button_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Button__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Button_PRTDSI__OE_SEL0        (* (reg8 *) Button__PRTDSI__OE_SEL0) 
#define Button_PRTDSI__OE_SEL1        (* (reg8 *) Button__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Button_PRTDSI__OUT_SEL0       (* (reg8 *) Button__PRTDSI__OUT_SEL0) 
#define Button_PRTDSI__OUT_SEL1       (* (reg8 *) Button__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Button_PRTDSI__SYNC_OUT       (* (reg8 *) Button__PRTDSI__SYNC_OUT) 


#if defined(Button__INTSTAT)  /* Interrupt Registers */

    #define Button_INTSTAT                (* (reg8 *) Button__INTSTAT)
    #define Button_SNAP                   (* (reg8 *) Button__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Button_H */


/* [] END OF FILE */
