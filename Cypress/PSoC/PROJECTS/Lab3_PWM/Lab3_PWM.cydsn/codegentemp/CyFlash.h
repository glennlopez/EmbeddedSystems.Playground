/*******************************************************************************
* File Name: CyFlash.h
* Version 4.20
*
*  Description:
*   Provides the function definitions for the FLASH.
*
*  Note:
*   Documentation of the API's in this file is located in the
*   System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2010-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_BOOT_CYFLASH_H)
#define CY_BOOT_CYFLASH_H

#include "CyLib.h"


/*******************************************************************************
*     Function Prototypes
*******************************************************************************/
uint32 CySysFlashWriteRow       (uint32 rowNum, const uint8 rowData[]);
void   CySysFlashSetWaitCycles  (uint32 freq);


/*******************************************************************************
*     Flash defines
*******************************************************************************/

/* Flash API macros */
#define CY_FLASH_BASE                   (CYDEV_FLASH_BASE)
#define CY_FLASH_SIZE                   (CYDEV_FLASH_SIZE)
#define CY_FLASH_NUMBER_ARRAYS          (CYDEV_FLASH_SIZE / CYDEV_FLS_SECTOR_SIZE)
#define CY_FLASH_SIZEOF_ARRAY           (CYDEV_FLS_SECTOR_SIZE)
#define CY_FLASH_NUMBER_ROWS            (CYDEV_FLASH_SIZE / CYDEV_FLS_ROW_SIZE)
#define CY_FLASH_SIZEOF_ROW             (CYDEV_FLS_ROW_SIZE)


/* CySysFlashWriteRow() - return codes */
#define CY_SYS_FLASH_SUCCESS            (0x00u)
#define CY_SYS_FLASH_INVALID_ADDR       (0x04u)
#define CY_SYS_FLASH_PROTECTED          (0x05u)


/* CySysFlashSetWaitCycles() - implementation definitions */
#define CY_FLASH_WAIT_STATE_EN          (( uint32 )(( uint32 )0x01u << 18u))
#define CY_FLASH_SYSCLK_BOUNDARY_MHZ    (24u)
#if (CY_IP_CPUSSV2)
    /* CySysFlashSetWaitCycles() */
    #if(CY_IP_FM)
        #define CY_FLASH_CTL_WS_0_FREQ_MIN      (0u)
        #define CY_FLASH_CTL_WS_0_FREQ_MAX      (24u)

        #define CY_FLASH_CTL_WS_1_FREQ_MIN      (24u)
        #define CY_FLASH_CTL_WS_1_FREQ_MAX      (48u)
    #else
        #define CY_FLASH_CTL_WS_0_FREQ_MIN      (0u)
        #define CY_FLASH_CTL_WS_0_FREQ_MAX      (16u)

        #define CY_FLASH_CTL_WS_1_FREQ_MIN      (16u)
        #define CY_FLASH_CTL_WS_1_FREQ_MAX      (32u)

        #define CY_FLASH_CTL_WS_2_FREQ_MIN      (32u)
        #define CY_FLASH_CTL_WS_2_FREQ_MAX      (48u)
    #endif  /* (CY_IP_FM) */

    #define CY_FLASH_CTL_WS_MASK        ((uint32) 0x03u)
    #define CY_FLASH_CTL_WS_0_VALUE     (0x00u)
    #define CY_FLASH_CTL_WS_1_VALUE     (0x01u)
    #if(CY_IP_FMLT)
        #define CY_FLASH_CTL_WS_2_VALUE (0x02u)
    #endif  /* (CY_IP_FMLT) */
#endif  /* (CY_IP_CPUSSV2) */


#define CY_FLASH_KEY_ONE                (0xB6u)
#define CY_FLASH_KEY_TWO(x)             ((uint32) (((uint16) 0xD3u) + ((uint16) (x))))

#define CY_FLASH_PAGE_LATCH_START_ADDR  ((uint32) (0x00u))
#define CY_FLASH_ROW_NUM_MASK           (0x100u)
#define CY_FLASH_CPUSS_REQ_START        (( uint32 )(( uint32 )0x1u << 31u))

/* Opcodes */
#define CY_FLASH_API_OPCODE_LOAD        (0x04u)
#define CY_FLASH_API_OPCODE_WRITE_ROW   (0x05u)

#define CY_FLASH_API_OPCODE_PROGRAM_ROW (0x06u)

#define CY_FLASH_API_OPCODE_CLK_CONFIG  (0x15u)
#define CY_FLASH_API_OPCODE_CLK_BACKUP  (0x16u)
#define CY_FLASH_API_OPCODE_CLK_RESTORE (0x17u)

/* SROM API parameters offsets */
#define CY_FLASH_PARAM_KEY_TWO_OFFSET   (8u)
#define CY_FLASH_PARAM_ADDR_OFFSET      (16u)
#define CY_FLASH_PARAM_MACRO_SEL_OFFSET (24u)

#if (CY_PSOC4_4200BL || CY_PSOC4_4100BL)
    /*  Macro #0: rows 0x00-0x1ff, Macro #1: rows 0x200-0x3ff */
    #define CY_FLASH_GET_MACRO_FROM_ROW(row)         ((uint32)(((row) > 0x1ffu) ? 1u : 0u))
#else
    /* Only macro # 0 is available */
    #define CY_FLASH_GET_MACRO_FROM_ROW(row)         ((uint32)(((row) != 0u)    ? 0u : 0u))
#endif  /* (CY_PSOC4_4200BL || CY_PSOC4_4100BL) */

#if(CY_IP_FMLT)
    /* SROM size greater than 4k */
    #define CY_FLASH_IS_BACKUP_RESTORE   (CYDEV_SROM_SIZE > 0x00001000u)
#endif  /* (CY_IP_FMLT) */


#if(CY_IP_SRSSV2)
    #define CY_FLASH_CLOCK_BACKUP_SIZE      (4u)
#else /* CY_IP_SRSSLT */
    #define CY_FLASH_CLOCK_BACKUP_SIZE      (6u)
#endif  /* (CY_IP_SRSSV2) */


typedef struct cySysFlashClockBackupStruct
{
#if(CY_IP_FM)
        uint32   imoConfigReg;
#else   /* (CY_IP_FMLT) */
    #if (CY_PSOC4_4000)
        uint32 clkSelectReg;
        uint32 clkImoEna;
        uint32 clkImoFreq;
    #else
        #if(CY_IP_SRSSV2)
            uint32 clkImoPump;
        #endif /* (CY_IP_SRSSV2) */
        uint32 clockSettings[CY_FLASH_CLOCK_BACKUP_SIZE];       /* FM-Lite Clock Backup */
    #endif  /* (CY_PSOC4_4000) */

#endif  /* (CY_IP_FM) */
} CY_SYS_FLASH_CLOCK_BACKUP_STRUCT;


/* SYSARG control register */
#define CY_FLASH_CPUSS_SYSARG_REG       (*(reg32 *) CYREG_CPUSS_SYSARG)
#define CY_FLASH_CPUSS_SYSARG_PTR       ( (reg32 *) CYREG_CPUSS_SYSARG)

/* SYSCALL control register */
#define CY_FLASH_CPUSS_SYSREQ_REG       (*(reg32 *) CYREG_CPUSS_SYSREQ)
#define CY_FLASH_CPUSS_SYSREQ_PTR       ( (reg32 *) CYREG_CPUSS_SYSREQ)

#if (CY_IP_CPUSSV2)
    /* SYSARG control register */
    #define CY_FLASH_CTL_REG            (*(reg32 *) CYREG_CPUSS_FLASH_CTL)
    #define CY_FLASH_CTL_PTR            ( (reg32 *) CYREG_CPUSS_FLASH_CTL)
#endif  /* (CY_IP_CPUSSV2) */

#define CY_FLASH_API_RETURN             (((CY_FLASH_CPUSS_SYSARG_REG & 0xF0000000u) == 0xA0000000u) ? \
                                            CYRET_SUCCESS : \
                                            (CY_FLASH_CPUSS_SYSARG_REG & 0x0000000Fu))


/*******************************************************************************
* Thne following code is OBSOLETE and must not be used starting with cy_boot
* 4.20.
*
* If the obsoleted macro definitions intended for use in the application use the
* following scheme, redefine your own versions of these definitions:
*    #ifdef <OBSOLETED_DEFINE>
*        #undef  <OBSOLETED_DEFINE>
*        #define <OBSOLETED_DEFINE>      (<New Value>)
*    #endif
*
* Note: Redefine obsoleted macro definitions with caution. They might still be
*       used in the application and their modification might lead to unexpected
*       consequences.
*******************************************************************************/
#define CY_FLASH_SRAM_ROM_KEY1          (( uint32 )0x00u)
#define CY_FLASH_SRAM_ROM_PARAM2        (CY_FLASH_SRAM_ROM_KEY1 + 0x04u)
#define CY_FLASH_SRAM_ROM_DATA          (CY_FLASH_SRAM_ROM_KEY1 + 0x08u)

#define CY_FLASH_SROM_CMD_RETURN_MASK   (0xF0000000u)
#define CY_FLASH_SROM_CMD_RETURN_SUCC   (0xA0000000u)
#define CY_FLASH_SROM_KEY1              (( uint32 )0xB6u)
#define CY_FLASH_SROM_KEY2_LOAD         (( uint32 )0xD7u)
#define CY_FLASH_SROM_KEY2_WRITE        (( uint32 )0xD8u)
#define CY_FLASH_SROM_LOAD_CMD          ((CY_FLASH_SROM_KEY2_LOAD << 8u) | CY_FLASH_SROM_KEY1)
#define CY_FLASH_LOAD_BYTE_OPCODE       (( uint32 )0x04u)
#define CY_FLASH_WRITE_ROW_OPCODE       (( uint32 )0x05u)


#endif  /* (CY_BOOT_CYFLASH_H) */


/* [] END OF FILE */
