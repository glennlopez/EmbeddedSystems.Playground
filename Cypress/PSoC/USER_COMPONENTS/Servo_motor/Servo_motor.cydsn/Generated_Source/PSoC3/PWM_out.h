/*******************************************************************************
* File Name: PWM_out.h  
* Version 1.70
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

#if !defined(CY_PINS_PWM_out_H) /* Pins PWM_out_H */
#define CY_PINS_PWM_out_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PWM_out_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    PWM_out_Write(uint8 value) ;
void    PWM_out_SetDriveMode(uint8 mode) ;
uint8   PWM_out_ReadDataReg(void) ;
uint8   PWM_out_Read(void) ;
uint8   PWM_out_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define PWM_out_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define PWM_out_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define PWM_out_DM_RES_UP          PIN_DM_RES_UP
#define PWM_out_DM_RES_DWN         PIN_DM_RES_DWN
#define PWM_out_DM_OD_LO           PIN_DM_OD_LO
#define PWM_out_DM_OD_HI           PIN_DM_OD_HI
#define PWM_out_DM_STRONG          PIN_DM_STRONG
#define PWM_out_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define PWM_out_MASK               PWM_out__MASK
#define PWM_out_SHIFT              PWM_out__SHIFT
#define PWM_out_WIDTH              1u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PWM_out_PS                     (* (reg8 *) PWM_out__PS)
/* Data Register */
#define PWM_out_DR                     (* (reg8 *) PWM_out__DR)
/* Port Number */
#define PWM_out_PRT_NUM                (* (reg8 *) PWM_out__PRT) 
/* Connect to Analog Globals */                                                  
#define PWM_out_AG                     (* (reg8 *) PWM_out__AG)                       
/* Analog MUX bux enable */
#define PWM_out_AMUX                   (* (reg8 *) PWM_out__AMUX) 
/* Bidirectional Enable */                                                        
#define PWM_out_BIE                    (* (reg8 *) PWM_out__BIE)
/* Bit-mask for Aliased Register Access */
#define PWM_out_BIT_MASK               (* (reg8 *) PWM_out__BIT_MASK)
/* Bypass Enable */
#define PWM_out_BYP                    (* (reg8 *) PWM_out__BYP)
/* Port wide control signals */                                                   
#define PWM_out_CTL                    (* (reg8 *) PWM_out__CTL)
/* Drive Modes */
#define PWM_out_DM0                    (* (reg8 *) PWM_out__DM0) 
#define PWM_out_DM1                    (* (reg8 *) PWM_out__DM1)
#define PWM_out_DM2                    (* (reg8 *) PWM_out__DM2) 
/* Input Buffer Disable Override */
#define PWM_out_INP_DIS                (* (reg8 *) PWM_out__INP_DIS)
/* LCD Common or Segment Drive */
#define PWM_out_LCD_COM_SEG            (* (reg8 *) PWM_out__LCD_COM_SEG)
/* Enable Segment LCD */
#define PWM_out_LCD_EN                 (* (reg8 *) PWM_out__LCD_EN)
/* Slew Rate Control */
#define PWM_out_SLW                    (* (reg8 *) PWM_out__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PWM_out_PRTDSI__CAPS_SEL       (* (reg8 *) PWM_out__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PWM_out_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PWM_out__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PWM_out_PRTDSI__OE_SEL0        (* (reg8 *) PWM_out__PRTDSI__OE_SEL0) 
#define PWM_out_PRTDSI__OE_SEL1        (* (reg8 *) PWM_out__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PWM_out_PRTDSI__OUT_SEL0       (* (reg8 *) PWM_out__PRTDSI__OUT_SEL0) 
#define PWM_out_PRTDSI__OUT_SEL1       (* (reg8 *) PWM_out__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PWM_out_PRTDSI__SYNC_OUT       (* (reg8 *) PWM_out__PRTDSI__SYNC_OUT) 


#if defined(PWM_out__INTSTAT)  /* Interrupt Registers */

    #define PWM_out_INTSTAT                (* (reg8 *) PWM_out__INTSTAT)
    #define PWM_out_SNAP                   (* (reg8 *) PWM_out__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins PWM_out_H */


/* [] END OF FILE */
