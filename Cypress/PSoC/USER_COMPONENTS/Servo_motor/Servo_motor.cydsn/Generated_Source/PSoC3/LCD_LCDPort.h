/*******************************************************************************
* File Name: LCD_LCDPort.h  
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

#if !defined(CY_PINS_LCD_LCDPort_H) /* Pins LCD_LCDPort_H */
#define CY_PINS_LCD_LCDPort_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LCD_LCDPort_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LCD_LCDPort_Write(uint8 value) ;
void    LCD_LCDPort_SetDriveMode(uint8 mode) ;
uint8   LCD_LCDPort_ReadDataReg(void) ;
uint8   LCD_LCDPort_Read(void) ;
uint8   LCD_LCDPort_ClearInterrupt(void) ;

/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LCD_LCDPort_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define LCD_LCDPort_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define LCD_LCDPort_DM_RES_UP          PIN_DM_RES_UP
#define LCD_LCDPort_DM_RES_DWN         PIN_DM_RES_DWN
#define LCD_LCDPort_DM_OD_LO           PIN_DM_OD_LO
#define LCD_LCDPort_DM_OD_HI           PIN_DM_OD_HI
#define LCD_LCDPort_DM_STRONG          PIN_DM_STRONG
#define LCD_LCDPort_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define LCD_LCDPort_MASK               LCD_LCDPort__MASK
#define LCD_LCDPort_SHIFT              LCD_LCDPort__SHIFT
#define LCD_LCDPort_WIDTH              7u

/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LCD_LCDPort_PS                     (* (reg8 *) LCD_LCDPort__PS)
/* Data Register */
#define LCD_LCDPort_DR                     (* (reg8 *) LCD_LCDPort__DR)
/* Port Number */
#define LCD_LCDPort_PRT_NUM                (* (reg8 *) LCD_LCDPort__PRT) 
/* Connect to Analog Globals */                                                  
#define LCD_LCDPort_AG                     (* (reg8 *) LCD_LCDPort__AG)                       
/* Analog MUX bux enable */
#define LCD_LCDPort_AMUX                   (* (reg8 *) LCD_LCDPort__AMUX) 
/* Bidirectional Enable */                                                        
#define LCD_LCDPort_BIE                    (* (reg8 *) LCD_LCDPort__BIE)
/* Bit-mask for Aliased Register Access */
#define LCD_LCDPort_BIT_MASK               (* (reg8 *) LCD_LCDPort__BIT_MASK)
/* Bypass Enable */
#define LCD_LCDPort_BYP                    (* (reg8 *) LCD_LCDPort__BYP)
/* Port wide control signals */                                                   
#define LCD_LCDPort_CTL                    (* (reg8 *) LCD_LCDPort__CTL)
/* Drive Modes */
#define LCD_LCDPort_DM0                    (* (reg8 *) LCD_LCDPort__DM0) 
#define LCD_LCDPort_DM1                    (* (reg8 *) LCD_LCDPort__DM1)
#define LCD_LCDPort_DM2                    (* (reg8 *) LCD_LCDPort__DM2) 
/* Input Buffer Disable Override */
#define LCD_LCDPort_INP_DIS                (* (reg8 *) LCD_LCDPort__INP_DIS)
/* LCD Common or Segment Drive */
#define LCD_LCDPort_LCD_COM_SEG            (* (reg8 *) LCD_LCDPort__LCD_COM_SEG)
/* Enable Segment LCD */
#define LCD_LCDPort_LCD_EN                 (* (reg8 *) LCD_LCDPort__LCD_EN)
/* Slew Rate Control */
#define LCD_LCDPort_SLW                    (* (reg8 *) LCD_LCDPort__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LCD_LCDPort_PRTDSI__CAPS_SEL       (* (reg8 *) LCD_LCDPort__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LCD_LCDPort_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LCD_LCDPort__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LCD_LCDPort_PRTDSI__OE_SEL0        (* (reg8 *) LCD_LCDPort__PRTDSI__OE_SEL0) 
#define LCD_LCDPort_PRTDSI__OE_SEL1        (* (reg8 *) LCD_LCDPort__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LCD_LCDPort_PRTDSI__OUT_SEL0       (* (reg8 *) LCD_LCDPort__PRTDSI__OUT_SEL0) 
#define LCD_LCDPort_PRTDSI__OUT_SEL1       (* (reg8 *) LCD_LCDPort__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LCD_LCDPort_PRTDSI__SYNC_OUT       (* (reg8 *) LCD_LCDPort__PRTDSI__SYNC_OUT) 


#if defined(LCD_LCDPort__INTSTAT)  /* Interrupt Registers */

    #define LCD_LCDPort_INTSTAT                (* (reg8 *) LCD_LCDPort__INTSTAT)
    #define LCD_LCDPort_SNAP                   (* (reg8 *) LCD_LCDPort__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins LCD_LCDPort_H */


/* [] END OF FILE */
