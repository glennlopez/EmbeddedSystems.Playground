/*******************************************************************************
* File Name: cyPm.h
* Version 2.40
*
* Description:
*  Provides the function definitions for the power management API.
*
* Note:
*  Documentation of the API's in this file is located in the
*  System Reference Guide provided with PSoC Creator.
*
********************************************************************************
* Copyright 2008-2011, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PM_H)
#define CY_PM_H

#include "cytypes.h"        /* Register access API      */
#include "cydevice_trm.h"   /* Registers addresses      */
#include "cyfitter.h"       /* Comparators placement    */
#include "CyLib.h"          /* Clock API                */
#include "CyFlash.h"        /* Flash API - CyFlash_SetWaitCycles()  */


/***************************************
*    Function Prototypes
***************************************/
void CyPmSaveClocks(void);
void CyPmRestoreClocks(void) ;
void CyPmAltAct(uint16 wakeupTime, uint16 wakeupSource);

/*******************************************************************************
* Note: PSoC 3 ES2 silicon has a defect that causes connections to several
* analog resources to be unreliable when the device is placed in a low power
* mode. See the silicon errata for details.
*******************************************************************************/
void CyPmSleep(uint8 wakeupTime, uint16 wakeupSource);
void CyPmHibernate(void);

uint8 CyPmReadStatus(uint8 mask) ;


/***************************************
*    API Constants
***************************************/

/* Device is PSoC 5 */
#if(CY_PSOC5)

    #define PM_SLEEP_TIME_NONE              (0x00u)
    #define PM_SLEEP_SRC_NONE               (0x0000u)
    #define PM_ALT_ACT_TIME_NONE            (0x0000u)
    #define PM_ALT_ACT_SRC_NONE             (0x0000u)

#endif  /* (CY_PSOC5) */


#if(CY_PSOC3)    /* Device is PSoC 3 */

    /* Wake up time for the Sleep mode */
    #define PM_SLEEP_TIME_NONE              (0x00u)
    #define PM_SLEEP_TIME_ONE_PPS           (0x01u)
    #define PM_SLEEP_TIME_CTW_2MS           (0x02u)
    #define PM_SLEEP_TIME_CTW_4MS           (0x03u)
    #define PM_SLEEP_TIME_CTW_8MS           (0x04u)
    #define PM_SLEEP_TIME_CTW_16MS          (0x05u)
    #define PM_SLEEP_TIME_CTW_32MS          (0x06u)
    #define PM_SLEEP_TIME_CTW_64MS          (0x07u)
    #define PM_SLEEP_TIME_CTW_128MS         (0x08u)
    #define PM_SLEEP_TIME_CTW_256MS         (0x09u)
    #define PM_SLEEP_TIME_CTW_512MS         (0x0Au)
    #define PM_SLEEP_TIME_CTW_1024MS        (0x0Bu)
    #define PM_SLEEP_TIME_CTW_2048MS        (0x0Cu)
    #define PM_SLEEP_TIME_CTW_4096MS        (0x0Du)

    /* Wake up sources for the Sleep mode */
    #define PM_SLEEP_SRC_NONE               (0x0000u)
    #define PM_SLEEP_SRC_COMPARATOR0        (0x0001u)
    #define PM_SLEEP_SRC_COMPARATOR1        (0x0002u)
    #define PM_SLEEP_SRC_COMPARATOR2        (0x0004u)
    #define PM_SLEEP_SRC_COMPARATOR3        (0x0008u)
    #define PM_SLEEP_SRC_PICU               (0x0040u)
    #define PM_SLEEP_SRC_I2C                (0x0080u)
    #define PM_SLEEP_SRC_BOOSTCONVERTER     (0x0200u)
    #define PM_SLEEP_SRC_CTW                (0x0800u)
    #define PM_SLEEP_SRC_ONE_PPS            (0x0800u)

    /* Device is PSoC 3 and the revision is ES3 or later */
    #if(CY_PSOC3_ES3)

        #define PM_SLEEP_SRC_LCD            (0x1000u)

    #endif  /* (CY_PSOC3_ES3) */

    /* Difference between parameter's value and register's one */
    #define CY_PM_FTW_INTERVAL_SHIFT        (0x000Eu)

    /* Wake up time for the Alternate Active mode */
    #define PM_ALT_ACT_TIME_NONE            (0x0000u)
    #define PM_ALT_ACT_TIME_ONE_PPS         (0x0001u)
    #define PM_ALT_ACT_TIME_CTW_2MS         (0x0002u)
    #define PM_ALT_ACT_TIME_CTW_4MS         (0x0003u)
    #define PM_ALT_ACT_TIME_CTW_8MS         (0x0004u)
    #define PM_ALT_ACT_TIME_CTW_16MS        (0x0005u)
    #define PM_ALT_ACT_TIME_CTW_32MS        (0x0006u)
    #define PM_ALT_ACT_TIME_CTW_64MS        (0x0007u)
    #define PM_ALT_ACT_TIME_CTW_128MS       (0x0008u)
    #define PM_ALT_ACT_TIME_CTW_256MS       (0x0009u)
    #define PM_ALT_ACT_TIME_CTW_512MS       (0x000Au)
    #define PM_ALT_ACT_TIME_CTW_1024MS      (0x000Bu)
    #define PM_ALT_ACT_TIME_CTW_2048MS      (0x000Cu)
    #define PM_ALT_ACT_TIME_CTW_4096MS      (0x000Du)
    #define PM_ALT_ACT_TIME_FTW(x)          ((x) + CY_PM_FTW_INTERVAL_SHIFT)

    /* Wake up sources for the Alternate Active mode */
    #define PM_ALT_ACT_SRC_NONE             (0x0000u)
    #define PM_ALT_ACT_SRC_COMPARATOR0      (0x0001u)
    #define PM_ALT_ACT_SRC_COMPARATOR1      (0x0002u)
    #define PM_ALT_ACT_SRC_COMPARATOR2      (0x0004u)
    #define PM_ALT_ACT_SRC_COMPARATOR3      (0x0008u)
    #define PM_ALT_ACT_SRC_INTERRUPT        (0x0010u)
    #define PM_ALT_ACT_SRC_PICU             (0x0040u)
    #define PM_ALT_ACT_SRC_I2C              (0x0080u)
    #define PM_ALT_ACT_SRC_BOOSTCONVERTER   (0x0200u)

    #define PM_ALT_ACT_SRC_FTW              (0x0400u)
    #define PM_ALT_ACT_SRC_CTW              (0x0800u)
    #define PM_ALT_ACT_SRC_ONE_PPS          (0x0800u)

    /* Device is PSoC 3 and the revision is ES3 or later */
    #if(CY_PSOC3_ES3)

        #define PM_ALT_ACT_SRC_LCD          (0x1000u)

    #endif  /* (CY_PSOC3_ES3) */

#endif  /* (CY_PSOC3) */


#define CY_PM_WAKEUP_PICU               (0x04u)
#define CY_PM_IMO_NO_WAIT_TO_SETTLE     (0x00u)
#define CY_PM_POWERDOWN_MODE            (0x01u)
#define CY_PM_HIGHPOWER_MODE            (0x00u)     /* Deprecated */
#define CY_PM_ENABLED                   (0x01u)
#define CY_PM_DISABLED                  (0x00u)

/* No wait for PLL to stabilize, used in CyPLL_OUT_Start() */
#define CY_PM_PLL_OUT_NO_WAIT           (0u)

/* No wait for MHZ XTAL to stabilize, used in CyXTAL_Start() */
#define CY_PM_XTAL_MHZ_NO_WAIT          (0u)

#define CY_PM_WAIT_200_US               (200u)
#define CY_PM_WAIT_250_US               (250u)
#define CY_PM_WAIT_20_US                (20u)

#define CY_PM_FREQ_3MHZ                 (3u)
#define CY_PM_FREQ_12MHZ                (12u)
#define CY_PM_FREQ_48MHZ                (48u)


/* Device is PSoC 3 and the revision is ES2 or earlier, or
*  device is PSoC 5 and the revision is ES1 or earlier.
*/
#if(CY_PSOC5_ES1 || CY_PSOC3_ES2)
    #define     CY_PM_MHZ_XTAL_WAIT_NUM_OF_200_US   (650u)
#else
    #define     CY_PM_MHZ_XTAL_WAIT_NUM_OF_200_US   (5u)
#endif  /* (CY_PSOC5_ES1 || CY_PSOC3_ES2) */


/* Max flash wait cycles for each device */
#if(CY_PSOC3_ES3)    /* Device is PSoC 3 and the revision is ES3 or later */
    #define     CY_PM_MAX_FLASH_WAIT_CYCLES        (45u)
#endif  /* (CY_PSOC3_ES3) */

#if(CY_PSOC3_ES2)   /* Device is PSoC 3 and the revision is ES2 or earlier */
    #define     CY_PM_MAX_FLASH_WAIT_CYCLES        (49u)
#endif  /* (CY_PSOC3_ES2) */

#if(CY_PSOC5)    /* Device is PSoC 5 */
    #define     CY_PM_MAX_FLASH_WAIT_CYCLES        (55u)
#endif  /* (CY_PSOC5) */


/*******************************************************************************
* This marco is used to obtain the CPU frequency in MHz. It should be only used
* when the clock distribution system is prepared for the low power mode entry.
* This macro is silicon dependent as PSoC5 devices have no CPU clock divider and
* PSoC3 devices have different placement of the CPU clock divider register
* bitfield.
*******************************************************************************/

/* Device is PSoC 3 and the revision is ES3 or later */
#if(CY_PSOC3_ES3)
    #define CY_PM_GET_CPU_FREQ_MHZ (cyPmImoFreqReg2Mhz[CY_PM_FASTCLK_IMO_CR_REG & CY_PM_FASTCLK_IMO_CR_FREQ_MASK] / \
                                   (((CY_PM_CLKDIST_MSTR1_REG & CY_PM_CLKDIST_CPU_DIV_MASK) >> 4u) + 1u))
#endif  /* (CY_PSOC3_ES3) */

/* Device is PSoC 3 and the revision is ES2 or earlier */
#if(CY_PSOC3_ES2)
    #define CY_PM_GET_CPU_FREQ_MHZ (cyPmImoFreqReg2Mhz[CY_PM_FASTCLK_IMO_CR_REG & CY_PM_FASTCLK_IMO_CR_FREQ_MASK] / \
                                    ((CY_GET_XTND_REG8(CYREG_SFR_USER_CPUCLK_DIV) & CY_PM_SFR_USER_CPUCLK_MASK) + 1u))
#endif  /* (CY_PSOC3_ES2) */

/* Device is PSoC 5 */
#if(CY_PSOC5)

    /* The CPU clock is directly derived from bus clock */
    #define     CY_PM_GET_CPU_FREQ_MHZ (cyPmImoFreqReg2Mhz[CY_PM_FASTCLK_IMO_CR_REG & CY_PM_FASTCLK_IMO_CR_FREQ_MASK])

#endif  /* (CY_PSOC5) */


/*******************************************************************************
* The low power mode entry is different for PSoC3 and PSoC5 devices. The low
* power modes in PSoC5 devices are invoked by Wait-For-Interrupt (WFI)
* instruction. The ARM compilers has __wfi() instristic that inserts a WFI
* instruction into the instruction stream generated by the compiler. The GCC
* compiler has to execute assembly language instruction.
*******************************************************************************/

/* Device is PSoC 5 */
#if(CY_PSOC5)

    #if defined(__ARMCC_VERSION)    /* Instristic for Keil compilers */
        #define CY_PM_WFI       __wfi()
    #else   /* ASM for GCC */
        #define CY_PM_WFI       asm volatile ("WFI \n")
    #endif /* (__ARMCC_VERSION) */

#else

    #define CY_PM_WFI

#endif /* (CY_PSOC5) */


/*******************************************************************************
* The fast timewheel (FTW) is programmed using a 5-bit terminal count for
* PSoC3 ES2 devices and using 8-bit terminal count for PSoC3 ES3 devices.
* The FTW should be programmed manually for PSoC5 ES1 devices.
*******************************************************************************/

/* Device is PSoC 3 and the revision is ES2 or earlier. */
#if(CY_PSOC3_ES2)

    /* FTW interval mask */
    #define CY_PM_FTW_INTERVAL_MASK    (0x1Fu)

    #define PM_ALT_ACT_FTW_INTERVAL(x) \
        ((x) >= PM_ALT_ACT_TIME_FTW(32u) ? \
        ((PM_ALT_ACT_TIME_FTW(31u) - CY_PM_FTW_INTERVAL_SHIFT) & CY_PM_FTW_INTERVAL_MASK) : \
        (((x) - CY_PM_FTW_INTERVAL_SHIFT) & CY_PM_FTW_INTERVAL_MASK))

#elif (CY_PSOC3_ES3) /* Device is PSoC 3 and the revision is ES3 or later */

    /* FTW interval mask */
    #define CY_PM_FTW_INTERVAL_MASK    (0xFFu)

    #define PM_ALT_ACT_FTW_INTERVAL(x) \
        (((x) - CY_PM_FTW_INTERVAL_SHIFT) & CY_PM_FTW_INTERVAL_MASK)

#endif  /* (CY_PSOC3_ES2) */


/*******************************************************************************
* This macro is used for preparing IMO frequency for correct low power mode
* etry. It is dependant on device and silicon. The maximum allowed IMO value for
* correct low power mode entry for PSoC3 ES2 devices is 12 MHz. The IMO
* frequency for the PSoC3 ES3 and PSoC5 ES1 devices depends on Fast IMO
* configuration: if Fast IMO is enabled the IMO should be set to 48 MHz
* before LPM entry, otherwise IMO should be set to 12 MHz.
*******************************************************************************/

/* Device is PSoC 3 and the revision is ES3 or later, or
*  device is PSoC 5 and the revision is ES1 or earlier.
*/
#if(CY_PSOC3_ES3 || CY_PSOC5_ES1)

    #if(CYDEV_CONFIGURATION_IMOENABLED) /* Fast IMO is configured to 48 MHz */

        #define CY_PM_IMO_FREQ_LPM      (CY_IMO_FREQ_48MHZ)

    #else   /* Fast IMO is configured to be 12 MHz */

        #define CY_PM_IMO_FREQ_LPM      (CY_IMO_FREQ_12MHZ)

    #endif  /* (CYDEV_CONFIGURATION_IMOENABLED) */

#elif(CY_PSOC3_ES2)  /* Device is PSoC 3 and the revision is ES2 or earlier */

    /* IMO - set 12 MHz frequency (24/48 MHz is not allowed) */
    #define CY_PM_IMO_FREQ_LPM          (CY_IMO_FREQ_12MHZ)

#endif  /* (CY_PSOC3_ES2) */


typedef struct _cyPmClockBackupStruct
{
    /* CyPmSaveClocks()/CyPmRestoreClocks() */
    uint8  enClkA;              /* Analog clocks enable         */
    uint8  enClkD;              /* Digital clocks enable        */
    uint8  masterClkSrc;        /* The Master clock source      */
    uint8  imoFreq;             /* IMO frequency (reg's value)  */
    uint8  imoUsbClk;           /* IMO USB CLK (reg's value)    */
    uint8  flashWaitCycles;     /* Flash wait cycles            */
    uint8  imoEnable;           /* IMO enable in Active mode    */
    uint8  imoClkSrc;           /* The IMO output               */
    uint8  clkImoSrc;
    uint8  imo2x;               /* IMO doubler enable state     */
    uint8  clkSyncDiv;          /* Master clk divider           */
    uint16 clkBusDiv;           /* The clk_bus divider          */
    uint8  pllEnableState;      /* PLL enable state             */
    uint8  xmhzEnableState;     /* XM HZ enable state           */

} CY_PM_CLOCK_BACKUP_STRUCT;


typedef struct _cyPmBackupStruct
{
    uint8 iloPowerMode;         /* ILO power mode               */
    uint8 ilo1kEnable;          /* ILO 1K enable state          */
    uint8 ilo100kEnable;        /* ILO 100K enable state        */

    #if(CY_PSOC3_ES2 || CY_PSOC5_ES1)

        /* State of the I2C regulator backup */
        uint8 i2cRegBackup;

    #endif /* (CY_PSOC3_ES2 || CY_PSOC5_ES1) */

    uint8 lviaLvidHvi;          /* State of en_lvia, en_lvid, en_hvi */

    /* Device is PSoC 3 and the revision is ES3 or later */
    #if(CY_PSOC3_ES3)

        uint8 slpTrBypass;      /* Sleep Trim Bypass        */

        uint8 swvClkEnabled;    /* SWV clock enable state   */
        uint8 prt1Dm;           /* Ports drive mode configuration */

        uint8 wakeupCfg0;       /* Wake up configuration 0  */
        uint8 wakeupCfg1;       /* Wake up configuration 1  */
        uint8 wakeupCfg2;       /* Wake up configuration 2  */

    #endif  /* (CY_PSOC3_ES3)  */


    /* Device is PSoC 3 and the revision is ES3 or later, or
    *  device is PSoC 5 and the revision is ES1 or earlier.
    */
    #if(CY_PSOC3_ES3 || CY_PSOC5_ES1)

        uint8 scctData[28u];   /* SC/CT routing registers  */

    #endif  /* (CY_PSOC3_ES3 || CY_PSOC5_ES1)  */

    /* Device is PSoC 5 and the revision is ES1 or earlier */
    #if(CY_PSOC5_ES1)

        uint8 cmpData[20u];
        uint8 dacData[16u];
        uint8 dsmData[5u];
        uint8 sarData[10u];

        uint8 pmTwCfg2;
        uint8 picuIntType[72u];

    #endif  /* (CY_PSOC5_ES1)  */


    /* Device is PSoC 3 and the revision is ES2 or earlier, or
    *  device is PSoC 5 and the revision is ES1 or earlier.
    */
    #if(CY_PSOC5_ES1 || CY_PSOC3_ES2)

        uint8 buzzSleepTrim;

    #endif  /* (CY_PSOC5_ES1 || CY_PSOC3_ES2)  */

    uint8 imoActFreq;       /* Last moment IMO change   */
    uint8 imoActFreq12Mhz;  /* 12 MHz or not            */

    uint8 clkDistDelay;     /* Delay for clk_d_sync and each of ACLK */

} CY_PM_BACKUP_STRUCT;


/***************************************
* Registers
***************************************/

/* Power Mode Wakeup Trim Register 1 */
#define CY_PM_PWRSYS_WAKE_TR1_REG           (* (reg8 *) CYREG_PWRSYS_WAKE_TR1 )
#define CY_PM_PWRSYS_WAKE_TR1_PTR           (  (reg8 *) CYREG_PWRSYS_WAKE_TR1 )

/* Master clock Divider Value Register */
#define CY_PM_CLKDIST_MSTR0_REG             (* (reg8 *) CYREG_CLKDIST_MSTR0 )
#define CY_PM_CLKDIST_MSTR0_PTR             (  (reg8 *) CYREG_CLKDIST_MSTR0 )

/* Master Clock Configuration Register/CPU Divider Value */
#define CY_PM_CLKDIST_MSTR1_REG             (* (reg8 *) CYREG_CLKDIST_MSTR1 )
#define CY_PM_CLKDIST_MSTR1_PTR             (  (reg8 *) CYREG_CLKDIST_MSTR1 )

/* Device is PSoC 3 and the revision is ES2 or earlier */
#if(CY_PSOC3_ES2)

    /* CPU Divider Value (specific for PSoC3 ES2) */
    #define CY_PM_SFR_USER_CPUCLK_DIV_REG   (* (reg8 *) CYREG_SFR_USER_CPUCLK_DIV )
    #define CY_PM_SFR_USER_CPUCLK_DIV_PTR   (  (reg8 *) CYREG_SFR_USER_CPUCLK_DIV )

#endif  /* (CY_PSOC3_ES2) */

/* Clock distribution configuration Register */
#define CY_PM_CLKDIST_CR_REG                (* (reg8 *) CYREG_CLKDIST_CR )
#define CY_PM_CLKDIST_CR_PTR                (  (reg8 *) CYREG_CLKDIST_CR )

/* CLK_BUS LSB Divider Value Register */
#define CY_PM_CLK_BUS_LSB_DIV_REG           (* (reg8 *) CYREG_CLKDIST_BCFG0 )
#define CY_PM_CLK_BUS_LSB_DIV_PTR           (  (reg8 *) CYREG_CLKDIST_BCFG0 )

/* CLK_BUS MSB Divider Value Register */
#define CY_PM_CLK_BUS_MSB_DIV_REG           (* (reg8 *) CYREG_CLKDIST_BCFG1 )
#define CY_PM_CLK_BUS_MSB_DIV_PTR           (  (reg8 *) CYREG_CLKDIST_BCFG1 )

/* CLK_BUS Configuration Register */
#define CLK_BUS_CFG_REG                     (* (reg8 *) CYREG_CLKDIST_BCFG2 )
#define CLK_BUS_CFG_PTR                     (  (reg8 *) CYREG_CLKDIST_BCFG2 )

/* Power Mode Control/Status Register */
#define CY_PM_MODE_CSR_REG                  (* (reg8 *) CYREG_PM_MODE_CSR )
#define CY_PM_MODE_CSR_PTR                  (  (reg8 *) CYREG_PM_MODE_CSR )

/* Power System Control Register 1 */
#define CY_PM_PWRSYS_CR1_REG                (* (reg8 *) CYREG_PWRSYS_CR1 )
#define CY_PM_PWRSYS_CR1_PTR                (  (reg8 *) CYREG_PWRSYS_CR1 )

/* Power System Control Register 0 */
#define CY_PM_PWRSYS_CR0_REG                (* (reg8 *) CYREG_PWRSYS_CR0 )
#define CY_PM_PWRSYS_CR0_PTR                (  (reg8 *) CYREG_PWRSYS_CR0 )

/* Internal Low-speed Oscillator Control Register 0 */
#define CY_PM_SLOWCLK_ILO_CR0_REG           (* (reg8 *) CYREG_SLOWCLK_ILO_CR0 )
#define CY_PM_SLOWCLK_ILO_CR0_PTR           (  (reg8 *) CYREG_SLOWCLK_ILO_CR0 )

/* External 32kHz Crystal Oscillator Control Register */
#define CY_PM_SLOWCLK_X32_CR_REG            (* (reg8 *) CYREG_SLOWCLK_X32_CR )
#define CY_PM_SLOWCLK_X32_CR_PTR            (  (reg8 *) CYREG_SLOWCLK_X32_CR )

/* Device is PSoC 3 and the revision is ES3 or later */
#if(CY_PSOC3_ES3)

    /* MLOGIC Debug Register */
    #define CY_PM_MLOGIC_DBG_REG            (* (reg8 *) CYREG_MLOGIC_DEBUG )
    #define CY_PM_MLOGIC_DBG_PTR            (  (reg8 *) CYREG_MLOGIC_DEBUG )

    /* Port Pin Configuration Register */
    #define CY_PM_PRT1_PC3_REG              (* (reg8 *) CYREG_PRT1_PC3 )
    #define CY_PM_PRT1_PC3_PTR              (  (reg8 *) CYREG_PRT1_PC3 )

    /* Sleep Regulator Trim Register */
    #define CY_PM_PWRSYS_SLP_TR_REG         (* (reg8 *) CYREG_PWRSYS_SLP_TR )
    #define CY_PM_PWRSYS_SLP_TR_PTR         (  (reg8 *) CYREG_PWRSYS_SLP_TR )

    /* Power Mode Wakeup Trim Register 2 */
    #define CY_PM_PWRSYS_WAKE_TR2_REG           (* (reg8 *) CYREG_PWRSYS_WAKE_TR2 )
    #define CY_PM_PWRSYS_WAKE_TR2_PTR           (  (reg8 *) CYREG_PWRSYS_WAKE_TR2 )

#endif /* (CY_PSOC3_ES3) */

/* Reset System Control Register */
#define CY_PM_RESET_CR1_REG                 (* (reg8 *) CYREG_RESET_CR1 )
#define CY_PM_RESET_CR1_PTR                 (  (reg8 *) CYREG_RESET_CR1 )

/* Power Mode Wakeup Trim Register 0 */
#define CY_PM_PWRSYS_WAKE_TR0_REG           (* (reg8 *) CYREG_PWRSYS_WAKE_TR0 )
#define CY_PM_PWRSYS_WAKE_TR0_PTR           (  (reg8 *) CYREG_PWRSYS_WAKE_TR0 )

/* Device is PSoC 3 and the revision is ES2 or earlier, or
*  device is PSoC 5 and the revision is ES1 or earlier.
*/
#if(CY_PSOC5_ES1 || CY_PSOC3_ES2)

    /* Power Mode Buzz Trim Register */
    #define CY_PM_PWRSYS_BUZZ_TR_REG        (* (reg8 *) CYREG_PWRSYS_BUZZ_TR )
    #define CY_PM_PWRSYS_BUZZ_TR_PTR        (  (reg8 *) CYREG_PWRSYS_BUZZ_TR )

#endif  /* (CY_PSOC5_ES1 || CY_PSOC3_ES2) */

/* Power Manager Interrupt Status Register */
#define CY_PM_INT_SR_REG                    (* (reg8 *) CYREG_PM_INT_SR )
#define CY_PM_INT_SR_PTR                    (  (reg8 *) CYREG_PM_INT_SR )

/* Active Power Mode Configuration Register 0 */
#define CY_PM_ACT_CFG0_REG                  (* (reg8 *) CYREG_PM_ACT_CFG0 )
#define CY_PM_ACT_CFG0_PTR                  (  (reg8 *) CYREG_PM_ACT_CFG0 )

/* Active Power Mode Configuration Register 1 */
#define CY_PM_ACT_CFG1_REG                  (* (reg8 *) CYREG_PM_ACT_CFG1 )
#define CY_PM_ACT_CFG1_PTR                  (  (reg8 *) CYREG_PM_ACT_CFG1 )

/* Active Power Mode Configuration Register 2 */
#define CY_PM_ACT_CFG2_REG                  (* (reg8 *) CYREG_PM_ACT_CFG2 )
#define CY_PM_ACT_CFG2_PTR                  (  (reg8 *) CYREG_PM_ACT_CFG2 )

/* Boost Control 1 */
#define CY_PM_BOOST_CR1_REG                 (* (reg8 *) CYREG_BOOST_CR1 )
#define CY_PM_BOOST_CR1_PTR                 (  (reg8 *) CYREG_BOOST_CR1 )

/* Timewheel Configuration Register 0 */
#define CY_PM_TW_CFG0_REG                   (* (reg8 *) CYREG_PM_TW_CFG0 )
#define CY_PM_TW_CFG0_PTR                   (  (reg8 *) CYREG_PM_TW_CFG0 )

/* Timewheel Configuration Register 1 */
#define CY_PM_TW_CFG1_REG                   (* (reg8 *) CYREG_PM_TW_CFG1 )
#define CY_PM_TW_CFG1_PTR                   (  (reg8 *) CYREG_PM_TW_CFG1 )

/* Timewheel Configuration Register 2 */
#define CY_PM_TW_CFG2_REG                   (* (reg8 *) CYREG_PM_TW_CFG2 )
#define CY_PM_TW_CFG2_PTR                   (  (reg8 *) CYREG_PM_TW_CFG2 )

/* PLL Status Register */
#define CY_PM_FASTCLK_PLL_SR_REG            (*(reg8 *) CYREG_FASTCLK_PLL_SR )
#define CY_PM_FASTCLK_PLL_SR_PTR            ( (reg8 *) CYREG_FASTCLK_PLL_SR )

/* Internal Main Oscillator Control Register */
#define CY_PM_FASTCLK_IMO_CR_REG            (* (reg8 *) CYREG_FASTCLK_IMO_CR )
#define CY_PM_FASTCLK_IMO_CR_PTR            (  (reg8 *) CYREG_FASTCLK_IMO_CR )

/* PLL Configuration Register */
#define CY_PM_FASTCLK_PLL_CFG0_REG          (* (reg8 *) CYREG_FASTCLK_PLL_CFG0 )
#define CY_PM_FASTCLK_PLL_CFG0_PTR          (  (reg8 *) CYREG_FASTCLK_PLL_CFG0 )

/* External 4-33 MHz Crystal Oscillator Status and Control Register */
#define CY_PM_FASTCLK_XMHZ_CSR_REG          (* (reg8 *) CYREG_FASTCLK_XMHZ_CSR )
#define CY_PM_FASTCLK_XMHZ_CSR_PTR          (  (reg8 *) CYREG_FASTCLK_XMHZ_CSR )

/* Delay block Configuration Register */
#define CY_PM_CLKDIST_DELAY_REG             (* (reg8 *) CYREG_CLKDIST_DLY1 )
#define CY_PM_CLKDIST_DELAY_PTR             (  (reg8 *) CYREG_CLKDIST_DLY1 )

/* Device is PSoC 3 */
#if(CY_PSOC3)

    /* Cache Control Register */
    #define CY_PM_CACHE_CR_REG              (* (reg8 *) CYREG_CACHE_CR )
    #define CY_PM_CACHE_CR_PTR              (  (reg8 *) CYREG_CACHE_CR )

#else   /* Device is PSoC 5 */

    /* Cache Control Register */
    #define CY_PM_CACHE_CR_REG              (* (reg8 *) CYREG_CACHE_CC_CTL )
    #define CY_PM_CACHE_CR_PTR              (  (reg8 *) CYREG_CACHE_CC_CTL )

#endif  /* (CY_PSOC3) */

/* Device is PSoC 3 and the revision is ES3 or later. */
#if(CY_PSOC3_ES3)

    /* Power Mode Wakeup Mask Configuration Register 0 */
    #define CY_PM_WAKEUP_CFG0_REG           (* (reg8 *) CYREG_PM_WAKEUP_CFG0 )
    #define CY_PM_WAKEUP_CFG0_PTR           (  (reg8 *) CYREG_PM_WAKEUP_CFG0 )

    /* Power Mode Wakeup Mask Configuration Register 1 */
    #define CY_PM_WAKEUP_CFG1_REG           (* (reg8 *) CYREG_PM_WAKEUP_CFG1 )
    #define CY_PM_WAKEUP_CFG1_PTR           (  (reg8 *) CYREG_PM_WAKEUP_CFG1 )

    /* Power Mode Wakeup Mask Configuration Register 2 */
    #define CY_PM_WAKEUP_CFG2_REG           (* (reg8 *) CYREG_PM_WAKEUP_CFG2 )
    #define CY_PM_WAKEUP_CFG2_PTR           (  (reg8 *) CYREG_PM_WAKEUP_CFG2 )

#endif  /* (CY_PSOC3_ES3) */

/* Device is PSoC 5 and the revision is ES1 or earlier. */
#if(CY_PSOC5_ES1)

    /* Watchdog Timer Configuration Register */
    #define CY_PM_WDT_CFG_REG               (* (reg8 *) CYREG_PM_WDT_CFG )
    #define CY_PM_WDT_CFG_PTR               (  (reg8 *) CYREG_PM_WDT_CFG )

#endif  /* (CY_PSOC5_ES1) */


/***************************************
* Register Constants
***************************************/

/* Internal Main Oscillator Control Register */

#define CY_PM_FASTCLK_IMO_CR_FREQ_MASK  (0x07u)    /* IMO frequency mask    */
#define CY_PM_FASTCLK_IMO_CR_FREQ_12MHZ (0x00u)    /* IMO frequency 12 MHz  */
#define CY_PM_FASTCLK_IMO_CR_F2XON      (0x10u)    /* IMO doubler enable    */
#define CY_PM_FASTCLK_IMO_CR_USB        (0x40u)    /* IMO is in USB mode    */

#define CY_PM_MASTER_CLK_SRC_IMO        (0u)
#define CY_PM_MASTER_CLK_SRC_PLL        (1u)
#define CY_PM_MASTER_CLK_SRC_XTAL       (2u)
#define CY_PM_MASTER_CLK_SRC_DSI        (3u)
#define CY_PM_MASTER_CLK_SRC_MASK       (3u)

#define CY_PM_PLL_CFG0_ENABLE           (0x01u)     /* PLL enable             */
#define CY_PM_PLL_STATUS_LOCK           (0x01u)     /* PLL Lock Status        */
#define CY_PM_XMHZ_CSR_ENABLE           (0x01u)     /* Enable X MHz OSC       */
#define CY_PM_XMHZ_CSR_XERR             (0x80u)     /* High indicates failure */
#define CY_PM_BOOST_ENABLE              (0x08u)     /* Boost enable           */
#define CY_PM_ILO_CR0_EN_1K             (0x02u)     /* Enable 1kHz ILO        */
#define CY_PM_ILO_CR0_EN_100K           (0x04u)     /* Enable 100kHz ILO      */
#define CY_PM_ILO_CR0_PD_MODE           (0x10u)     /* Power down mode for ILO*/
#define CY_PM_X32_CR_X32EN              (0x01u)     /* Enable 32kHz OSC       */

#define CY_PM_CTW_INTERVAL_MASK         (0x0Fu)     /* CTW interval mask      */
#define CY_PM_CTW_IE                    (0x08u)     /* CTW interrupt enable   */
#define CY_PM_CTW_EN                    (0x04u)     /* CTW enable             */
#define CY_PM_FTW_IE                    (0x02u)     /* FTW interrupt enable   */
#define CY_PM_FTW_EN                    (0x01u)     /* FTW enable             */
#define CY_PM_1PPS_EN                   (0x10u)     /* 1PPS enable            */
#define CY_PM_1PPS_IE                   (0x20u)     /* 1PPS interrupt enable  */


#define CY_PM_ACT_EN_CLK_A_MASK         (0x0Fu)
#define CY_PM_ACT_EN_CLK_D_MASK         (0xFFu)

#define CY_PM_DIV_BY_ONE                (0x00u)

/* Internal Main Oscillator Control Register */
#define CY_PM_FASTCLK_IMO_CR_XCLKEN     (0x20u)

/* Clock distribution configuration Register */
#define CY_PM_CLKDIST_IMO_OUT_MASK      (0x30u)
#define CY_PM_CLKDIST_IMO_OUT_IMO       (0x00u)
#define CY_PM_CLKDIST_IMO2X_SRC         (0x40u)

/* Waiting for the hibernate/sleep regulator to stabilize */
#define CY_PM_MODE_CSR_PWRUP_PULSE_Q    (0x08u)

#define CY_PM_MODE_CSR_ACTIVE           (0x00u)     /* Active power mode      */
#define CY_PM_MODE_CSR_ALT_ACT          (0x01u)     /* Alternate Active power */
#define CY_PM_MODE_CSR_SLEEP            (0x03u)     /* Sleep power mode       */
#define CY_PM_MODE_CSR_HIBERNATE        (0x04u)     /* Hibernate power mode   */
#define CY_PM_MODE_CSR_MASK             (0x07u)

/* I2C regulator backup enable */
#define CY_PM_PWRSYS_CR1_I2CREG_BACKUP  (0x04u)

/* When set, prepares the system to disable the LDO-A */
#define CY_PM_PWRSYS_CR1_LDOA_ISO       (0x01u)

/* When set, disables the analog LDO regulator */
#define CY_PM_PWRSYS_CR1_LDOA_DIS       (0x02u)

#define CY_PM_PWRSYS_WAKE_TR2_VCCD_CLK_DET  (0x04u)

#define CY_PM_FTW_INT                   (0x01u)     /* FTW event has occured  */
#define CY_PM_CTW_INT                   (0x02u)     /* CTW event has occured  */
#define CY_PM_ONEPPS_INT                (0x04u)     /* 1PPS event has occured */

/* Active Power Mode Configuration Register 0 */
#define CY_PM_ACT_CFG0_IMO              (0x10u)     /* IMO enable in Active */

/* Cache Control Register (same mask for all device revisions) */
#define CY_PM_CACHE_CR_CYCLES_MASK      (0xC0u)

/* Bus Clock divider to divide-by-one */
#define CY_PM_BUS_CLK_DIV_BY_ONE        (0x00u)

/* HVI/LVI feature on the external analog and digital supply mask */
#define CY_PM_RESET_CR1_HVI_LVI_EN_MASK (0x07u)

/* The high-voltage-interrupt feature on the external analog supply */
#define CY_PM_RESET_CR1_HVIA_EN         (0x04u)

/* The low-voltage-interrupt feature on the external analog supply */
#define CY_PM_RESET_CR1_LVIA_EN         (0x02u)

/* The low-voltage-interrupt feature on the external digital supply */
#define CY_PM_RESET_CR1_LVID_EN         (0x01u)

/* Allows the system to program delays on clk_sync_d */
#define CY_PM_CLKDIST_DELAY_EN          (0x04u)


/* Device is PSoC 3 and the revision is ES3 or later */
#if(CY_PSOC3_ES3)

    #define CY_PM_WAKEUP_SRC_CMPS_MASK          (0x000Fu)

    /* Disable the sleep regulator and shorts vccd to vpwrsleep */
    #define CY_PM_PWRSYS_SLP_TR_BYPASS          (0x10u)

    /* CPU clock divider mask */
    #define CY_PM_CLKDIST_CPU_DIV_MASK          (0xF0u)

    /* Serial Wire View (SWV) clock enable */
    #define CY_PM_MLOGIC_DBG_SWV_CLK_EN         (0x04u)

    /* Port drive mode */
    #define CY_PM_PRT1_PC3_DM_MASK              (0xf1u)

    /* Mode 6, stong pull-up, strong pull-down */
    #define CY_PM_PRT1_PC3_DM_STRONG            (0x0Cu)

    /* Holdoff mask sleep trim */
    #define CY_PM_PWRSYS_SLP_TR_HIBSLP_HOLDOFF_MASK (0x1Fu)

    /* When set, enables buzz wakeups */
    #define CY_PM_PWRSYS_WAKE_TR2_EN_BUZZ       (0x01u)

#endif  /* (CY_PSOC3_ES3) */


/* Device is PSoC 3 and the revision is ES2 or earlier */
#if(CY_PSOC3_ES2)

    /* CPU clock divider mask */
    #define CY_PM_SFR_USER_CPUCLK_MASK          (0x0Fu)

#endif  /* (CY_PSOC3_ES2) */


/* Device is PSoC 3 and the revision is ES2 or earlier, or
*  device is PSoC 5 and the revision is ES1 or earlier.
*/
#if(CY_PSOC5_ES1 || CY_PSOC3_ES2)

    #define CY_PM_PWRSYS_BUZZ_TR_512_TICKS      (0x08u)
    #define CY_PM_PWRSYS_BUZZ_TR_MASK           (0xF0u)

#endif  /* (CY_PSOC5_ES1 || CY_PSOC3_ES2) */


/* Device is PSoC 5 and the revision is ES1 or earlier. */
#if(CY_PSOC5_ES1)

    /* Watchdog Timer Configuration Register */
    #define CY_PM_WDT_CFG_CTW_RESET             (0x80u)

    /***************************************************************************
    * The PICU interrupt type registers are divided into three sections where
    * the registers addresses are consecutive.
    ***************************************************************************/
    #define CY_PM_PICU_0_6_INT_BASE      (CYDEV_PICU_INTTYPE_PICU0_BASE )
    #define CY_PM_PICU_12_INT_BASE       (CYDEV_PICU_INTTYPE_PICU12_BASE)
    #define CY_PM_PICU_15_INT_BASE       (CYDEV_PICU_INTTYPE_PICU15_BASE)

    #define CY_PM_PICU_0_6_INT_SIZE      (CYDEV_PICU_INTTYPE_PICU0_SIZE + CYDEV_PICU_INTTYPE_PICU1_SIZE + \
                                          CYDEV_PICU_INTTYPE_PICU2_SIZE + CYDEV_PICU_INTTYPE_PICU3_SIZE + \
                                          CYDEV_PICU_INTTYPE_PICU4_SIZE + CYDEV_PICU_INTTYPE_PICU5_SIZE + \
                                          CYDEV_PICU_INTTYPE_PICU6_SIZE)
    #define CY_PM_PICU_12_INT_SIZE       (CYDEV_PICU_INTTYPE_PICU12_SIZE)
    #define CY_PM_PICU_15_INT_SIZE       (CYDEV_PICU_INTTYPE_PICU15_SIZE)

#endif  /* (CY_PSOC5_ES1) */


#endif  /* CY_PM_H */


/* [] END OF FILE */
