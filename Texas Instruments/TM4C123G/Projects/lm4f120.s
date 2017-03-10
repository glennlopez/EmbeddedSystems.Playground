;*************************************************************
;
; lm4f120.s - LM4F120H5QR Register Definitions
;
; Copyright (c) 2011-2012 Texas Instruments Incorporated.  All rights reserved.
; Software License Agreement
; 
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions
;   are met:
; 
;   Redistributions of source code must retain the above copyright
;   notice, this list of conditions and the following disclaimer.
; 
;   Redistributions in binary form must reproduce the above copyright
;   notice, this list of conditions and the following disclaimer in the
;   documentation and/or other materials provided with the  
;   distribution.
; 
;   Neither the name of Texas Instruments Incorporated nor the names of
;   its contributors may be used to endorse or promote products derived
;   from this software without specific prior written permission.
; 
; THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
; "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
; LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
; A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
; OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
; SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
; LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
; DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
; THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
; (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
; OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; 
; This is part of revision 9453 of the Stellaris Firmware Development Package.
;
;*************************************************************

;*********************************************************
;edited from C to assembly by Jonathan Valvano 2/17/2013
;*********************************************************

;*************************************************************
;
; Watchdog Timer registers (WATCHDOG0)
;
;*************************************************************
WATCHDOG0_LOAD_R        EQU   0x40000000
WATCHDOG0_VALUE_R       EQU   0x40000004
WATCHDOG0_CTL_R         EQU   0x40000008
WATCHDOG0_ICR_R         EQU   0x4000000C
WATCHDOG0_RIS_R         EQU   0x40000010
WATCHDOG0_MIS_R         EQU   0x40000014
WATCHDOG0_TEST_R        EQU   0x40000418
WATCHDOG0_LOCK_R        EQU   0x40000C00

;*************************************************************
;
; Watchdog Timer registers (WATCHDOG1)
;
;*************************************************************
WATCHDOG1_LOAD_R        EQU   0x40001000
WATCHDOG1_VALUE_R       EQU   0x40001004
WATCHDOG1_CTL_R         EQU   0x40001008
WATCHDOG1_ICR_R         EQU   0x4000100C
WATCHDOG1_RIS_R         EQU   0x40001010
WATCHDOG1_MIS_R         EQU   0x40001014
WATCHDOG1_TEST_R        EQU   0x40001418
WATCHDOG1_LOCK_R        EQU   0x40001C00

;*************************************************************
;
; GPIO registers (PORTA)
;
;*************************************************************
GPIO_PORTA_DATA_BITS_R  EQU   0x40004000   
GPIO_PORTA_DATA_R       EQU   0x400043FC
GPIO_PORTA_DIR_R        EQU   0x40004400
GPIO_PORTA_IS_R         EQU   0x40004404
GPIO_PORTA_IBE_R        EQU   0x40004408
GPIO_PORTA_IEV_R        EQU   0x4000440C
GPIO_PORTA_IM_R         EQU   0x40004410
GPIO_PORTA_RIS_R        EQU   0x40004414
GPIO_PORTA_MIS_R        EQU   0x40004418
GPIO_PORTA_ICR_R        EQU   0x4000441C
GPIO_PORTA_AFSEL_R      EQU   0x40004420
GPIO_PORTA_DR2R_R       EQU   0x40004500
GPIO_PORTA_DR4R_R       EQU   0x40004504
GPIO_PORTA_DR8R_R       EQU   0x40004508
GPIO_PORTA_ODR_R        EQU   0x4000450C
GPIO_PORTA_PUR_R        EQU   0x40004510
GPIO_PORTA_PDR_R        EQU   0x40004514
GPIO_PORTA_SLR_R        EQU   0x40004518
GPIO_PORTA_DEN_R        EQU   0x4000451C
GPIO_PORTA_LOCK_R       EQU   0x40004520
GPIO_PORTA_CR_R         EQU   0x40004524
GPIO_PORTA_AMSEL_R      EQU   0x40004528
GPIO_PORTA_PCTL_R       EQU   0x4000452C
GPIO_PORTA_ADCCTL_R     EQU   0x40004530
GPIO_PORTA_DMACTL_R     EQU   0x40004534
GPIO_PORTA_SI_R         EQU   0x40004538

;*************************************************************
;
; GPIO registers (PORTB)
;
;*************************************************************
GPIO_PORTB_DATA_BITS_R  EQU   0x40005000   
GPIO_PORTB_DATA_R       EQU   0x400053FC
GPIO_PORTB_DIR_R        EQU   0x40005400
GPIO_PORTB_IS_R         EQU   0x40005404
GPIO_PORTB_IBE_R        EQU   0x40005408
GPIO_PORTB_IEV_R        EQU   0x4000540C
GPIO_PORTB_IM_R         EQU   0x40005410
GPIO_PORTB_RIS_R        EQU   0x40005414
GPIO_PORTB_MIS_R        EQU   0x40005418
GPIO_PORTB_ICR_R        EQU   0x4000541C
GPIO_PORTB_AFSEL_R      EQU   0x40005420
GPIO_PORTB_DR2R_R       EQU   0x40005500
GPIO_PORTB_DR4R_R       EQU   0x40005504
GPIO_PORTB_DR8R_R       EQU   0x40005508
GPIO_PORTB_ODR_R        EQU   0x4000550C
GPIO_PORTB_PUR_R        EQU   0x40005510
GPIO_PORTB_PDR_R        EQU   0x40005514
GPIO_PORTB_SLR_R        EQU   0x40005518
GPIO_PORTB_DEN_R        EQU   0x4000551C
GPIO_PORTB_LOCK_R       EQU   0x40005520
GPIO_PORTB_CR_R         EQU   0x40005524
GPIO_PORTB_AMSEL_R      EQU   0x40005528
GPIO_PORTB_PCTL_R       EQU   0x4000552C
GPIO_PORTB_ADCCTL_R     EQU   0x40005530
GPIO_PORTB_DMACTL_R     EQU   0x40005534
GPIO_PORTB_SI_R         EQU   0x40005538

;*************************************************************
;
; GPIO registers (PORTC)
;
;*************************************************************
GPIO_PORTC_DATA_BITS_R  EQU   0x40006000   
GPIO_PORTC_DATA_R       EQU   0x400063FC
GPIO_PORTC_DIR_R        EQU   0x40006400
GPIO_PORTC_IS_R         EQU   0x40006404
GPIO_PORTC_IBE_R        EQU   0x40006408
GPIO_PORTC_IEV_R        EQU   0x4000640C
GPIO_PORTC_IM_R         EQU   0x40006410
GPIO_PORTC_RIS_R        EQU   0x40006414
GPIO_PORTC_MIS_R        EQU   0x40006418
GPIO_PORTC_ICR_R        EQU   0x4000641C
GPIO_PORTC_AFSEL_R      EQU   0x40006420
GPIO_PORTC_DR2R_R       EQU   0x40006500
GPIO_PORTC_DR4R_R       EQU   0x40006504
GPIO_PORTC_DR8R_R       EQU   0x40006508
GPIO_PORTC_ODR_R        EQU   0x4000650C
GPIO_PORTC_PUR_R        EQU   0x40006510
GPIO_PORTC_PDR_R        EQU   0x40006514
GPIO_PORTC_SLR_R        EQU   0x40006518
GPIO_PORTC_DEN_R        EQU   0x4000651C
GPIO_PORTC_LOCK_R       EQU   0x40006520
GPIO_PORTC_CR_R         EQU   0x40006524
GPIO_PORTC_AMSEL_R      EQU   0x40006528
GPIO_PORTC_PCTL_R       EQU   0x4000652C
GPIO_PORTC_ADCCTL_R     EQU   0x40006530
GPIO_PORTC_DMACTL_R     EQU   0x40006534
GPIO_PORTC_SI_R         EQU   0x40006538

;*************************************************************
;
; GPIO registers (PORTD)
;
;*************************************************************
GPIO_PORTD_DATA_BITS_R  EQU   0x40007000   
GPIO_PORTD_DATA_R       EQU   0x400073FC
GPIO_PORTD_DIR_R        EQU   0x40007400
GPIO_PORTD_IS_R         EQU   0x40007404
GPIO_PORTD_IBE_R        EQU   0x40007408
GPIO_PORTD_IEV_R        EQU   0x4000740C
GPIO_PORTD_IM_R         EQU   0x40007410
GPIO_PORTD_RIS_R        EQU   0x40007414
GPIO_PORTD_MIS_R        EQU   0x40007418
GPIO_PORTD_ICR_R        EQU   0x4000741C
GPIO_PORTD_AFSEL_R      EQU   0x40007420
GPIO_PORTD_DR2R_R       EQU   0x40007500
GPIO_PORTD_DR4R_R       EQU   0x40007504
GPIO_PORTD_DR8R_R       EQU   0x40007508
GPIO_PORTD_ODR_R        EQU   0x4000750C
GPIO_PORTD_PUR_R        EQU   0x40007510
GPIO_PORTD_PDR_R        EQU   0x40007514
GPIO_PORTD_SLR_R        EQU   0x40007518
GPIO_PORTD_DEN_R        EQU   0x4000751C
GPIO_PORTD_LOCK_R       EQU   0x40007520
GPIO_PORTD_CR_R         EQU   0x40007524
GPIO_PORTD_AMSEL_R      EQU   0x40007528
GPIO_PORTD_PCTL_R       EQU   0x4000752C
GPIO_PORTD_ADCCTL_R     EQU   0x40007530
GPIO_PORTD_DMACTL_R     EQU   0x40007534
GPIO_PORTD_SI_R         EQU   0x40007538

;*************************************************************
;
; SSI registers (SSI0)
;
;*************************************************************
SSI0_CR0_R              EQU   0x40008000
SSI0_CR1_R              EQU   0x40008004
SSI0_DR_R               EQU   0x40008008
SSI0_SR_R               EQU   0x4000800C
SSI0_CPSR_R             EQU   0x40008010
SSI0_IM_R               EQU   0x40008014
SSI0_RIS_R              EQU   0x40008018
SSI0_MIS_R              EQU   0x4000801C
SSI0_ICR_R              EQU   0x40008020
SSI0_DMACTL_R           EQU   0x40008024
SSI0_CC_R               EQU   0x40008FC8

;*************************************************************
;
; SSI registers (SSI1)
;
;*************************************************************
SSI1_CR0_R              EQU   0x40009000
SSI1_CR1_R              EQU   0x40009004
SSI1_DR_R               EQU   0x40009008
SSI1_SR_R               EQU   0x4000900C
SSI1_CPSR_R             EQU   0x40009010
SSI1_IM_R               EQU   0x40009014
SSI1_RIS_R              EQU   0x40009018
SSI1_MIS_R              EQU   0x4000901C
SSI1_ICR_R              EQU   0x40009020
SSI1_DMACTL_R           EQU   0x40009024
SSI1_CC_R               EQU   0x40009FC8

;*************************************************************
;
; SSI registers (SSI2)
;
;*************************************************************
SSI2_CR0_R              EQU   0x4000A000
SSI2_CR1_R              EQU   0x4000A004
SSI2_DR_R               EQU   0x4000A008
SSI2_SR_R               EQU   0x4000A00C
SSI2_CPSR_R             EQU   0x4000A010
SSI2_IM_R               EQU   0x4000A014
SSI2_RIS_R              EQU   0x4000A018
SSI2_MIS_R              EQU   0x4000A01C
SSI2_ICR_R              EQU   0x4000A020
SSI2_DMACTL_R           EQU   0x4000A024
SSI2_CC_R               EQU   0x4000AFC8

;*************************************************************
;
; SSI registers (SSI3)
;
;*************************************************************
SSI3_CR0_R              EQU   0x4000B000
SSI3_CR1_R              EQU   0x4000B004
SSI3_DR_R               EQU   0x4000B008
SSI3_SR_R               EQU   0x4000B00C
SSI3_CPSR_R             EQU   0x4000B010
SSI3_IM_R               EQU   0x4000B014
SSI3_RIS_R              EQU   0x4000B018
SSI3_MIS_R              EQU   0x4000B01C
SSI3_ICR_R              EQU   0x4000B020
SSI3_DMACTL_R           EQU   0x4000B024
SSI3_CC_R               EQU   0x4000BFC8

;*************************************************************
;
; UART registers (UART0)
;
;*************************************************************
UART0_DR_R              EQU   0x4000C000
UART0_RSR_R             EQU   0x4000C004
UART0_ECR_R             EQU   0x4000C004
UART0_FR_R              EQU   0x4000C018
UART0_ILPR_R            EQU   0x4000C020
UART0_IBRD_R            EQU   0x4000C024
UART0_FBRD_R            EQU   0x4000C028
UART0_LCRH_R            EQU   0x4000C02C
UART0_CTL_R             EQU   0x4000C030
UART0_IFLS_R            EQU   0x4000C034
UART0_IM_R              EQU   0x4000C038
UART0_RIS_R             EQU   0x4000C03C
UART0_MIS_R             EQU   0x4000C040
UART0_ICR_R             EQU   0x4000C044
UART0_DMACTL_R          EQU   0x4000C048
UART0_LCTL_R            EQU   0x4000C090
UART0_LSS_R             EQU   0x4000C094
UART0_LTIM_R            EQU   0x4000C098
UART0_9BITADDR_R        EQU   0x4000C0A4
UART0_9BITAMASK_R       EQU   0x4000C0A8
UART0_PP_R              EQU   0x4000CFC0
UART0_CC_R              EQU   0x4000CFC8

;*************************************************************
;
; UART registers (UART1)
;
;*************************************************************
UART1_DR_R              EQU   0x4000D000
UART1_RSR_R             EQU   0x4000D004
UART1_ECR_R             EQU   0x4000D004
UART1_FR_R              EQU   0x4000D018
UART1_ILPR_R            EQU   0x4000D020
UART1_IBRD_R            EQU   0x4000D024
UART1_FBRD_R            EQU   0x4000D028
UART1_LCRH_R            EQU   0x4000D02C
UART1_CTL_R             EQU   0x4000D030
UART1_IFLS_R            EQU   0x4000D034
UART1_IM_R              EQU   0x4000D038
UART1_RIS_R             EQU   0x4000D03C
UART1_MIS_R             EQU   0x4000D040
UART1_ICR_R             EQU   0x4000D044
UART1_DMACTL_R          EQU   0x4000D048
UART1_LCTL_R            EQU   0x4000D090
UART1_LSS_R             EQU   0x4000D094
UART1_LTIM_R            EQU   0x4000D098
UART1_9BITADDR_R        EQU   0x4000D0A4
UART1_9BITAMASK_R       EQU   0x4000D0A8
UART1_PP_R              EQU   0x4000DFC0
UART1_CC_R              EQU   0x4000DFC8

;*************************************************************
;
; UART registers (UART2)
;
;*************************************************************
UART2_DR_R              EQU   0x4000E000
UART2_RSR_R             EQU   0x4000E004
UART2_ECR_R             EQU   0x4000E004
UART2_FR_R              EQU   0x4000E018
UART2_ILPR_R            EQU   0x4000E020
UART2_IBRD_R            EQU   0x4000E024
UART2_FBRD_R            EQU   0x4000E028
UART2_LCRH_R            EQU   0x4000E02C
UART2_CTL_R             EQU   0x4000E030
UART2_IFLS_R            EQU   0x4000E034
UART2_IM_R              EQU   0x4000E038
UART2_RIS_R             EQU   0x4000E03C
UART2_MIS_R             EQU   0x4000E040
UART2_ICR_R             EQU   0x4000E044
UART2_DMACTL_R          EQU   0x4000E048
UART2_LCTL_R            EQU   0x4000E090
UART2_LSS_R             EQU   0x4000E094
UART2_LTIM_R            EQU   0x4000E098
UART2_9BITADDR_R        EQU   0x4000E0A4
UART2_9BITAMASK_R       EQU   0x4000E0A8
UART2_PP_R              EQU   0x4000EFC0
UART2_CC_R              EQU   0x4000EFC8

;*************************************************************
;
; UART registers (UART3)
;
;*************************************************************
UART3_DR_R              EQU   0x4000F000
UART3_RSR_R             EQU   0x4000F004
UART3_ECR_R             EQU   0x4000F004
UART3_FR_R              EQU   0x4000F018
UART3_ILPR_R            EQU   0x4000F020
UART3_IBRD_R            EQU   0x4000F024
UART3_FBRD_R            EQU   0x4000F028
UART3_LCRH_R            EQU   0x4000F02C
UART3_CTL_R             EQU   0x4000F030
UART3_IFLS_R            EQU   0x4000F034
UART3_IM_R              EQU   0x4000F038
UART3_RIS_R             EQU   0x4000F03C
UART3_MIS_R             EQU   0x4000F040
UART3_ICR_R             EQU   0x4000F044
UART3_DMACTL_R          EQU   0x4000F048
UART3_LCTL_R            EQU   0x4000F090
UART3_LSS_R             EQU   0x4000F094
UART3_LTIM_R            EQU   0x4000F098
UART3_9BITADDR_R        EQU   0x4000F0A4
UART3_9BITAMASK_R       EQU   0x4000F0A8
UART3_PP_R              EQU   0x4000FFC0
UART3_CC_R              EQU   0x4000FFC8

;*************************************************************
;
; UART registers (UART4)
;
;*************************************************************
UART4_DR_R              EQU   0x40010000
UART4_RSR_R             EQU   0x40010004
UART4_ECR_R             EQU   0x40010004
UART4_FR_R              EQU   0x40010018
UART4_ILPR_R            EQU   0x40010020
UART4_IBRD_R            EQU   0x40010024
UART4_FBRD_R            EQU   0x40010028
UART4_LCRH_R            EQU   0x4001002C
UART4_CTL_R             EQU   0x40010030
UART4_IFLS_R            EQU   0x40010034
UART4_IM_R              EQU   0x40010038
UART4_RIS_R             EQU   0x4001003C
UART4_MIS_R             EQU   0x40010040
UART4_ICR_R             EQU   0x40010044
UART4_DMACTL_R          EQU   0x40010048
UART4_LCTL_R            EQU   0x40010090
UART4_LSS_R             EQU   0x40010094
UART4_LTIM_R            EQU   0x40010098
UART4_9BITADDR_R        EQU   0x400100A4
UART4_9BITAMASK_R       EQU   0x400100A8
UART4_PP_R              EQU   0x40010FC0
UART4_CC_R              EQU   0x40010FC8

;*************************************************************
;
; UART registers (UART5)
;
;*************************************************************
UART5_DR_R              EQU   0x40011000
UART5_RSR_R             EQU   0x40011004
UART5_ECR_R             EQU   0x40011004
UART5_FR_R              EQU   0x40011018
UART5_ILPR_R            EQU   0x40011020
UART5_IBRD_R            EQU   0x40011024
UART5_FBRD_R            EQU   0x40011028
UART5_LCRH_R            EQU   0x4001102C
UART5_CTL_R             EQU   0x40011030
UART5_IFLS_R            EQU   0x40011034
UART5_IM_R              EQU   0x40011038
UART5_RIS_R             EQU   0x4001103C
UART5_MIS_R             EQU   0x40011040
UART5_ICR_R             EQU   0x40011044
UART5_DMACTL_R          EQU   0x40011048
UART5_LCTL_R            EQU   0x40011090
UART5_LSS_R             EQU   0x40011094
UART5_LTIM_R            EQU   0x40011098
UART5_9BITADDR_R        EQU   0x400110A4
UART5_9BITAMASK_R       EQU   0x400110A8
UART5_PP_R              EQU   0x40011FC0
UART5_CC_R              EQU   0x40011FC8

;*************************************************************
;
; UART registers (UART6)
;
;*************************************************************
UART6_DR_R              EQU   0x40012000
UART6_RSR_R             EQU   0x40012004
UART6_ECR_R             EQU   0x40012004
UART6_FR_R              EQU   0x40012018
UART6_ILPR_R            EQU   0x40012020
UART6_IBRD_R            EQU   0x40012024
UART6_FBRD_R            EQU   0x40012028
UART6_LCRH_R            EQU   0x4001202C
UART6_CTL_R             EQU   0x40012030
UART6_IFLS_R            EQU   0x40012034
UART6_IM_R              EQU   0x40012038
UART6_RIS_R             EQU   0x4001203C
UART6_MIS_R             EQU   0x40012040
UART6_ICR_R             EQU   0x40012044
UART6_DMACTL_R          EQU   0x40012048
UART6_LCTL_R            EQU   0x40012090
UART6_LSS_R             EQU   0x40012094
UART6_LTIM_R            EQU   0x40012098
UART6_9BITADDR_R        EQU   0x400120A4
UART6_9BITAMASK_R       EQU   0x400120A8
UART6_PP_R              EQU   0x40012FC0
UART6_CC_R              EQU   0x40012FC8

;*************************************************************
;
; UART registers (UART7)
;
;*************************************************************
UART7_DR_R              EQU   0x40013000
UART7_RSR_R             EQU   0x40013004
UART7_ECR_R             EQU   0x40013004
UART7_FR_R              EQU   0x40013018
UART7_ILPR_R            EQU   0x40013020
UART7_IBRD_R            EQU   0x40013024
UART7_FBRD_R            EQU   0x40013028
UART7_LCRH_R            EQU   0x4001302C
UART7_CTL_R             EQU   0x40013030
UART7_IFLS_R            EQU   0x40013034
UART7_IM_R              EQU   0x40013038
UART7_RIS_R             EQU   0x4001303C
UART7_MIS_R             EQU   0x40013040
UART7_ICR_R             EQU   0x40013044
UART7_DMACTL_R          EQU   0x40013048
UART7_LCTL_R            EQU   0x40013090
UART7_LSS_R             EQU   0x40013094
UART7_LTIM_R            EQU   0x40013098
UART7_9BITADDR_R        EQU   0x400130A4
UART7_9BITAMASK_R       EQU   0x400130A8
UART7_PP_R              EQU   0x40013FC0
UART7_CC_R              EQU   0x40013FC8

;*************************************************************
;
; I2C registers (I2C0 MASTER)
;
;*************************************************************
I2C0_MASTER_MSA_R       EQU   0x40020000
I2C0_MASTER_MCS_R       EQU   0x40020004
I2C0_MASTER_MDR_R       EQU   0x40020008
I2C0_MASTER_MTPR_R      EQU   0x4002000C
I2C0_MASTER_MIMR_R      EQU   0x40020010
I2C0_MASTER_MRIS_R      EQU   0x40020014
I2C0_MASTER_MMIS_R      EQU   0x40020018
I2C0_MASTER_MICR_R      EQU   0x4002001C
I2C0_MASTER_MCR_R       EQU   0x40020020
I2C0_MASTER_MCLKOCNT_R  EQU   0x40020024
I2C0_MASTER_MBMON_R     EQU   0x4002002C

;*************************************************************
;
; I2C registers (I2C0 SLAVE)
;
;*************************************************************
I2C0_SLAVE_SOAR_R       EQU   0x40020800
I2C0_SLAVE_SCSR_R       EQU   0x40020804
I2C0_SLAVE_SDR_R        EQU   0x40020808
I2C0_SLAVE_SIMR_R       EQU   0x4002080C
I2C0_SLAVE_SRIS_R       EQU   0x40020810
I2C0_SLAVE_SMIS_R       EQU   0x40020814
I2C0_SLAVE_SICR_R       EQU   0x40020818
I2C0_SLAVE_SOAR2_R      EQU   0x4002081C
I2C0_SLAVE_SACKCTL_R    EQU   0x40020820

;*************************************************************
;
; I2C registers (I2C1 MASTER)
;
;*************************************************************
I2C1_MASTER_MSA_R       EQU   0x40021000
I2C1_MASTER_MCS_R       EQU   0x40021004
I2C1_MASTER_MDR_R       EQU   0x40021008
I2C1_MASTER_MTPR_R      EQU   0x4002100C
I2C1_MASTER_MIMR_R      EQU   0x40021010
I2C1_MASTER_MRIS_R      EQU   0x40021014
I2C1_MASTER_MMIS_R      EQU   0x40021018
I2C1_MASTER_MICR_R      EQU   0x4002101C
I2C1_MASTER_MCR_R       EQU   0x40021020
I2C1_MASTER_MCLKOCNT_R  EQU   0x40021024
I2C1_MASTER_MBMON_R     EQU   0x4002102C

;*************************************************************
;
; I2C registers (I2C1 SLAVE)
;
;*************************************************************
I2C1_SLAVE_SOAR_R       EQU   0x40021800
I2C1_SLAVE_SCSR_R       EQU   0x40021804
I2C1_SLAVE_SDR_R        EQU   0x40021808
I2C1_SLAVE_SIMR_R       EQU   0x4002180C
I2C1_SLAVE_SRIS_R       EQU   0x40021810
I2C1_SLAVE_SMIS_R       EQU   0x40021814
I2C1_SLAVE_SICR_R       EQU   0x40021818
I2C1_SLAVE_SOAR2_R      EQU   0x4002181C
I2C1_SLAVE_SACKCTL_R    EQU   0x40021820

;*************************************************************
;
; I2C registers (I2C2 MASTER)
;
;*************************************************************
I2C2_MASTER_MSA_R       EQU   0x40022000
I2C2_MASTER_MCS_R       EQU   0x40022004
I2C2_MASTER_MDR_R       EQU   0x40022008
I2C2_MASTER_MTPR_R      EQU   0x4002200C
I2C2_MASTER_MIMR_R      EQU   0x40022010
I2C2_MASTER_MRIS_R      EQU   0x40022014
I2C2_MASTER_MMIS_R      EQU   0x40022018
I2C2_MASTER_MICR_R      EQU   0x4002201C
I2C2_MASTER_MCR_R       EQU   0x40022020
I2C2_MASTER_MCLKOCNT_R  EQU   0x40022024
I2C2_MASTER_MBMON_R     EQU   0x4002202C

;*************************************************************
;
; I2C registers (I2C2 SLAVE)
;
;*************************************************************
I2C2_SLAVE_SOAR_R       EQU   0x40022800
I2C2_SLAVE_SCSR_R       EQU   0x40022804
I2C2_SLAVE_SDR_R        EQU   0x40022808
I2C2_SLAVE_SIMR_R       EQU   0x4002280C
I2C2_SLAVE_SRIS_R       EQU   0x40022810
I2C2_SLAVE_SMIS_R       EQU   0x40022814
I2C2_SLAVE_SICR_R       EQU   0x40022818
I2C2_SLAVE_SOAR2_R      EQU   0x4002281C
I2C2_SLAVE_SACKCTL_R    EQU   0x40022820

;*************************************************************
;
; I2C registers (I2C3 MASTER)
;
;*************************************************************
I2C3_MASTER_MSA_R       EQU   0x40023000
I2C3_MASTER_MCS_R       EQU   0x40023004
I2C3_MASTER_MDR_R       EQU   0x40023008
I2C3_MASTER_MTPR_R      EQU   0x4002300C
I2C3_MASTER_MIMR_R      EQU   0x40023010
I2C3_MASTER_MRIS_R      EQU   0x40023014
I2C3_MASTER_MMIS_R      EQU   0x40023018
I2C3_MASTER_MICR_R      EQU   0x4002301C
I2C3_MASTER_MCR_R       EQU   0x40023020
I2C3_MASTER_MCLKOCNT_R  EQU   0x40023024
I2C3_MASTER_MBMON_R     EQU   0x4002302C

;*************************************************************
;
; I2C registers (I2C3 SLAVE)
;
;*************************************************************
I2C3_SLAVE_SOAR_R       EQU   0x40023800
I2C3_SLAVE_SCSR_R       EQU   0x40023804
I2C3_SLAVE_SDR_R        EQU   0x40023808
I2C3_SLAVE_SIMR_R       EQU   0x4002380C
I2C3_SLAVE_SRIS_R       EQU   0x40023810
I2C3_SLAVE_SMIS_R       EQU   0x40023814
I2C3_SLAVE_SICR_R       EQU   0x40023818
I2C3_SLAVE_SOAR2_R      EQU   0x4002381C
I2C3_SLAVE_SACKCTL_R    EQU   0x40023820

;*************************************************************
;
; GPIO registers (PORTE)
;
;*************************************************************
GPIO_PORTE_DATA_BITS_R  EQU   0x40024000   
GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_IS_R         EQU   0x40024404
GPIO_PORTE_IBE_R        EQU   0x40024408
GPIO_PORTE_IEV_R        EQU   0x4002440C
GPIO_PORTE_IM_R         EQU   0x40024410
GPIO_PORTE_RIS_R        EQU   0x40024414
GPIO_PORTE_MIS_R        EQU   0x40024418
GPIO_PORTE_ICR_R        EQU   0x4002441C
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DR2R_R       EQU   0x40024500
GPIO_PORTE_DR4R_R       EQU   0x40024504
GPIO_PORTE_DR8R_R       EQU   0x40024508
GPIO_PORTE_ODR_R        EQU   0x4002450C
GPIO_PORTE_PUR_R        EQU   0x40024510
GPIO_PORTE_PDR_R        EQU   0x40024514
GPIO_PORTE_SLR_R        EQU   0x40024518
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_LOCK_R       EQU   0x40024520
GPIO_PORTE_CR_R         EQU   0x40024524
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
GPIO_PORTE_ADCCTL_R     EQU   0x40024530
GPIO_PORTE_DMACTL_R     EQU   0x40024534
GPIO_PORTE_SI_R         EQU   0x40024538

;*************************************************************
;
; GPIO registers (PORTF)
;
;*************************************************************
GPIO_PORTF_DATA_BITS_R  EQU   0x40025000   
GPIO_PORTF_DATA_R       EQU   0x400253FC
GPIO_PORTF_DIR_R        EQU   0x40025400
GPIO_PORTF_IS_R         EQU   0x40025404
GPIO_PORTF_IBE_R        EQU   0x40025408
GPIO_PORTF_IEV_R        EQU   0x4002540C
GPIO_PORTF_IM_R         EQU   0x40025410
GPIO_PORTF_RIS_R        EQU   0x40025414
GPIO_PORTF_MIS_R        EQU   0x40025418
GPIO_PORTF_ICR_R        EQU   0x4002541C
GPIO_PORTF_AFSEL_R      EQU   0x40025420
GPIO_PORTF_DR2R_R       EQU   0x40025500
GPIO_PORTF_DR4R_R       EQU   0x40025504
GPIO_PORTF_DR8R_R       EQU   0x40025508
GPIO_PORTF_ODR_R        EQU   0x4002550C
GPIO_PORTF_PUR_R        EQU   0x40025510
GPIO_PORTF_PDR_R        EQU   0x40025514
GPIO_PORTF_SLR_R        EQU   0x40025518
GPIO_PORTF_DEN_R        EQU   0x4002551C
GPIO_PORTF_LOCK_R       EQU   0x40025520
GPIO_PORTF_CR_R         EQU   0x40025524
GPIO_PORTF_AMSEL_R      EQU   0x40025528
GPIO_PORTF_PCTL_R       EQU   0x4002552C
GPIO_PORTF_ADCCTL_R     EQU   0x40025530
GPIO_PORTF_DMACTL_R     EQU   0x40025534
GPIO_PORTF_SI_R         EQU   0x40025538

;*************************************************************
;
; Timer registers (TIMER0)
;
;*************************************************************
TIMER0_CFG_R            EQU   0x40030000
TIMER0_TAMR_R           EQU   0x40030004
TIMER0_TBMR_R           EQU   0x40030008
TIMER0_CTL_R            EQU   0x4003000C
TIMER0_SYNC_R           EQU   0x40030010
TIMER0_IMR_R            EQU   0x40030018
TIMER0_RIS_R            EQU   0x4003001C
TIMER0_MIS_R            EQU   0x40030020
TIMER0_ICR_R            EQU   0x40030024
TIMER0_TAILR_R          EQU   0x40030028
TIMER0_TBILR_R          EQU   0x4003002C
TIMER0_TAMATCHR_R       EQU   0x40030030
TIMER0_TBMATCHR_R       EQU   0x40030034
TIMER0_TAPR_R           EQU   0x40030038
TIMER0_TBPR_R           EQU   0x4003003C
TIMER0_TAPMR_R          EQU   0x40030040
TIMER0_TBPMR_R          EQU   0x40030044
TIMER0_TAR_R            EQU   0x40030048
TIMER0_TBR_R            EQU   0x4003004C
TIMER0_TAV_R            EQU   0x40030050
TIMER0_TBV_R            EQU   0x40030054
TIMER0_RTCPD_R          EQU   0x40030058
TIMER0_TAPS_R           EQU   0x4003005C
TIMER0_TBPS_R           EQU   0x40030060
TIMER0_TAPV_R           EQU   0x40030064
TIMER0_TBPV_R           EQU   0x40030068
TIMER0_PP_R             EQU   0x40030FC0

;*************************************************************
;
; Timer registers (TIMER1)
;
;*************************************************************
TIMER1_CFG_R            EQU   0x40031000
TIMER1_TAMR_R           EQU   0x40031004
TIMER1_TBMR_R           EQU   0x40031008
TIMER1_CTL_R            EQU   0x4003100C
TIMER1_SYNC_R           EQU   0x40031010
TIMER1_IMR_R            EQU   0x40031018
TIMER1_RIS_R            EQU   0x4003101C
TIMER1_MIS_R            EQU   0x40031020
TIMER1_ICR_R            EQU   0x40031024
TIMER1_TAILR_R          EQU   0x40031028
TIMER1_TBILR_R          EQU   0x4003102C
TIMER1_TAMATCHR_R       EQU   0x40031030
TIMER1_TBMATCHR_R       EQU   0x40031034
TIMER1_TAPR_R           EQU   0x40031038
TIMER1_TBPR_R           EQU   0x4003103C
TIMER1_TAPMR_R          EQU   0x40031040
TIMER1_TBPMR_R          EQU   0x40031044
TIMER1_TAR_R            EQU   0x40031048
TIMER1_TBR_R            EQU   0x4003104C
TIMER1_TAV_R            EQU   0x40031050
TIMER1_TBV_R            EQU   0x40031054
TIMER1_RTCPD_R          EQU   0x40031058
TIMER1_TAPS_R           EQU   0x4003105C
TIMER1_TBPS_R           EQU   0x40031060
TIMER1_TAPV_R           EQU   0x40031064
TIMER1_TBPV_R           EQU   0x40031068
TIMER1_PP_R             EQU   0x40031FC0

;*************************************************************
;
; Timer registers (TIMER2)
;
;*************************************************************
TIMER2_CFG_R            EQU   0x40032000
TIMER2_TAMR_R           EQU   0x40032004
TIMER2_TBMR_R           EQU   0x40032008
TIMER2_CTL_R            EQU   0x4003200C
TIMER2_SYNC_R           EQU   0x40032010
TIMER2_IMR_R            EQU   0x40032018
TIMER2_RIS_R            EQU   0x4003201C
TIMER2_MIS_R            EQU   0x40032020
TIMER2_ICR_R            EQU   0x40032024
TIMER2_TAILR_R          EQU   0x40032028
TIMER2_TBILR_R          EQU   0x4003202C
TIMER2_TAMATCHR_R       EQU   0x40032030
TIMER2_TBMATCHR_R       EQU   0x40032034
TIMER2_TAPR_R           EQU   0x40032038
TIMER2_TBPR_R           EQU   0x4003203C
TIMER2_TAPMR_R          EQU   0x40032040
TIMER2_TBPMR_R          EQU   0x40032044
TIMER2_TAR_R            EQU   0x40032048
TIMER2_TBR_R            EQU   0x4003204C
TIMER2_TAV_R            EQU   0x40032050
TIMER2_TBV_R            EQU   0x40032054
TIMER2_RTCPD_R          EQU   0x40032058
TIMER2_TAPS_R           EQU   0x4003205C
TIMER2_TBPS_R           EQU   0x40032060
TIMER2_TAPV_R           EQU   0x40032064
TIMER2_TBPV_R           EQU   0x40032068
TIMER2_PP_R             EQU   0x40032FC0

;*************************************************************
;
; Timer registers (TIMER3)
;
;*************************************************************
TIMER3_CFG_R            EQU   0x40033000
TIMER3_TAMR_R           EQU   0x40033004
TIMER3_TBMR_R           EQU   0x40033008
TIMER3_CTL_R            EQU   0x4003300C
TIMER3_SYNC_R           EQU   0x40033010
TIMER3_IMR_R            EQU   0x40033018
TIMER3_RIS_R            EQU   0x4003301C
TIMER3_MIS_R            EQU   0x40033020
TIMER3_ICR_R            EQU   0x40033024
TIMER3_TAILR_R          EQU   0x40033028
TIMER3_TBILR_R          EQU   0x4003302C
TIMER3_TAMATCHR_R       EQU   0x40033030
TIMER3_TBMATCHR_R       EQU   0x40033034
TIMER3_TAPR_R           EQU   0x40033038
TIMER3_TBPR_R           EQU   0x4003303C
TIMER3_TAPMR_R          EQU   0x40033040
TIMER3_TBPMR_R          EQU   0x40033044
TIMER3_TAR_R            EQU   0x40033048
TIMER3_TBR_R            EQU   0x4003304C
TIMER3_TAV_R            EQU   0x40033050
TIMER3_TBV_R            EQU   0x40033054
TIMER3_RTCPD_R          EQU   0x40033058
TIMER3_TAPS_R           EQU   0x4003305C
TIMER3_TBPS_R           EQU   0x40033060
TIMER3_TAPV_R           EQU   0x40033064
TIMER3_TBPV_R           EQU   0x40033068
TIMER3_PP_R             EQU   0x40033FC0

;*************************************************************
;
; Timer registers (TIMER4)
;
;*************************************************************
TIMER4_CFG_R            EQU   0x40034000
TIMER4_TAMR_R           EQU   0x40034004
TIMER4_TBMR_R           EQU   0x40034008
TIMER4_CTL_R            EQU   0x4003400C
TIMER4_SYNC_R           EQU   0x40034010
TIMER4_IMR_R            EQU   0x40034018
TIMER4_RIS_R            EQU   0x4003401C
TIMER4_MIS_R            EQU   0x40034020
TIMER4_ICR_R            EQU   0x40034024
TIMER4_TAILR_R          EQU   0x40034028
TIMER4_TBILR_R          EQU   0x4003402C
TIMER4_TAMATCHR_R       EQU   0x40034030
TIMER4_TBMATCHR_R       EQU   0x40034034
TIMER4_TAPR_R           EQU   0x40034038
TIMER4_TBPR_R           EQU   0x4003403C
TIMER4_TAPMR_R          EQU   0x40034040
TIMER4_TBPMR_R          EQU   0x40034044
TIMER4_TAR_R            EQU   0x40034048
TIMER4_TBR_R            EQU   0x4003404C
TIMER4_TAV_R            EQU   0x40034050
TIMER4_TBV_R            EQU   0x40034054
TIMER4_RTCPD_R          EQU   0x40034058
TIMER4_TAPS_R           EQU   0x4003405C
TIMER4_TBPS_R           EQU   0x40034060
TIMER4_TAPV_R           EQU   0x40034064
TIMER4_TBPV_R           EQU   0x40034068
TIMER4_PP_R             EQU   0x40034FC0

;*************************************************************
;
; Timer registers (TIMER5)
;
;*************************************************************
TIMER5_CFG_R            EQU   0x40035000
TIMER5_TAMR_R           EQU   0x40035004
TIMER5_TBMR_R           EQU   0x40035008
TIMER5_CTL_R            EQU   0x4003500C
TIMER5_SYNC_R           EQU   0x40035010
TIMER5_IMR_R            EQU   0x40035018
TIMER5_RIS_R            EQU   0x4003501C
TIMER5_MIS_R            EQU   0x40035020
TIMER5_ICR_R            EQU   0x40035024
TIMER5_TAILR_R          EQU   0x40035028
TIMER5_TBILR_R          EQU   0x4003502C
TIMER5_TAMATCHR_R       EQU   0x40035030
TIMER5_TBMATCHR_R       EQU   0x40035034
TIMER5_TAPR_R           EQU   0x40035038
TIMER5_TBPR_R           EQU   0x4003503C
TIMER5_TAPMR_R          EQU   0x40035040
TIMER5_TBPMR_R          EQU   0x40035044
TIMER5_TAR_R            EQU   0x40035048
TIMER5_TBR_R            EQU   0x4003504C
TIMER5_TAV_R            EQU   0x40035050
TIMER5_TBV_R            EQU   0x40035054
TIMER5_RTCPD_R          EQU   0x40035058
TIMER5_TAPS_R           EQU   0x4003505C
TIMER5_TBPS_R           EQU   0x40035060
TIMER5_TAPV_R           EQU   0x40035064
TIMER5_TBPV_R           EQU   0x40035068
TIMER5_PP_R             EQU   0x40035FC0

;*************************************************************
;
; Timer registers (WTIMER0)
;
;*************************************************************
WTIMER0_CFG_R           EQU   0x40036000
WTIMER0_TAMR_R          EQU   0x40036004
WTIMER0_TBMR_R          EQU   0x40036008
WTIMER0_CTL_R           EQU   0x4003600C
WTIMER0_SYNC_R          EQU   0x40036010
WTIMER0_IMR_R           EQU   0x40036018
WTIMER0_RIS_R           EQU   0x4003601C
WTIMER0_MIS_R           EQU   0x40036020
WTIMER0_ICR_R           EQU   0x40036024
WTIMER0_TAILR_R         EQU   0x40036028
WTIMER0_TBILR_R         EQU   0x4003602C
WTIMER0_TAMATCHR_R      EQU   0x40036030
WTIMER0_TBMATCHR_R      EQU   0x40036034
WTIMER0_TAPR_R          EQU   0x40036038
WTIMER0_TBPR_R          EQU   0x4003603C
WTIMER0_TAPMR_R         EQU   0x40036040
WTIMER0_TBPMR_R         EQU   0x40036044
WTIMER0_TAR_R           EQU   0x40036048
WTIMER0_TBR_R           EQU   0x4003604C
WTIMER0_TAV_R           EQU   0x40036050
WTIMER0_TBV_R           EQU   0x40036054
WTIMER0_RTCPD_R         EQU   0x40036058
WTIMER0_TAPS_R          EQU   0x4003605C
WTIMER0_TBPS_R          EQU   0x40036060
WTIMER0_TAPV_R          EQU   0x40036064
WTIMER0_TBPV_R          EQU   0x40036068
WTIMER0_PP_R            EQU   0x40036FC0

;*************************************************************
;
; Timer registers (WTIMER1)
;
;*************************************************************
WTIMER1_CFG_R           EQU   0x40037000
WTIMER1_TAMR_R          EQU   0x40037004
WTIMER1_TBMR_R          EQU   0x40037008
WTIMER1_CTL_R           EQU   0x4003700C
WTIMER1_SYNC_R          EQU   0x40037010
WTIMER1_IMR_R           EQU   0x40037018
WTIMER1_RIS_R           EQU   0x4003701C
WTIMER1_MIS_R           EQU   0x40037020
WTIMER1_ICR_R           EQU   0x40037024
WTIMER1_TAILR_R         EQU   0x40037028
WTIMER1_TBILR_R         EQU   0x4003702C
WTIMER1_TAMATCHR_R      EQU   0x40037030
WTIMER1_TBMATCHR_R      EQU   0x40037034
WTIMER1_TAPR_R          EQU   0x40037038
WTIMER1_TBPR_R          EQU   0x4003703C
WTIMER1_TAPMR_R         EQU   0x40037040
WTIMER1_TBPMR_R         EQU   0x40037044
WTIMER1_TAR_R           EQU   0x40037048
WTIMER1_TBR_R           EQU   0x4003704C
WTIMER1_TAV_R           EQU   0x40037050
WTIMER1_TBV_R           EQU   0x40037054
WTIMER1_RTCPD_R         EQU   0x40037058
WTIMER1_TAPS_R          EQU   0x4003705C
WTIMER1_TBPS_R          EQU   0x40037060
WTIMER1_TAPV_R          EQU   0x40037064
WTIMER1_TBPV_R          EQU   0x40037068
WTIMER1_PP_R            EQU   0x40037FC0

;*************************************************************
;
; ADC registers (ADC0)
;
;*************************************************************
ADC0_ACTSS_R            EQU   0x40038000
ADC0_RIS_R              EQU   0x40038004
ADC0_IM_R               EQU   0x40038008
ADC0_ISC_R              EQU   0x4003800C
ADC0_OSTAT_R            EQU   0x40038010
ADC0_EMUX_R             EQU   0x40038014
ADC0_USTAT_R            EQU   0x40038018
ADC0_SSPRI_R            EQU   0x40038020
ADC0_SPC_R              EQU   0x40038024
ADC0_PSSI_R             EQU   0x40038028
ADC0_SAC_R              EQU   0x40038030
ADC0_DCISC_R            EQU   0x40038034
ADC0_SSMUX0_R           EQU   0x40038040
ADC0_SSCTL0_R           EQU   0x40038044
ADC0_SSFIFO0_R          EQU   0x40038048
ADC0_SSFSTAT0_R         EQU   0x4003804C
ADC0_SSOP0_R            EQU   0x40038050
ADC0_SSDC0_R            EQU   0x40038054
ADC0_SSMUX1_R           EQU   0x40038060
ADC0_SSCTL1_R           EQU   0x40038064
ADC0_SSFIFO1_R          EQU   0x40038068
ADC0_SSFSTAT1_R         EQU   0x4003806C
ADC0_SSOP1_R            EQU   0x40038070
ADC0_SSDC1_R            EQU   0x40038074
ADC0_SSMUX2_R           EQU   0x40038080
ADC0_SSCTL2_R           EQU   0x40038084
ADC0_SSFIFO2_R          EQU   0x40038088
ADC0_SSFSTAT2_R         EQU   0x4003808C
ADC0_SSOP2_R            EQU   0x40038090
ADC0_SSDC2_R            EQU   0x40038094
ADC0_SSMUX3_R           EQU   0x400380A0
ADC0_SSCTL3_R           EQU   0x400380A4
ADC0_SSFIFO3_R          EQU   0x400380A8
ADC0_SSFSTAT3_R         EQU   0x400380AC
ADC0_SSOP3_R            EQU   0x400380B0
ADC0_SSDC3_R            EQU   0x400380B4
ADC0_DCRIC_R            EQU   0x40038D00
ADC0_DCCTL0_R           EQU   0x40038E00
ADC0_DCCTL1_R           EQU   0x40038E04
ADC0_DCCTL2_R           EQU   0x40038E08
ADC0_DCCTL3_R           EQU   0x40038E0C
ADC0_DCCTL4_R           EQU   0x40038E10
ADC0_DCCTL5_R           EQU   0x40038E14
ADC0_DCCTL6_R           EQU   0x40038E18
ADC0_DCCTL7_R           EQU   0x40038E1C
ADC0_DCCMP0_R           EQU   0x40038E40
ADC0_DCCMP1_R           EQU   0x40038E44
ADC0_DCCMP2_R           EQU   0x40038E48
ADC0_DCCMP3_R           EQU   0x40038E4C
ADC0_DCCMP4_R           EQU   0x40038E50
ADC0_DCCMP5_R           EQU   0x40038E54
ADC0_DCCMP6_R           EQU   0x40038E58
ADC0_DCCMP7_R           EQU   0x40038E5C
ADC0_PP_R               EQU   0x40038FC0
ADC0_PC_R               EQU   0x40038FC4
ADC0_CC_R               EQU   0x40038FC8

;*************************************************************
;
; ADC registers (ADC1)
;
;*************************************************************
ADC1_ACTSS_R            EQU   0x40039000
ADC1_RIS_R              EQU   0x40039004
ADC1_IM_R               EQU   0x40039008
ADC1_ISC_R              EQU   0x4003900C
ADC1_OSTAT_R            EQU   0x40039010
ADC1_EMUX_R             EQU   0x40039014
ADC1_USTAT_R            EQU   0x40039018
ADC1_SSPRI_R            EQU   0x40039020
ADC1_SPC_R              EQU   0x40039024
ADC1_PSSI_R             EQU   0x40039028
ADC1_SAC_R              EQU   0x40039030
ADC1_DCISC_R            EQU   0x40039034
ADC1_SSMUX0_R           EQU   0x40039040
ADC1_SSCTL0_R           EQU   0x40039044
ADC1_SSFIFO0_R          EQU   0x40039048
ADC1_SSFSTAT0_R         EQU   0x4003904C
ADC1_SSOP0_R            EQU   0x40039050
ADC1_SSDC0_R            EQU   0x40039054
ADC1_SSMUX1_R           EQU   0x40039060
ADC1_SSCTL1_R           EQU   0x40039064
ADC1_SSFIFO1_R          EQU   0x40039068
ADC1_SSFSTAT1_R         EQU   0x4003906C
ADC1_SSOP1_R            EQU   0x40039070
ADC1_SSDC1_R            EQU   0x40039074
ADC1_SSMUX2_R           EQU   0x40039080
ADC1_SSCTL2_R           EQU   0x40039084
ADC1_SSFIFO2_R          EQU   0x40039088
ADC1_SSFSTAT2_R         EQU   0x4003908C
ADC1_SSOP2_R            EQU   0x40039090
ADC1_SSDC2_R            EQU   0x40039094
ADC1_SSMUX3_R           EQU   0x400390A0
ADC1_SSCTL3_R           EQU   0x400390A4
ADC1_SSFIFO3_R          EQU   0x400390A8
ADC1_SSFSTAT3_R         EQU   0x400390AC
ADC1_SSOP3_R            EQU   0x400390B0
ADC1_SSDC3_R            EQU   0x400390B4
ADC1_DCRIC_R            EQU   0x40039D00
ADC1_DCCTL0_R           EQU   0x40039E00
ADC1_DCCTL1_R           EQU   0x40039E04
ADC1_DCCTL2_R           EQU   0x40039E08
ADC1_DCCTL3_R           EQU   0x40039E0C
ADC1_DCCTL4_R           EQU   0x40039E10
ADC1_DCCTL5_R           EQU   0x40039E14
ADC1_DCCTL6_R           EQU   0x40039E18
ADC1_DCCTL7_R           EQU   0x40039E1C
ADC1_DCCMP0_R           EQU   0x40039E40
ADC1_DCCMP1_R           EQU   0x40039E44
ADC1_DCCMP2_R           EQU   0x40039E48
ADC1_DCCMP3_R           EQU   0x40039E4C
ADC1_DCCMP4_R           EQU   0x40039E50
ADC1_DCCMP5_R           EQU   0x40039E54
ADC1_DCCMP6_R           EQU   0x40039E58
ADC1_DCCMP7_R           EQU   0x40039E5C
ADC1_PP_R               EQU   0x40039FC0
ADC1_PC_R               EQU   0x40039FC4
ADC1_CC_R               EQU   0x40039FC8

;*************************************************************
;
; Comparator registers (COMP)
;
;*************************************************************
COMP_ACMIS_R            EQU   0x4003C000
COMP_ACRIS_R            EQU   0x4003C004
COMP_ACINTEN_R          EQU   0x4003C008
COMP_ACREFCTL_R         EQU   0x4003C010
COMP_ACSTAT0_R          EQU   0x4003C020
COMP_ACCTL0_R           EQU   0x4003C024
COMP_ACSTAT1_R          EQU   0x4003C040
COMP_ACCTL1_R           EQU   0x4003C044
COMP_PP_R               EQU   0x4003CFC0

;*************************************************************
;
; CAN registers (CAN0)
;
;*************************************************************
CAN0_CTL_R              EQU   0x40040000
CAN0_STS_R              EQU   0x40040004
CAN0_ERR_R              EQU   0x40040008
CAN0_BIT_R              EQU   0x4004000C
CAN0_INT_R              EQU   0x40040010
CAN0_TST_R              EQU   0x40040014
CAN0_BRPE_R             EQU   0x40040018
CAN0_IF1CRQ_R           EQU   0x40040020
CAN0_IF1CMSK_R          EQU   0x40040024
CAN0_IF1MSK1_R          EQU   0x40040028
CAN0_IF1MSK2_R          EQU   0x4004002C
CAN0_IF1ARB1_R          EQU   0x40040030
CAN0_IF1ARB2_R          EQU   0x40040034
CAN0_IF1MCTL_R          EQU   0x40040038
CAN0_IF1DA1_R           EQU   0x4004003C
CAN0_IF1DA2_R           EQU   0x40040040
CAN0_IF1DB1_R           EQU   0x40040044
CAN0_IF1DB2_R           EQU   0x40040048
CAN0_IF2CRQ_R           EQU   0x40040080
CAN0_IF2CMSK_R          EQU   0x40040084
CAN0_IF2MSK1_R          EQU   0x40040088
CAN0_IF2MSK2_R          EQU   0x4004008C
CAN0_IF2ARB1_R          EQU   0x40040090
CAN0_IF2ARB2_R          EQU   0x40040094
CAN0_IF2MCTL_R          EQU   0x40040098
CAN0_IF2DA1_R           EQU   0x4004009C
CAN0_IF2DA2_R           EQU   0x400400A0
CAN0_IF2DB1_R           EQU   0x400400A4
CAN0_IF2DB2_R           EQU   0x400400A8
CAN0_TXRQ1_R            EQU   0x40040100
CAN0_TXRQ2_R            EQU   0x40040104
CAN0_NWDA1_R            EQU   0x40040120
CAN0_NWDA2_R            EQU   0x40040124
CAN0_MSG1INT_R          EQU   0x40040140
CAN0_MSG2INT_R          EQU   0x40040144
CAN0_MSG1VAL_R          EQU   0x40040160
CAN0_MSG2VAL_R          EQU   0x40040164

;*************************************************************
;
; Timer registers (WTIMER2)
;
;*************************************************************
WTIMER2_CFG_R           EQU   0x4004C000
WTIMER2_TAMR_R          EQU   0x4004C004
WTIMER2_TBMR_R          EQU   0x4004C008
WTIMER2_CTL_R           EQU   0x4004C00C
WTIMER2_SYNC_R          EQU   0x4004C010
WTIMER2_IMR_R           EQU   0x4004C018
WTIMER2_RIS_R           EQU   0x4004C01C
WTIMER2_MIS_R           EQU   0x4004C020
WTIMER2_ICR_R           EQU   0x4004C024
WTIMER2_TAILR_R         EQU   0x4004C028
WTIMER2_TBILR_R         EQU   0x4004C02C
WTIMER2_TAMATCHR_R      EQU   0x4004C030
WTIMER2_TBMATCHR_R      EQU   0x4004C034
WTIMER2_TAPR_R          EQU   0x4004C038
WTIMER2_TBPR_R          EQU   0x4004C03C
WTIMER2_TAPMR_R         EQU   0x4004C040
WTIMER2_TBPMR_R         EQU   0x4004C044
WTIMER2_TAR_R           EQU   0x4004C048
WTIMER2_TBR_R           EQU   0x4004C04C
WTIMER2_TAV_R           EQU   0x4004C050
WTIMER2_TBV_R           EQU   0x4004C054
WTIMER2_RTCPD_R         EQU   0x4004C058
WTIMER2_TAPS_R          EQU   0x4004C05C
WTIMER2_TBPS_R          EQU   0x4004C060
WTIMER2_TAPV_R          EQU   0x4004C064
WTIMER2_TBPV_R          EQU   0x4004C068
WTIMER2_PP_R            EQU   0x4004CFC0

;*************************************************************
;
; Timer registers (WTIMER3)
;
;*************************************************************
WTIMER3_CFG_R           EQU   0x4004D000
WTIMER3_TAMR_R          EQU   0x4004D004
WTIMER3_TBMR_R          EQU   0x4004D008
WTIMER3_CTL_R           EQU   0x4004D00C
WTIMER3_SYNC_R          EQU   0x4004D010
WTIMER3_IMR_R           EQU   0x4004D018
WTIMER3_RIS_R           EQU   0x4004D01C
WTIMER3_MIS_R           EQU   0x4004D020
WTIMER3_ICR_R           EQU   0x4004D024
WTIMER3_TAILR_R         EQU   0x4004D028
WTIMER3_TBILR_R         EQU   0x4004D02C
WTIMER3_TAMATCHR_R      EQU   0x4004D030
WTIMER3_TBMATCHR_R      EQU   0x4004D034
WTIMER3_TAPR_R          EQU   0x4004D038
WTIMER3_TBPR_R          EQU   0x4004D03C
WTIMER3_TAPMR_R         EQU   0x4004D040
WTIMER3_TBPMR_R         EQU   0x4004D044
WTIMER3_TAR_R           EQU   0x4004D048
WTIMER3_TBR_R           EQU   0x4004D04C
WTIMER3_TAV_R           EQU   0x4004D050
WTIMER3_TBV_R           EQU   0x4004D054
WTIMER3_RTCPD_R         EQU   0x4004D058
WTIMER3_TAPS_R          EQU   0x4004D05C
WTIMER3_TBPS_R          EQU   0x4004D060
WTIMER3_TAPV_R          EQU   0x4004D064
WTIMER3_TBPV_R          EQU   0x4004D068
WTIMER3_PP_R            EQU   0x4004DFC0

;*************************************************************
;
; Timer registers (WTIMER4)
;
;*************************************************************
WTIMER4_CFG_R           EQU   0x4004E000
WTIMER4_TAMR_R          EQU   0x4004E004
WTIMER4_TBMR_R          EQU   0x4004E008
WTIMER4_CTL_R           EQU   0x4004E00C
WTIMER4_SYNC_R          EQU   0x4004E010
WTIMER4_IMR_R           EQU   0x4004E018
WTIMER4_RIS_R           EQU   0x4004E01C
WTIMER4_MIS_R           EQU   0x4004E020
WTIMER4_ICR_R           EQU   0x4004E024
WTIMER4_TAILR_R         EQU   0x4004E028
WTIMER4_TBILR_R         EQU   0x4004E02C
WTIMER4_TAMATCHR_R      EQU   0x4004E030
WTIMER4_TBMATCHR_R      EQU   0x4004E034
WTIMER4_TAPR_R          EQU   0x4004E038
WTIMER4_TBPR_R          EQU   0x4004E03C
WTIMER4_TAPMR_R         EQU   0x4004E040
WTIMER4_TBPMR_R         EQU   0x4004E044
WTIMER4_TAR_R           EQU   0x4004E048
WTIMER4_TBR_R           EQU   0x4004E04C
WTIMER4_TAV_R           EQU   0x4004E050
WTIMER4_TBV_R           EQU   0x4004E054
WTIMER4_RTCPD_R         EQU   0x4004E058
WTIMER4_TAPS_R          EQU   0x4004E05C
WTIMER4_TBPS_R          EQU   0x4004E060
WTIMER4_TAPV_R          EQU   0x4004E064
WTIMER4_TBPV_R          EQU   0x4004E068
WTIMER4_PP_R            EQU   0x4004EFC0

;*************************************************************
;
; Timer registers (WTIMER5)
;
;*************************************************************
WTIMER5_CFG_R           EQU   0x4004F000
WTIMER5_TAMR_R          EQU   0x4004F004
WTIMER5_TBMR_R          EQU   0x4004F008
WTIMER5_CTL_R           EQU   0x4004F00C
WTIMER5_SYNC_R          EQU   0x4004F010
WTIMER5_IMR_R           EQU   0x4004F018
WTIMER5_RIS_R           EQU   0x4004F01C
WTIMER5_MIS_R           EQU   0x4004F020
WTIMER5_ICR_R           EQU   0x4004F024
WTIMER5_TAILR_R         EQU   0x4004F028
WTIMER5_TBILR_R         EQU   0x4004F02C
WTIMER5_TAMATCHR_R      EQU   0x4004F030
WTIMER5_TBMATCHR_R      EQU   0x4004F034
WTIMER5_TAPR_R          EQU   0x4004F038
WTIMER5_TBPR_R          EQU   0x4004F03C
WTIMER5_TAPMR_R         EQU   0x4004F040
WTIMER5_TBPMR_R         EQU   0x4004F044
WTIMER5_TAR_R           EQU   0x4004F048
WTIMER5_TBR_R           EQU   0x4004F04C
WTIMER5_TAV_R           EQU   0x4004F050
WTIMER5_TBV_R           EQU   0x4004F054
WTIMER5_RTCPD_R         EQU   0x4004F058
WTIMER5_TAPS_R          EQU   0x4004F05C
WTIMER5_TBPS_R          EQU   0x4004F060
WTIMER5_TAPV_R          EQU   0x4004F064
WTIMER5_TBPV_R          EQU   0x4004F068
WTIMER5_PP_R            EQU   0x4004FFC0

;*************************************************************
;
; Univeral Serial Bus registers (USB0)
;
;*************************************************************
USB0_FADDR_R            EQU   0x40050000
USB0_POWER_R            EQU   0x40050001
USB0_TXIS_R             EQU   0x40050002
USB0_RXIS_R             EQU   0x40050004
USB0_TXIE_R             EQU   0x40050006
USB0_RXIE_R             EQU   0x40050008
USB0_IS_R               EQU   0x4005000A
USB0_IE_R               EQU   0x4005000B
USB0_FRAME_R            EQU   0x4005000C
USB0_EPIDX_R            EQU   0x4005000E
USB0_TEST_R             EQU   0x4005000F
USB0_FIFO0_R            EQU   0x40050020
USB0_FIFO1_R            EQU   0x40050024
USB0_FIFO2_R            EQU   0x40050028
USB0_FIFO3_R            EQU   0x4005002C
USB0_FIFO4_R            EQU   0x40050030
USB0_FIFO5_R            EQU   0x40050034
USB0_FIFO6_R            EQU   0x40050038
USB0_FIFO7_R            EQU   0x4005003C
USB0_TXFIFOSZ_R         EQU   0x40050062
USB0_RXFIFOSZ_R         EQU   0x40050063
USB0_TXFIFOADD_R        EQU   0x40050064
USB0_RXFIFOADD_R        EQU   0x40050066
USB0_CONTIM_R           EQU   0x4005007A
USB0_FSEOF_R            EQU   0x4005007D
USB0_LSEOF_R            EQU   0x4005007E
USB0_CSRL0_R            EQU   0x40050102
USB0_CSRH0_R            EQU   0x40050103
USB0_COUNT0_R           EQU   0x40050108
USB0_TXMAXP1_R          EQU   0x40050110
USB0_TXCSRL1_R          EQU   0x40050112
USB0_TXCSRH1_R          EQU   0x40050113
USB0_RXMAXP1_R          EQU   0x40050114
USB0_RXCSRL1_R          EQU   0x40050116
USB0_RXCSRH1_R          EQU   0x40050117
USB0_RXCOUNT1_R         EQU   0x40050118
USB0_TXMAXP2_R          EQU   0x40050120
USB0_TXCSRL2_R          EQU   0x40050122
USB0_TXCSRH2_R          EQU   0x40050123
USB0_RXMAXP2_R          EQU   0x40050124
USB0_RXCSRL2_R          EQU   0x40050126
USB0_RXCSRH2_R          EQU   0x40050127
USB0_RXCOUNT2_R         EQU   0x40050128
USB0_TXMAXP3_R          EQU   0x40050130
USB0_TXCSRL3_R          EQU   0x40050132
USB0_TXCSRH3_R          EQU   0x40050133
USB0_RXMAXP3_R          EQU   0x40050134
USB0_RXCSRL3_R          EQU   0x40050136
USB0_RXCSRH3_R          EQU   0x40050137
USB0_RXCOUNT3_R         EQU   0x40050138
USB0_TXMAXP4_R          EQU   0x40050140
USB0_TXCSRL4_R          EQU   0x40050142
USB0_TXCSRH4_R          EQU   0x40050143
USB0_RXMAXP4_R          EQU   0x40050144
USB0_RXCSRL4_R          EQU   0x40050146
USB0_RXCSRH4_R          EQU   0x40050147
USB0_RXCOUNT4_R         EQU   0x40050148
USB0_TXMAXP5_R          EQU   0x40050150
USB0_TXCSRL5_R          EQU   0x40050152
USB0_TXCSRH5_R          EQU   0x40050153
USB0_RXMAXP5_R          EQU   0x40050154
USB0_RXCSRL5_R          EQU   0x40050156
USB0_RXCSRH5_R          EQU   0x40050157
USB0_RXCOUNT5_R         EQU   0x40050158
USB0_TXMAXP6_R          EQU   0x40050160
USB0_TXCSRL6_R          EQU   0x40050162
USB0_TXCSRH6_R          EQU   0x40050163
USB0_RXMAXP6_R          EQU   0x40050164
USB0_RXCSRL6_R          EQU   0x40050166
USB0_RXCSRH6_R          EQU   0x40050167
USB0_RXCOUNT6_R         EQU   0x40050168
USB0_TXMAXP7_R          EQU   0x40050170
USB0_TXCSRL7_R          EQU   0x40050172
USB0_TXCSRH7_R          EQU   0x40050173
USB0_RXMAXP7_R          EQU   0x40050174
USB0_RXCSRL7_R          EQU   0x40050176
USB0_RXCSRH7_R          EQU   0x40050177
USB0_RXCOUNT7_R         EQU   0x40050178
USB0_RXDPKTBUFDIS_R     EQU   0x40050340
USB0_TXDPKTBUFDIS_R     EQU   0x40050342
USB0_DRRIS_R            EQU   0x40050410
USB0_DRIM_R             EQU   0x40050414
USB0_DRISC_R            EQU   0x40050418
USB0_DMASEL_R           EQU   0x40050450
USB0_PP_R               EQU   0x40050FC0

;*************************************************************
;
; GPIO registers (PORTA AHB)
;
;*************************************************************
GPIO_PORTA_AHB_DATA_BITS_R  EQU   0x40058000   
GPIO_PORTA_AHB_DATA_R   EQU   0x400583FC
GPIO_PORTA_AHB_DIR_R    EQU   0x40058400
GPIO_PORTA_AHB_IS_R     EQU   0x40058404
GPIO_PORTA_AHB_IBE_R    EQU   0x40058408
GPIO_PORTA_AHB_IEV_R    EQU   0x4005840C
GPIO_PORTA_AHB_IM_R     EQU   0x40058410
GPIO_PORTA_AHB_RIS_R    EQU   0x40058414
GPIO_PORTA_AHB_MIS_R    EQU   0x40058418
GPIO_PORTA_AHB_ICR_R    EQU   0x4005841C
GPIO_PORTA_AHB_AFSEL_R  EQU   0x40058420
GPIO_PORTA_AHB_DR2R_R   EQU   0x40058500
GPIO_PORTA_AHB_DR4R_R   EQU   0x40058504
GPIO_PORTA_AHB_DR8R_R   EQU   0x40058508
GPIO_PORTA_AHB_ODR_R    EQU   0x4005850C
GPIO_PORTA_AHB_PUR_R    EQU   0x40058510
GPIO_PORTA_AHB_PDR_R    EQU   0x40058514
GPIO_PORTA_AHB_SLR_R    EQU   0x40058518
GPIO_PORTA_AHB_DEN_R    EQU   0x4005851C
GPIO_PORTA_AHB_LOCK_R   EQU   0x40058520
GPIO_PORTA_AHB_CR_R     EQU   0x40058524
GPIO_PORTA_AHB_AMSEL_R  EQU   0x40058528
GPIO_PORTA_AHB_PCTL_R   EQU   0x4005852C
GPIO_PORTA_AHB_ADCCTL_R EQU   0x40058530
GPIO_PORTA_AHB_DMACTL_R EQU   0x40058534
GPIO_PORTA_AHB_SI_R     EQU   0x40058538

;*************************************************************
;
; GPIO registers (PORTB AHB)
;
;*************************************************************
GPIO_PORTB_AHB_DATA_BITS_R  EQU   0x40059000   
GPIO_PORTB_AHB_DATA_R   EQU   0x400593FC
GPIO_PORTB_AHB_DIR_R    EQU   0x40059400
GPIO_PORTB_AHB_IS_R     EQU   0x40059404
GPIO_PORTB_AHB_IBE_R    EQU   0x40059408
GPIO_PORTB_AHB_IEV_R    EQU   0x4005940C
GPIO_PORTB_AHB_IM_R     EQU   0x40059410
GPIO_PORTB_AHB_RIS_R    EQU   0x40059414
GPIO_PORTB_AHB_MIS_R    EQU   0x40059418
GPIO_PORTB_AHB_ICR_R    EQU   0x4005941C
GPIO_PORTB_AHB_AFSEL_R  EQU   0x40059420
GPIO_PORTB_AHB_DR2R_R   EQU   0x40059500
GPIO_PORTB_AHB_DR4R_R   EQU   0x40059504
GPIO_PORTB_AHB_DR8R_R   EQU   0x40059508
GPIO_PORTB_AHB_ODR_R    EQU   0x4005950C
GPIO_PORTB_AHB_PUR_R    EQU   0x40059510
GPIO_PORTB_AHB_PDR_R    EQU   0x40059514
GPIO_PORTB_AHB_SLR_R    EQU   0x40059518
GPIO_PORTB_AHB_DEN_R    EQU   0x4005951C
GPIO_PORTB_AHB_LOCK_R   EQU   0x40059520
GPIO_PORTB_AHB_CR_R     EQU   0x40059524
GPIO_PORTB_AHB_AMSEL_R  EQU   0x40059528
GPIO_PORTB_AHB_PCTL_R   EQU   0x4005952C
GPIO_PORTB_AHB_ADCCTL_R EQU   0x40059530
GPIO_PORTB_AHB_DMACTL_R EQU   0x40059534
GPIO_PORTB_AHB_SI_R     EQU   0x40059538

;*************************************************************
;
; GPIO registers (PORTC AHB)
;
;*************************************************************
GPIO_PORTC_AHB_DATA_BITS_R  EQU   0x4005A000   
GPIO_PORTC_AHB_DATA_R   EQU   0x4005A3FC
GPIO_PORTC_AHB_DIR_R    EQU   0x4005A400
GPIO_PORTC_AHB_IS_R     EQU   0x4005A404
GPIO_PORTC_AHB_IBE_R    EQU   0x4005A408
GPIO_PORTC_AHB_IEV_R    EQU   0x4005A40C
GPIO_PORTC_AHB_IM_R     EQU   0x4005A410
GPIO_PORTC_AHB_RIS_R    EQU   0x4005A414
GPIO_PORTC_AHB_MIS_R    EQU   0x4005A418
GPIO_PORTC_AHB_ICR_R    EQU   0x4005A41C
GPIO_PORTC_AHB_AFSEL_R  EQU   0x4005A420
GPIO_PORTC_AHB_DR2R_R   EQU   0x4005A500
GPIO_PORTC_AHB_DR4R_R   EQU   0x4005A504
GPIO_PORTC_AHB_DR8R_R   EQU   0x4005A508
GPIO_PORTC_AHB_ODR_R    EQU   0x4005A50C
GPIO_PORTC_AHB_PUR_R    EQU   0x4005A510
GPIO_PORTC_AHB_PDR_R    EQU   0x4005A514
GPIO_PORTC_AHB_SLR_R    EQU   0x4005A518
GPIO_PORTC_AHB_DEN_R    EQU   0x4005A51C
GPIO_PORTC_AHB_LOCK_R   EQU   0x4005A520
GPIO_PORTC_AHB_CR_R     EQU   0x4005A524
GPIO_PORTC_AHB_AMSEL_R  EQU   0x4005A528
GPIO_PORTC_AHB_PCTL_R   EQU   0x4005A52C
GPIO_PORTC_AHB_ADCCTL_R EQU   0x4005A530
GPIO_PORTC_AHB_DMACTL_R EQU   0x4005A534
GPIO_PORTC_AHB_SI_R     EQU   0x4005A538

;*************************************************************
;
; GPIO registers (PORTD AHB)
;
;*************************************************************
GPIO_PORTD_AHB_DATA_BITS_R  EQU   0x4005B000   
GPIO_PORTD_AHB_DATA_R   EQU   0x4005B3FC
GPIO_PORTD_AHB_DIR_R    EQU   0x4005B400
GPIO_PORTD_AHB_IS_R     EQU   0x4005B404
GPIO_PORTD_AHB_IBE_R    EQU   0x4005B408
GPIO_PORTD_AHB_IEV_R    EQU   0x4005B40C
GPIO_PORTD_AHB_IM_R     EQU   0x4005B410
GPIO_PORTD_AHB_RIS_R    EQU   0x4005B414
GPIO_PORTD_AHB_MIS_R    EQU   0x4005B418
GPIO_PORTD_AHB_ICR_R    EQU   0x4005B41C
GPIO_PORTD_AHB_AFSEL_R  EQU   0x4005B420
GPIO_PORTD_AHB_DR2R_R   EQU   0x4005B500
GPIO_PORTD_AHB_DR4R_R   EQU   0x4005B504
GPIO_PORTD_AHB_DR8R_R   EQU   0x4005B508
GPIO_PORTD_AHB_ODR_R    EQU   0x4005B50C
GPIO_PORTD_AHB_PUR_R    EQU   0x4005B510
GPIO_PORTD_AHB_PDR_R    EQU   0x4005B514
GPIO_PORTD_AHB_SLR_R    EQU   0x4005B518
GPIO_PORTD_AHB_DEN_R    EQU   0x4005B51C
GPIO_PORTD_AHB_LOCK_R   EQU   0x4005B520
GPIO_PORTD_AHB_CR_R     EQU   0x4005B524
GPIO_PORTD_AHB_AMSEL_R  EQU   0x4005B528
GPIO_PORTD_AHB_PCTL_R   EQU   0x4005B52C
GPIO_PORTD_AHB_ADCCTL_R EQU   0x4005B530
GPIO_PORTD_AHB_DMACTL_R EQU   0x4005B534
GPIO_PORTD_AHB_SI_R     EQU   0x4005B538

;*************************************************************
;
; GPIO registers (PORTE AHB)
;
;*************************************************************
GPIO_PORTE_AHB_DATA_BITS_R  EQU   0x4005C000   
GPIO_PORTE_AHB_DATA_R   EQU   0x4005C3FC
GPIO_PORTE_AHB_DIR_R    EQU   0x4005C400
GPIO_PORTE_AHB_IS_R     EQU   0x4005C404
GPIO_PORTE_AHB_IBE_R    EQU   0x4005C408
GPIO_PORTE_AHB_IEV_R    EQU   0x4005C40C
GPIO_PORTE_AHB_IM_R     EQU   0x4005C410
GPIO_PORTE_AHB_RIS_R    EQU   0x4005C414
GPIO_PORTE_AHB_MIS_R    EQU   0x4005C418
GPIO_PORTE_AHB_ICR_R    EQU   0x4005C41C
GPIO_PORTE_AHB_AFSEL_R  EQU   0x4005C420
GPIO_PORTE_AHB_DR2R_R   EQU   0x4005C500
GPIO_PORTE_AHB_DR4R_R   EQU   0x4005C504
GPIO_PORTE_AHB_DR8R_R   EQU   0x4005C508
GPIO_PORTE_AHB_ODR_R    EQU   0x4005C50C
GPIO_PORTE_AHB_PUR_R    EQU   0x4005C510
GPIO_PORTE_AHB_PDR_R    EQU   0x4005C514
GPIO_PORTE_AHB_SLR_R    EQU   0x4005C518
GPIO_PORTE_AHB_DEN_R    EQU   0x4005C51C
GPIO_PORTE_AHB_LOCK_R   EQU   0x4005C520
GPIO_PORTE_AHB_CR_R     EQU   0x4005C524
GPIO_PORTE_AHB_AMSEL_R  EQU   0x4005C528
GPIO_PORTE_AHB_PCTL_R   EQU   0x4005C52C
GPIO_PORTE_AHB_ADCCTL_R EQU   0x4005C530
GPIO_PORTE_AHB_DMACTL_R EQU   0x4005C534
GPIO_PORTE_AHB_SI_R     EQU   0x4005C538

;*************************************************************
;
; GPIO registers (PORTF AHB)
;
;*************************************************************
GPIO_PORTF_AHB_DATA_BITS_R  EQU   0x4005D000   
GPIO_PORTF_AHB_DATA_R   EQU   0x4005D3FC
GPIO_PORTF_AHB_DIR_R    EQU   0x4005D400
GPIO_PORTF_AHB_IS_R     EQU   0x4005D404
GPIO_PORTF_AHB_IBE_R    EQU   0x4005D408
GPIO_PORTF_AHB_IEV_R    EQU   0x4005D40C
GPIO_PORTF_AHB_IM_R     EQU   0x4005D410
GPIO_PORTF_AHB_RIS_R    EQU   0x4005D414
GPIO_PORTF_AHB_MIS_R    EQU   0x4005D418
GPIO_PORTF_AHB_ICR_R    EQU   0x4005D41C
GPIO_PORTF_AHB_AFSEL_R  EQU   0x4005D420
GPIO_PORTF_AHB_DR2R_R   EQU   0x4005D500
GPIO_PORTF_AHB_DR4R_R   EQU   0x4005D504
GPIO_PORTF_AHB_DR8R_R   EQU   0x4005D508
GPIO_PORTF_AHB_ODR_R    EQU   0x4005D50C
GPIO_PORTF_AHB_PUR_R    EQU   0x4005D510
GPIO_PORTF_AHB_PDR_R    EQU   0x4005D514
GPIO_PORTF_AHB_SLR_R    EQU   0x4005D518
GPIO_PORTF_AHB_DEN_R    EQU   0x4005D51C
GPIO_PORTF_AHB_LOCK_R   EQU   0x4005D520
GPIO_PORTF_AHB_CR_R     EQU   0x4005D524
GPIO_PORTF_AHB_AMSEL_R  EQU   0x4005D528
GPIO_PORTF_AHB_PCTL_R   EQU   0x4005D52C
GPIO_PORTF_AHB_ADCCTL_R EQU   0x4005D530
GPIO_PORTF_AHB_DMACTL_R EQU   0x4005D534
GPIO_PORTF_AHB_SI_R     EQU   0x4005D538

;*************************************************************
;
; EEPROM registers (EEPROM)
;
;*************************************************************
EEPROM_EESIZE_R         EQU   0x400AF000
EEPROM_EEBLOCK_R        EQU   0x400AF004
EEPROM_EEOFFSET_R       EQU   0x400AF008
EEPROM_EERDWR_R         EQU   0x400AF010
EEPROM_EERDWRINC_R      EQU   0x400AF014
EEPROM_EEDONE_R         EQU   0x400AF018
EEPROM_EESUPP_R         EQU   0x400AF01C
EEPROM_EEUNLOCK_R       EQU   0x400AF020
EEPROM_EEPROT_R         EQU   0x400AF030
EEPROM_EEPASS0_R        EQU   0x400AF034
EEPROM_EEPASS1_R        EQU   0x400AF038
EEPROM_EEPASS2_R        EQU   0x400AF03C
EEPROM_EEINT_R          EQU   0x400AF040
EEPROM_EEHIDE_R         EQU   0x400AF050
EEPROM_EEDBGME_R        EQU   0x400AF080
EEPROM_PP_R             EQU   0x400AFFC0

;*************************************************************
;
; System Exception Module registers (SYSEXC)
;
;*************************************************************
SYSEXC_RIS_R            EQU   0x400F9000
SYSEXC_IM_R             EQU   0x400F9004
SYSEXC_MIS_R            EQU   0x400F9008
SYSEXC_IC_R             EQU   0x400F900C

;*************************************************************
;
; Hibernation module registers (HIB)
;
;*************************************************************
HIB_RTCC_R              EQU   0x400FC000
HIB_RTCM0_R             EQU   0x400FC004
HIB_RTCLD_R             EQU   0x400FC00C
HIB_CTL_R               EQU   0x400FC010
HIB_IM_R                EQU   0x400FC014
HIB_RIS_R               EQU   0x400FC018
HIB_MIS_R               EQU   0x400FC01C
HIB_IC_R                EQU   0x400FC020
HIB_RTCT_R              EQU   0x400FC024
HIB_RTCSS_R             EQU   0x400FC028
HIB_DATA_R              EQU   0x400FC030

;*************************************************************
;
; FLASH registers (FLASH CTRL)
;
;*************************************************************
FLASH_FMA_R             EQU   0x400FD000
FLASH_FMD_R             EQU   0x400FD004
FLASH_FMC_R             EQU   0x400FD008
FLASH_FCRIS_R           EQU   0x400FD00C
FLASH_FCIM_R            EQU   0x400FD010
FLASH_FCMISC_R          EQU   0x400FD014
FLASH_FMC2_R            EQU   0x400FD020
FLASH_FWBVAL_R          EQU   0x400FD030
FLASH_FWBN_R            EQU   0x400FD100
FLASH_FSIZE_R           EQU   0x400FDFC0
FLASH_SSIZE_R           EQU   0x400FDFC4
FLASH_ROMSWMAP_R        EQU   0x400FDFCC
FLASH_RMCTL_R           EQU   0x400FE0F0
FLASH_BOOTCFG_R         EQU   0x400FE1D0
FLASH_USERREG0_R        EQU   0x400FE1E0
FLASH_USERREG1_R        EQU   0x400FE1E4
FLASH_USERREG2_R        EQU   0x400FE1E8
FLASH_USERREG3_R        EQU   0x400FE1EC
FLASH_FMPRE0_R          EQU   0x400FE200
FLASH_FMPRE1_R          EQU   0x400FE204
FLASH_FMPRE2_R          EQU   0x400FE208
FLASH_FMPRE3_R          EQU   0x400FE20C
FLASH_FMPPE0_R          EQU   0x400FE400
FLASH_FMPPE1_R          EQU   0x400FE404
FLASH_FMPPE2_R          EQU   0x400FE408
FLASH_FMPPE3_R          EQU   0x400FE40C

;*************************************************************
;
; System Control registers (SYSCTL)
;
;*************************************************************
SYSCTL_DID0_R           EQU   0x400FE000
SYSCTL_DID1_R           EQU   0x400FE004
SYSCTL_DC0_R            EQU   0x400FE008
SYSCTL_DC1_R            EQU   0x400FE010
SYSCTL_DC2_R            EQU   0x400FE014
SYSCTL_DC3_R            EQU   0x400FE018
SYSCTL_DC4_R            EQU   0x400FE01C
SYSCTL_DC5_R            EQU   0x400FE020
SYSCTL_DC6_R            EQU   0x400FE024
SYSCTL_DC7_R            EQU   0x400FE028
SYSCTL_DC8_R            EQU   0x400FE02C
SYSCTL_PBORCTL_R        EQU   0x400FE030
SYSCTL_SRCR0_R          EQU   0x400FE040
SYSCTL_SRCR1_R          EQU   0x400FE044
SYSCTL_SRCR2_R          EQU   0x400FE048
SYSCTL_RIS_R            EQU   0x400FE050
SYSCTL_IMC_R            EQU   0x400FE054
SYSCTL_MISC_R           EQU   0x400FE058
SYSCTL_RESC_R           EQU   0x400FE05C
SYSCTL_RCC_R            EQU   0x400FE060
SYSCTL_GPIOHBCTL_R      EQU   0x400FE06C
SYSCTL_RCC2_R           EQU   0x400FE070
SYSCTL_MOSCCTL_R        EQU   0x400FE07C
SYSCTL_RCGC0_R          EQU   0x400FE100
SYSCTL_RCGC1_R          EQU   0x400FE104
SYSCTL_RCGC2_R          EQU   0x400FE108
SYSCTL_SCGC0_R          EQU   0x400FE110
SYSCTL_SCGC1_R          EQU   0x400FE114
SYSCTL_SCGC2_R          EQU   0x400FE118
SYSCTL_DCGC0_R          EQU   0x400FE120
SYSCTL_DCGC1_R          EQU   0x400FE124
SYSCTL_DCGC2_R          EQU   0x400FE128
SYSCTL_DSLPCLKCFG_R     EQU   0x400FE144
SYSCTL_SYSPROP_R        EQU   0x400FE14C
SYSCTL_PIOSCCAL_R       EQU   0x400FE150
SYSCTL_PIOSCSTAT_R      EQU   0x400FE154
SYSCTL_PLLFREQ0_R       EQU   0x400FE160
SYSCTL_PLLFREQ1_R       EQU   0x400FE164
SYSCTL_PLLSTAT_R        EQU   0x400FE168
SYSCTL_DC9_R            EQU   0x400FE190
SYSCTL_NVMSTAT_R        EQU   0x400FE1A0
SYSCTL_PPWD_R           EQU   0x400FE300
SYSCTL_PPTIMER_R        EQU   0x400FE304
SYSCTL_PPGPIO_R         EQU   0x400FE308
SYSCTL_PPDMA_R          EQU   0x400FE30C
SYSCTL_PPHIB_R          EQU   0x400FE314
SYSCTL_PPUART_R         EQU   0x400FE318
SYSCTL_PPSSI_R          EQU   0x400FE31C
SYSCTL_PPI2C_R          EQU   0x400FE320
SYSCTL_PPUSB_R          EQU   0x400FE328
SYSCTL_PPCAN_R          EQU   0x400FE334
SYSCTL_PPADC_R          EQU   0x400FE338
SYSCTL_PPACMP_R         EQU   0x400FE33C
SYSCTL_PPPWM_R          EQU   0x400FE340
SYSCTL_PPQEI_R          EQU   0x400FE344
SYSCTL_PPEEPROM_R       EQU   0x400FE358
SYSCTL_PPWTIMER_R       EQU   0x400FE35C
SYSCTL_SRWD_R           EQU   0x400FE500
SYSCTL_SRTIMER_R        EQU   0x400FE504
SYSCTL_SRGPIO_R         EQU   0x400FE508
SYSCTL_SRDMA_R          EQU   0x400FE50C
SYSCTL_SRHIB_R          EQU   0x400FE514
SYSCTL_SRUART_R         EQU   0x400FE518
SYSCTL_SRSSI_R          EQU   0x400FE51C
SYSCTL_SRI2C_R          EQU   0x400FE520
SYSCTL_SRUSB_R          EQU   0x400FE528
SYSCTL_SRCAN_R          EQU   0x400FE534
SYSCTL_SRADC_R          EQU   0x400FE538
SYSCTL_SRACMP_R         EQU   0x400FE53C
SYSCTL_SREEPROM_R       EQU   0x400FE558
SYSCTL_SRWTIMER_R       EQU   0x400FE55C
SYSCTL_RCGCWD_R         EQU   0x400FE600
SYSCTL_RCGCTIMER_R      EQU   0x400FE604
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
SYSCTL_RCGCDMA_R        EQU   0x400FE60C
SYSCTL_RCGCHIB_R        EQU   0x400FE614
SYSCTL_RCGCUART_R       EQU   0x400FE618
SYSCTL_RCGCSSI_R        EQU   0x400FE61C
SYSCTL_RCGCI2C_R        EQU   0x400FE620
SYSCTL_RCGCUSB_R        EQU   0x400FE628
SYSCTL_RCGCCAN_R        EQU   0x400FE634
SYSCTL_RCGCADC_R        EQU   0x400FE638
SYSCTL_RCGCACMP_R       EQU   0x400FE63C
SYSCTL_RCGCEEPROM_R     EQU   0x400FE658
SYSCTL_RCGCWTIMER_R     EQU   0x400FE65C
SYSCTL_SCGCWD_R         EQU   0x400FE700
SYSCTL_SCGCTIMER_R      EQU   0x400FE704
SYSCTL_SCGCGPIO_R       EQU   0x400FE708
SYSCTL_SCGCDMA_R        EQU   0x400FE70C
SYSCTL_SCGCHIB_R        EQU   0x400FE714
SYSCTL_SCGCUART_R       EQU   0x400FE718
SYSCTL_SCGCSSI_R        EQU   0x400FE71C
SYSCTL_SCGCI2C_R        EQU   0x400FE720
SYSCTL_SCGCUSB_R        EQU   0x400FE728
SYSCTL_SCGCCAN_R        EQU   0x400FE734
SYSCTL_SCGCADC_R        EQU   0x400FE738
SYSCTL_SCGCACMP_R       EQU   0x400FE73C
SYSCTL_SCGCEEPROM_R     EQU   0x400FE758
SYSCTL_SCGCWTIMER_R     EQU   0x400FE75C
SYSCTL_DCGCWD_R         EQU   0x400FE800
SYSCTL_DCGCTIMER_R      EQU   0x400FE804
SYSCTL_DCGCGPIO_R       EQU   0x400FE808
SYSCTL_DCGCDMA_R        EQU   0x400FE80C
SYSCTL_DCGCHIB_R        EQU   0x400FE814
SYSCTL_DCGCUART_R       EQU   0x400FE818
SYSCTL_DCGCSSI_R        EQU   0x400FE81C
SYSCTL_DCGCI2C_R        EQU   0x400FE820
SYSCTL_DCGCUSB_R        EQU   0x400FE828
SYSCTL_DCGCCAN_R        EQU   0x400FE834
SYSCTL_DCGCADC_R        EQU   0x400FE838
SYSCTL_DCGCACMP_R       EQU   0x400FE83C
SYSCTL_DCGCEEPROM_R     EQU   0x400FE858
SYSCTL_DCGCWTIMER_R     EQU   0x400FE85C
SYSCTL_PCWD_R           EQU   0x400FE900
SYSCTL_PCTIMER_R        EQU   0x400FE904
SYSCTL_PCGPIO_R         EQU   0x400FE908
SYSCTL_PCDMA_R          EQU   0x400FE90C
SYSCTL_PCHIB_R          EQU   0x400FE914
SYSCTL_PCUART_R         EQU   0x400FE918
SYSCTL_PCSSI_R          EQU   0x400FE91C
SYSCTL_PCI2C_R          EQU   0x400FE920
SYSCTL_PCUSB_R          EQU   0x400FE928
SYSCTL_PCCAN_R          EQU   0x400FE934
SYSCTL_PCADC_R          EQU   0x400FE938
SYSCTL_PCACMP_R         EQU   0x400FE93C
SYSCTL_PCEEPROM_R       EQU   0x400FE958
SYSCTL_PCWTIMER_R       EQU   0x400FE95C
SYSCTL_PRWD_R           EQU   0x400FEA00
SYSCTL_PRTIMER_R        EQU   0x400FEA04
SYSCTL_PRGPIO_R         EQU   0x400FEA08
SYSCTL_PRDMA_R          EQU   0x400FEA0C
SYSCTL_PRHIB_R          EQU   0x400FEA14
SYSCTL_PRUART_R         EQU   0x400FEA18
SYSCTL_PRSSI_R          EQU   0x400FEA1C
SYSCTL_PRI2C_R          EQU   0x400FEA20
SYSCTL_PRUSB_R          EQU   0x400FEA28
SYSCTL_PRCAN_R          EQU   0x400FEA34
SYSCTL_PRADC_R          EQU   0x400FEA38
SYSCTL_PRACMP_R         EQU   0x400FEA3C
SYSCTL_PREEPROM_R       EQU   0x400FEA58
SYSCTL_PRWTIMER_R       EQU   0x400FEA5C

;*************************************************************
;
; Micro Direct Memory Access registers (UDMA)
;
;*************************************************************
UDMA_STAT_R             EQU   0x400FF000
UDMA_CFG_R              EQU   0x400FF004
UDMA_CTLBASE_R          EQU   0x400FF008
UDMA_ALTBASE_R          EQU   0x400FF00C
UDMA_WAITSTAT_R         EQU   0x400FF010
UDMA_SWREQ_R            EQU   0x400FF014
UDMA_USEBURSTSET_R      EQU   0x400FF018
UDMA_USEBURSTCLR_R      EQU   0x400FF01C
UDMA_REQMASKSET_R       EQU   0x400FF020
UDMA_REQMASKCLR_R       EQU   0x400FF024
UDMA_ENASET_R           EQU   0x400FF028
UDMA_ENACLR_R           EQU   0x400FF02C
UDMA_ALTSET_R           EQU   0x400FF030
UDMA_ALTCLR_R           EQU   0x400FF034
UDMA_PRIOSET_R          EQU   0x400FF038
UDMA_PRIOCLR_R          EQU   0x400FF03C
UDMA_ERRCLR_R           EQU   0x400FF04C
UDMA_CHASGN_R           EQU   0x400FF500
UDMA_CHIS_R             EQU   0x400FF504
UDMA_CHMAP0_R           EQU   0x400FF510
UDMA_CHMAP1_R           EQU   0x400FF514
UDMA_CHMAP2_R           EQU   0x400FF518
UDMA_CHMAP3_R           EQU   0x400FF51C

;*************************************************************
;
; Micro Direct Memory Access (uDMA) offsets (UDMA)
;
;*************************************************************
UDMA_SRCENDP    EQU       0x00000000  ; DMA Channel Source Address End
                                            ; Pointer
UDMA_DSTENDP    EQU       0x00000004  ; DMA Channel Destination Address
                                            ; End Pointer
UDMA_CHCTL      EQU       0x00000008  ; DMA Channel Control Word

;*************************************************************
;
; NVIC registers (NVIC)
;
;*************************************************************
NVIC_INT_TYPE_R         EQU   0xE000E004
NVIC_ACTLR_R            EQU   0xE000E008
NVIC_ST_CTRL_R          EQU   0xE000E010
NVIC_ST_RELOAD_R        EQU   0xE000E014
NVIC_ST_CURRENT_R       EQU   0xE000E018
NVIC_ST_CAL_R           EQU   0xE000E01C
NVIC_EN0_R              EQU   0xE000E100
NVIC_EN1_R              EQU   0xE000E104
NVIC_EN2_R              EQU   0xE000E108
NVIC_EN3_R              EQU   0xE000E10C
NVIC_EN4_R              EQU   0xE000E110
NVIC_DIS0_R             EQU   0xE000E180
NVIC_DIS1_R             EQU   0xE000E184
NVIC_DIS2_R             EQU   0xE000E188
NVIC_DIS3_R             EQU   0xE000E18C
NVIC_DIS4_R             EQU   0xE000E190
NVIC_PEND0_R            EQU   0xE000E200
NVIC_PEND1_R            EQU   0xE000E204
NVIC_PEND2_R            EQU   0xE000E208
NVIC_PEND3_R            EQU   0xE000E20C
NVIC_PEND4_R            EQU   0xE000E210
NVIC_UNPEND0_R          EQU   0xE000E280
NVIC_UNPEND1_R          EQU   0xE000E284
NVIC_UNPEND2_R          EQU   0xE000E288
NVIC_UNPEND3_R          EQU   0xE000E28C
NVIC_UNPEND4_R          EQU   0xE000E290
NVIC_ACTIVE0_R          EQU   0xE000E300
NVIC_ACTIVE1_R          EQU   0xE000E304
NVIC_ACTIVE2_R          EQU   0xE000E308
NVIC_ACTIVE3_R          EQU   0xE000E30C
NVIC_ACTIVE4_R          EQU   0xE000E310
NVIC_PRI0_R             EQU   0xE000E400
NVIC_PRI1_R             EQU   0xE000E404
NVIC_PRI2_R             EQU   0xE000E408
NVIC_PRI3_R             EQU   0xE000E40C
NVIC_PRI4_R             EQU   0xE000E410
NVIC_PRI5_R             EQU   0xE000E414
NVIC_PRI6_R             EQU   0xE000E418
NVIC_PRI7_R             EQU   0xE000E41C
NVIC_PRI8_R             EQU   0xE000E420
NVIC_PRI9_R             EQU   0xE000E424
NVIC_PRI10_R            EQU   0xE000E428
NVIC_PRI11_R            EQU   0xE000E42C
NVIC_PRI12_R            EQU   0xE000E430
NVIC_PRI13_R            EQU   0xE000E434
NVIC_PRI14_R            EQU   0xE000E438
NVIC_PRI15_R            EQU   0xE000E43C
NVIC_PRI16_R            EQU   0xE000E440
NVIC_PRI17_R            EQU   0xE000E444
NVIC_PRI18_R            EQU   0xE000E448
NVIC_PRI19_R            EQU   0xE000E44C
NVIC_PRI20_R            EQU   0xE000E450
NVIC_PRI21_R            EQU   0xE000E454
NVIC_PRI22_R            EQU   0xE000E458
NVIC_PRI23_R            EQU   0xE000E45C
NVIC_PRI24_R            EQU   0xE000E460
NVIC_PRI25_R            EQU   0xE000E464
NVIC_PRI26_R            EQU   0xE000E468
NVIC_PRI27_R            EQU   0xE000E46C
NVIC_PRI28_R            EQU   0xE000E470
NVIC_PRI29_R            EQU   0xE000E474
NVIC_PRI30_R            EQU   0xE000E478
NVIC_PRI31_R            EQU   0xE000E47C
NVIC_PRI32_R            EQU   0xE000E480
NVIC_PRI33_R            EQU   0xE000E484
NVIC_PRI34_R            EQU   0xE000E488
NVIC_CPUID_R            EQU   0xE000ED00
NVIC_INT_CTRL_R         EQU   0xE000ED04
NVIC_VTABLE_R           EQU   0xE000ED08
NVIC_APINT_R            EQU   0xE000ED0C
NVIC_SYS_CTRL_R         EQU   0xE000ED10
NVIC_CFG_CTRL_R         EQU   0xE000ED14
NVIC_SYS_PRI1_R         EQU   0xE000ED18
NVIC_SYS_PRI2_R         EQU   0xE000ED1C
NVIC_SYS_PRI3_R         EQU   0xE000ED20
NVIC_SYS_HND_CTRL_R     EQU   0xE000ED24
NVIC_FAULT_STAT_R       EQU   0xE000ED28
NVIC_HFAULT_STAT_R      EQU   0xE000ED2C
NVIC_DEBUG_STAT_R       EQU   0xE000ED30
NVIC_MM_ADDR_R          EQU   0xE000ED34
NVIC_FAULT_ADDR_R       EQU   0xE000ED38
NVIC_CPAC_R             EQU   0xE000ED88
NVIC_MPU_TYPE_R         EQU   0xE000ED90
NVIC_MPU_CTRL_R         EQU   0xE000ED94
NVIC_MPU_NUMBER_R       EQU   0xE000ED98
NVIC_MPU_BASE_R         EQU   0xE000ED9C
NVIC_MPU_ATTR_R         EQU   0xE000EDA0
NVIC_MPU_BASE1_R        EQU   0xE000EDA4
NVIC_MPU_ATTR1_R        EQU   0xE000EDA8
NVIC_MPU_BASE2_R        EQU   0xE000EDAC
NVIC_MPU_ATTR2_R        EQU   0xE000EDB0
NVIC_MPU_BASE3_R        EQU   0xE000EDB4
NVIC_MPU_ATTR3_R        EQU   0xE000EDB8
NVIC_DBG_CTRL_R         EQU   0xE000EDF0
NVIC_DBG_XFER_R         EQU   0xE000EDF4
NVIC_DBG_DATA_R         EQU   0xE000EDF8
NVIC_DBG_INT_R          EQU   0xE000EDFC
NVIC_SW_TRIG_R          EQU   0xE000EF00
NVIC_FPCC_R             EQU   0xE000EF34
NVIC_FPCA_R             EQU   0xE000EF38
NVIC_FPDSC_R            EQU   0xE000EF3C

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_LOAD register.
;
;*************************************************************
WDT_LOAD_M             EQU  0xFFFFFFFF  ; Watchdog Load Value
WDT_LOAD_S             EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_VALUE register.
;
;*************************************************************
WDT_VALUE_M            EQU  0xFFFFFFFF  ; Watchdog Value
WDT_VALUE_S            EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_CTL register.
;
;*************************************************************
WDT_CTL_WRC            EQU  0x80000000  ; Write Complete
WDT_CTL_INTTYPE        EQU  0x00000004  ; Watchdog Interrupt Type
WDT_CTL_RESEN          EQU  0x00000002  ; Watchdog Reset Enable
WDT_CTL_INTEN          EQU  0x00000001  ; Watchdog Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_ICR register.
;
;*************************************************************
WDT_ICR_M              EQU  0xFFFFFFFF  ; Watchdog Interrupt Clear
WDT_ICR_S              EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_RIS register.
;
;*************************************************************
WDT_RIS_WDTRIS         EQU  0x00000001  ; Watchdog Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_MIS register.
;
;*************************************************************
WDT_MIS_WDTMIS         EQU  0x00000001  ; Watchdog Masked Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_TEST register.
;
;*************************************************************
WDT_TEST_STALL         EQU  0x00000100  ; Watchdog Stall Enable

;*************************************************************
;
; The following are defines for the bit fields in the WDT_O_LOCK register.
;
;*************************************************************
WDT_LOCK_M             EQU  0xFFFFFFFF  ; Watchdog Lock
WDT_LOCK_UNLOCKED      EQU  0x00000000  ; Unlocked
WDT_LOCK_LOCKED        EQU  0x00000001  ; Locked

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_IM register.
;
;*************************************************************
GPIO_IM_GPIO_M         EQU  0x000000FF  ; GPIO Interrupt Mask Enable
GPIO_IM_GPIO_S         EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_RIS register.
;
;*************************************************************
GPIO_RIS_GPIO_M        EQU  0x000000FF  ; GPIO Interrupt Raw Status
GPIO_RIS_GPIO_S        EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_MIS register.
;
;*************************************************************
GPIO_MIS_GPIO_M        EQU  0x000000FF  ; GPIO Masked Interrupt Status
GPIO_MIS_GPIO_S        EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_ICR register.
;
;*************************************************************
GPIO_ICR_GPIO_M        EQU  0x000000FF  ; GPIO Interrupt Clear
GPIO_ICR_GPIO_S        EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_LOCK register.
;
;*************************************************************
GPIO_LOCK_M            EQU  0xFFFFFFFF  ; GPIO Lock
GPIO_LOCK_UNLOCKED     EQU  0x00000000  ; The GPIOCR register is unlocked
                                            ; and may be modified
GPIO_LOCK_LOCKED       EQU  0x00000001  ; The GPIOCR register is locked
                                            ; and may not be modified
GPIO_LOCK_KEY          EQU  0x4C4F434B  ; Unlocks the GPIO_CR register

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_O_SI register.
;
;*************************************************************
GPIO_SI_SUM            EQU  0x00000001  ; Summary Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port A.
;
;*************************************************************
GPIO_PCTL_PA7_M        EQU  0xF0000000  ; PA7 mask
GPIO_PCTL_PA7_I2C1SDA  EQU  0x30000000  ; I2C1SDA on PA7
GPIO_PCTL_PA6_M        EQU  0x0F000000  ; PA6 mask
GPIO_PCTL_PA6_I2C1SCL  EQU  0x03000000  ; I2C1SCL on PA6
GPIO_PCTL_PA5_M        EQU  0x00F00000  ; PA5 mask
GPIO_PCTL_PA5_SSI0TX   EQU  0x00200000  ; SSI0TX on PA5
GPIO_PCTL_PA4_M        EQU  0x000F0000  ; PA4 mask
GPIO_PCTL_PA4_SSI0RX   EQU  0x00020000  ; SSI0RX on PA4
GPIO_PCTL_PA3_M        EQU  0x0000F000  ; PA3 mask
GPIO_PCTL_PA3_SSI0FSS  EQU  0x00002000  ; SSI0FSS on PA3
GPIO_PCTL_PA2_M        EQU  0x00000F00  ; PA2 mask
GPIO_PCTL_PA2_SSI0CLK  EQU  0x00000200  ; SSI0CLK on PA2
GPIO_PCTL_PA1_M        EQU  0x000000F0  ; PA1 mask
GPIO_PCTL_PA1_U0TX     EQU  0x00000010  ; U0TX on PA1
GPIO_PCTL_PA0_M        EQU  0x0000000F  ; PA0 mask
GPIO_PCTL_PA0_U0RX     EQU  0x00000001  ; U0RX on PA0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port B.
;
;*************************************************************
GPIO_PCTL_PB7_M        EQU  0xF0000000  ; PB7 mask
GPIO_PCTL_PB7_SSI2TX   EQU  0x20000000  ; SSI2TX on PB7
GPIO_PCTL_PB7_T0CCP1   EQU  0x70000000  ; T0CCP1 on PB7
GPIO_PCTL_PB6_M        EQU  0x0F000000  ; PB6 mask
GPIO_PCTL_PB6_SSI2RX   EQU  0x02000000  ; SSI2RX on PB6
GPIO_PCTL_PB6_T0CCP0   EQU  0x07000000  ; T0CCP0 on PB6
GPIO_PCTL_PB5_M        EQU  0x00F00000  ; PB5 mask
GPIO_PCTL_PB5_SSI2FSS  EQU  0x00200000  ; SSI2FSS on PB5
GPIO_PCTL_PB5_T1CCP1   EQU  0x00700000  ; T1CCP1 on PB5
GPIO_PCTL_PB5_CAN0TX   EQU  0x00800000  ; CAN0TX on PB5
GPIO_PCTL_PB4_M        EQU  0x000F0000  ; PB4 mask
GPIO_PCTL_PB4_SSI2CLK  EQU  0x00020000  ; SSI2CLK on PB4
GPIO_PCTL_PB4_T1CCP0   EQU  0x00070000  ; T1CCP0 on PB4
GPIO_PCTL_PB4_CAN0RX   EQU  0x00080000  ; CAN0RX on PB4
GPIO_PCTL_PB3_M        EQU  0x0000F000  ; PB3 mask
GPIO_PCTL_PB3_I2C0SDA  EQU  0x00003000  ; I2C0SDA on PB3
GPIO_PCTL_PB3_T3CCP1   EQU  0x00007000  ; T3CCP1 on PB3
GPIO_PCTL_PB2_M        EQU  0x00000F00  ; PB2 mask
GPIO_PCTL_PB2_I2C0SCL  EQU  0x00000300  ; I2C0SCL on PB2
GPIO_PCTL_PB2_T3CCP0   EQU  0x00000700  ; T3CCP0 on PB2
GPIO_PCTL_PB1_M        EQU  0x000000F0  ; PB1 mask
GPIO_PCTL_PB1_U1TX     EQU  0x00000010  ; U1TX on PB1
GPIO_PCTL_PB1_T2CCP1   EQU  0x00000070  ; T2CCP1 on PB1
GPIO_PCTL_PB0_M        EQU  0x0000000F  ; PB0 mask
GPIO_PCTL_PB0_U1RX     EQU  0x00000001  ; U1RX on PB0
GPIO_PCTL_PB0_T2CCP0   EQU  0x00000007  ; T2CCP0 on PB0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port C.
;
;*************************************************************
GPIO_PCTL_PC7_M        EQU  0xF0000000  ; PC7 mask
GPIO_PCTL_PC7_U3TX     EQU  0x10000000  ; U3TX on PC7
GPIO_PCTL_PC7_WT1CCP1  EQU  0x70000000  ; WT1CCP1 on PC7
GPIO_PCTL_PC6_M        EQU  0x0F000000  ; PC6 mask
GPIO_PCTL_PC6_U3RX     EQU  0x01000000  ; U3RX on PC6
GPIO_PCTL_PC6_WT1CCP0  EQU  0x07000000  ; WT1CCP0 on PC6
GPIO_PCTL_PC5_M        EQU  0x00F00000  ; PC5 mask
GPIO_PCTL_PC5_U4TX     EQU  0x00100000  ; U4TX on PC5
GPIO_PCTL_PC5_U1TX     EQU  0x00200000  ; U1TX on PC5
GPIO_PCTL_PC5_WT0CCP1  EQU  0x00700000  ; WT0CCP1 on PC5
GPIO_PCTL_PC5_U1CTS    EQU  0x00800000  ; U1CTS on PC5
GPIO_PCTL_PC4_M        EQU  0x000F0000  ; PC4 mask
GPIO_PCTL_PC4_U4RX     EQU  0x00010000  ; U4RX on PC4
GPIO_PCTL_PC4_U1RX     EQU  0x00020000  ; U1RX on PC4
GPIO_PCTL_PC4_WT0CCP0  EQU  0x00070000  ; WT0CCP0 on PC4
GPIO_PCTL_PC4_U1RTS    EQU  0x00080000  ; U1RTS on PC4
GPIO_PCTL_PC3_M        EQU  0x0000F000  ; PC3 mask
GPIO_PCTL_PC3_TDO      EQU  0x00001000  ; TDO on PC3
GPIO_PCTL_PC3_T5CCP1   EQU  0x00007000  ; T5CCP1 on PC3
GPIO_PCTL_PC2_M        EQU  0x00000F00  ; PC2 mask
GPIO_PCTL_PC2_TDI      EQU  0x00000100  ; TDI on PC2
GPIO_PCTL_PC2_T5CCP0   EQU  0x00000700  ; T5CCP0 on PC2
GPIO_PCTL_PC1_M        EQU  0x000000F0  ; PC1 mask
GPIO_PCTL_PC1_TMS      EQU  0x00000010  ; TMS on PC1
GPIO_PCTL_PC1_T4CCP1   EQU  0x00000070  ; T4CCP1 on PC1
GPIO_PCTL_PC0_M        EQU  0x0000000F  ; PC0 mask
GPIO_PCTL_PC0_TCK      EQU  0x00000001  ; TCK on PC0
GPIO_PCTL_PC0_T4CCP0   EQU  0x00000007  ; T4CCP0 on PC0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port D.
;
;*************************************************************
GPIO_PCTL_PD7_M        EQU  0xF0000000  ; PD7 mask
GPIO_PCTL_PD7_U2TX     EQU  0x10000000  ; U2TX on PD7
GPIO_PCTL_PD7_WT5CCP1  EQU  0x70000000  ; WT5CCP1 on PD7
GPIO_PCTL_PD7_NMI      EQU  0x80000000  ; NMI on PD7
GPIO_PCTL_PD6_M        EQU  0x0F000000  ; PD6 mask
GPIO_PCTL_PD6_U2RX     EQU  0x01000000  ; U2RX on PD6
GPIO_PCTL_PD6_WT5CCP0  EQU  0x07000000  ; WT5CCP0 on PD6
GPIO_PCTL_PD5_M        EQU  0x00F00000  ; PD5 mask
GPIO_PCTL_PD5_U6TX     EQU  0x00100000  ; U6TX on PD5
GPIO_PCTL_PD5_WT4CCP1  EQU  0x00700000  ; WT4CCP1 on PD5
GPIO_PCTL_PD4_M        EQU  0x000F0000  ; PD4 mask
GPIO_PCTL_PD4_U6RX     EQU  0x00010000  ; U6RX on PD4
GPIO_PCTL_PD4_WT4CCP0  EQU  0x00070000  ; WT4CCP0 on PD4
GPIO_PCTL_PD3_M        EQU  0x0000F000  ; PD3 mask
GPIO_PCTL_PD3_SSI3TX   EQU  0x00001000  ; SSI3TX on PD3
GPIO_PCTL_PD3_SSI1TX   EQU  0x00002000  ; SSI1TX on PD3
GPIO_PCTL_PD3_WT3CCP1  EQU  0x00007000  ; WT3CCP1 on PD3
GPIO_PCTL_PD2_M        EQU  0x00000F00  ; PD2 mask
GPIO_PCTL_PD2_SSI3RX   EQU  0x00000100  ; SSI3RX on PD2
GPIO_PCTL_PD2_SSI1RX   EQU  0x00000200  ; SSI1RX on PD2
GPIO_PCTL_PD2_WT3CCP0  EQU  0x00000700  ; WT3CCP0 on PD2
GPIO_PCTL_PD1_M        EQU  0x000000F0  ; PD1 mask
GPIO_PCTL_PD1_SSI3FSS  EQU  0x00000010  ; SSI3FSS on PD1
GPIO_PCTL_PD1_SSI1FSS  EQU  0x00000020  ; SSI1FSS on PD1
GPIO_PCTL_PD1_I2C3SDA  EQU  0x00000030  ; I2C3SDA on PD1
GPIO_PCTL_PD1_WT2CCP1  EQU  0x00000070  ; WT2CCP1 on PD1
GPIO_PCTL_PD0_M        EQU  0x0000000F  ; PD0 mask
GPIO_PCTL_PD0_SSI3CLK  EQU  0x00000001  ; SSI3CLK on PD0
GPIO_PCTL_PD0_SSI1CLK  EQU  0x00000002  ; SSI1CLK on PD0
GPIO_PCTL_PD0_I2C3SCL  EQU  0x00000003  ; I2C3SCL on PD0
GPIO_PCTL_PD0_WT2CCP0  EQU  0x00000007  ; WT2CCP0 on PD0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port E.
;
;*************************************************************
GPIO_PCTL_PE5_M        EQU  0x00F00000  ; PE5 mask
GPIO_PCTL_PE5_U5TX     EQU  0x00100000  ; U5TX on PE5
GPIO_PCTL_PE5_I2C2SDA  EQU  0x00300000  ; I2C2SDA on PE5
GPIO_PCTL_PE5_CAN0TX   EQU  0x00800000  ; CAN0TX on PE5
GPIO_PCTL_PE4_M        EQU  0x000F0000  ; PE4 mask
GPIO_PCTL_PE4_U5RX     EQU  0x00010000  ; U5RX on PE4
GPIO_PCTL_PE4_I2C2SCL  EQU  0x00030000  ; I2C2SCL on PE4
GPIO_PCTL_PE4_CAN0RX   EQU  0x00080000  ; CAN0RX on PE4
GPIO_PCTL_PE3_M        EQU  0x0000F000  ; PE3 mask
GPIO_PCTL_PE2_M        EQU  0x00000F00  ; PE2 mask
GPIO_PCTL_PE1_M        EQU  0x000000F0  ; PE1 mask
GPIO_PCTL_PE1_U7TX     EQU  0x00000010  ; U7TX on PE1
GPIO_PCTL_PE0_M        EQU  0x0000000F  ; PE0 mask
GPIO_PCTL_PE0_U7RX     EQU  0x00000001  ; U7RX on PE0

;*************************************************************
;
; The following are defines for the bit fields in the GPIO_PCTL register for
; port F.
;
;*************************************************************
GPIO_PCTL_PF4_M        EQU  0x000F0000  ; PF4 mask
GPIO_PCTL_PF4_T2CCP0   EQU  0x00070000  ; T2CCP0 on PF4
GPIO_PCTL_PF3_M        EQU  0x0000F000  ; PF3 mask
GPIO_PCTL_PF3_SSI1FSS  EQU  0x00002000  ; SSI1FSS on PF3
GPIO_PCTL_PF3_CAN0TX   EQU  0x00003000  ; CAN0TX on PF3
GPIO_PCTL_PF3_T1CCP1   EQU  0x00007000  ; T1CCP1 on PF3
GPIO_PCTL_PF3_TRCLK    EQU  0x0000E000  ; TRCLK on PF3
GPIO_PCTL_PF2_M        EQU  0x00000F00  ; PF2 mask
GPIO_PCTL_PF2_SSI1CLK  EQU  0x00000200  ; SSI1CLK on PF2
GPIO_PCTL_PF2_T1CCP0   EQU  0x00000700  ; T1CCP0 on PF2
GPIO_PCTL_PF2_TRD0     EQU  0x00000E00  ; TRD0 on PF2
GPIO_PCTL_PF1_M        EQU  0x000000F0  ; PF1 mask
GPIO_PCTL_PF1_U1CTS    EQU  0x00000010  ; U1CTS on PF1
GPIO_PCTL_PF1_SSI1TX   EQU  0x00000020  ; SSI1TX on PF1
GPIO_PCTL_PF1_T0CCP1   EQU  0x00000070  ; T0CCP1 on PF1
GPIO_PCTL_PF1_C1O      EQU  0x00000090  ; C1O on PF1
GPIO_PCTL_PF1_TRD1     EQU  0x000000E0  ; TRD1 on PF1
GPIO_PCTL_PF0_M        EQU  0x0000000F  ; PF0 mask
GPIO_PCTL_PF0_U1RTS    EQU  0x00000001  ; U1RTS on PF0
GPIO_PCTL_PF0_SSI1RX   EQU  0x00000002  ; SSI1RX on PF0
GPIO_PCTL_PF0_CAN0RX   EQU  0x00000003  ; CAN0RX on PF0
GPIO_PCTL_PF0_T0CCP0   EQU  0x00000007  ; T0CCP0 on PF0
GPIO_PCTL_PF0_NMI      EQU  0x00000008  ; NMI on PF0
GPIO_PCTL_PF0_C0O      EQU  0x00000009  ; C0O on PF0
GPIO_PCTL_PF0_TRD2     EQU  0x0000000E  ; TRD2 on PF0

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_CR0 register.
;
;*************************************************************
SSI_CR0_SCR_M          EQU  0x0000FF00  ; SSI Serial Clock Rate
SSI_CR0_SPH            EQU  0x00000080  ; SSI Serial Clock Phase
SSI_CR0_SPO            EQU  0x00000040  ; SSI Serial Clock Polarity
SSI_CR0_FRF_M          EQU  0x00000030  ; SSI Frame Format Select
SSI_CR0_FRF_MOTO       EQU  0x00000000  ; Freescale SPI Frame Format
SSI_CR0_FRF_TI         EQU  0x00000010  ; Texas Instruments Synchronous
                                            ; Serial Frame Format
SSI_CR0_FRF_NMW        EQU  0x00000020  ; MICROWIRE Frame Format
SSI_CR0_DSS_M          EQU  0x0000000F  ; SSI Data Size Select
SSI_CR0_DSS_4          EQU  0x00000003  ; 4-bit data
SSI_CR0_DSS_5          EQU  0x00000004  ; 5-bit data
SSI_CR0_DSS_6          EQU  0x00000005  ; 6-bit data
SSI_CR0_DSS_7          EQU  0x00000006  ; 7-bit data
SSI_CR0_DSS_8          EQU  0x00000007  ; 8-bit data
SSI_CR0_DSS_9          EQU  0x00000008  ; 9-bit data
SSI_CR0_DSS_10         EQU  0x00000009  ; 10-bit data
SSI_CR0_DSS_11         EQU  0x0000000A  ; 11-bit data
SSI_CR0_DSS_12         EQU  0x0000000B  ; 12-bit data
SSI_CR0_DSS_13         EQU  0x0000000C  ; 13-bit data
SSI_CR0_DSS_14         EQU  0x0000000D  ; 14-bit data
SSI_CR0_DSS_15         EQU  0x0000000E  ; 15-bit data
SSI_CR0_DSS_16         EQU  0x0000000F  ; 16-bit data
SSI_CR0_SCR_S          EQU  8

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_CR1 register.
;
;*************************************************************
SSI_CR1_EOT            EQU  0x00000010  ; End of Transmission
SSI_CR1_SOD            EQU  0x00000008  ; SSI Slave Mode Output Disable
SSI_CR1_MS             EQU  0x00000004  ; SSI Master/Slave Select
SSI_CR1_SSE            EQU  0x00000002  ; SSI Synchronous Serial Port
                                            ; Enable
SSI_CR1_LBM            EQU  0x00000001  ; SSI Loopback Mode

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_DR register.
;
;*************************************************************
SSI_DR_DATA_M          EQU  0x0000FFFF  ; SSI Receive/Transmit Data
SSI_DR_DATA_S          EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_SR register.
;
;*************************************************************
SSI_SR_BSY             EQU  0x00000010  ; SSI Busy Bit
SSI_SR_RFF             EQU  0x00000008  ; SSI Receive FIFO Full
SSI_SR_RNE             EQU  0x00000004  ; SSI Receive FIFO Not Empty
SSI_SR_TNF             EQU  0x00000002  ; SSI Transmit FIFO Not Full
SSI_SR_TFE             EQU  0x00000001  ; SSI Transmit FIFO Empty

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_CPSR register.
;
;*************************************************************
SSI_CPSR_CPSDVSR_M     EQU  0x000000FF  ; SSI Clock Prescale Divisor
SSI_CPSR_CPSDVSR_S     EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_IM register.
;
;*************************************************************
SSI_IM_TXIM            EQU  0x00000008  ; SSI Transmit FIFO Interrupt Mask
SSI_IM_RXIM            EQU  0x00000004  ; SSI Receive FIFO Interrupt Mask
SSI_IM_RTIM            EQU  0x00000002  ; SSI Receive Time-Out Interrupt
                                            ; Mask
SSI_IM_RORIM           EQU  0x00000001  ; SSI Receive Overrun Interrupt
                                            ; Mask

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_RIS register.
;
;*************************************************************
SSI_RIS_TXRIS          EQU  0x00000008  ; SSI Transmit FIFO Raw Interrupt
                                            ; Status
SSI_RIS_RXRIS          EQU  0x00000004  ; SSI Receive FIFO Raw Interrupt
                                            ; Status
SSI_RIS_RTRIS          EQU  0x00000002  ; SSI Receive Time-Out Raw
                                            ; Interrupt Status
SSI_RIS_RORRIS         EQU  0x00000001  ; SSI Receive Overrun Raw
                                            ; Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_MIS register.
;
;*************************************************************
SSI_MIS_TXMIS          EQU  0x00000008  ; SSI Transmit FIFO Masked
                                            ; Interrupt Status
SSI_MIS_RXMIS          EQU  0x00000004  ; SSI Receive FIFO Masked
                                            ; Interrupt Status
SSI_MIS_RTMIS          EQU  0x00000002  ; SSI Receive Time-Out Masked
                                            ; Interrupt Status
SSI_MIS_RORMIS         EQU  0x00000001  ; SSI Receive Overrun Masked
                                            ; Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_ICR register.
;
;*************************************************************
SSI_ICR_RTIC           EQU  0x00000002  ; SSI Receive Time-Out Interrupt
                                            ; Clear
SSI_ICR_RORIC          EQU  0x00000001  ; SSI Receive Overrun Interrupt
                                            ; Clear

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_DMACTL register.
;
;*************************************************************
SSI_DMACTL_TXDMAE      EQU  0x00000002  ; Transmit DMA Enable
SSI_DMACTL_RXDMAE      EQU  0x00000001  ; Receive DMA Enable

;*************************************************************
;
; The following are defines for the bit fields in the SSI_O_CC register.
;
;*************************************************************
SSI_CC_CS_M            EQU  0x0000000F  ; SSI Baud Clock Source
SSI_CC_CS_SYSPLL       EQU  0x00000000  ; Either the system clock (if the
                                            ; PLL bypass is in effect) or the
                                            ; PLL output (default)
SSI_CC_CS_PIOSC        EQU  0x00000005  ; PIOSC

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_DR register.
;
;*************************************************************
UART_DR_OE             EQU  0x00000800  ; UART Overrun Error
UART_DR_BE             EQU  0x00000400  ; UART Break Error
UART_DR_PE             EQU  0x00000200  ; UART Parity Error
UART_DR_FE             EQU  0x00000100  ; UART Framing Error
UART_DR_DATA_M         EQU  0x000000FF  ; Data Transmitted or Received
UART_DR_DATA_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_RSR register.
;
;*************************************************************
UART_RSR_OE            EQU  0x00000008  ; UART Overrun Error
UART_RSR_BE            EQU  0x00000004  ; UART Break Error
UART_RSR_PE            EQU  0x00000002  ; UART Parity Error
UART_RSR_FE            EQU  0x00000001  ; UART Framing Error

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_ECR register.
;
;*************************************************************
UART_ECR_DATA_M        EQU  0x000000FF  ; Error Clear
UART_ECR_DATA_S        EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_FR register.
;
;*************************************************************
UART_FR_TXFE           EQU  0x00000080  ; UART Transmit FIFO Empty
UART_FR_RXFF           EQU  0x00000040  ; UART Receive FIFO Full
UART_FR_TXFF           EQU  0x00000020  ; UART Transmit FIFO Full
UART_FR_RXFE           EQU  0x00000010  ; UART Receive FIFO Empty
UART_FR_BUSY           EQU  0x00000008  ; UART Busy
UART_FR_CTS            EQU  0x00000001  ; Clear To Send

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_ILPR register.
;
;*************************************************************
UART_ILPR_ILPDVSR_M    EQU  0x000000FF  ; IrDA Low-Power Divisor
UART_ILPR_ILPDVSR_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_IBRD register.
;
;*************************************************************
UART_IBRD_DIVINT_M     EQU  0x0000FFFF  ; Integer Baud-Rate Divisor
UART_IBRD_DIVINT_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_FBRD register.
;
;*************************************************************
UART_FBRD_DIVFRAC_M    EQU  0x0000003F  ; Fractional Baud-Rate Divisor
UART_FBRD_DIVFRAC_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_LCRH register.
;
;*************************************************************
UART_LCRH_SPS          EQU  0x00000080  ; UART Stick Parity Select
UART_LCRH_WLEN_M       EQU  0x00000060  ; UART Word Length
UART_LCRH_WLEN_5       EQU  0x00000000  ; 5 bits (default)
UART_LCRH_WLEN_6       EQU  0x00000020  ; 6 bits
UART_LCRH_WLEN_7       EQU  0x00000040  ; 7 bits
UART_LCRH_WLEN_8       EQU  0x00000060  ; 8 bits
UART_LCRH_FEN          EQU  0x00000010  ; UART Enable FIFOs
UART_LCRH_STP2         EQU  0x00000008  ; UART Two Stop Bits Select
UART_LCRH_EPS          EQU  0x00000004  ; UART Even Parity Select
UART_LCRH_PEN          EQU  0x00000002  ; UART Parity Enable
UART_LCRH_BRK          EQU  0x00000001  ; UART Send Break

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_CTL register.
;
;*************************************************************
UART_CTL_RXE           EQU  0x00000200  ; UART Receive Enable
UART_CTL_TXE           EQU  0x00000100  ; UART Transmit Enable
UART_CTL_LBE           EQU  0x00000080  ; UART Loop Back Enable
UART_CTL_LIN           EQU  0x00000040  ; LIN Mode Enable
UART_CTL_HSE           EQU  0x00000020  ; High-Speed Enable
UART_CTL_EOT           EQU  0x00000010  ; End of Transmission
UART_CTL_SMART         EQU  0x00000008  ; ISO 7816 Smart Card Support
UART_CTL_SIRLP         EQU  0x00000004  ; UART SIR Low-Power Mode
UART_CTL_SIREN         EQU  0x00000002  ; UART SIR Enable
UART_CTL_UARTEN        EQU  0x00000001  ; UART Enable

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_IFLS register.
;
;*************************************************************
UART_IFLS_RX_M         EQU  0x00000038  ; UART Receive Interrupt FIFO
                                            ; Level Select
UART_IFLS_RX1_8        EQU  0x00000000  ; RX FIFO >= 1/8 full
UART_IFLS_RX2_8        EQU  0x00000008  ; RX FIFO >= 1/4 full
UART_IFLS_RX4_8        EQU  0x00000010  ; RX FIFO >= 1/2 full (default)
UART_IFLS_RX6_8        EQU  0x00000018  ; RX FIFO >= 3/4 full
UART_IFLS_RX7_8        EQU  0x00000020  ; RX FIFO >= 7/8 full
UART_IFLS_TX_M         EQU  0x00000007  ; UART Transmit Interrupt FIFO
                                            ; Level Select
UART_IFLS_TX1_8        EQU  0x00000000  ; TX FIFO <= 1/8 full
UART_IFLS_TX2_8        EQU  0x00000001  ; TX FIFO <= 1/4 full
UART_IFLS_TX4_8        EQU  0x00000002  ; TX FIFO <= 1/2 full (default)
UART_IFLS_TX6_8        EQU  0x00000003  ; TX FIFO <= 3/4 full
UART_IFLS_TX7_8        EQU  0x00000004  ; TX FIFO <= 7/8 full

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_IM register.
;
;*************************************************************
UART_IM_LME5IM         EQU  0x00008000  ; LIN Mode Edge 5 Interrupt Mask
UART_IM_LME1IM         EQU  0x00004000  ; LIN Mode Edge 1 Interrupt Mask
UART_IM_LMSBIM         EQU  0x00002000  ; LIN Mode Sync Break Interrupt
                                            ; Mask
UART_IM_9BITIM         EQU  0x00001000  ; 9-Bit Mode Interrupt Mask
UART_IM_OEIM           EQU  0x00000400  ; UART Overrun Error Interrupt
                                            ; Mask
UART_IM_BEIM           EQU  0x00000200  ; UART Break Error Interrupt Mask
UART_IM_PEIM           EQU  0x00000100  ; UART Parity Error Interrupt Mask
UART_IM_FEIM           EQU  0x00000080  ; UART Framing Error Interrupt
                                            ; Mask
UART_IM_RTIM           EQU  0x00000040  ; UART Receive Time-Out Interrupt
                                            ; Mask
UART_IM_TXIM           EQU  0x00000020  ; UART Transmit Interrupt Mask
UART_IM_RXIM           EQU  0x00000010  ; UART Receive Interrupt Mask
UART_IM_CTSMIM         EQU  0x00000002  ; UART Clear to Send Modem
                                            ; Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_RIS register.
;
;*************************************************************
UART_RIS_LME5RIS       EQU  0x00008000  ; LIN Mode Edge 5 Raw Interrupt
                                            ; Status
UART_RIS_LME1RIS       EQU  0x00004000  ; LIN Mode Edge 1 Raw Interrupt
                                            ; Status
UART_RIS_LMSBRIS       EQU  0x00002000  ; LIN Mode Sync Break Raw
                                            ; Interrupt Status
UART_RIS_9BITRIS       EQU  0x00001000  ; 9-Bit Mode Raw Interrupt Status
UART_RIS_OERIS         EQU  0x00000400  ; UART Overrun Error Raw Interrupt
                                            ; Status
UART_RIS_BERIS         EQU  0x00000200  ; UART Break Error Raw Interrupt
                                            ; Status
UART_RIS_PERIS         EQU  0x00000100  ; UART Parity Error Raw Interrupt
                                            ; Status
UART_RIS_FERIS         EQU  0x00000080  ; UART Framing Error Raw Interrupt
                                            ; Status
UART_RIS_RTRIS         EQU  0x00000040  ; UART Receive Time-Out Raw
                                            ; Interrupt Status
UART_RIS_TXRIS         EQU  0x00000020  ; UART Transmit Raw Interrupt
                                            ; Status
UART_RIS_RXRIS         EQU  0x00000010  ; UART Receive Raw Interrupt
                                            ; Status
UART_RIS_CTSRIS        EQU  0x00000002  ; UART Clear to Send Modem Raw
                                            ; Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_MIS register.
;
;*************************************************************
UART_MIS_LME5MIS       EQU  0x00008000  ; LIN Mode Edge 5 Masked Interrupt
                                            ; Status
UART_MIS_LME1MIS       EQU  0x00004000  ; LIN Mode Edge 1 Masked Interrupt
                                            ; Status
UART_MIS_LMSBMIS       EQU  0x00002000  ; LIN Mode Sync Break Masked
                                            ; Interrupt Status
UART_MIS_9BITMIS       EQU  0x00001000  ; 9-Bit Mode Masked Interrupt
                                            ; Status
UART_MIS_OEMIS         EQU  0x00000400  ; UART Overrun Error Masked
                                            ; Interrupt Status
UART_MIS_BEMIS         EQU  0x00000200  ; UART Break Error Masked
                                            ; Interrupt Status
UART_MIS_PEMIS         EQU  0x00000100  ; UART Parity Error Masked
                                            ; Interrupt Status
UART_MIS_FEMIS         EQU  0x00000080  ; UART Framing Error Masked
                                            ; Interrupt Status
UART_MIS_RTMIS         EQU  0x00000040  ; UART Receive Time-Out Masked
                                            ; Interrupt Status
UART_MIS_TXMIS         EQU  0x00000020  ; UART Transmit Masked Interrupt
                                            ; Status
UART_MIS_RXMIS         EQU  0x00000010  ; UART Receive Masked Interrupt
                                            ; Status
UART_MIS_CTSMIS        EQU  0x00000002  ; UART Clear to Send Modem Masked
                                            ; Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_ICR register.
;
;*************************************************************
UART_ICR_LME5IC        EQU  0x00008000  ; LIN Mode Edge 5 Interrupt Clear
UART_ICR_LME1IC        EQU  0x00004000  ; LIN Mode Edge 1 Interrupt Clear
UART_ICR_LMSBIC        EQU  0x00002000  ; LIN Mode Sync Break Interrupt
                                            ; Clear
UART_ICR_9BITIC        EQU  0x00001000  ; 9-Bit Mode Interrupt Clear
UART_ICR_OEIC          EQU  0x00000400  ; Overrun Error Interrupt Clear
UART_ICR_BEIC          EQU  0x00000200  ; Break Error Interrupt Clear
UART_ICR_PEIC          EQU  0x00000100  ; Parity Error Interrupt Clear
UART_ICR_FEIC          EQU  0x00000080  ; Framing Error Interrupt Clear
UART_ICR_RTIC          EQU  0x00000040  ; Receive Time-Out Interrupt Clear
UART_ICR_TXIC          EQU  0x00000020  ; Transmit Interrupt Clear
UART_ICR_RXIC          EQU  0x00000010  ; Receive Interrupt Clear
UART_ICR_CTSMIC        EQU  0x00000002  ; UART Clear to Send Modem
                                            ; Interrupt Clear

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_DMACTL register.
;
;*************************************************************
UART_DMACTL_DMAERR     EQU  0x00000004  ; DMA on Error
UART_DMACTL_TXDMAE     EQU  0x00000002  ; Transmit DMA Enable
UART_DMACTL_RXDMAE     EQU  0x00000001  ; Receive DMA Enable

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_LCTL register.
;
;*************************************************************
UART_LCTL_BLEN_M       EQU  0x00000030  ; Sync Break Length
UART_LCTL_BLEN_13T     EQU  0x00000000  ; Sync break length is 13T bits
                                            ; (default)
UART_LCTL_BLEN_14T     EQU  0x00000010  ; Sync break length is 14T bits
UART_LCTL_BLEN_15T     EQU  0x00000020  ; Sync break length is 15T bits
UART_LCTL_BLEN_16T     EQU  0x00000030  ; Sync break length is 16T bits
UART_LCTL_MASTER       EQU  0x00000001  ; LIN Master Enable

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_LSS register.
;
;*************************************************************
UART_LSS_TSS_M         EQU  0x0000FFFF  ; Timer Snap Shot
UART_LSS_TSS_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_LTIM register.
;
;*************************************************************
UART_LTIM_TIMER_M      EQU  0x0000FFFF  ; Timer Value
UART_LTIM_TIMER_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_9BITADDR
; register.
;
;*************************************************************
UART_9BITADDR_9BITEN   EQU  0x00008000  ; Enable 9-Bit Mode
UART_9BITADDR_ADDR_M   EQU  0x000000FF  ; Self Address for 9-Bit Mode
UART_9BITADDR_ADDR_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_9BITAMASK
; register.
;
;*************************************************************
UART_9BITAMASK_MASK_M  EQU  0x000000FF  ; Self Address Mask for 9-Bit Mode
UART_9BITAMASK_MASK_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_PP register.
;
;*************************************************************
UART_PP_NB             EQU  0x00000002  ; 9-Bit Support
UART_PP_SC             EQU  0x00000001  ; Smart Card Support

;*************************************************************
;
; The following are defines for the bit fields in the UART_O_CC register.
;
;*************************************************************
UART_CC_CS_M           EQU  0x0000000F  ; UART Baud Clock Source
UART_CC_CS_SYSCLK      EQU  0x00000000  ; The system clock (default)
UART_CC_CS_PIOSC       EQU  0x00000005  ; PIOSC

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MSA register.
;
;*************************************************************
I2C_MSA_SA_M           EQU  0x000000FE  ; I2C Slave Address
I2C_MSA_RS             EQU  0x00000001  ; Receive not send
I2C_MSA_SA_S    EQU          1

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SOAR register.
;
;*************************************************************
I2C_SOAR_OAR_M         EQU  0x0000007F  ; I2C Slave Own Address
I2C_SOAR_OAR_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SCSR register.
;
;*************************************************************
I2C_SCSR_OAR2SEL       EQU  0x00000008  ; OAR2 Address Matched
I2C_SCSR_FBR           EQU  0x00000004  ; First Byte Received
I2C_SCSR_TREQ          EQU  0x00000002  ; Transmit Request
I2C_SCSR_DA            EQU  0x00000001  ; Device Active
I2C_SCSR_RREQ          EQU  0x00000001  ; Receive Request

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MCS register.
;
;*************************************************************
I2C_MCS_CLKTO          EQU  0x00000080  ; Clock Timeout Error
I2C_MCS_BUSBSY         EQU  0x00000040  ; Bus Busy
I2C_MCS_IDLE           EQU  0x00000020  ; I2C Idle
I2C_MCS_ARBLST         EQU  0x00000010  ; Arbitration Lost
I2C_MCS_HS             EQU  0x00000010  ; High-Speed Enable
I2C_MCS_ACK            EQU  0x00000008  ; Data Acknowledge Enable
I2C_MCS_DATACK         EQU  0x00000008  ; Acknowledge Data
I2C_MCS_ADRACK         EQU  0x00000004  ; Acknowledge Address
I2C_MCS_STOP           EQU  0x00000004  ; Generate STOP
I2C_MCS_ERROR          EQU  0x00000002  ; Error
I2C_MCS_START          EQU  0x00000002  ; Generate START
I2C_MCS_RUN            EQU  0x00000001  ; I2C Master Enable
I2C_MCS_BUSY           EQU  0x00000001  ; I2C Busy

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SDR register.
;
;*************************************************************
I2C_SDR_DATA_M         EQU  0x000000FF  ; Data for Transfer
I2C_SDR_DATA_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MDR register.
;
;*************************************************************
I2C_MDR_DATA_M         EQU  0x000000FF  ; Data Transferred
I2C_MDR_DATA_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MTPR register.
;
;*************************************************************
I2C_MTPR_HS            EQU  0x00000080  ; High-Speed Enable
I2C_MTPR_TPR_M         EQU  0x0000007F  ; SCL Clock Period
I2C_MTPR_TPR_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SIMR register.
;
;*************************************************************
I2C_SIMR_STOPIM        EQU  0x00000004  ; Stop Condition Interrupt Mask
I2C_SIMR_STARTIM       EQU  0x00000002  ; Start Condition Interrupt Mask
I2C_SIMR_DATAIM        EQU  0x00000001  ; Data Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SRIS register.
;
;*************************************************************
I2C_SRIS_STOPRIS       EQU  0x00000004  ; Stop Condition Raw Interrupt
                                            ; Status
I2C_SRIS_STARTRIS      EQU  0x00000002  ; Start Condition Raw Interrupt
                                            ; Status
I2C_SRIS_DATARIS       EQU  0x00000001  ; Data Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MIMR register.
;
;*************************************************************
I2C_MIMR_CLKIM         EQU  0x00000002  ; Clock Timeout Interrupt Mask
I2C_MIMR_IM            EQU  0x00000001  ; Master Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MRIS register.
;
;*************************************************************
I2C_MRIS_CLKRIS        EQU  0x00000002  ; Clock Timeout Raw Interrupt
                                            ; Status
I2C_MRIS_RIS           EQU  0x00000001  ; Master Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SMIS register.
;
;*************************************************************
I2C_SMIS_STOPMIS       EQU  0x00000004  ; Stop Condition Masked Interrupt
                                            ; Status
I2C_SMIS_STARTMIS      EQU  0x00000002  ; Start Condition Masked Interrupt
                                            ; Status
I2C_SMIS_DATAMIS       EQU  0x00000001  ; Data Masked Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SICR register.
;
;*************************************************************
I2C_SICR_STOPIC        EQU  0x00000004  ; Stop Condition Interrupt Clear
I2C_SICR_STARTIC       EQU  0x00000002  ; Start Condition Interrupt Clear
I2C_SICR_DATAIC        EQU  0x00000001  ; Data Interrupt Clear

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MMIS register.
;
;*************************************************************
I2C_MMIS_CLKMIS        EQU  0x00000002  ; Clock Timeout Masked Interrupt
                                            ; Status
I2C_MMIS_MIS           EQU  0x00000001  ; Masked Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MICR register.
;
;*************************************************************
I2C_MICR_CLKIC         EQU  0x00000002  ; Clock Timeout Interrupt Clear
I2C_MICR_IC            EQU  0x00000001  ; Master Interrupt Clear

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SOAR2 register.
;
;*************************************************************
I2C_SOAR2_OAR2EN       EQU  0x00000080  ; I2C Slave Own Address 2 Enable
I2C_SOAR2_OAR2_M       EQU  0x0000007F  ; I2C Slave Own Address 2
I2C_SOAR2_OAR2_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MCR register.
;
;*************************************************************
I2C_MCR_SFE            EQU  0x00000020  ; I2C Slave Function Enable
I2C_MCR_MFE            EQU  0x00000010  ; I2C Master Function Enable
I2C_MCR_LPBK           EQU  0x00000001  ; I2C Loopback

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_SACKCTL register.
;
;*************************************************************
I2C_SACKCTL_ACKOVAL    EQU  0x00000002  ; I2C Slave ACK Override Value
I2C_SACKCTL_ACKOEN     EQU  0x00000001  ; I2C Slave ACK Override Enable

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MCLKOCNT register.
;
;*************************************************************
I2C_MCLKOCNT_CNTL_M    EQU  0x000000FF  ; I2C Master Count
I2C_MCLKOCNT_CNTL_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_MBMON register.
;
;*************************************************************
I2C_MBMON_SDA          EQU  0x00000002  ; I2C SDA Status
I2C_MBMON_SCL          EQU  0x00000001  ; I2C SCL Status

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_PP register.
;
;*************************************************************
I2C_PP_HS              EQU  0x00000001  ; High-Speed Capable

;*************************************************************
;
; The following are defines for the bit fields in the I2C_O_PC register.
;
;*************************************************************
I2C_PC_HS              EQU  0x00000001  ; High-Speed Capable

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_CFG register.
;
;*************************************************************
TIMER_CFG_M            EQU  0x00000007  ; GPTM Configuration
TIMER_CFG_32_BIT_TIMER EQU  0x00000000  ; 32-bit timer configuration
TIMER_CFG_32_BIT_RTC   EQU  0x00000001  ; 32-bit real-time clock (RTC)
                                            ; counter configuration
TIMER_CFG_16_BIT       EQU  0x00000004  ; 16-bit timer configuration. The
                                            ; function is controlled by bits
                                            ; 1:0 of GPTMTAMR and GPTMTBMR

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAMR register.
;
;*************************************************************
TIMER_TAMR_TAPLO       EQU  0x00000800  ; GPTM Timer A PWM Legacy
                                            ; Operation
TIMER_TAMR_TAMRSU      EQU  0x00000400  ; GPTM Timer A Match Register
                                            ; Update
TIMER_TAMR_TAPWMIE     EQU  0x00000200  ; GPTM Timer A PWM Interrupt
                                            ; Enable
TIMER_TAMR_TAILD       EQU  0x00000100  ; GPTM Timer A Interval Load Write
TIMER_TAMR_TASNAPS     EQU  0x00000080  ; GPTM Timer A Snap-Shot Mode
TIMER_TAMR_TAWOT       EQU  0x00000040  ; GPTM Timer A Wait-on-Trigger
TIMER_TAMR_TAMIE       EQU  0x00000020  ; GPTM Timer A Match Interrupt
                                            ; Enable
TIMER_TAMR_TACDIR      EQU  0x00000010  ; GPTM Timer A Count Direction
TIMER_TAMR_TAAMS       EQU  0x00000008  ; GPTM Timer A Alternate Mode
                                            ; Select
TIMER_TAMR_TACMR       EQU  0x00000004  ; GPTM Timer A Capture Mode
TIMER_TAMR_TAMR_M      EQU  0x00000003  ; GPTM Timer A Mode
TIMER_TAMR_TAMR_1_SHOT EQU  0x00000001  ; One-Shot Timer mode
TIMER_TAMR_TAMR_PERIOD EQU  0x00000002  ; Periodic Timer mode
TIMER_TAMR_TAMR_CAP    EQU  0x00000003  ; Capture mode

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBMR register.
;
;*************************************************************
TIMER_TBMR_TBPLO       EQU  0x00000800  ; GPTM Timer B PWM Legacy
                                            ; Operation
TIMER_TBMR_TBMRSU      EQU  0x00000400  ; GPTM Timer B Match Register
                                            ; Update
TIMER_TBMR_TBPWMIE     EQU  0x00000200  ; GPTM Timer B PWM Interrupt
                                            ; Enable
TIMER_TBMR_TBILD       EQU  0x00000100  ; GPTM Timer B Interval Load Write
TIMER_TBMR_TBSNAPS     EQU  0x00000080  ; GPTM Timer B Snap-Shot Mode
TIMER_TBMR_TBWOT       EQU  0x00000040  ; GPTM Timer B Wait-on-Trigger
TIMER_TBMR_TBMIE       EQU  0x00000020  ; GPTM Timer B Match Interrupt
                                            ; Enable
TIMER_TBMR_TBCDIR      EQU  0x00000010  ; GPTM Timer B Count Direction
TIMER_TBMR_TBAMS       EQU  0x00000008  ; GPTM Timer B Alternate Mode
                                            ; Select
TIMER_TBMR_TBCMR       EQU  0x00000004  ; GPTM Timer B Capture Mode
TIMER_TBMR_TBMR_M      EQU  0x00000003  ; GPTM Timer B Mode
TIMER_TBMR_TBMR_1_SHOT EQU  0x00000001  ; One-Shot Timer mode
TIMER_TBMR_TBMR_PERIOD EQU  0x00000002  ; Periodic Timer mode
TIMER_TBMR_TBMR_CAP    EQU  0x00000003  ; Capture mode

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_CTL register.
;
;*************************************************************
TIMER_CTL_TBPWML       EQU  0x00004000  ; GPTM Timer B PWM Output Level
TIMER_CTL_TBOTE        EQU  0x00002000  ; GPTM Timer B Output Trigger
                                            ; Enable
TIMER_CTL_TBEVENT_M    EQU  0x00000C00  ; GPTM Timer B Event Mode
TIMER_CTL_TBEVENT_POS  EQU  0x00000000  ; Positive edge
TIMER_CTL_TBEVENT_NEG  EQU  0x00000400  ; Negative edge
TIMER_CTL_TBEVENT_BOTH EQU  0x00000C00  ; Both edges
TIMER_CTL_TBSTALL      EQU  0x00000200  ; GPTM Timer B Stall Enable
TIMER_CTL_TBEN         EQU  0x00000100  ; GPTM Timer B Enable
TIMER_CTL_TAPWML       EQU  0x00000040  ; GPTM Timer A PWM Output Level
TIMER_CTL_TAOTE        EQU  0x00000020  ; GPTM Timer A Output Trigger
                                            ; Enable
TIMER_CTL_RTCEN        EQU  0x00000010  ; GPTM RTC Stall Enable
TIMER_CTL_TAEVENT_M    EQU  0x0000000C  ; GPTM Timer A Event Mode
TIMER_CTL_TAEVENT_POS  EQU  0x00000000  ; Positive edge
TIMER_CTL_TAEVENT_NEG  EQU  0x00000004  ; Negative edge
TIMER_CTL_TAEVENT_BOTH EQU  0x0000000C  ; Both edges
TIMER_CTL_TASTALL      EQU  0x00000002  ; GPTM Timer A Stall Enable
TIMER_CTL_TAEN         EQU  0x00000001  ; GPTM Timer A Enable

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_SYNC register.
;
;*************************************************************
TIMER_SYNC_SYNCWT5_M   EQU  0x00C00000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 5
TIMER_SYNC_SYNCWT5_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 5 is not
                                            ; affected
TIMER_SYNC_SYNCWT5_TA  EQU  0x00400000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 5 is
                                            ; triggered
TIMER_SYNC_SYNCWT5_TB  EQU  0x00800000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 5 is
                                            ; triggered
TIMER_SYNC_SYNCWT5_TATB EQU  0x00C00000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 5 is triggered
TIMER_SYNC_SYNCWT4_M   EQU  0x00300000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 4
TIMER_SYNC_SYNCWT4_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 4 is not
                                            ; affected
TIMER_SYNC_SYNCWT4_TA  EQU  0x00100000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 4 is
                                            ; triggered
TIMER_SYNC_SYNCWT4_TB  EQU  0x00200000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 4 is
                                            ; triggered
TIMER_SYNC_SYNCWT4_TATB EQU  0x00300000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 4 is triggered
TIMER_SYNC_SYNCWT3_M   EQU  0x000C0000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 3
TIMER_SYNC_SYNCWT3_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 3 is not
                                            ; affected
TIMER_SYNC_SYNCWT3_TA  EQU  0x00040000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 3 is
                                            ; triggered
TIMER_SYNC_SYNCWT3_TB  EQU  0x00080000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 3 is
                                            ; triggered
TIMER_SYNC_SYNCWT3_TATB EQU  0x000C0000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 3 is triggered
TIMER_SYNC_SYNCWT2_M   EQU  0x00030000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 2
TIMER_SYNC_SYNCWT2_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 2 is not
                                            ; affected
TIMER_SYNC_SYNCWT2_TA  EQU  0x00010000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 2 is
                                            ; triggered
TIMER_SYNC_SYNCWT2_TB  EQU  0x00020000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 2 is
                                            ; triggered
TIMER_SYNC_SYNCWT2_TATB EQU  0x00030000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 2 is triggered
TIMER_SYNC_SYNCWT1_M   EQU  0x0000C000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 1
TIMER_SYNC_SYNCWT1_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 1 is not
                                            ; affected
TIMER_SYNC_SYNCWT1_TA  EQU  0x00004000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 1 is
                                            ; triggered
TIMER_SYNC_SYNCWT1_TB  EQU  0x00008000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 1 is
                                            ; triggered
TIMER_SYNC_SYNCWT1_TATB EQU  0x0000C000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 1 is triggered
TIMER_SYNC_SYNCWT0_M   EQU  0x00003000  ; Synchronize GPTM 32/64-Bit Timer
                                            ; 0
TIMER_SYNC_SYNCWT0_NONE EQU  0x00000000  ; GPTM 32/64-Bit Timer 0 is not
                                            ; affected
TIMER_SYNC_SYNCWT0_TA  EQU  0x00001000  ; A timeout event for Timer A of
                                            ; GPTM 32/64-Bit Timer 0 is
                                            ; triggered
TIMER_SYNC_SYNCWT0_TB  EQU  0x00002000  ; A timeout event for Timer B of
                                            ; GPTM 32/64-Bit Timer 0 is
                                            ; triggered
TIMER_SYNC_SYNCWT0_TATB EQU  0x00003000  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 32/64-Bit
                                            ; Timer 0 is triggered
TIMER_SYNC_SYNCT5_M    EQU  0x00000C00  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 5
TIMER_SYNC_SYNCT5_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 5 is not
                                            ; affected
TIMER_SYNC_SYNCT5_TA   EQU  0x00000400  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 5 is
                                            ; triggered
TIMER_SYNC_SYNCT5_TB   EQU  0x00000800  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 5 is
                                            ; triggered
TIMER_SYNC_SYNCT5_TATB EQU  0x00000C00  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 5 is triggered
TIMER_SYNC_SYNCT4_M    EQU  0x00000300  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 4
TIMER_SYNC_SYNCT4_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 4 is not
                                            ; affected
TIMER_SYNC_SYNCT4_TA   EQU  0x00000100  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 4 is
                                            ; triggered
TIMER_SYNC_SYNCT4_TB   EQU  0x00000200  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 4 is
                                            ; triggered
TIMER_SYNC_SYNCT4_TATB EQU  0x00000300  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 4 is triggered
TIMER_SYNC_SYNCT3_M    EQU  0x000000C0  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 3
TIMER_SYNC_SYNCT3_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 3 is not
                                            ; affected
TIMER_SYNC_SYNCT3_TA   EQU  0x00000040  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 3 is
                                            ; triggered
TIMER_SYNC_SYNCT3_TB   EQU  0x00000080  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 3 is
                                            ; triggered
TIMER_SYNC_SYNCT3_TATB EQU  0x000000C0  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 3 is triggered
TIMER_SYNC_SYNCT2_M    EQU  0x00000030  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 2
TIMER_SYNC_SYNCT2_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 2 is not
                                            ; affected
TIMER_SYNC_SYNCT2_TA   EQU  0x00000010  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 2 is
                                            ; triggered
TIMER_SYNC_SYNCT2_TB   EQU  0x00000020  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 2 is
                                            ; triggered
TIMER_SYNC_SYNCT2_TATB EQU  0x00000030  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 2 is triggered
TIMER_SYNC_SYNCT1_M    EQU  0x0000000C  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 1
TIMER_SYNC_SYNCT1_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 1 is not
                                            ; affected
TIMER_SYNC_SYNCT1_TA   EQU  0x00000004  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 1 is
                                            ; triggered
TIMER_SYNC_SYNCT1_TB   EQU  0x00000008  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 1 is
                                            ; triggered
TIMER_SYNC_SYNCT1_TATB EQU  0x0000000C  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 1 is triggered
TIMER_SYNC_SYNCT0_M    EQU  0x00000003  ; Synchronize GPTM 16/32-Bit Timer
                                            ; 0
TIMER_SYNC_SYNCT0_NONE EQU  0x00000000  ; GPTM 16/32-Bit Timer 0 is not
                                            ; affected
TIMER_SYNC_SYNCT0_TA   EQU  0x00000001  ; A timeout event for Timer A of
                                            ; GPTM 16/32-Bit Timer 0 is
                                            ; triggered
TIMER_SYNC_SYNCT0_TB   EQU  0x00000002  ; A timeout event for Timer B of
                                            ; GPTM 16/32-Bit Timer 0 is
                                            ; triggered
TIMER_SYNC_SYNCT0_TATB EQU  0x00000003  ; A timeout event for both Timer A
                                            ; and Timer B of GPTM 16/32-Bit
                                            ; Timer 0 is triggered

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_IMR register.
;
;*************************************************************
TIMER_IMR_WUEIM        EQU  0x00010000  ; GPTM Write Update Error
                                            ; Interrupt Mask
TIMER_IMR_TBMIM        EQU  0x00000800  ; GPTM Timer B Match Interrupt
                                            ; Mask
TIMER_IMR_CBEIM        EQU  0x00000400  ; GPTM Timer B Capture Mode Event
                                            ; Interrupt Mask
TIMER_IMR_CBMIM        EQU  0x00000200  ; GPTM Timer B Capture Mode Match
                                            ; Interrupt Mask
TIMER_IMR_TBTOIM       EQU  0x00000100  ; GPTM Timer B Time-Out Interrupt
                                            ; Mask
TIMER_IMR_TAMIM        EQU  0x00000010  ; GPTM Timer A Match Interrupt
                                            ; Mask
TIMER_IMR_RTCIM        EQU  0x00000008  ; GPTM RTC Interrupt Mask
TIMER_IMR_CAEIM        EQU  0x00000004  ; GPTM Timer A Capture Mode Event
                                            ; Interrupt Mask
TIMER_IMR_CAMIM        EQU  0x00000002  ; GPTM Timer A Capture Mode Match
                                            ; Interrupt Mask
TIMER_IMR_TATOIM       EQU  0x00000001  ; GPTM Timer A Time-Out Interrupt
                                            ; Mask

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_RIS register.
;
;*************************************************************
TIMER_RIS_WUERIS       EQU  0x00010000  ; GPTM Write Update Error Raw
                                            ; Interrupt
TIMER_RIS_TBMRIS       EQU  0x00000800  ; GPTM Timer B Match Raw Interrupt
TIMER_RIS_CBERIS       EQU  0x00000400  ; GPTM Timer B Capture Mode Event
                                            ; Raw Interrupt
TIMER_RIS_CBMRIS       EQU  0x00000200  ; GPTM Timer B Capture Mode Match
                                            ; Raw Interrupt
TIMER_RIS_TBTORIS      EQU  0x00000100  ; GPTM Timer B Time-Out Raw
                                            ; Interrupt
TIMER_RIS_TAMRIS       EQU  0x00000010  ; GPTM Timer A Match Raw Interrupt
TIMER_RIS_RTCRIS       EQU  0x00000008  ; GPTM RTC Raw Interrupt
TIMER_RIS_CAERIS       EQU  0x00000004  ; GPTM Timer A Capture Mode Event
                                            ; Raw Interrupt
TIMER_RIS_CAMRIS       EQU  0x00000002  ; GPTM Timer A Capture Mode Match
                                            ; Raw Interrupt
TIMER_RIS_TATORIS      EQU  0x00000001  ; GPTM Timer A Time-Out Raw
                                            ; Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_MIS register.
;
;*************************************************************
TIMER_MIS_WUEMIS       EQU  0x00010000  ; GPTM Write Update Error Masked
                                            ; Interrupt
TIMER_MIS_TBMMIS       EQU  0x00000800  ; GPTM Timer B Match Masked
                                            ; Interrupt
TIMER_MIS_CBEMIS       EQU  0x00000400  ; GPTM Timer B Capture Mode Event
                                            ; Masked Interrupt
TIMER_MIS_CBMMIS       EQU  0x00000200  ; GPTM Timer B Capture Mode Match
                                            ; Masked Interrupt
TIMER_MIS_TBTOMIS      EQU  0x00000100  ; GPTM Timer B Time-Out Masked
                                            ; Interrupt
TIMER_MIS_TAMMIS       EQU  0x00000010  ; GPTM Timer A Match Masked
                                            ; Interrupt
TIMER_MIS_RTCMIS       EQU  0x00000008  ; GPTM RTC Masked Interrupt
TIMER_MIS_CAEMIS       EQU  0x00000004  ; GPTM Timer A Capture Mode Event
                                            ; Masked Interrupt
TIMER_MIS_CAMMIS       EQU  0x00000002  ; GPTM Timer A Capture Mode Match
                                            ; Masked Interrupt
TIMER_MIS_TATOMIS      EQU  0x00000001  ; GPTM Timer A Time-Out Masked
                                            ; Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_ICR register.
;
;*************************************************************
TIMER_ICR_WUECINT      EQU  0x00010000  ; 32/64-Bit GPTM Write Update
                                            ; Error Interrupt Clear
TIMER_ICR_TBMCINT      EQU  0x00000800  ; GPTM Timer B Match Interrupt
                                            ; Clear
TIMER_ICR_CBECINT      EQU  0x00000400  ; GPTM Timer B Capture Mode Event
                                            ; Interrupt Clear
TIMER_ICR_CBMCINT      EQU  0x00000200  ; GPTM Timer B Capture Mode Match
                                            ; Interrupt Clear
TIMER_ICR_TBTOCINT     EQU  0x00000100  ; GPTM Timer B Time-Out Interrupt
                                            ; Clear
TIMER_ICR_TAMCINT      EQU  0x00000010  ; GPTM Timer A Match Interrupt
                                            ; Clear
TIMER_ICR_RTCCINT      EQU  0x00000008  ; GPTM RTC Interrupt Clear
TIMER_ICR_CAECINT      EQU  0x00000004  ; GPTM Timer A Capture Mode Event
                                            ; Interrupt Clear
TIMER_ICR_CAMCINT      EQU  0x00000002  ; GPTM Timer A Capture Mode Match
                                            ; Interrupt Clear
TIMER_ICR_TATOCINT     EQU  0x00000001  ; GPTM Timer A Time-Out Raw
                                            ; Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAILR register.
;
;*************************************************************
TIMER_TAILR_M          EQU  0xFFFFFFFF  ; GPTM Timer A Interval Load
                                            ; Register
TIMER_TAILR_S       EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBILR register.
;
;*************************************************************
TIMER_TBILR_M          EQU  0xFFFFFFFF  ; GPTM Timer B Interval Load
                                            ; Register
TIMER_TBILR_S       EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAMATCHR
; register.
;
;*************************************************************
TIMER_TAMATCHR_TAMR_M  EQU  0xFFFFFFFF  ; GPTM Timer A Match Register
TIMER_TAMATCHR_TAMR_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBMATCHR
; register.
;
;*************************************************************
TIMER_TBMATCHR_TBMR_M  EQU  0xFFFFFFFF  ; GPTM Timer B Match Register
TIMER_TBMATCHR_TBMR_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAPR register.
;
;*************************************************************
TIMER_TAPR_TAPSRH_M    EQU  0x0000FF00  ; GPTM Timer A Prescale High Byte
TIMER_TAPR_TAPSR_M     EQU  0x000000FF  ; GPTM Timer A Prescale
TIMER_TAPR_TAPSRH_S    EQU   8
TIMER_TAPR_TAPSR_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBPR register.
;
;*************************************************************
TIMER_TBPR_TBPSRH_M    EQU  0x0000FF00  ; GPTM Timer B Prescale High Byte
TIMER_TBPR_TBPSR_M     EQU  0x000000FF  ; GPTM Timer B Prescale
TIMER_TBPR_TBPSRH_S    EQU   8
TIMER_TBPR_TBPSR_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAPMR register.
;
;*************************************************************
TIMER_TAPMR_TAPSMRH_M  EQU  0x0000FF00  ; GPTM Timer A Prescale Match High
                                            ; Byte
TIMER_TAPMR_TAPSMR_M   EQU  0x000000FF  ; GPTM TimerA Prescale Match
TIMER_TAPMR_TAPSMRH_S    EQU 8
TIMER_TAPMR_TAPSMR_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBPMR register.
;
;*************************************************************
TIMER_TBPMR_TBPSMRH_M  EQU  0x0000FF00  ; GPTM Timer B Prescale Match High
                                            ; Byte
TIMER_TBPMR_TBPSMR_M   EQU  0x000000FF  ; GPTM TimerB Prescale Match
TIMER_TBPMR_TBPSMRH_S    EQU 8
TIMER_TBPMR_TBPSMR_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAR register.
;
;*************************************************************
TIMER_TAR_M            EQU  0xFFFFFFFF  ; GPTM Timer A Register
TIMER_TAR_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBR register.
;
;*************************************************************
TIMER_TBR_M            EQU  0xFFFFFFFF  ; GPTM Timer B Register
TIMER_TBR_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAV register.
;
;*************************************************************
TIMER_TAV_M            EQU  0xFFFFFFFF  ; GPTM Timer A Value
TIMER_TAV_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBV register.
;
;*************************************************************
TIMER_TBV_M            EQU  0xFFFFFFFF  ; GPTM Timer B Value
TIMER_TBV_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_RTCPD register.
;
;*************************************************************
TIMER_RTCPD_RTCPD_M    EQU  0x0000FFFF  ; RTC Predivide Counter Value
TIMER_RTCPD_RTCPD_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAPS register.
;
;*************************************************************
TIMER_TAPS_PSS_M       EQU  0x0000FFFF  ; GPTM Timer A Prescaler Snapshot
TIMER_TAPS_PSS_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBPS register.
;
;*************************************************************
TIMER_TBPS_PSS_M       EQU  0x0000FFFF  ; GPTM Timer A Prescaler Value
TIMER_TBPS_PSS_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TAPV register.
;
;*************************************************************
TIMER_TAPV_PSV_M       EQU  0x0000FFFF  ; GPTM Timer A Prescaler Value
TIMER_TAPV_PSV_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_TBPV register.
;
;*************************************************************
TIMER_TBPV_PSV_M       EQU  0x0000FFFF  ; GPTM Timer B Prescaler Value
TIMER_TBPV_PSV_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the TIMER_O_PP register.
;
;*************************************************************
TIMER_PP_SIZE_M        EQU  0x0000000F  ; Count Size
TIMER_PP_SIZE_16       EQU  0x00000000  ; Timer A and Timer B counters are
                                            ; 16 bits each with an 8-bit
                                            ; prescale counter
TIMER_PP_SIZE_32       EQU  0x00000001  ; Timer A and Timer B counters are
                                            ; 32 bits each with a 16-bit
                                            ; prescale counter

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_ACTSS register.
;
;*************************************************************
ADC_ACTSS_ASEN3        EQU  0x00000008  ; ADC SS3 Enable
ADC_ACTSS_ASEN2        EQU  0x00000004  ; ADC SS2 Enable
ADC_ACTSS_ASEN1        EQU  0x00000002  ; ADC SS1 Enable
ADC_ACTSS_ASEN0        EQU  0x00000001  ; ADC SS0 Enable

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_RIS register.
;
;*************************************************************
ADC_RIS_INRDC          EQU  0x00010000  ; Digital Comparator Raw Interrupt
                                            ; Status
ADC_RIS_INR3           EQU  0x00000008  ; SS3 Raw Interrupt Status
ADC_RIS_INR2           EQU  0x00000004  ; SS2 Raw Interrupt Status
ADC_RIS_INR1           EQU  0x00000002  ; SS1 Raw Interrupt Status
ADC_RIS_INR0           EQU  0x00000001  ; SS0 Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_IM register.
;
;*************************************************************
ADC_IM_DCONSS3         EQU  0x00080000  ; Digital Comparator Interrupt on
                                            ; SS3
ADC_IM_DCONSS2         EQU  0x00040000  ; Digital Comparator Interrupt on
                                            ; SS2
ADC_IM_DCONSS1         EQU  0x00020000  ; Digital Comparator Interrupt on
                                            ; SS1
ADC_IM_DCONSS0         EQU  0x00010000  ; Digital Comparator Interrupt on
                                            ; SS0
ADC_IM_MASK3           EQU  0x00000008  ; SS3 Interrupt Mask
ADC_IM_MASK2           EQU  0x00000004  ; SS2 Interrupt Mask
ADC_IM_MASK1           EQU  0x00000002  ; SS1 Interrupt Mask
ADC_IM_MASK0           EQU  0x00000001  ; SS0 Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_ISC register.
;
;*************************************************************
ADC_ISC_DCINSS3        EQU  0x00080000  ; Digital Comparator Interrupt
                                            ; Status on SS3
ADC_ISC_DCINSS2        EQU  0x00040000  ; Digital Comparator Interrupt
                                            ; Status on SS2
ADC_ISC_DCINSS1        EQU  0x00020000  ; Digital Comparator Interrupt
                                            ; Status on SS1
ADC_ISC_DCINSS0        EQU  0x00010000  ; Digital Comparator Interrupt
                                            ; Status on SS0
ADC_ISC_IN3            EQU  0x00000008  ; SS3 Interrupt Status and Clear
ADC_ISC_IN2            EQU  0x00000004  ; SS2 Interrupt Status and Clear
ADC_ISC_IN1            EQU  0x00000002  ; SS1 Interrupt Status and Clear
ADC_ISC_IN0            EQU  0x00000001  ; SS0 Interrupt Status and Clear

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_OSTAT register.
;
;*************************************************************
ADC_OSTAT_OV3          EQU  0x00000008  ; SS3 FIFO Overflow
ADC_OSTAT_OV2          EQU  0x00000004  ; SS2 FIFO Overflow
ADC_OSTAT_OV1          EQU  0x00000002  ; SS1 FIFO Overflow
ADC_OSTAT_OV0          EQU  0x00000001  ; SS0 FIFO Overflow

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_EMUX register.
;
;*************************************************************
ADC_EMUX_EM3_M         EQU  0x0000F000  ; SS3 Trigger Select
ADC_EMUX_EM3_PROCESSOR EQU  0x00000000  ; Processor (default)
ADC_EMUX_EM3_COMP0     EQU  0x00001000  ; Analog Comparator 0
ADC_EMUX_EM3_COMP1     EQU  0x00002000  ; Analog Comparator 1
ADC_EMUX_EM3_EXTERNAL  EQU  0x00004000  ; External (GPIO PB4)
ADC_EMUX_EM3_TIMER     EQU  0x00005000  ; Timer
ADC_EMUX_EM3_ALWAYS    EQU  0x0000F000  ; Always (continuously sample)
ADC_EMUX_EM2_M         EQU  0x00000F00  ; SS2 Trigger Select
ADC_EMUX_EM2_PROCESSOR EQU  0x00000000  ; Processor (default)
ADC_EMUX_EM2_COMP0     EQU  0x00000100  ; Analog Comparator 0
ADC_EMUX_EM2_COMP1     EQU  0x00000200  ; Analog Comparator 1
ADC_EMUX_EM2_EXTERNAL  EQU  0x00000400  ; External (GPIO PB4)
ADC_EMUX_EM2_TIMER     EQU  0x00000500  ; Timer
ADC_EMUX_EM2_ALWAYS    EQU  0x00000F00  ; Always (continuously sample)
ADC_EMUX_EM1_M         EQU  0x000000F0  ; SS1 Trigger Select
ADC_EMUX_EM1_PROCESSOR EQU  0x00000000  ; Processor (default)
ADC_EMUX_EM1_COMP0     EQU  0x00000010  ; Analog Comparator 0
ADC_EMUX_EM1_COMP1     EQU  0x00000020  ; Analog Comparator 1
ADC_EMUX_EM1_EXTERNAL  EQU  0x00000040  ; External (GPIO PB4)
ADC_EMUX_EM1_TIMER     EQU  0x00000050  ; Timer
ADC_EMUX_EM1_ALWAYS    EQU  0x000000F0  ; Always (continuously sample)
ADC_EMUX_EM0_M         EQU  0x0000000F  ; SS0 Trigger Select
ADC_EMUX_EM0_PROCESSOR EQU  0x00000000  ; Processor (default)
ADC_EMUX_EM0_COMP0     EQU  0x00000001  ; Analog Comparator 0
ADC_EMUX_EM0_COMP1     EQU  0x00000002  ; Analog Comparator 1
ADC_EMUX_EM0_EXTERNAL  EQU  0x00000004  ; External (GPIO PB4)
ADC_EMUX_EM0_TIMER     EQU  0x00000005  ; Timer
ADC_EMUX_EM0_ALWAYS    EQU  0x0000000F  ; Always (continuously sample)

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_USTAT register.
;
;*************************************************************
ADC_USTAT_UV3          EQU  0x00000008  ; SS3 FIFO Underflow
ADC_USTAT_UV2          EQU  0x00000004  ; SS2 FIFO Underflow
ADC_USTAT_UV1          EQU  0x00000002  ; SS1 FIFO Underflow
ADC_USTAT_UV0          EQU  0x00000001  ; SS0 FIFO Underflow

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSPRI register.
;
;*************************************************************
ADC_SSPRI_SS3_M        EQU  0x00003000  ; SS3 Priority
ADC_SSPRI_SS3_1ST      EQU  0x00000000  ; First priority
ADC_SSPRI_SS3_2ND      EQU  0x00001000  ; Second priority
ADC_SSPRI_SS3_3RD      EQU  0x00002000  ; Third priority
ADC_SSPRI_SS3_4TH      EQU  0x00003000  ; Fourth priority
ADC_SSPRI_SS2_M        EQU  0x00000300  ; SS2 Priority
ADC_SSPRI_SS2_1ST      EQU  0x00000000  ; First priority
ADC_SSPRI_SS2_2ND      EQU  0x00000100  ; Second priority
ADC_SSPRI_SS2_3RD      EQU  0x00000200  ; Third priority
ADC_SSPRI_SS2_4TH      EQU  0x00000300  ; Fourth priority
ADC_SSPRI_SS1_M        EQU  0x00000030  ; SS1 Priority
ADC_SSPRI_SS1_1ST      EQU  0x00000000  ; First priority
ADC_SSPRI_SS1_2ND      EQU  0x00000010  ; Second priority
ADC_SSPRI_SS1_3RD      EQU  0x00000020  ; Third priority
ADC_SSPRI_SS1_4TH      EQU  0x00000030  ; Fourth priority
ADC_SSPRI_SS0_M        EQU  0x00000003  ; SS0 Priority
ADC_SSPRI_SS0_1ST      EQU  0x00000000  ; First priority
ADC_SSPRI_SS0_2ND      EQU  0x00000001  ; Second priority
ADC_SSPRI_SS0_3RD      EQU  0x00000002  ; Third priority
ADC_SSPRI_SS0_4TH      EQU  0x00000003  ; Fourth priority

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SPC register.
;
;*************************************************************
ADC_SPC_PHASE_M        EQU  0x0000000F  ; Phase Difference
ADC_SPC_PHASE_0        EQU  0x00000000  ; ADC sample lags by 0.0
ADC_SPC_PHASE_22_5     EQU  0x00000001  ; ADC sample lags by 22.5
ADC_SPC_PHASE_45       EQU  0x00000002  ; ADC sample lags by 45.0
ADC_SPC_PHASE_67_5     EQU  0x00000003  ; ADC sample lags by 67.5
ADC_SPC_PHASE_90       EQU  0x00000004  ; ADC sample lags by 90.0
ADC_SPC_PHASE_112_5    EQU  0x00000005  ; ADC sample lags by 112.5
ADC_SPC_PHASE_135      EQU  0x00000006  ; ADC sample lags by 135.0
ADC_SPC_PHASE_157_5    EQU  0x00000007  ; ADC sample lags by 157.5
ADC_SPC_PHASE_180      EQU  0x00000008  ; ADC sample lags by 180.0
ADC_SPC_PHASE_202_5    EQU  0x00000009  ; ADC sample lags by 202.5
ADC_SPC_PHASE_225      EQU  0x0000000A  ; ADC sample lags by 225.0
ADC_SPC_PHASE_247_5    EQU  0x0000000B  ; ADC sample lags by 247.5
ADC_SPC_PHASE_270      EQU  0x0000000C  ; ADC sample lags by 270.0
ADC_SPC_PHASE_292_5    EQU  0x0000000D  ; ADC sample lags by 292.5
ADC_SPC_PHASE_315      EQU  0x0000000E  ; ADC sample lags by 315.0
ADC_SPC_PHASE_337_5    EQU  0x0000000F  ; ADC sample lags by 337.5

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_PSSI register.
;
;*************************************************************
ADC_PSSI_GSYNC         EQU  0x80000000  ; Global Synchronize
ADC_PSSI_SYNCWAIT      EQU  0x08000000  ; Synchronize Wait
ADC_PSSI_SS3           EQU  0x00000008  ; SS3 Initiate
ADC_PSSI_SS2           EQU  0x00000004  ; SS2 Initiate
ADC_PSSI_SS1           EQU  0x00000002  ; SS1 Initiate
ADC_PSSI_SS0           EQU  0x00000001  ; SS0 Initiate

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SAC register.
;
;*************************************************************
ADC_SAC_AVG_M          EQU  0x00000007  ; Hardware Averaging Control
ADC_SAC_AVG_OFF        EQU  0x00000000  ; No hardware oversampling
ADC_SAC_AVG_2X         EQU  0x00000001  ; 2x hardware oversampling
ADC_SAC_AVG_4X         EQU  0x00000002  ; 4x hardware oversampling
ADC_SAC_AVG_8X         EQU  0x00000003  ; 8x hardware oversampling
ADC_SAC_AVG_16X        EQU  0x00000004  ; 16x hardware oversampling
ADC_SAC_AVG_32X        EQU  0x00000005  ; 32x hardware oversampling
ADC_SAC_AVG_64X        EQU  0x00000006  ; 64x hardware oversampling

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCISC register.
;
;*************************************************************
ADC_DCISC_DCINT7       EQU  0x00000080  ; Digital Comparator 7 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT6       EQU  0x00000040  ; Digital Comparator 6 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT5       EQU  0x00000020  ; Digital Comparator 5 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT4       EQU  0x00000010  ; Digital Comparator 4 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT3       EQU  0x00000008  ; Digital Comparator 3 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT2       EQU  0x00000004  ; Digital Comparator 2 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT1       EQU  0x00000002  ; Digital Comparator 1 Interrupt
                                            ; Status and Clear
ADC_DCISC_DCINT0       EQU  0x00000001  ; Digital Comparator 0 Interrupt
                                            ; Status and Clear

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSMUX0 register.
;
;*************************************************************
ADC_SSMUX0_MUX7_M      EQU  0xF0000000  ; 8th Sample Input Select
ADC_SSMUX0_MUX6_M      EQU  0x0F000000  ; 7th Sample Input Select
ADC_SSMUX0_MUX5_M      EQU  0x00F00000  ; 6th Sample Input Select
ADC_SSMUX0_MUX4_M      EQU  0x000F0000  ; 5th Sample Input Select
ADC_SSMUX0_MUX3_M      EQU  0x0000F000  ; 4th Sample Input Select
ADC_SSMUX0_MUX2_M      EQU  0x00000F00  ; 3rd Sample Input Select
ADC_SSMUX0_MUX1_M      EQU  0x000000F0  ; 2nd Sample Input Select
ADC_SSMUX0_MUX0_M      EQU  0x0000000F  ; 1st Sample Input Select
ADC_SSMUX0_MUX7_S   EQU   28
ADC_SSMUX0_MUX6_S   EQU   24
ADC_SSMUX0_MUX5_S   EQU   20
ADC_SSMUX0_MUX4_S   EQU   16
ADC_SSMUX0_MUX3_S   EQU   12
ADC_SSMUX0_MUX2_S   EQU   8
ADC_SSMUX0_MUX1_S   EQU   4
ADC_SSMUX0_MUX0_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSCTL0 register.
;
;*************************************************************
ADC_SSCTL0_TS7         EQU  0x80000000  ; 8th Sample Temp Sensor Select
ADC_SSCTL0_IE7         EQU  0x40000000  ; 8th Sample Interrupt Enable
ADC_SSCTL0_END7        EQU  0x20000000  ; 8th Sample is End of Sequence
ADC_SSCTL0_D7          EQU  0x10000000  ; 8th Sample Diff Input Select
ADC_SSCTL0_TS6         EQU  0x08000000  ; 7th Sample Temp Sensor Select
ADC_SSCTL0_IE6         EQU  0x04000000  ; 7th Sample Interrupt Enable
ADC_SSCTL0_END6        EQU  0x02000000  ; 7th Sample is End of Sequence
ADC_SSCTL0_D6          EQU  0x01000000  ; 7th Sample Diff Input Select
ADC_SSCTL0_TS5         EQU  0x00800000  ; 6th Sample Temp Sensor Select
ADC_SSCTL0_IE5         EQU  0x00400000  ; 6th Sample Interrupt Enable
ADC_SSCTL0_END5        EQU  0x00200000  ; 6th Sample is End of Sequence
ADC_SSCTL0_D5          EQU  0x00100000  ; 6th Sample Diff Input Select
ADC_SSCTL0_TS4         EQU  0x00080000  ; 5th Sample Temp Sensor Select
ADC_SSCTL0_IE4         EQU  0x00040000  ; 5th Sample Interrupt Enable
ADC_SSCTL0_END4        EQU  0x00020000  ; 5th Sample is End of Sequence
ADC_SSCTL0_D4          EQU  0x00010000  ; 5th Sample Diff Input Select
ADC_SSCTL0_TS3         EQU  0x00008000  ; 4th Sample Temp Sensor Select
ADC_SSCTL0_IE3         EQU  0x00004000  ; 4th Sample Interrupt Enable
ADC_SSCTL0_END3        EQU  0x00002000  ; 4th Sample is End of Sequence
ADC_SSCTL0_D3          EQU  0x00001000  ; 4th Sample Diff Input Select
ADC_SSCTL0_TS2         EQU  0x00000800  ; 3rd Sample Temp Sensor Select
ADC_SSCTL0_IE2         EQU  0x00000400  ; 3rd Sample Interrupt Enable
ADC_SSCTL0_END2        EQU  0x00000200  ; 3rd Sample is End of Sequence
ADC_SSCTL0_D2          EQU  0x00000100  ; 3rd Sample Diff Input Select
ADC_SSCTL0_TS1         EQU  0x00000080  ; 2nd Sample Temp Sensor Select
ADC_SSCTL0_IE1         EQU  0x00000040  ; 2nd Sample Interrupt Enable
ADC_SSCTL0_END1        EQU  0x00000020  ; 2nd Sample is End of Sequence
ADC_SSCTL0_D1          EQU  0x00000010  ; 2nd Sample Diff Input Select
ADC_SSCTL0_TS0         EQU  0x00000008  ; 1st Sample Temp Sensor Select
ADC_SSCTL0_IE0         EQU  0x00000004  ; 1st Sample Interrupt Enable
ADC_SSCTL0_END0        EQU  0x00000002  ; 1st Sample is End of Sequence
ADC_SSCTL0_D0          EQU  0x00000001  ; 1st Sample Diff Input Select

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFIFO0 register.
;
;*************************************************************
ADC_SSFIFO0_DATA_M     EQU  0x00000FFF  ; Conversion Result Data
ADC_SSFIFO0_DATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFSTAT0 register.
;
;*************************************************************
ADC_SSFSTAT0_FULL      EQU  0x00001000  ; FIFO Full
ADC_SSFSTAT0_EMPTY     EQU  0x00000100  ; FIFO Empty
ADC_SSFSTAT0_HPTR_M    EQU  0x000000F0  ; FIFO Head Pointer
ADC_SSFSTAT0_TPTR_M    EQU  0x0000000F  ; FIFO Tail Pointer
ADC_SSFSTAT0_HPTR_S    EQU   4
ADC_SSFSTAT0_TPTR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSOP0 register.
;
;*************************************************************
ADC_SSOP0_S7DCOP       EQU  0x10000000  ; Sample 7 Digital Comparator
                                            ; Operation
ADC_SSOP0_S6DCOP       EQU  0x01000000  ; Sample 6 Digital Comparator
                                            ; Operation
ADC_SSOP0_S5DCOP       EQU  0x00100000  ; Sample 5 Digital Comparator
                                            ; Operation
ADC_SSOP0_S4DCOP       EQU  0x00010000  ; Sample 4 Digital Comparator
                                            ; Operation
ADC_SSOP0_S3DCOP       EQU  0x00001000  ; Sample 3 Digital Comparator
                                            ; Operation
ADC_SSOP0_S2DCOP       EQU  0x00000100  ; Sample 2 Digital Comparator
                                            ; Operation
ADC_SSOP0_S1DCOP       EQU  0x00000010  ; Sample 1 Digital Comparator
                                            ; Operation
ADC_SSOP0_S0DCOP       EQU  0x00000001  ; Sample 0 Digital Comparator
                                            ; Operation

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSDC0 register.
;
;*************************************************************
ADC_SSDC0_S7DCSEL_M    EQU  0xF0000000  ; Sample 7 Digital Comparator
                                            ; Select
ADC_SSDC0_S6DCSEL_M    EQU  0x0F000000  ; Sample 6 Digital Comparator
                                            ; Select
ADC_SSDC0_S5DCSEL_M    EQU  0x00F00000  ; Sample 5 Digital Comparator
                                            ; Select
ADC_SSDC0_S4DCSEL_M    EQU  0x000F0000  ; Sample 4 Digital Comparator
                                            ; Select
ADC_SSDC0_S3DCSEL_M    EQU  0x0000F000  ; Sample 3 Digital Comparator
                                            ; Select
ADC_SSDC0_S2DCSEL_M    EQU  0x00000F00  ; Sample 2 Digital Comparator
                                            ; Select
ADC_SSDC0_S1DCSEL_M    EQU  0x000000F0  ; Sample 1 Digital Comparator
                                            ; Select
ADC_SSDC0_S0DCSEL_M    EQU  0x0000000F  ; Sample 0 Digital Comparator
                                            ; Select
ADC_SSDC0_S6DCSEL_S    EQU   24
ADC_SSDC0_S5DCSEL_S    EQU   20
ADC_SSDC0_S4DCSEL_S    EQU   16
ADC_SSDC0_S3DCSEL_S    EQU   12
ADC_SSDC0_S2DCSEL_S    EQU   8
ADC_SSDC0_S1DCSEL_S    EQU   4
ADC_SSDC0_S0DCSEL_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSMUX1 register.
;
;*************************************************************
ADC_SSMUX1_MUX3_M      EQU  0x0000F000  ; 4th Sample Input Select
ADC_SSMUX1_MUX2_M      EQU  0x00000F00  ; 3rd Sample Input Select
ADC_SSMUX1_MUX1_M      EQU  0x000000F0  ; 2nd Sample Input Select
ADC_SSMUX1_MUX0_M      EQU  0x0000000F  ; 1st Sample Input Select
ADC_SSMUX1_MUX3_S   EQU   12
ADC_SSMUX1_MUX2_S   EQU   8
ADC_SSMUX1_MUX1_S   EQU   4
ADC_SSMUX1_MUX0_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSCTL1 register.
;
;*************************************************************
ADC_SSCTL1_TS3         EQU  0x00008000  ; 4th Sample Temp Sensor Select
ADC_SSCTL1_IE3         EQU  0x00004000  ; 4th Sample Interrupt Enable
ADC_SSCTL1_END3        EQU  0x00002000  ; 4th Sample is End of Sequence
ADC_SSCTL1_D3          EQU  0x00001000  ; 4th Sample Diff Input Select
ADC_SSCTL1_TS2         EQU  0x00000800  ; 3rd Sample Temp Sensor Select
ADC_SSCTL1_IE2         EQU  0x00000400  ; 3rd Sample Interrupt Enable
ADC_SSCTL1_END2        EQU  0x00000200  ; 3rd Sample is End of Sequence
ADC_SSCTL1_D2          EQU  0x00000100  ; 3rd Sample Diff Input Select
ADC_SSCTL1_TS1         EQU  0x00000080  ; 2nd Sample Temp Sensor Select
ADC_SSCTL1_IE1         EQU  0x00000040  ; 2nd Sample Interrupt Enable
ADC_SSCTL1_END1        EQU  0x00000020  ; 2nd Sample is End of Sequence
ADC_SSCTL1_D1          EQU  0x00000010  ; 2nd Sample Diff Input Select
ADC_SSCTL1_TS0         EQU  0x00000008  ; 1st Sample Temp Sensor Select
ADC_SSCTL1_IE0         EQU  0x00000004  ; 1st Sample Interrupt Enable
ADC_SSCTL1_END0        EQU  0x00000002  ; 1st Sample is End of Sequence
ADC_SSCTL1_D0          EQU  0x00000001  ; 1st Sample Diff Input Select

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFIFO1 register.
;
;*************************************************************
ADC_SSFIFO1_DATA_M     EQU  0x00000FFF  ; Conversion Result Data
ADC_SSFIFO1_DATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFSTAT1 register.
;
;*************************************************************
ADC_SSFSTAT1_FULL      EQU  0x00001000  ; FIFO Full
ADC_SSFSTAT1_EMPTY     EQU  0x00000100  ; FIFO Empty
ADC_SSFSTAT1_HPTR_M    EQU  0x000000F0  ; FIFO Head Pointer
ADC_SSFSTAT1_TPTR_M    EQU  0x0000000F  ; FIFO Tail Pointer
ADC_SSFSTAT1_HPTR_S    EQU   4
ADC_SSFSTAT1_TPTR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSOP1 register.
;
;*************************************************************
ADC_SSOP1_S3DCOP       EQU  0x00001000  ; Sample 3 Digital Comparator
                                            ; Operation
ADC_SSOP1_S2DCOP       EQU  0x00000100  ; Sample 2 Digital Comparator
                                            ; Operation
ADC_SSOP1_S1DCOP       EQU  0x00000010  ; Sample 1 Digital Comparator
                                            ; Operation
ADC_SSOP1_S0DCOP       EQU  0x00000001  ; Sample 0 Digital Comparator
                                            ; Operation

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSDC1 register.
;
;*************************************************************
ADC_SSDC1_S3DCSEL_M    EQU  0x0000F000  ; Sample 3 Digital Comparator
                                            ; Select
ADC_SSDC1_S2DCSEL_M    EQU  0x00000F00  ; Sample 2 Digital Comparator
                                            ; Select
ADC_SSDC1_S1DCSEL_M    EQU  0x000000F0  ; Sample 1 Digital Comparator
                                            ; Select
ADC_SSDC1_S0DCSEL_M    EQU  0x0000000F  ; Sample 0 Digital Comparator
                                            ; Select
ADC_SSDC1_S2DCSEL_S    EQU   8
ADC_SSDC1_S1DCSEL_S    EQU   4
ADC_SSDC1_S0DCSEL_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSMUX2 register.
;
;*************************************************************
ADC_SSMUX2_MUX3_M      EQU  0x0000F000  ; 4th Sample Input Select
ADC_SSMUX2_MUX2_M      EQU  0x00000F00  ; 3rd Sample Input Select
ADC_SSMUX2_MUX1_M      EQU  0x000000F0  ; 2nd Sample Input Select
ADC_SSMUX2_MUX0_M      EQU  0x0000000F  ; 1st Sample Input Select
ADC_SSMUX2_MUX3_S   EQU   12
ADC_SSMUX2_MUX2_S   EQU   8
ADC_SSMUX2_MUX1_S   EQU   4
ADC_SSMUX2_MUX0_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSCTL2 register.
;
;*************************************************************
ADC_SSCTL2_TS3         EQU  0x00008000  ; 4th Sample Temp Sensor Select
ADC_SSCTL2_IE3         EQU  0x00004000  ; 4th Sample Interrupt Enable
ADC_SSCTL2_END3        EQU  0x00002000  ; 4th Sample is End of Sequence
ADC_SSCTL2_D3          EQU  0x00001000  ; 4th Sample Diff Input Select
ADC_SSCTL2_TS2         EQU  0x00000800  ; 3rd Sample Temp Sensor Select
ADC_SSCTL2_IE2         EQU  0x00000400  ; 3rd Sample Interrupt Enable
ADC_SSCTL2_END2        EQU  0x00000200  ; 3rd Sample is End of Sequence
ADC_SSCTL2_D2          EQU  0x00000100  ; 3rd Sample Diff Input Select
ADC_SSCTL2_TS1         EQU  0x00000080  ; 2nd Sample Temp Sensor Select
ADC_SSCTL2_IE1         EQU  0x00000040  ; 2nd Sample Interrupt Enable
ADC_SSCTL2_END1        EQU  0x00000020  ; 2nd Sample is End of Sequence
ADC_SSCTL2_D1          EQU  0x00000010  ; 2nd Sample Diff Input Select
ADC_SSCTL2_TS0         EQU  0x00000008  ; 1st Sample Temp Sensor Select
ADC_SSCTL2_IE0         EQU  0x00000004  ; 1st Sample Interrupt Enable
ADC_SSCTL2_END0        EQU  0x00000002  ; 1st Sample is End of Sequence
ADC_SSCTL2_D0          EQU  0x00000001  ; 1st Sample Diff Input Select

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFIFO2 register.
;
;*************************************************************
ADC_SSFIFO2_DATA_M     EQU  0x00000FFF  ; Conversion Result Data
ADC_SSFIFO2_DATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFSTAT2 register.
;
;*************************************************************
ADC_SSFSTAT2_FULL      EQU  0x00001000  ; FIFO Full
ADC_SSFSTAT2_EMPTY     EQU  0x00000100  ; FIFO Empty
ADC_SSFSTAT2_HPTR_M    EQU  0x000000F0  ; FIFO Head Pointer
ADC_SSFSTAT2_TPTR_M    EQU  0x0000000F  ; FIFO Tail Pointer
ADC_SSFSTAT2_HPTR_S    EQU   4
ADC_SSFSTAT2_TPTR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSOP2 register.
;
;*************************************************************
ADC_SSOP2_S3DCOP       EQU  0x00001000  ; Sample 3 Digital Comparator
                                            ; Operation
ADC_SSOP2_S2DCOP       EQU  0x00000100  ; Sample 2 Digital Comparator
                                            ; Operation
ADC_SSOP2_S1DCOP       EQU  0x00000010  ; Sample 1 Digital Comparator
                                            ; Operation
ADC_SSOP2_S0DCOP       EQU  0x00000001  ; Sample 0 Digital Comparator
                                            ; Operation

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSDC2 register.
;
;*************************************************************
ADC_SSDC2_S3DCSEL_M    EQU  0x0000F000  ; Sample 3 Digital Comparator
                                            ; Select
ADC_SSDC2_S2DCSEL_M    EQU  0x00000F00  ; Sample 2 Digital Comparator
                                            ; Select
ADC_SSDC2_S1DCSEL_M    EQU  0x000000F0  ; Sample 1 Digital Comparator
                                            ; Select
ADC_SSDC2_S0DCSEL_M    EQU  0x0000000F  ; Sample 0 Digital Comparator
                                            ; Select
ADC_SSDC2_S2DCSEL_S    EQU   8
ADC_SSDC2_S1DCSEL_S    EQU   4
ADC_SSDC2_S0DCSEL_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSMUX3 register.
;
;*************************************************************
ADC_SSMUX3_MUX0_M      EQU  0x0000000F  ; 1st Sample Input Select
ADC_SSMUX3_MUX0_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSCTL3 register.
;
;*************************************************************
ADC_SSCTL3_TS0         EQU  0x00000008  ; 1st Sample Temp Sensor Select
ADC_SSCTL3_IE0         EQU  0x00000004  ; 1st Sample Interrupt Enable
ADC_SSCTL3_END0        EQU  0x00000002  ; 1st Sample is End of Sequence
ADC_SSCTL3_D0          EQU  0x00000001  ; 1st Sample Diff Input Select

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFIFO3 register.
;
;*************************************************************
ADC_SSFIFO3_DATA_M     EQU  0x00000FFF  ; Conversion Result Data
ADC_SSFIFO3_DATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSFSTAT3 register.
;
;*************************************************************
ADC_SSFSTAT3_FULL      EQU  0x00001000  ; FIFO Full
ADC_SSFSTAT3_EMPTY     EQU  0x00000100  ; FIFO Empty
ADC_SSFSTAT3_HPTR_M    EQU  0x000000F0  ; FIFO Head Pointer
ADC_SSFSTAT3_TPTR_M    EQU  0x0000000F  ; FIFO Tail Pointer
ADC_SSFSTAT3_HPTR_S    EQU   4
ADC_SSFSTAT3_TPTR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSOP3 register.
;
;*************************************************************
ADC_SSOP3_S0DCOP       EQU  0x00000001  ; Sample 0 Digital Comparator
                                            ; Operation

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_SSDC3 register.
;
;*************************************************************
ADC_SSDC3_S0DCSEL_M    EQU  0x0000000F  ; Sample 0 Digital Comparator
                                            ; Select

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCRIC register.
;
;*************************************************************
ADC_DCRIC_DCTRIG7      EQU  0x00800000  ; Digital Comparator Trigger 7
ADC_DCRIC_DCTRIG6      EQU  0x00400000  ; Digital Comparator Trigger 6
ADC_DCRIC_DCTRIG5      EQU  0x00200000  ; Digital Comparator Trigger 5
ADC_DCRIC_DCTRIG4      EQU  0x00100000  ; Digital Comparator Trigger 4
ADC_DCRIC_DCTRIG3      EQU  0x00080000  ; Digital Comparator Trigger 3
ADC_DCRIC_DCTRIG2      EQU  0x00040000  ; Digital Comparator Trigger 2
ADC_DCRIC_DCTRIG1      EQU  0x00020000  ; Digital Comparator Trigger 1
ADC_DCRIC_DCTRIG0      EQU  0x00010000  ; Digital Comparator Trigger 0
ADC_DCRIC_DCINT7       EQU  0x00000080  ; Digital Comparator Interrupt 7
ADC_DCRIC_DCINT6       EQU  0x00000040  ; Digital Comparator Interrupt 6
ADC_DCRIC_DCINT5       EQU  0x00000020  ; Digital Comparator Interrupt 5
ADC_DCRIC_DCINT4       EQU  0x00000010  ; Digital Comparator Interrupt 4
ADC_DCRIC_DCINT3       EQU  0x00000008  ; Digital Comparator Interrupt 3
ADC_DCRIC_DCINT2       EQU  0x00000004  ; Digital Comparator Interrupt 2
ADC_DCRIC_DCINT1       EQU  0x00000002  ; Digital Comparator Interrupt 1
ADC_DCRIC_DCINT0       EQU  0x00000001  ; Digital Comparator Interrupt 0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL0 register.
;
;*************************************************************
ADC_DCCTL0_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL0_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL0_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL0_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL0_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL0_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL0_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL0_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL0_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL0_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL1 register.
;
;*************************************************************
ADC_DCCTL1_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL1_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL1_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL1_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL1_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL1_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL1_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL1_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL1_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL1_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL2 register.
;
;*************************************************************
ADC_DCCTL2_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL2_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL2_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL2_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL2_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL2_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL2_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL2_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL2_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL2_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL3 register.
;
;*************************************************************
ADC_DCCTL3_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL3_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL3_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL3_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL3_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL3_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL3_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL3_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL3_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL3_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL4 register.
;
;*************************************************************
ADC_DCCTL4_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL4_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL4_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL4_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL4_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL4_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL4_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL4_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL4_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL4_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL5 register.
;
;*************************************************************
ADC_DCCTL5_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL5_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL5_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL5_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL5_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL5_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL5_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL5_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL5_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL5_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL6 register.
;
;*************************************************************
ADC_DCCTL6_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL6_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL6_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL6_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL6_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL6_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL6_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL6_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL6_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL6_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCTL7 register.
;
;*************************************************************
ADC_DCCTL7_CIE         EQU  0x00000010  ; Comparison Interrupt Enable
ADC_DCCTL7_CIC_M       EQU  0x0000000C  ; Comparison Interrupt Condition
ADC_DCCTL7_CIC_LOW     EQU  0x00000000  ; Low Band
ADC_DCCTL7_CIC_MID     EQU  0x00000004  ; Mid Band
ADC_DCCTL7_CIC_HIGH    EQU  0x0000000C  ; High Band
ADC_DCCTL7_CIM_M       EQU  0x00000003  ; Comparison Interrupt Mode
ADC_DCCTL7_CIM_ALWAYS  EQU  0x00000000  ; Always
ADC_DCCTL7_CIM_ONCE    EQU  0x00000001  ; Once
ADC_DCCTL7_CIM_HALWAYS EQU  0x00000002  ; Hysteresis Always
ADC_DCCTL7_CIM_HONCE   EQU  0x00000003  ; Hysteresis Once

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP0 register.
;
;*************************************************************
ADC_DCCMP0_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP0_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP0_COMP1_S  EQU   16
ADC_DCCMP0_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP1 register.
;
;*************************************************************
ADC_DCCMP1_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP1_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP1_COMP1_S  EQU   16
ADC_DCCMP1_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP2 register.
;
;*************************************************************
ADC_DCCMP2_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP2_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP2_COMP1_S  EQU   16
ADC_DCCMP2_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP3 register.
;
;*************************************************************
ADC_DCCMP3_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP3_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP3_COMP1_S  EQU   16
ADC_DCCMP3_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP4 register.
;
;*************************************************************
ADC_DCCMP4_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP4_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP4_COMP1_S  EQU   16
ADC_DCCMP4_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP5 register.
;
;*************************************************************
ADC_DCCMP5_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP5_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP5_COMP1_S  EQU   16
ADC_DCCMP5_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP6 register.
;
;*************************************************************
ADC_DCCMP6_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP6_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP6_COMP1_S  EQU   16
ADC_DCCMP6_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_DCCMP7 register.
;
;*************************************************************
ADC_DCCMP7_COMP1_M     EQU  0x0FFF0000  ; Compare 1
ADC_DCCMP7_COMP0_M     EQU  0x00000FFF  ; Compare 0
ADC_DCCMP7_COMP1_S  EQU   16
ADC_DCCMP7_COMP0_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_PP register.
;
;*************************************************************
ADC_PP_TS              EQU  0x00800000  ; Temperature Sensor
ADC_PP_RSL_M           EQU  0x007C0000  ; Resolution
ADC_PP_TYPE_M          EQU  0x00030000  ; ADC Architecture
ADC_PP_TYPE_SAR        EQU  0x00000000  ; SAR
ADC_PP_DC_M            EQU  0x0000FC00  ; Digital Comparator Count
ADC_PP_CH_M            EQU  0x000003F0  ; ADC Channel Count
ADC_PP_MSR_M           EQU  0x0000000F  ; Maximum ADC Sample Rate
ADC_PP_MSR_125K        EQU  0x00000001  ; 125 ksps
ADC_PP_MSR_250K        EQU  0x00000003  ; 250 ksps
ADC_PP_MSR_500K        EQU  0x00000005  ; 500 ksps
ADC_PP_MSR_1M          EQU  0x00000007  ; 1 Msps
ADC_PP_RSL_S    EQU          18
ADC_PP_DC_S    EQU           10
ADC_PP_CH_S         EQU   4

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_PC register.
;
;*************************************************************
ADC_PC_SR_M            EQU  0x0000000F  ; ADC Sample Rate
ADC_PC_SR_125K         EQU  0x00000001  ; 125 ksps
ADC_PC_SR_250K         EQU  0x00000003  ; 250 ksps
ADC_PC_SR_500K         EQU  0x00000005  ; 500 ksps
ADC_PC_SR_1M           EQU  0x00000007  ; 1 Msps

;*************************************************************
;
; The following are defines for the bit fields in the ADC_O_CC register.
;
;*************************************************************
ADC_CC_CS_M            EQU  0x0000000F  ; ADC Clock Source
ADC_CC_CS_SYSPLL       EQU  0x00000000  ; Either the system clock (if the
                                            ; PLL bypass is in effect) or the
                                            ; 16 MHz clock derived from PLL /
                                            ; 25 (default)
ADC_CC_CS_PIOSC        EQU  0x00000001  ; PIOSC

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACMIS register.
;
;*************************************************************
COMP_ACMIS_IN1         EQU  0x00000002  ; Comparator 1 Masked Interrupt
                                            ; Status
COMP_ACMIS_IN0         EQU  0x00000001  ; Comparator 0 Masked Interrupt
                                            ; Status

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACRIS register.
;
;*************************************************************
COMP_ACRIS_IN1         EQU  0x00000002  ; Comparator 1 Interrupt Status
COMP_ACRIS_IN0         EQU  0x00000001  ; Comparator 0 Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACINTEN register.
;
;*************************************************************
COMP_ACINTEN_IN1       EQU  0x00000002  ; Comparator 1 Interrupt Enable
COMP_ACINTEN_IN0       EQU  0x00000001  ; Comparator 0 Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACREFCTL
; register.
;
;*************************************************************
COMP_ACREFCTL_EN       EQU  0x00000200  ; Resistor Ladder Enable
COMP_ACREFCTL_RNG      EQU  0x00000100  ; Resistor Ladder Range
COMP_ACREFCTL_VREF_M   EQU  0x0000000F  ; Resistor Ladder Voltage Ref
COMP_ACREFCTL_VREF_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACSTAT0 register.
;
;*************************************************************
COMP_ACSTAT0_OVAL      EQU  0x00000002  ; Comparator Output Value

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACCTL0 register.
;
;*************************************************************
COMP_ACCTL0_TOEN       EQU  0x00000800  ; Trigger Output Enable
COMP_ACCTL0_ASRCP_M    EQU  0x00000600  ; Analog Source Positive
COMP_ACCTL0_ASRCP_PIN  EQU  0x00000000  ; Pin value of Cn+
COMP_ACCTL0_ASRCP_PIN0 EQU  0x00000200  ; Pin value of C0+
COMP_ACCTL0_ASRCP_REF  EQU  0x00000400  ; Internal voltage reference
COMP_ACCTL0_TSLVAL     EQU  0x00000080  ; Trigger Sense Level Value
COMP_ACCTL0_TSEN_M     EQU  0x00000060  ; Trigger Sense
COMP_ACCTL0_TSEN_LEVEL EQU  0x00000000  ; Level sense, see TSLVAL
COMP_ACCTL0_TSEN_FALL  EQU  0x00000020  ; Falling edge
COMP_ACCTL0_TSEN_RISE  EQU  0x00000040  ; Rising edge
COMP_ACCTL0_TSEN_BOTH  EQU  0x00000060  ; Either edge
COMP_ACCTL0_ISLVAL     EQU  0x00000010  ; Interrupt Sense Level Value
COMP_ACCTL0_ISEN_M     EQU  0x0000000C  ; Interrupt Sense
COMP_ACCTL0_ISEN_LEVEL EQU  0x00000000  ; Level sense, see ISLVAL
COMP_ACCTL0_ISEN_FALL  EQU  0x00000004  ; Falling edge
COMP_ACCTL0_ISEN_RISE  EQU  0x00000008  ; Rising edge
COMP_ACCTL0_ISEN_BOTH  EQU  0x0000000C  ; Either edge
COMP_ACCTL0_CINV       EQU  0x00000002  ; Comparator Output Invert

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACSTAT1 register.
;
;*************************************************************
COMP_ACSTAT1_OVAL      EQU  0x00000002  ; Comparator Output Value

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_ACCTL1 register.
;
;*************************************************************
COMP_ACCTL1_TOEN       EQU  0x00000800  ; Trigger Output Enable
COMP_ACCTL1_ASRCP_M    EQU  0x00000600  ; Analog Source Positive
COMP_ACCTL1_ASRCP_PIN  EQU  0x00000000  ; Pin value of Cn+
COMP_ACCTL1_ASRCP_PIN0 EQU  0x00000200  ; Pin value of C0+
COMP_ACCTL1_ASRCP_REF  EQU  0x00000400  ; Internal voltage reference
                                            ; (VIREF)
COMP_ACCTL1_TSLVAL     EQU  0x00000080  ; Trigger Sense Level Value
COMP_ACCTL1_TSEN_M     EQU  0x00000060  ; Trigger Sense
COMP_ACCTL1_TSEN_LEVEL EQU  0x00000000  ; Level sense, see TSLVAL
COMP_ACCTL1_TSEN_FALL  EQU  0x00000020  ; Falling edge
COMP_ACCTL1_TSEN_RISE  EQU  0x00000040  ; Rising edge
COMP_ACCTL1_TSEN_BOTH  EQU  0x00000060  ; Either edge
COMP_ACCTL1_ISLVAL     EQU  0x00000010  ; Interrupt Sense Level Value
COMP_ACCTL1_ISEN_M     EQU  0x0000000C  ; Interrupt Sense
COMP_ACCTL1_ISEN_LEVEL EQU  0x00000000  ; Level sense, see ISLVAL
COMP_ACCTL1_ISEN_FALL  EQU  0x00000004  ; Falling edge
COMP_ACCTL1_ISEN_RISE  EQU  0x00000008  ; Rising edge
COMP_ACCTL1_ISEN_BOTH  EQU  0x0000000C  ; Either edge
COMP_ACCTL1_CINV       EQU  0x00000002  ; Comparator Output Invert

;*************************************************************
;
; The following are defines for the bit fields in the COMP_O_PP register.
;
;*************************************************************
COMP_PP_C2O            EQU  0x00040000  ; Comparator Output 2 Present
COMP_PP_C1O            EQU  0x00020000  ; Comparator Output 1 Present
COMP_PP_C0O            EQU  0x00010000  ; Comparator Output 0 Present
COMP_PP_CMP2           EQU  0x00000004  ; Comparator 2 Present
COMP_PP_CMP1           EQU  0x00000002  ; Comparator 1 Present
COMP_PP_CMP0           EQU  0x00000001  ; Comparator 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_CTL register.
;
;*************************************************************
CAN_CTL_TEST           EQU  0x00000080  ; Test Mode Enable
CAN_CTL_CCE            EQU  0x00000040  ; Configuration Change Enable
CAN_CTL_DAR            EQU  0x00000020  ; Disable Automatic-Retransmission
CAN_CTL_EIE            EQU  0x00000008  ; Error Interrupt Enable
CAN_CTL_SIE            EQU  0x00000004  ; Status Interrupt Enable
CAN_CTL_IE             EQU  0x00000002  ; CAN Interrupt Enable
CAN_CTL_INIT           EQU  0x00000001  ; Initialization

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_STS register.
;
;*************************************************************
CAN_STS_BOFF           EQU  0x00000080  ; Bus-Off Status
CAN_STS_EWARN          EQU  0x00000040  ; Warning Status
CAN_STS_EPASS          EQU  0x00000020  ; Error Passive
CAN_STS_RXOK           EQU  0x00000010  ; Received a Message Successfully
CAN_STS_TXOK           EQU  0x00000008  ; Transmitted a Message
                                            ; Successfully
CAN_STS_LEC_M          EQU  0x00000007  ; Last Error Code
CAN_STS_LEC_NONE       EQU  0x00000000  ; No Error
CAN_STS_LEC_STUFF      EQU  0x00000001  ; Stuff Error
CAN_STS_LEC_FORM       EQU  0x00000002  ; Format Error
CAN_STS_LEC_ACK        EQU  0x00000003  ; ACK Error
CAN_STS_LEC_BIT1       EQU  0x00000004  ; Bit 1 Error
CAN_STS_LEC_BIT0       EQU  0x00000005  ; Bit 0 Error
CAN_STS_LEC_CRC        EQU  0x00000006  ; CRC Error
CAN_STS_LEC_NOEVENT    EQU  0x00000007  ; No Event

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_ERR register.
;
;*************************************************************
CAN_ERR_RP             EQU  0x00008000  ; Received Error Passive
CAN_ERR_REC_M          EQU  0x00007F00  ; Receive Error Counter
CAN_ERR_TEC_M          EQU  0x000000FF  ; Transmit Error Counter
CAN_ERR_REC_S       EQU   8
CAN_ERR_TEC_S       EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_BIT register.
;
;*************************************************************
CAN_BIT_TSEG2_M        EQU  0x00007000  ; Time Segment after Sample Point
CAN_BIT_TSEG1_M        EQU  0x00000F00  ; Time Segment Before Sample Point
CAN_BIT_SJW_M          EQU  0x000000C0  ; (Re)Synchronization Jump Width
CAN_BIT_BRP_M          EQU  0x0000003F  ; Baud Rate Prescaler
CAN_BIT_TSEG2_S     EQU   12
CAN_BIT_TSEG1_S     EQU   8
CAN_BIT_SJW_S    EQU         6
CAN_BIT_BRP_S       EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_INT register.
;
;*************************************************************
CAN_INT_INTID_M        EQU  0x0000FFFF  ; Interrupt Identifier
CAN_INT_INTID_NONE     EQU  0x00000000  ; No interrupt pending
CAN_INT_INTID_STATUS   EQU  0x00008000  ; Status Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_TST register.
;
;*************************************************************
CAN_TST_RX             EQU  0x00000080  ; Receive Observation
CAN_TST_TX_M           EQU  0x00000060  ; Transmit Control
CAN_TST_TX_CANCTL      EQU  0x00000000  ; CAN Module Control
CAN_TST_TX_SAMPLE      EQU  0x00000020  ; Sample Point
CAN_TST_TX_DOMINANT    EQU  0x00000040  ; Driven Low
CAN_TST_TX_RECESSIVE   EQU  0x00000060  ; Driven High
CAN_TST_LBACK          EQU  0x00000010  ; Loopback Mode
CAN_TST_SILENT         EQU  0x00000008  ; Silent Mode
CAN_TST_BASIC          EQU  0x00000004  ; Basic Mode

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_BRPE register.
;
;*************************************************************
CAN_BRPE_BRPE_M        EQU  0x0000000F  ; Baud Rate Prescaler Extension
CAN_BRPE_BRPE_S     EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1CRQ register.
;
;*************************************************************
CAN_IF1CRQ_BUSY        EQU  0x00008000  ; Busy Flag
CAN_IF1CRQ_MNUM_M      EQU  0x0000003F  ; Message Number
CAN_IF1CRQ_MNUM_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1CMSK register.
;
;*************************************************************
CAN_IF1CMSK_WRNRD      EQU  0x00000080  ; Write, Not Read
CAN_IF1CMSK_MASK       EQU  0x00000040  ; Access Mask Bits
CAN_IF1CMSK_ARB        EQU  0x00000020  ; Access Arbitration Bits
CAN_IF1CMSK_CONTROL    EQU  0x00000010  ; Access Control Bits
CAN_IF1CMSK_CLRINTPND  EQU  0x00000008  ; Clear Interrupt Pending Bit
CAN_IF1CMSK_NEWDAT     EQU  0x00000004  ; Access New Data
CAN_IF1CMSK_TXRQST     EQU  0x00000004  ; Access Transmission Request
CAN_IF1CMSK_DATAA      EQU  0x00000002  ; Access Data Byte 0 to 3
CAN_IF1CMSK_DATAB      EQU  0x00000001  ; Access Data Byte 4 to 7

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1MSK1 register.
;
;*************************************************************
CAN_IF1MSK1_IDMSK_M    EQU  0x0000FFFF  ; Identifier Mask
CAN_IF1MSK1_IDMSK_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1MSK2 register.
;
;*************************************************************
CAN_IF1MSK2_MXTD       EQU  0x00008000  ; Mask Extended Identifier
CAN_IF1MSK2_MDIR       EQU  0x00004000  ; Mask Message Direction
CAN_IF1MSK2_IDMSK_M    EQU  0x00001FFF  ; Identifier Mask
CAN_IF1MSK2_IDMSK_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1ARB1 register.
;
;*************************************************************
CAN_IF1ARB1_ID_M       EQU  0x0000FFFF  ; Message Identifier
CAN_IF1ARB1_ID_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1ARB2 register.
;
;*************************************************************
CAN_IF1ARB2_MSGVAL     EQU  0x00008000  ; Message Valid
CAN_IF1ARB2_XTD        EQU  0x00004000  ; Extended Identifier
CAN_IF1ARB2_DIR        EQU  0x00002000  ; Message Direction
CAN_IF1ARB2_ID_M       EQU  0x00001FFF  ; Message Identifier
CAN_IF1ARB2_ID_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1MCTL register.
;
;*************************************************************
CAN_IF1MCTL_NEWDAT     EQU  0x00008000  ; New Data
CAN_IF1MCTL_MSGLST     EQU  0x00004000  ; Message Lost
CAN_IF1MCTL_INTPND     EQU  0x00002000  ; Interrupt Pending
CAN_IF1MCTL_UMASK      EQU  0x00001000  ; Use Acceptance Mask
CAN_IF1MCTL_TXIE       EQU  0x00000800  ; Transmit Interrupt Enable
CAN_IF1MCTL_RXIE       EQU  0x00000400  ; Receive Interrupt Enable
CAN_IF1MCTL_RMTEN      EQU  0x00000200  ; Remote Enable
CAN_IF1MCTL_TXRQST     EQU  0x00000100  ; Transmit Request
CAN_IF1MCTL_EOB        EQU  0x00000080  ; End of Buffer
CAN_IF1MCTL_DLC_M      EQU  0x0000000F  ; Data Length Code
CAN_IF1MCTL_DLC_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1DA1 register.
;
;*************************************************************
CAN_IF1DA1_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF1DA1_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1DA2 register.
;
;*************************************************************
CAN_IF1DA2_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF1DA2_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1DB1 register.
;
;*************************************************************
CAN_IF1DB1_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF1DB1_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF1DB2 register.
;
;*************************************************************
CAN_IF1DB2_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF1DB2_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2CRQ register.
;
;*************************************************************
CAN_IF2CRQ_BUSY        EQU  0x00008000  ; Busy Flag
CAN_IF2CRQ_MNUM_M      EQU  0x0000003F  ; Message Number
CAN_IF2CRQ_MNUM_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2CMSK register.
;
;*************************************************************
CAN_IF2CMSK_WRNRD      EQU  0x00000080  ; Write, Not Read
CAN_IF2CMSK_MASK       EQU  0x00000040  ; Access Mask Bits
CAN_IF2CMSK_ARB        EQU  0x00000020  ; Access Arbitration Bits
CAN_IF2CMSK_CONTROL    EQU  0x00000010  ; Access Control Bits
CAN_IF2CMSK_CLRINTPND  EQU  0x00000008  ; Clear Interrupt Pending Bit
CAN_IF2CMSK_NEWDAT     EQU  0x00000004  ; Access New Data
CAN_IF2CMSK_TXRQST     EQU  0x00000004  ; Access Transmission Request
CAN_IF2CMSK_DATAA      EQU  0x00000002  ; Access Data Byte 0 to 3
CAN_IF2CMSK_DATAB      EQU  0x00000001  ; Access Data Byte 4 to 7

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2MSK1 register.
;
;*************************************************************
CAN_IF2MSK1_IDMSK_M    EQU  0x0000FFFF  ; Identifier Mask
CAN_IF2MSK1_IDMSK_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2MSK2 register.
;
;*************************************************************
CAN_IF2MSK2_MXTD       EQU  0x00008000  ; Mask Extended Identifier
CAN_IF2MSK2_MDIR       EQU  0x00004000  ; Mask Message Direction
CAN_IF2MSK2_IDMSK_M    EQU  0x00001FFF  ; Identifier Mask
CAN_IF2MSK2_IDMSK_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2ARB1 register.
;
;*************************************************************
CAN_IF2ARB1_ID_M       EQU  0x0000FFFF  ; Message Identifier
CAN_IF2ARB1_ID_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2ARB2 register.
;
;*************************************************************
CAN_IF2ARB2_MSGVAL     EQU  0x00008000  ; Message Valid
CAN_IF2ARB2_XTD        EQU  0x00004000  ; Extended Identifier
CAN_IF2ARB2_DIR        EQU  0x00002000  ; Message Direction
CAN_IF2ARB2_ID_M       EQU  0x00001FFF  ; Message Identifier
CAN_IF2ARB2_ID_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2MCTL register.
;
;*************************************************************
CAN_IF2MCTL_NEWDAT     EQU  0x00008000  ; New Data
CAN_IF2MCTL_MSGLST     EQU  0x00004000  ; Message Lost
CAN_IF2MCTL_INTPND     EQU  0x00002000  ; Interrupt Pending
CAN_IF2MCTL_UMASK      EQU  0x00001000  ; Use Acceptance Mask
CAN_IF2MCTL_TXIE       EQU  0x00000800  ; Transmit Interrupt Enable
CAN_IF2MCTL_RXIE       EQU  0x00000400  ; Receive Interrupt Enable
CAN_IF2MCTL_RMTEN      EQU  0x00000200  ; Remote Enable
CAN_IF2MCTL_TXRQST     EQU  0x00000100  ; Transmit Request
CAN_IF2MCTL_EOB        EQU  0x00000080  ; End of Buffer
CAN_IF2MCTL_DLC_M      EQU  0x0000000F  ; Data Length Code
CAN_IF2MCTL_DLC_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2DA1 register.
;
;*************************************************************
CAN_IF2DA1_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF2DA1_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2DA2 register.
;
;*************************************************************
CAN_IF2DA2_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF2DA2_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2DB1 register.
;
;*************************************************************
CAN_IF2DB1_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF2DB1_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_IF2DB2 register.
;
;*************************************************************
CAN_IF2DB2_DATA_M      EQU  0x0000FFFF  ; Data
CAN_IF2DB2_DATA_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_TXRQ1 register.
;
;*************************************************************
CAN_TXRQ1_TXRQST_M     EQU  0x0000FFFF  ; Transmission Request Bits
CAN_TXRQ1_TXRQST_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_TXRQ2 register.
;
;*************************************************************
CAN_TXRQ2_TXRQST_M     EQU  0x0000FFFF  ; Transmission Request Bits
CAN_TXRQ2_TXRQST_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_NWDA1 register.
;
;*************************************************************
CAN_NWDA1_NEWDAT_M     EQU  0x0000FFFF  ; New Data Bits
CAN_NWDA1_NEWDAT_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_NWDA2 register.
;
;*************************************************************
CAN_NWDA2_NEWDAT_M     EQU  0x0000FFFF  ; New Data Bits
CAN_NWDA2_NEWDAT_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_MSG1INT register.
;
;*************************************************************
CAN_MSG1INT_INTPND_M   EQU  0x0000FFFF  ; Interrupt Pending Bits
CAN_MSG1INT_INTPND_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_MSG2INT register.
;
;*************************************************************
CAN_MSG2INT_INTPND_M   EQU  0x0000FFFF  ; Interrupt Pending Bits
CAN_MSG2INT_INTPND_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_MSG1VAL register.
;
;*************************************************************
CAN_MSG1VAL_MSGVAL_M   EQU  0x0000FFFF  ; Message Valid Bits
CAN_MSG1VAL_MSGVAL_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the CAN_O_MSG2VAL register.
;
;*************************************************************
CAN_MSG2VAL_MSGVAL_M   EQU  0x0000FFFF  ; Message Valid Bits
CAN_MSG2VAL_MSGVAL_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FADDR register.
;
;*************************************************************
USB_FADDR_M            EQU  0x0000007F  ; Function Address
USB_FADDR_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_POWER register.
;
;*************************************************************
USB_POWER_ISOUP        EQU  0x00000080  ; Isochronous Update
USB_POWER_SOFTCONN     EQU  0x00000040  ; Soft Connect/Disconnect
USB_POWER_RESET        EQU  0x00000008  ; RESET Signaling
USB_POWER_RESUME       EQU  0x00000004  ; RESUME Signaling
USB_POWER_SUSPEND      EQU  0x00000002  ; SUSPEND Mode
USB_POWER_PWRDNPHY     EQU  0x00000001  ; Power Down PHY

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXIS register.
;
;*************************************************************
USB_TXIS_EP7           EQU  0x00000080  ; TX Endpoint 7 Interrupt
USB_TXIS_EP6           EQU  0x00000040  ; TX Endpoint 6 Interrupt
USB_TXIS_EP5           EQU  0x00000020  ; TX Endpoint 5 Interrupt
USB_TXIS_EP4           EQU  0x00000010  ; TX Endpoint 4 Interrupt
USB_TXIS_EP3           EQU  0x00000008  ; TX Endpoint 3 Interrupt
USB_TXIS_EP2           EQU  0x00000004  ; TX Endpoint 2 Interrupt
USB_TXIS_EP1           EQU  0x00000002  ; TX Endpoint 1 Interrupt
USB_TXIS_EP0           EQU  0x00000001  ; TX and RX Endpoint 0 Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXIS register.
;
;*************************************************************
USB_RXIS_EP7           EQU  0x00000080  ; RX Endpoint 7 Interrupt
USB_RXIS_EP6           EQU  0x00000040  ; RX Endpoint 6 Interrupt
USB_RXIS_EP5           EQU  0x00000020  ; RX Endpoint 5 Interrupt
USB_RXIS_EP4           EQU  0x00000010  ; RX Endpoint 4 Interrupt
USB_RXIS_EP3           EQU  0x00000008  ; RX Endpoint 3 Interrupt
USB_RXIS_EP2           EQU  0x00000004  ; RX Endpoint 2 Interrupt
USB_RXIS_EP1           EQU  0x00000002  ; RX Endpoint 1 Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXIE register.
;
;*************************************************************
USB_TXIE_EP7           EQU  0x00000080  ; TX Endpoint 7 Interrupt Enable
USB_TXIE_EP6           EQU  0x00000040  ; TX Endpoint 6 Interrupt Enable
USB_TXIE_EP5           EQU  0x00000020  ; TX Endpoint 5 Interrupt Enable
USB_TXIE_EP4           EQU  0x00000010  ; TX Endpoint 4 Interrupt Enable
USB_TXIE_EP3           EQU  0x00000008  ; TX Endpoint 3 Interrupt Enable
USB_TXIE_EP2           EQU  0x00000004  ; TX Endpoint 2 Interrupt Enable
USB_TXIE_EP1           EQU  0x00000002  ; TX Endpoint 1 Interrupt Enable
USB_TXIE_EP0           EQU  0x00000001  ; TX and RX Endpoint 0 Interrupt
                                            ; Enable

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXIE register.
;
;*************************************************************
USB_RXIE_EP7           EQU  0x00000080  ; RX Endpoint 7 Interrupt Enable
USB_RXIE_EP6           EQU  0x00000040  ; RX Endpoint 6 Interrupt Enable
USB_RXIE_EP5           EQU  0x00000020  ; RX Endpoint 5 Interrupt Enable
USB_RXIE_EP4           EQU  0x00000010  ; RX Endpoint 4 Interrupt Enable
USB_RXIE_EP3           EQU  0x00000008  ; RX Endpoint 3 Interrupt Enable
USB_RXIE_EP2           EQU  0x00000004  ; RX Endpoint 2 Interrupt Enable
USB_RXIE_EP1           EQU  0x00000002  ; RX Endpoint 1 Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_IS register.
;
;*************************************************************
USB_IS_DISCON          EQU  0x00000020  ; Session Disconnect
USB_IS_SOF             EQU  0x00000008  ; Start of Frame
USB_IS_RESET           EQU  0x00000004  ; RESET Signaling Detected
USB_IS_RESUME          EQU  0x00000002  ; RESUME Signaling Detected
USB_IS_SUSPEND         EQU  0x00000001  ; SUSPEND Signaling Detected

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_IE register.
;
;*************************************************************
USB_IE_DISCON          EQU  0x00000020  ; Enable Disconnect Interrupt
USB_IE_SOF             EQU  0x00000008  ; Enable Start-of-Frame Interrupt
USB_IE_RESET           EQU  0x00000004  ; Enable RESET Interrupt
USB_IE_RESUME          EQU  0x00000002  ; Enable RESUME Interrupt
USB_IE_SUSPND          EQU  0x00000001  ; Enable SUSPEND Interrupt

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FRAME register.
;
;*************************************************************
USB_FRAME_M            EQU  0x000007FF  ; Frame Number
USB_FRAME_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_EPIDX register.
;
;*************************************************************
USB_EPIDX_EPIDX_M      EQU  0x0000000F  ; Endpoint Index
USB_EPIDX_EPIDX_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TEST register.
;
;*************************************************************
USB_TEST_FIFOACC       EQU  0x00000040  ; FIFO Access
USB_TEST_FORCEFS       EQU  0x00000020  ; Force Full-Speed Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO0 register.
;
;*************************************************************
USB_FIFO0_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO0_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO1 register.
;
;*************************************************************
USB_FIFO1_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO1_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO2 register.
;
;*************************************************************
USB_FIFO2_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO2_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO3 register.
;
;*************************************************************
USB_FIFO3_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO3_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO4 register.
;
;*************************************************************
USB_FIFO4_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO4_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO5 register.
;
;*************************************************************
USB_FIFO5_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO5_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO6 register.
;
;*************************************************************
USB_FIFO6_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO6_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FIFO7 register.
;
;*************************************************************
USB_FIFO7_EPDATA_M     EQU  0xFFFFFFFF  ; Endpoint Data
USB_FIFO7_EPDATA_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXFIFOSZ register.
;
;*************************************************************
USB_TXFIFOSZ_DPB       EQU  0x00000010  ; Double Packet Buffer Support
USB_TXFIFOSZ_SIZE_M    EQU  0x0000000F  ; Max Packet Size
USB_TXFIFOSZ_SIZE_8    EQU  0x00000000  ; 8
USB_TXFIFOSZ_SIZE_16   EQU  0x00000001  ; 16
USB_TXFIFOSZ_SIZE_32   EQU  0x00000002  ; 32
USB_TXFIFOSZ_SIZE_64   EQU  0x00000003  ; 64
USB_TXFIFOSZ_SIZE_128  EQU  0x00000004  ; 128
USB_TXFIFOSZ_SIZE_256  EQU  0x00000005  ; 256
USB_TXFIFOSZ_SIZE_512  EQU  0x00000006  ; 512
USB_TXFIFOSZ_SIZE_1024 EQU  0x00000007  ; 1024
USB_TXFIFOSZ_SIZE_2048 EQU  0x00000008  ; 2048

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXFIFOSZ register.
;
;*************************************************************
USB_RXFIFOSZ_DPB       EQU  0x00000010  ; Double Packet Buffer Support
USB_RXFIFOSZ_SIZE_M    EQU  0x0000000F  ; Max Packet Size
USB_RXFIFOSZ_SIZE_8    EQU  0x00000000  ; 8
USB_RXFIFOSZ_SIZE_16   EQU  0x00000001  ; 16
USB_RXFIFOSZ_SIZE_32   EQU  0x00000002  ; 32
USB_RXFIFOSZ_SIZE_64   EQU  0x00000003  ; 64
USB_RXFIFOSZ_SIZE_128  EQU  0x00000004  ; 128
USB_RXFIFOSZ_SIZE_256  EQU  0x00000005  ; 256
USB_RXFIFOSZ_SIZE_512  EQU  0x00000006  ; 512
USB_RXFIFOSZ_SIZE_1024 EQU  0x00000007  ; 1024
USB_RXFIFOSZ_SIZE_2048 EQU  0x00000008  ; 2048

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXFIFOADD
; register.
;
;*************************************************************
USB_TXFIFOADD_ADDR_M   EQU  0x000001FF  ; Transmit/Receive Start Address
USB_TXFIFOADD_ADDR_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXFIFOADD
; register.
;
;*************************************************************
USB_RXFIFOADD_ADDR_M   EQU  0x000001FF  ; Transmit/Receive Start Address
USB_RXFIFOADD_ADDR_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_CONTIM register.
;
;*************************************************************
USB_CONTIM_WTCON_M     EQU  0x000000F0  ; Connect Wait
USB_CONTIM_WTID_M      EQU  0x0000000F  ; Wait ID
USB_CONTIM_WTCON_S  EQU   4
USB_CONTIM_WTID_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_FSEOF register.
;
;*************************************************************
USB_FSEOF_FSEOFG_M     EQU  0x000000FF  ; Full-Speed End-of-Frame Gap
USB_FSEOF_FSEOFG_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_LSEOF register.
;
;*************************************************************
USB_LSEOF_LSEOFG_M     EQU  0x000000FF  ; Low-Speed End-of-Frame Gap
USB_LSEOF_LSEOFG_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_CSRL0 register.
;
;*************************************************************
USB_CSRL0_SETENDC      EQU  0x00000080  ; Setup End Clear
USB_CSRL0_RXRDYC       EQU  0x00000040  ; RXRDY Clear
USB_CSRL0_STALL        EQU  0x00000020  ; Send Stall
USB_CSRL0_SETEND       EQU  0x00000010  ; Setup End
USB_CSRL0_DATAEND      EQU  0x00000008  ; Data End
USB_CSRL0_STALLED      EQU  0x00000004  ; Endpoint Stalled
USB_CSRL0_TXRDY        EQU  0x00000002  ; Transmit Packet Ready
USB_CSRL0_RXRDY        EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_CSRH0 register.
;
;*************************************************************
USB_CSRH0_FLUSH        EQU  0x00000001  ; Flush FIFO

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_COUNT0 register.
;
;*************************************************************
USB_COUNT0_COUNT_M     EQU  0x0000007F  ; FIFO Count
USB_COUNT0_COUNT_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP1 register.
;
;*************************************************************
USB_TXMAXP1_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP1_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL1 register.
;
;*************************************************************
USB_TXCSRL1_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL1_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL1_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL1_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL1_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL1_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL1_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH1 register.
;
;*************************************************************
USB_TXCSRH1_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH1_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH1_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH1_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH1_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH1_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP1 register.
;
;*************************************************************
USB_RXMAXP1_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP1_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL1 register.
;
;*************************************************************
USB_RXCSRL1_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL1_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL1_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL1_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL1_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL1_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL1_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL1_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH1 register.
;
;*************************************************************
USB_RXCSRH1_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH1_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH1_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH1_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH1_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH1_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT1 register.
;
;*************************************************************
USB_RXCOUNT1_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT1_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP2 register.
;
;*************************************************************
USB_TXMAXP2_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP2_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL2 register.
;
;*************************************************************
USB_TXCSRL2_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL2_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL2_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL2_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL2_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL2_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL2_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH2 register.
;
;*************************************************************
USB_TXCSRH2_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH2_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH2_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH2_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH2_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH2_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP2 register.
;
;*************************************************************
USB_RXMAXP2_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP2_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL2 register.
;
;*************************************************************
USB_RXCSRL2_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL2_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL2_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL2_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL2_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL2_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL2_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL2_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH2 register.
;
;*************************************************************
USB_RXCSRH2_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH2_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH2_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH2_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH2_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH2_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT2 register.
;
;*************************************************************
USB_RXCOUNT2_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT2_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP3 register.
;
;*************************************************************
USB_TXMAXP3_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP3_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL3 register.
;
;*************************************************************
USB_TXCSRL3_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL3_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL3_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL3_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL3_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL3_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL3_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH3 register.
;
;*************************************************************
USB_TXCSRH3_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH3_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH3_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH3_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH3_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH3_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP3 register.
;
;*************************************************************
USB_RXMAXP3_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP3_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL3 register.
;
;*************************************************************
USB_RXCSRL3_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL3_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL3_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL3_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL3_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL3_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL3_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL3_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH3 register.
;
;*************************************************************
USB_RXCSRH3_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH3_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH3_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH3_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH3_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH3_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT3 register.
;
;*************************************************************
USB_RXCOUNT3_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT3_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP4 register.
;
;*************************************************************
USB_TXMAXP4_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP4_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL4 register.
;
;*************************************************************
USB_TXCSRL4_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL4_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL4_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL4_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL4_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL4_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL4_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH4 register.
;
;*************************************************************
USB_TXCSRH4_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH4_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH4_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH4_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH4_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH4_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP4 register.
;
;*************************************************************
USB_RXMAXP4_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP4_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL4 register.
;
;*************************************************************
USB_RXCSRL4_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL4_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL4_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL4_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL4_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL4_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL4_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL4_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH4 register.
;
;*************************************************************
USB_RXCSRH4_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH4_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH4_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH4_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH4_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH4_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT4 register.
;
;*************************************************************
USB_RXCOUNT4_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT4_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP5 register.
;
;*************************************************************
USB_TXMAXP5_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP5_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL5 register.
;
;*************************************************************
USB_TXCSRL5_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL5_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL5_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL5_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL5_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL5_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL5_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH5 register.
;
;*************************************************************
USB_TXCSRH5_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH5_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH5_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH5_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH5_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH5_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP5 register.
;
;*************************************************************
USB_RXMAXP5_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP5_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL5 register.
;
;*************************************************************
USB_RXCSRL5_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL5_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL5_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL5_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL5_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL5_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL5_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL5_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH5 register.
;
;*************************************************************
USB_RXCSRH5_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH5_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH5_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH5_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH5_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH5_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT5 register.
;
;*************************************************************
USB_RXCOUNT5_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT5_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP6 register.
;
;*************************************************************
USB_TXMAXP6_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP6_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL6 register.
;
;*************************************************************
USB_TXCSRL6_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL6_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL6_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL6_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL6_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL6_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL6_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH6 register.
;
;*************************************************************
USB_TXCSRH6_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH6_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH6_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH6_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH6_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH6_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP6 register.
;
;*************************************************************
USB_RXMAXP6_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP6_MAXLOAD_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL6 register.
;
;*************************************************************
USB_RXCSRL6_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL6_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL6_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL6_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL6_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL6_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL6_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL6_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH6 register.
;
;*************************************************************
USB_RXCSRH6_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH6_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH6_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH6_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH6_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH6_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT6 register.
;
;*************************************************************
USB_RXCOUNT6_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT6_COUNT_S   EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXMAXP7 register.
;
;*************************************************************
USB_TXMAXP7_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_TXMAXP7_MAXLOAD_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRL7 register.
;
;*************************************************************
USB_TXCSRL7_CLRDT      EQU  0x00000040  ; Clear Data Toggle
USB_TXCSRL7_STALLED    EQU  0x00000020  ; Endpoint Stalled
USB_TXCSRL7_STALL      EQU  0x00000010  ; Send STALL
USB_TXCSRL7_FLUSH      EQU  0x00000008  ; Flush FIFO
USB_TXCSRL7_UNDRN      EQU  0x00000004  ; Underrun
USB_TXCSRL7_FIFONE     EQU  0x00000002  ; FIFO Not Empty
USB_TXCSRL7_TXRDY      EQU  0x00000001  ; Transmit Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXCSRH7 register.
;
;*************************************************************
USB_TXCSRH7_AUTOSET    EQU  0x00000080  ; Auto Set
USB_TXCSRH7_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_TXCSRH7_MODE       EQU  0x00000020  ; Mode
USB_TXCSRH7_DMAEN      EQU  0x00000010  ; DMA Request Enable
USB_TXCSRH7_FDT        EQU  0x00000008  ; Force Data Toggle
USB_TXCSRH7_DMAMOD     EQU  0x00000004  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXMAXP7 register.
;
;*************************************************************
USB_RXMAXP7_MAXLOAD_M  EQU  0x000007FF  ; Maximum Payload
USB_RXMAXP7_MAXLOAD_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRL7 register.
;
;*************************************************************
USB_RXCSRL7_CLRDT      EQU  0x00000080  ; Clear Data Toggle
USB_RXCSRL7_STALLED    EQU  0x00000040  ; Endpoint Stalled
USB_RXCSRL7_STALL      EQU  0x00000020  ; Send STALL
USB_RXCSRL7_FLUSH      EQU  0x00000010  ; Flush FIFO
USB_RXCSRL7_DATAERR    EQU  0x00000008  ; Data Error
USB_RXCSRL7_OVER       EQU  0x00000004  ; Overrun
USB_RXCSRL7_FULL       EQU  0x00000002  ; FIFO Full
USB_RXCSRL7_RXRDY      EQU  0x00000001  ; Receive Packet Ready

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCSRH7 register.
;
;*************************************************************
USB_RXCSRH7_AUTOCL     EQU  0x00000080  ; Auto Clear
USB_RXCSRH7_ISO        EQU  0x00000040  ; Isochronous Transfers
USB_RXCSRH7_DMAEN      EQU  0x00000020  ; DMA Request Enable
USB_RXCSRH7_PIDERR     EQU  0x00000010  ; PID Error
USB_RXCSRH7_DISNYET    EQU  0x00000010  ; Disable NYET
USB_RXCSRH7_DMAMOD     EQU  0x00000008  ; DMA Request Mode

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXCOUNT7 register.
;
;*************************************************************
USB_RXCOUNT7_COUNT_M   EQU  0x00001FFF  ; Receive Packet Count
USB_RXCOUNT7_COUNT_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_RXDPKTBUFDIS
; register.
;
;*************************************************************
USB_RXDPKTBUFDIS_EP7   EQU  0x00000080  ; EP7 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP6   EQU  0x00000040  ; EP6 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP5   EQU  0x00000020  ; EP5 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP4   EQU  0x00000010  ; EP4 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP3   EQU  0x00000008  ; EP3 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP2   EQU  0x00000004  ; EP2 RX Double-Packet Buffer
                                            ; Disable
USB_RXDPKTBUFDIS_EP1   EQU  0x00000002  ; EP1 RX Double-Packet Buffer
                                            ; Disable

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_TXDPKTBUFDIS
; register.
;
;*************************************************************
USB_TXDPKTBUFDIS_EP7   EQU  0x00000080  ; EP7 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP6   EQU  0x00000040  ; EP6 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP5   EQU  0x00000020  ; EP5 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP4   EQU  0x00000010  ; EP4 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP3   EQU  0x00000008  ; EP3 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP2   EQU  0x00000004  ; EP2 TX Double-Packet Buffer
                                            ; Disable
USB_TXDPKTBUFDIS_EP1   EQU  0x00000002  ; EP1 TX Double-Packet Buffer
                                            ; Disable

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_DRRIS register.
;
;*************************************************************
USB_DRRIS_RESUME       EQU  0x00000001  ; RESUME Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_DRIM register.
;
;*************************************************************
USB_DRIM_RESUME        EQU  0x00000001  ; RESUME Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_DRISC register.
;
;*************************************************************
USB_DRISC_RESUME       EQU  0x00000001  ; RESUME Interrupt Status and
                                            ; Clear

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_DMASEL register.
;
;*************************************************************
USB_DMASEL_DMACTX_M    EQU  0x00F00000  ; DMA C TX Select
USB_DMASEL_DMACRX_M    EQU  0x000F0000  ; DMA C RX Select
USB_DMASEL_DMABTX_M    EQU  0x0000F000  ; DMA B TX Select
USB_DMASEL_DMABRX_M    EQU  0x00000F00  ; DMA B RX Select
USB_DMASEL_DMAATX_M    EQU  0x000000F0  ; DMA A TX Select
USB_DMASEL_DMAARX_M    EQU  0x0000000F  ; DMA A RX Select
USB_DMASEL_DMACTX_S    EQU  20
USB_DMASEL_DMACRX_S    EQU  16
USB_DMASEL_DMABTX_S    EQU  12
USB_DMASEL_DMABRX_S    EQU  8
USB_DMASEL_DMAATX_S    EQU  4
USB_DMASEL_DMAARX_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the USB_O_PP register.
;
;*************************************************************
USB_PP_ECNT_M          EQU  0x0000FF00  ; Endpoint Count
USB_PP_USB_M           EQU  0x000000C0  ; USB Capability
USB_PP_USB_DEVICE      EQU  0x00000040  ; DEVICE
USB_PP_USB_HOSTDEVICE  EQU  0x00000080  ; HOST
USB_PP_USB_OTG         EQU  0x000000C0  ; OTG
USB_PP_PHY             EQU  0x00000010  ; PHY Present
USB_PP_TYPE_M          EQU  0x0000000F  ; Controller Type
USB_PP_TYPE_0          EQU  0x00000000  ; The first-generation USB
                                            ; controller
USB_PP_ECNT_S       EQU   8

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EESIZE register.
;
;*************************************************************
EEPROM_EESIZE_BLKCNT_M EQU  0x07FF0000  ; Number of 16-Word Blocks
EEPROM_EESIZE_WORDCNT_M EQU  0x0000FFFF  ; Number of 32-Bit Words
EEPROM_EESIZE_BLKCNT_S  EQU 16
EEPROM_EESIZE_WORDCNT_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEBLOCK register.
;
;*************************************************************
EEPROM_EEBLOCK_BLOCK_M EQU  0x0000FFFF  ; Current Block
EEPROM_EEBLOCK_BLOCK_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEOFFSET
; register.
;
;*************************************************************
EEPROM_EEOFFSET_OFFSET_M EQU  0x0000000F  ; Current Address Offset
EEPROM_EEOFFSET_OFFSET_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EERDWR register.
;
;*************************************************************
EEPROM_EERDWR_VALUE_M  EQU  0xFFFFFFFF  ; EEPROM Read or Write Data
EEPROM_EERDWR_VALUE_S  EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EERDWRINC
; register.
;
;*************************************************************
EEPROM_EERDWRINC_VALUE_M EQU  0xFFFFFFFF  ; EEPROM Read or Write Data with
                                            ; Increment
EEPROM_EERDWRINC_VALUE_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEDONE register.
;
;*************************************************************
EEPROM_EEDONE_INVPL    EQU  0x00000100  ; Invalid Program Voltage Level
EEPROM_EEDONE_WRBUSY   EQU  0x00000020  ; Write Busy
EEPROM_EEDONE_NOPERM   EQU  0x00000010  ; Write Without Permission
EEPROM_EEDONE_WKCOPY   EQU  0x00000008  ; Working on a Copy
EEPROM_EEDONE_WKERASE  EQU  0x00000004  ; Working on an Erase
EEPROM_EEDONE_WORKING  EQU  0x00000001  ; EEPROM Working

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EESUPP register.
;
;*************************************************************
EEPROM_EESUPP_PRETRY   EQU  0x00000008  ; Programming Must Be Retried
EEPROM_EESUPP_ERETRY   EQU  0x00000004  ; Erase Must Be Retried
EEPROM_EESUPP_EREQ     EQU  0x00000002  ; Erase Required
EEPROM_EESUPP_START    EQU  0x00000001  ; Start Erase

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEUNLOCK
; register.
;
;*************************************************************
EEPROM_EEUNLOCK_UNLOCK_M EQU  0xFFFFFFFF  ; EEPROM Unlock

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEPROT register.
;
;*************************************************************
EEPROM_EEPROT_ACC      EQU  0x00000008  ; Access Control
EEPROM_EEPROT_PROT_M   EQU  0x00000007  ; Protection Control
EEPROM_EEPROT_PROT_RWNPW EQU  0x00000000  ; This setting is the default. If
                                            ; there is no password, the block
                                            ; is not protected and is readable
                                            ; and writable
EEPROM_EEPROT_PROT_RWPW EQU  0x00000001  ; If there is a password, the
                                            ; block is readable or writable
                                            ; only when unlocked
EEPROM_EEPROT_PROT_RONPW EQU  0x00000002  ; If there is no password, the
                                            ; block is readable, not writable

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEPASS0 register.
;
;*************************************************************
EEPROM_EEPASS0_PASS_M  EQU  0xFFFFFFFF  ; Password
EEPROM_EEPASS0_PASS_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEPASS1 register.
;
;*************************************************************
EEPROM_EEPASS1_PASS_M  EQU  0xFFFFFFFF  ; Password
EEPROM_EEPASS1_PASS_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEPASS2 register.
;
;*************************************************************
EEPROM_EEPASS2_PASS_M  EQU  0xFFFFFFFF  ; Password
EEPROM_EEPASS2_PASS_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEINT register.
;
;*************************************************************
EEPROM_EEINT_INT       EQU  0x00000001  ; Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEHIDE register.
;
;*************************************************************
EEPROM_EEHIDE_HN_M     EQU  0xFFFFFFFE  ; Hide Block

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_EEDBGME register.
;
;*************************************************************
EEPROM_EEDBGME_KEY_M   EQU  0xFFFF0000  ; Erase Key
EEPROM_EEDBGME_ME      EQU  0x00000001  ; Mass Erase
EEPROM_EEDBGME_KEY_S    EQU 16

;*************************************************************
;
; The following are defines for the bit fields in the EEPROM_PP register.
;
;*************************************************************
EEPROM_PP_SIZE_M       EQU  0x0000001F  ; EEPROM Size
EEPROM_PP_SIZE_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the SYSEXC_RIS register.
;
;*************************************************************
SYSEXC_RIS_FPIXCRIS    EQU  0x00000020  ; Floating-Point Inexact Exception
                                            ; Raw Interrupt Status
SYSEXC_RIS_FPOFCRIS    EQU  0x00000010  ; Floating-Point Overflow
                                            ; Exception Raw Interrupt Status
SYSEXC_RIS_FPUFCRIS    EQU  0x00000008  ; Floating-Point Underflow
                                            ; Exception Raw Interrupt Status
SYSEXC_RIS_FPIOCRIS    EQU  0x00000004  ; Floating-Point Invalid Operation
                                            ; Raw Interrupt Status
SYSEXC_RIS_FPDZCRIS    EQU  0x00000002  ; Floating-Point Divide By 0
                                            ; Exception Raw Interrupt Status
SYSEXC_RIS_FPIDCRIS    EQU  0x00000001  ; Floating-Point Input Denormal
                                            ; Exception Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the SYSEXC_IM register.
;
;*************************************************************
SYSEXC_IM_FPIXCIM      EQU  0x00000020  ; Floating-Point Inexact Exception
                                            ; Interrupt Mask
SYSEXC_IM_FPOFCIM      EQU  0x00000010  ; Floating-Point Overflow
                                            ; Exception Interrupt Mask
SYSEXC_IM_FPUFCIM      EQU  0x00000008  ; Floating-Point Underflow
                                            ; Exception Interrupt Mask
SYSEXC_IM_FPIOCIM      EQU  0x00000004  ; Floating-Point Invalid Operation
                                            ; Interrupt Mask
SYSEXC_IM_FPDZCIM      EQU  0x00000002  ; Floating-Point Divide By 0
                                            ; Exception Interrupt Mask
SYSEXC_IM_FPIDCIM      EQU  0x00000001  ; Floating-Point Input Denormal
                                            ; Exception Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the SYSEXC_MIS register.
;
;*************************************************************
SYSEXC_MIS_FPIXCMIS    EQU  0x00000020  ; Floating-Point Inexact Exception
                                            ; Masked Interrupt Status
SYSEXC_MIS_FPOFCMIS    EQU  0x00000010  ; Floating-Point Overflow
                                            ; Exception Masked Interrupt
                                            ; Status
SYSEXC_MIS_FPUFCMIS    EQU  0x00000008  ; Floating-Point Underflow
                                            ; Exception Masked Interrupt
                                            ; Status
SYSEXC_MIS_FPIOCMIS    EQU  0x00000004  ; Floating-Point Invalid Operation
                                            ; Masked Interrupt Status
SYSEXC_MIS_FPDZCMIS    EQU  0x00000002  ; Floating-Point Divide By 0
                                            ; Exception Masked Interrupt
                                            ; Status
SYSEXC_MIS_FPIDCMIS    EQU  0x00000001  ; Floating-Point Input Denormal
                                            ; Exception Masked Interrupt
                                            ; Status

;*************************************************************
;
; The following are defines for the bit fields in the SYSEXC_IC register.
;
;*************************************************************
SYSEXC_IC_FPIXCIC      EQU  0x00000020  ; Floating-Point Inexact Exception
                                            ; Interrupt Clear
SYSEXC_IC_FPOFCIC      EQU  0x00000010  ; Floating-Point Overflow
                                            ; Exception Interrupt Clear
SYSEXC_IC_FPUFCIC      EQU  0x00000008  ; Floating-Point Underflow
                                            ; Exception Interrupt Clear
SYSEXC_IC_FPIOCIC      EQU  0x00000004  ; Floating-Point Invalid Operation
                                            ; Interrupt Clear
SYSEXC_IC_FPDZCIC      EQU  0x00000002  ; Floating-Point Divide By 0
                                            ; Exception Interrupt Clear
SYSEXC_IC_FPIDCIC      EQU  0x00000001  ; Floating-Point Input Denormal
                                            ; Exception Interrupt Clear

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RTCC register.
;
;*************************************************************
HIB_RTCC_M             EQU  0xFFFFFFFF  ; RTC Counter
HIB_RTCC_S          EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RTCM0 register.
;
;*************************************************************
HIB_RTCM0_M            EQU  0xFFFFFFFF  ; RTC Match 0
HIB_RTCM0_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RTCLD register.
;
;*************************************************************
HIB_RTCLD_M            EQU  0xFFFFFFFF  ; RTC Load
HIB_RTCLD_S         EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the HIB_CTL register.
;
;*************************************************************
HIB_CTL_WRC            EQU  0x80000000  ; Write Complete/Capable
HIB_CTL_OSCDRV         EQU  0x00020000  ; Oscillator Drive Capability
HIB_CTL_OSCBYP         EQU  0x00010000  ; Oscillator Bypass
HIB_CTL_VBATSEL_M      EQU  0x00006000  ; Select for Low-Battery
                                            ; Comparator
HIB_CTL_VBATSEL_1_9V   EQU  0x00000000  ; 1.9 Volts
HIB_CTL_VBATSEL_2_1V   EQU  0x00002000  ; 2.1 Volts (default)
HIB_CTL_VBATSEL_2_3V   EQU  0x00004000  ; 2.3 Volts
HIB_CTL_VBATSEL_2_5V   EQU  0x00006000  ; 2.5 Volts
HIB_CTL_BATCHK         EQU  0x00000400  ; Check Battery Status
HIB_CTL_BATWKEN        EQU  0x00000200  ; Wake on Low Battery
HIB_CTL_VDD3ON         EQU  0x00000100  ; VDD Powered
HIB_CTL_VABORT         EQU  0x00000080  ; Power Cut Abort Enable
HIB_CTL_CLK32EN        EQU  0x00000040  ; Clocking Enable
HIB_CTL_LOWBATEN       EQU  0x00000020  ; Low Battery Monitoring Enable
HIB_CTL_PINWEN         EQU  0x00000010  ; External WAKE Pin Enable
HIB_CTL_RTCWEN         EQU  0x00000008  ; RTC Wake-up Enable
HIB_CTL_HIBREQ         EQU  0x00000002  ; Hibernation Request
HIB_CTL_RTCEN          EQU  0x00000001  ; RTC Timer Enable

;*************************************************************
;
; The following are defines for the bit fields in the HIB_IM register.
;
;*************************************************************
HIB_IM_WC              EQU  0x00000010  ; External Write Complete/Capable
                                            ; Interrupt Mask
HIB_IM_EXTW            EQU  0x00000008  ; External Wake-Up Interrupt Mask
HIB_IM_LOWBAT          EQU  0x00000004  ; Low Battery Voltage Interrupt
                                            ; Mask
HIB_IM_RTCALT0         EQU  0x00000001  ; RTC Alert 0 Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RIS register.
;
;*************************************************************
HIB_RIS_WC             EQU  0x00000010  ; Write Complete/Capable Raw
                                            ; Interrupt Status
HIB_RIS_EXTW           EQU  0x00000008  ; External Wake-Up Raw Interrupt
                                            ; Status
HIB_RIS_LOWBAT         EQU  0x00000004  ; Low Battery Voltage Raw
                                            ; Interrupt Status
HIB_RIS_RTCALT0        EQU  0x00000001  ; RTC Alert 0 Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the HIB_MIS register.
;
;*************************************************************
HIB_MIS_WC             EQU  0x00000010  ; Write Complete/Capable Masked
                                            ; Interrupt Status
HIB_MIS_EXTW           EQU  0x00000008  ; External Wake-Up Masked
                                            ; Interrupt Status
HIB_MIS_LOWBAT         EQU  0x00000004  ; Low Battery Voltage Masked
                                            ; Interrupt Status
HIB_MIS_RTCALT0        EQU  0x00000001  ; RTC Alert 0 Masked Interrupt
                                            ; Status

;*************************************************************
;
; The following are defines for the bit fields in the HIB_IC register.
;
;*************************************************************
HIB_IC_WC              EQU  0x00000010  ; Write Complete/Capable Masked
                                            ; Interrupt Clear
HIB_IC_EXTW            EQU  0x00000008  ; External Wake-Up Masked
                                            ; Interrupt Clear
HIB_IC_LOWBAT          EQU  0x00000004  ; Low Battery Voltage Masked
                                            ; Interrupt Clear
HIB_IC_RTCALT0         EQU  0x00000001  ; RTC Alert0 Masked Interrupt
                                            ; Clear

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RTCT register.
;
;*************************************************************
HIB_RTCT_TRIM_M        EQU  0x0000FFFF  ; RTC Trim Value
HIB_RTCT_TRIM_S     EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the HIB_RTCSS register.
;
;*************************************************************
HIB_RTCSS_RTCSSM_M     EQU  0x7FFF0000  ; RTC Sub Seconds Match
HIB_RTCSS_RTCSSC_M     EQU  0x00007FFF  ; RTC Sub Seconds Count
HIB_RTCSS_RTCSSM_S  EQU   16
HIB_RTCSS_RTCSSC_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the HIB_DATA register.
;
;*************************************************************
HIB_DATA_RTD_M         EQU  0xFFFFFFFF  ; Hibernation Module NV Data
HIB_DATA_RTD_S      EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FMA register.
;
;*************************************************************
FLASH_FMA_OFFSET_M     EQU  0x0003FFFF  ; Address Offset
FLASH_FMA_OFFSET_S  EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FMD register.
;
;*************************************************************
FLASH_FMD_DATA_M       EQU  0xFFFFFFFF  ; Data Value
FLASH_FMD_DATA_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FMC register.
;
;*************************************************************
FLASH_FMC_WRKEY        EQU  0xA4420000  ; FLASH write key
FLASH_FMC_COMT         EQU  0x00000008  ; Commit Register Value
FLASH_FMC_MERASE       EQU  0x00000004  ; Mass Erase Flash Memory
FLASH_FMC_ERASE        EQU  0x00000002  ; Erase a Page of Flash Memory
FLASH_FMC_WRITE        EQU  0x00000001  ; Write a Word into Flash Memory

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FCRIS register.
;
;*************************************************************
FLASH_FCRIS_PROGRIS    EQU  0x00002000  ; PROGVER Raw Interrupt Status
FLASH_FCRIS_ERRIS      EQU  0x00000800  ; ERVER Raw Interrupt Status
FLASH_FCRIS_INVDRIS    EQU  0x00000400  ; Invalid Data Raw Interrupt
                                            ; Status
FLASH_FCRIS_VOLTRIS    EQU  0x00000200  ; VOLTSTAT Raw Interrupt Status
FLASH_FCRIS_ERIS       EQU  0x00000004  ; EEPROM Raw Interrupt Status
FLASH_FCRIS_PRIS       EQU  0x00000002  ; Programming Raw Interrupt Status
FLASH_FCRIS_ARIS       EQU  0x00000001  ; Access Raw Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FCIM register.
;
;*************************************************************
FLASH_FCIM_PROGMASK    EQU  0x00002000  ; PROGVER Interrupt Mask
FLASH_FCIM_ERMASK      EQU  0x00000800  ; ERVER Interrupt Mask
FLASH_FCIM_INVDMASK    EQU  0x00000400  ; Invalid Data Interrupt Mask
FLASH_FCIM_VOLTMASK    EQU  0x00000200  ; VOLT Interrupt Mask
FLASH_FCIM_EMASK       EQU  0x00000004  ; EEPROM Interrupt Mask
FLASH_FCIM_PMASK       EQU  0x00000002  ; Programming Interrupt Mask
FLASH_FCIM_AMASK       EQU  0x00000001  ; Access Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FCMISC register.
;
;*************************************************************
FLASH_FCMISC_PROGMISC  EQU  0x00002000  ; PROGVER Masked Interrupt Status
                                            ; and Clear
FLASH_FCMISC_ERMISC    EQU  0x00000800  ; ERVER Masked Interrupt Status
                                            ; and Clear
FLASH_FCMISC_INVDMISC  EQU  0x00000400  ; Invalid Data Masked Interrupt
                                            ; Status and Clear
FLASH_FCMISC_VOLTMISC  EQU  0x00000200  ; VOLT Masked Interrupt Status and
                                            ; Clear
FLASH_FCMISC_EMISC     EQU  0x00000004  ; EEPROM Masked Interrupt Status
                                            ; and Clear
FLASH_FCMISC_PMISC     EQU  0x00000002  ; Programming Masked Interrupt
                                            ; Status and Clear
FLASH_FCMISC_AMISC     EQU  0x00000001  ; Access Masked Interrupt Status
                                            ; and Clear

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FMC2 register.
;
;*************************************************************
FLASH_FMC2_WRKEY       EQU  0xA4420000  ; FLASH write key
FLASH_FMC2_WRBUF       EQU  0x00000001  ; Buffered Flash Memory Write

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FWBVAL register.
;
;*************************************************************
FLASH_FWBVAL_FWB_M     EQU  0xFFFFFFFF  ; Flash Memory Write Buffer

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FWBN register.
;
;*************************************************************
FLASH_FWBN_DATA_M      EQU  0xFFFFFFFF  ; Data

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_FSIZE register.
;
;*************************************************************
FLASH_FSIZE_SIZE_M     EQU  0x0000FFFF  ; Flash Size
FLASH_FSIZE_SIZE_8KB   EQU  0x00000003  ; 8 KB of Flash
FLASH_FSIZE_SIZE_16KB  EQU  0x00000007  ; 16 KB of Flash
FLASH_FSIZE_SIZE_32KB  EQU  0x0000000F  ; 32 KB of Flash
FLASH_FSIZE_SIZE_64KB  EQU  0x0000001F  ; 64 KB of Flash
FLASH_FSIZE_SIZE_96KB  EQU  0x0000002F  ; 96 KB of Flash
FLASH_FSIZE_SIZE_128KB EQU  0x0000003F  ; 128 KB of Flash
FLASH_FSIZE_SIZE_192KB EQU  0x0000005F  ; 192 KB of Flash
FLASH_FSIZE_SIZE_256KB EQU  0x0000007F  ; 256 KB of Flash

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_SSIZE register.
;
;*************************************************************
FLASH_SSIZE_SIZE_M     EQU  0x0000FFFF  ; SRAM Size
FLASH_SSIZE_SIZE_2KB   EQU  0x00000007  ; 2 KB of SRAM
FLASH_SSIZE_SIZE_4KB   EQU  0x0000000F  ; 4 KB of SRAM
FLASH_SSIZE_SIZE_6KB   EQU  0x00000017  ; 6 KB of SRAM
FLASH_SSIZE_SIZE_8KB   EQU  0x0000001F  ; 8 KB of SRAM
FLASH_SSIZE_SIZE_12KB  EQU  0x0000002F  ; 12 KB of SRAM
FLASH_SSIZE_SIZE_16KB  EQU  0x0000003F  ; 16 KB of SRAM
FLASH_SSIZE_SIZE_20KB  EQU  0x0000004F  ; 20 KB of SRAM
FLASH_SSIZE_SIZE_24KB  EQU  0x0000005F  ; 24 KB of SRAM
FLASH_SSIZE_SIZE_32KB  EQU  0x0000007F  ; 32 KB of SRAM

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_ROMSWMAP register.
;
;*************************************************************
FLASH_ROMSWMAP_SAFERTOS EQU  0x00000001  ; SafeRTOS Present

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_RMCTL register.
;
;*************************************************************
FLASH_RMCTL_BA         EQU  0x00000001  ; Boot Alias

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_BOOTCFG register.
;
;*************************************************************
FLASH_BOOTCFG_NW       EQU  0x80000000  ; Not Written
FLASH_BOOTCFG_PORT_M   EQU  0x0000E000  ; Boot GPIO Port
FLASH_BOOTCFG_PORT_A   EQU  0x00000000  ; Port A
FLASH_BOOTCFG_PORT_B   EQU  0x00002000  ; Port B
FLASH_BOOTCFG_PORT_C   EQU  0x00004000  ; Port C
FLASH_BOOTCFG_PORT_D   EQU  0x00006000  ; Port D
FLASH_BOOTCFG_PORT_E   EQU  0x00008000  ; Port E
FLASH_BOOTCFG_PORT_F   EQU  0x0000A000  ; Port F
FLASH_BOOTCFG_PORT_G   EQU  0x0000C000  ; Port G
FLASH_BOOTCFG_PORT_H   EQU  0x0000E000  ; Port H
FLASH_BOOTCFG_PIN_M    EQU  0x00001C00  ; Boot GPIO Pin
FLASH_BOOTCFG_PIN_0    EQU  0x00000000  ; Pin 0
FLASH_BOOTCFG_PIN_1    EQU  0x00000400  ; Pin 1
FLASH_BOOTCFG_PIN_2    EQU  0x00000800  ; Pin 2
FLASH_BOOTCFG_PIN_3    EQU  0x00000C00  ; Pin 3
FLASH_BOOTCFG_PIN_4    EQU  0x00001000  ; Pin 4
FLASH_BOOTCFG_PIN_5    EQU  0x00001400  ; Pin 5
FLASH_BOOTCFG_PIN_6    EQU  0x00001800  ; Pin 6
FLASH_BOOTCFG_PIN_7    EQU  0x00001C00  ; Pin 7
FLASH_BOOTCFG_POL      EQU  0x00000200  ; Boot GPIO Polarity
FLASH_BOOTCFG_EN       EQU  0x00000100  ; Boot GPIO Enable
FLASH_BOOTCFG_DBG1     EQU  0x00000002  ; Debug Control 1
FLASH_BOOTCFG_DBG0     EQU  0x00000001  ; Debug Control 0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_USERREG0 register.
;
;*************************************************************
FLASH_USERREG0_DATA_M  EQU  0xFFFFFFFF  ; User Data
FLASH_USERREG0_DATA_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_USERREG1 register.
;
;*************************************************************
FLASH_USERREG1_DATA_M  EQU  0xFFFFFFFF  ; User Data
FLASH_USERREG1_DATA_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_USERREG2 register.
;
;*************************************************************
FLASH_USERREG2_DATA_M  EQU  0xFFFFFFFF  ; User Data
FLASH_USERREG2_DATA_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the FLASH_USERREG3 register.
;
;*************************************************************
FLASH_USERREG3_DATA_M  EQU  0xFFFFFFFF  ; User Data
FLASH_USERREG3_DATA_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DID0 register.
;
;*************************************************************
SYSCTL_DID0_VER_M      EQU  0x70000000  ; DID0 Version
SYSCTL_DID0_VER_1      EQU  0x10000000  ; Second version of the DID0
                                            ; register format
SYSCTL_DID0_CLASS_M    EQU  0x00FF0000  ; Device Class
SYSCTL_DID0_CLASS_BLIZZARD EQU  0x00050000  ; Stellaris(R) Blizzard-class
                                            ; microcontrollers
SYSCTL_DID0_MAJ_M      EQU  0x0000FF00  ; Major Revision
SYSCTL_DID0_MAJ_REVA   EQU  0x00000000  ; Revision A (initial device)
SYSCTL_DID0_MAJ_REVB   EQU  0x00000100  ; Revision B (first base layer
                                            ; revision)
SYSCTL_DID0_MAJ_REVC   EQU  0x00000200  ; Revision C (second base layer
                                            ; revision)
SYSCTL_DID0_MIN_M      EQU  0x000000FF  ; Minor Revision
SYSCTL_DID0_MIN_0      EQU  0x00000000  ; Initial device, or a major
                                            ; revision update
SYSCTL_DID0_MIN_1      EQU  0x00000001  ; First metal layer change
SYSCTL_DID0_MIN_2      EQU  0x00000002  ; Second metal layer change

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DID1 register.
;
;*************************************************************
SYSCTL_DID1_VER_M      EQU  0xF0000000  ; DID1 Version
SYSCTL_DID1_VER_0      EQU  0x00000000  ; Initial DID1 register format
                                            ; definition, indicating a
                                            ; Stellaris LM3Snnn device
SYSCTL_DID1_VER_1      EQU  0x10000000  ; Second version of the DID1
                                            ; register format
SYSCTL_DID1_FAM_M      EQU  0x0F000000  ; Family
SYSCTL_DID1_FAM_STELLARIS EQU  0x00000000  ; Stellaris family of
                                            ; microcontollers, that is, all
                                            ; devices with external part
                                            ; numbers starting with LM3S
SYSCTL_DID1_PRTNO_M    EQU  0x00FF0000  ; Part Number
SYSCTL_DID1_PRTNO_LM4F120H5QR EQU  0x00040000  ; LM4F120H5QR
SYSCTL_DID1_PINCNT_M   EQU  0x0000E000  ; Package Pin Count
SYSCTL_DID1_PINCNT_28  EQU  0x00000000  ; 28-pin package
SYSCTL_DID1_PINCNT_48  EQU  0x00002000  ; 48-pin package
SYSCTL_DID1_PINCNT_100 EQU  0x00004000  ; 100-pin package
SYSCTL_DID1_PINCNT_64  EQU  0x00006000  ; 64-pin package
SYSCTL_DID1_PINCNT_144 EQU  0x00008000  ; 144-pin package
SYSCTL_DID1_PINCNT_157 EQU  0x0000A000  ; 157-pin package
SYSCTL_DID1_TEMP_M     EQU  0x000000E0  ; Temperature Range
SYSCTL_DID1_TEMP_C     EQU  0x00000000  ; Commercial temperature range (0C
                                            ; to 70C)
SYSCTL_DID1_TEMP_I     EQU  0x00000020  ; Industrial temperature range
                                            ; (-40C to 85C)
SYSCTL_DID1_TEMP_E     EQU  0x00000040  ; Extended temperature range (-40C
                                            ; to 105C)
SYSCTL_DID1_PKG_M      EQU  0x00000018  ; Package Type
SYSCTL_DID1_PKG_SOIC   EQU  0x00000000  ; SOIC package
SYSCTL_DID1_PKG_QFP    EQU  0x00000008  ; LQFP package
SYSCTL_DID1_PKG_BGA    EQU  0x00000010  ; BGA package
SYSCTL_DID1_ROHS       EQU  0x00000004  ; RoHS-Compliance
SYSCTL_DID1_QUAL_M     EQU  0x00000003  ; Qualification Status
SYSCTL_DID1_QUAL_ES    EQU  0x00000000  ; Engineering Sample (unqualified)
SYSCTL_DID1_QUAL_PP    EQU  0x00000001  ; Pilot Production (unqualified)
SYSCTL_DID1_QUAL_FQ    EQU  0x00000002  ; Fully Qualified

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC0 register.
;
;*************************************************************
SYSCTL_DC0_SRAMSZ_M    EQU  0xFFFF0000  ; SRAM Size
SYSCTL_DC0_SRAMSZ_2KB  EQU  0x00070000  ; 2 KB of SRAM
SYSCTL_DC0_SRAMSZ_4KB  EQU  0x000F0000  ; 4 KB of SRAM
SYSCTL_DC0_SRAMSZ_6KB  EQU  0x00170000  ; 6 KB of SRAM
SYSCTL_DC0_SRAMSZ_8KB  EQU  0x001F0000  ; 8 KB of SRAM
SYSCTL_DC0_SRAMSZ_12KB EQU  0x002F0000  ; 12 KB of SRAM
SYSCTL_DC0_SRAMSZ_16KB EQU  0x003F0000  ; 16 KB of SRAM
SYSCTL_DC0_SRAMSZ_20KB EQU  0x004F0000  ; 20 KB of SRAM
SYSCTL_DC0_SRAMSZ_24KB EQU  0x005F0000  ; 24 KB of SRAM
SYSCTL_DC0_SRAMSZ_32KB EQU  0x007F0000  ; 32 KB of SRAM
SYSCTL_DC0_FLASHSZ_M   EQU  0x0000FFFF  ; Flash Size
SYSCTL_DC0_FLASHSZ_8KB EQU  0x00000003  ; 8 KB of Flash
SYSCTL_DC0_FLASHSZ_16KB EQU  0x00000007  ; 16 KB of Flash
SYSCTL_DC0_FLASHSZ_32KB EQU  0x0000000F  ; 32 KB of Flash
SYSCTL_DC0_FLASHSZ_64KB EQU  0x0000001F  ; 64 KB of Flash
SYSCTL_DC0_FLASHSZ_96KB EQU  0x0000002F  ; 96 KB of Flash
SYSCTL_DC0_FLASHSZ_128K EQU  0x0000003F  ; 128 KB of Flash
SYSCTL_DC0_FLASHSZ_192K EQU  0x0000005F  ; 192 KB of Flash
SYSCTL_DC0_FLASHSZ_256K EQU  0x0000007F  ; 256 KB of Flash
SYSCTL_DC0_SRAMSZ_S    EQU  16          ; SRAM size shift
SYSCTL_DC0_FLASHSZ_S    EQU 0           ; Flash size shift

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC1 register.
;
;*************************************************************
SYSCTL_DC1_WDT1        EQU  0x10000000  ; Watchdog Timer1 Present
SYSCTL_DC1_CAN1        EQU  0x02000000  ; CAN Module 1 Present
SYSCTL_DC1_CAN0        EQU  0x01000000  ; CAN Module 0 Present
SYSCTL_DC1_PWM1        EQU  0x00200000  ; PWM Module 1 Present
SYSCTL_DC1_PWM0        EQU  0x00100000  ; PWM Module 0 Present
SYSCTL_DC1_ADC1        EQU  0x00020000  ; ADC Module 1 Present
SYSCTL_DC1_ADC0        EQU  0x00010000  ; ADC Module 0 Present
SYSCTL_DC1_MINSYSDIV_M EQU  0x0000F000  ; System Clock Divider
SYSCTL_DC1_MINSYSDIV_100 EQU  0x00001000  ; Divide VCO (400MHZ) by 5 minimum
SYSCTL_DC1_MINSYSDIV_66 EQU  0x00002000  ; Divide VCO (400MHZ) by 2*2 + 2 =
                                            ; 6 minimum
SYSCTL_DC1_MINSYSDIV_50 EQU  0x00003000  ; Specifies a 50-MHz CPU clock
                                            ; with a PLL divider of 4
SYSCTL_DC1_MINSYSDIV_40 EQU  0x00004000  ; Specifies a 40-MHz CPU clock
                                            ; with a PLL divider of 5
SYSCTL_DC1_MINSYSDIV_25 EQU  0x00007000  ; Specifies a 25-MHz clock with a
                                            ; PLL divider of 8
SYSCTL_DC1_MINSYSDIV_20 EQU  0x00009000  ; Specifies a 20-MHz clock with a
                                            ; PLL divider of 10
SYSCTL_DC1_ADC1SPD_M   EQU  0x00000C00  ; Max ADC1 Speed
SYSCTL_DC1_ADC1SPD_125K EQU  0x00000000  ; 125K samples/second
SYSCTL_DC1_ADC1SPD_250K EQU  0x00000400  ; 250K samples/second
SYSCTL_DC1_ADC1SPD_500K EQU  0x00000800  ; 500K samples/second
SYSCTL_DC1_ADC1SPD_1M  EQU  0x00000C00  ; 1M samples/second
SYSCTL_DC1_ADC0SPD_M   EQU  0x00000300  ; Max ADC0 Speed
SYSCTL_DC1_ADC0SPD_125K EQU  0x00000000  ; 125K samples/second
SYSCTL_DC1_ADC0SPD_250K EQU  0x00000100  ; 250K samples/second
SYSCTL_DC1_ADC0SPD_500K EQU  0x00000200  ; 500K samples/second
SYSCTL_DC1_ADC0SPD_1M  EQU  0x00000300  ; 1M samples/second
SYSCTL_DC1_MPU         EQU  0x00000080  ; MPU Present
SYSCTL_DC1_HIB         EQU  0x00000040  ; Hibernation Module Present
SYSCTL_DC1_TEMP        EQU  0x00000020  ; Temp Sensor Present
SYSCTL_DC1_PLL         EQU  0x00000010  ; PLL Present
SYSCTL_DC1_WDT0        EQU  0x00000008  ; Watchdog Timer 0 Present
SYSCTL_DC1_SWO         EQU  0x00000004  ; SWO Trace Port Present
SYSCTL_DC1_SWD         EQU  0x00000002  ; SWD Present
SYSCTL_DC1_JTAG        EQU  0x00000001  ; JTAG Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC2 register.
;
;*************************************************************
SYSCTL_DC2_EPI0        EQU  0x40000000  ; EPI Module 0 Present
SYSCTL_DC2_I2S0        EQU  0x10000000  ; I2S Module 0 Present
SYSCTL_DC2_COMP2       EQU  0x04000000  ; Analog Comparator 2 Present
SYSCTL_DC2_COMP1       EQU  0x02000000  ; Analog Comparator 1 Present
SYSCTL_DC2_COMP0       EQU  0x01000000  ; Analog Comparator 0 Present
SYSCTL_DC2_TIMER3      EQU  0x00080000  ; Timer Module 3 Present
SYSCTL_DC2_TIMER2      EQU  0x00040000  ; Timer Module 2 Present
SYSCTL_DC2_TIMER1      EQU  0x00020000  ; Timer Module 1 Present
SYSCTL_DC2_TIMER0      EQU  0x00010000  ; Timer Module 0 Present
SYSCTL_DC2_I2C1HS      EQU  0x00008000  ; I2C Module 1 Speed
SYSCTL_DC2_I2C1        EQU  0x00004000  ; I2C Module 1 Present
SYSCTL_DC2_I2C0HS      EQU  0x00002000  ; I2C Module 0 Speed
SYSCTL_DC2_I2C0        EQU  0x00001000  ; I2C Module 0 Present
SYSCTL_DC2_QEI1        EQU  0x00000200  ; QEI Module 1 Present
SYSCTL_DC2_QEI0        EQU  0x00000100  ; QEI Module 0 Present
SYSCTL_DC2_SSI1        EQU  0x00000020  ; SSI Module 1 Present
SYSCTL_DC2_SSI0        EQU  0x00000010  ; SSI Module 0 Present
SYSCTL_DC2_UART2       EQU  0x00000004  ; UART Module 2 Present
SYSCTL_DC2_UART1       EQU  0x00000002  ; UART Module 1 Present
SYSCTL_DC2_UART0       EQU  0x00000001  ; UART Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC3 register.
;
;*************************************************************
SYSCTL_DC3_32KHZ       EQU  0x80000000  ; 32KHz Input Clock Available
SYSCTL_DC3_CCP5        EQU  0x20000000  ; CCP5 Pin Present
SYSCTL_DC3_CCP4        EQU  0x10000000  ; CCP4 Pin Present
SYSCTL_DC3_CCP3        EQU  0x08000000  ; CCP3 Pin Present
SYSCTL_DC3_CCP2        EQU  0x04000000  ; CCP2 Pin Present
SYSCTL_DC3_CCP1        EQU  0x02000000  ; CCP1 Pin Present
SYSCTL_DC3_CCP0        EQU  0x01000000  ; CCP0 Pin Present
SYSCTL_DC3_ADC0AIN7    EQU  0x00800000  ; ADC Module 0 AIN7 Pin Present
SYSCTL_DC3_ADC0AIN6    EQU  0x00400000  ; ADC Module 0 AIN6 Pin Present
SYSCTL_DC3_ADC0AIN5    EQU  0x00200000  ; ADC Module 0 AIN5 Pin Present
SYSCTL_DC3_ADC0AIN4    EQU  0x00100000  ; ADC Module 0 AIN4 Pin Present
SYSCTL_DC3_ADC0AIN3    EQU  0x00080000  ; ADC Module 0 AIN3 Pin Present
SYSCTL_DC3_ADC0AIN2    EQU  0x00040000  ; ADC Module 0 AIN2 Pin Present
SYSCTL_DC3_ADC0AIN1    EQU  0x00020000  ; ADC Module 0 AIN1 Pin Present
SYSCTL_DC3_ADC0AIN0    EQU  0x00010000  ; ADC Module 0 AIN0 Pin Present
SYSCTL_DC3_PWMFAULT    EQU  0x00008000  ; PWM Fault Pin Present
SYSCTL_DC3_C2O         EQU  0x00004000  ; C2o Pin Present
SYSCTL_DC3_C2PLUS      EQU  0x00002000  ; C2+ Pin Present
SYSCTL_DC3_C2MINUS     EQU  0x00001000  ; C2- Pin Present
SYSCTL_DC3_C1O         EQU  0x00000800  ; C1o Pin Present
SYSCTL_DC3_C1PLUS      EQU  0x00000400  ; C1+ Pin Present
SYSCTL_DC3_C1MINUS     EQU  0x00000200  ; C1- Pin Present
SYSCTL_DC3_C0O         EQU  0x00000100  ; C0o Pin Present
SYSCTL_DC3_C0PLUS      EQU  0x00000080  ; C0+ Pin Present
SYSCTL_DC3_C0MINUS     EQU  0x00000040  ; C0- Pin Present
SYSCTL_DC3_PWM5        EQU  0x00000020  ; PWM5 Pin Present
SYSCTL_DC3_PWM4        EQU  0x00000010  ; PWM4 Pin Present
SYSCTL_DC3_PWM3        EQU  0x00000008  ; PWM3 Pin Present
SYSCTL_DC3_PWM2        EQU  0x00000004  ; PWM2 Pin Present
SYSCTL_DC3_PWM1        EQU  0x00000002  ; PWM1 Pin Present
SYSCTL_DC3_PWM0        EQU  0x00000001  ; PWM0 Pin Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC4 register.
;
;*************************************************************
SYSCTL_DC4_EPHY0       EQU  0x40000000  ; Ethernet PHY Layer 0 Present
SYSCTL_DC4_EMAC0       EQU  0x10000000  ; Ethernet MAC Layer 0 Present
SYSCTL_DC4_E1588       EQU  0x01000000  ; 1588 Capable
SYSCTL_DC4_PICAL       EQU  0x00040000  ; PIOSC Calibrate
SYSCTL_DC4_CCP7        EQU  0x00008000  ; CCP7 Pin Present
SYSCTL_DC4_CCP6        EQU  0x00004000  ; CCP6 Pin Present
SYSCTL_DC4_UDMA        EQU  0x00002000  ; Micro-DMA Module Present
SYSCTL_DC4_ROM         EQU  0x00001000  ; Internal Code ROM Present
SYSCTL_DC4_GPIOJ       EQU  0x00000100  ; GPIO Port J Present
SYSCTL_DC4_GPIOH       EQU  0x00000080  ; GPIO Port H Present
SYSCTL_DC4_GPIOG       EQU  0x00000040  ; GPIO Port G Present
SYSCTL_DC4_GPIOF       EQU  0x00000020  ; GPIO Port F Present
SYSCTL_DC4_GPIOE       EQU  0x00000010  ; GPIO Port E Present
SYSCTL_DC4_GPIOD       EQU  0x00000008  ; GPIO Port D Present
SYSCTL_DC4_GPIOC       EQU  0x00000004  ; GPIO Port C Present
SYSCTL_DC4_GPIOB       EQU  0x00000002  ; GPIO Port B Present
SYSCTL_DC4_GPIOA       EQU  0x00000001  ; GPIO Port A Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC5 register.
;
;*************************************************************
SYSCTL_DC5_PWMFAULT3   EQU  0x08000000  ; PWM Fault 3 Pin Present
SYSCTL_DC5_PWMFAULT2   EQU  0x04000000  ; PWM Fault 2 Pin Present
SYSCTL_DC5_PWMFAULT1   EQU  0x02000000  ; PWM Fault 1 Pin Present
SYSCTL_DC5_PWMFAULT0   EQU  0x01000000  ; PWM Fault 0 Pin Present
SYSCTL_DC5_PWMEFLT     EQU  0x00200000  ; PWM Extended Fault Active
SYSCTL_DC5_PWMESYNC    EQU  0x00100000  ; PWM Extended SYNC Active
SYSCTL_DC5_PWM7        EQU  0x00000080  ; PWM7 Pin Present
SYSCTL_DC5_PWM6        EQU  0x00000040  ; PWM6 Pin Present
SYSCTL_DC5_PWM5        EQU  0x00000020  ; PWM5 Pin Present
SYSCTL_DC5_PWM4        EQU  0x00000010  ; PWM4 Pin Present
SYSCTL_DC5_PWM3        EQU  0x00000008  ; PWM3 Pin Present
SYSCTL_DC5_PWM2        EQU  0x00000004  ; PWM2 Pin Present
SYSCTL_DC5_PWM1        EQU  0x00000002  ; PWM1 Pin Present
SYSCTL_DC5_PWM0        EQU  0x00000001  ; PWM0 Pin Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC6 register.
;
;*************************************************************
SYSCTL_DC6_USB0PHY     EQU  0x00000010  ; USB Module 0 PHY Present
SYSCTL_DC6_USB0_M      EQU  0x00000003  ; USB Module 0 Present
SYSCTL_DC6_USB0_DEV    EQU  0x00000001  ; USB0 is Device Only
SYSCTL_DC6_USB0_HOSTDEV EQU  0x00000002  ; USB is Device or Host
SYSCTL_DC6_USB0_OTG    EQU  0x00000003  ; USB0 is OTG

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC7 register.
;
;*************************************************************
SYSCTL_DC7_DMACH30     EQU  0x40000000  ; SW
SYSCTL_DC7_DMACH29     EQU  0x20000000  ; I2S0_TX / CAN1_TX
SYSCTL_DC7_DMACH28     EQU  0x10000000  ; I2S0_RX / CAN1_RX
SYSCTL_DC7_DMACH27     EQU  0x08000000  ; CAN1_TX / ADC1_SS3
SYSCTL_DC7_DMACH26     EQU  0x04000000  ; CAN1_RX / ADC1_SS2
SYSCTL_DC7_DMACH25     EQU  0x02000000  ; SSI1_TX / ADC1_SS1
SYSCTL_DC7_DMACH24     EQU  0x01000000  ; SSI1_RX / ADC1_SS0
SYSCTL_DC7_DMACH23     EQU  0x00800000  ; UART1_TX / CAN2_TX
SYSCTL_DC7_DMACH22     EQU  0x00400000  ; UART1_RX / CAN2_RX
SYSCTL_DC7_DMACH21     EQU  0x00200000  ; Timer1B / EPI0_WFIFO
SYSCTL_DC7_DMACH20     EQU  0x00100000  ; Timer1A / EPI0_NBRFIFO
SYSCTL_DC7_DMACH19     EQU  0x00080000  ; Timer0B / Timer1B
SYSCTL_DC7_DMACH18     EQU  0x00040000  ; Timer0A / Timer1A
SYSCTL_DC7_DMACH17     EQU  0x00020000  ; ADC0_SS3
SYSCTL_DC7_DMACH16     EQU  0x00010000  ; ADC0_SS2
SYSCTL_DC7_DMACH15     EQU  0x00008000  ; ADC0_SS1 / Timer2B
SYSCTL_DC7_DMACH14     EQU  0x00004000  ; ADC0_SS0 / Timer2A
SYSCTL_DC7_DMACH13     EQU  0x00002000  ; CAN0_TX / UART2_TX
SYSCTL_DC7_DMACH12     EQU  0x00001000  ; CAN0_RX / UART2_RX
SYSCTL_DC7_DMACH11     EQU  0x00000800  ; SSI0_TX / SSI1_TX
SYSCTL_DC7_DMACH10     EQU  0x00000400  ; SSI0_RX / SSI1_RX
SYSCTL_DC7_DMACH9      EQU  0x00000200  ; UART0_TX / UART1_TX
SYSCTL_DC7_DMACH8      EQU  0x00000100  ; UART0_RX / UART1_RX
SYSCTL_DC7_DMACH7      EQU  0x00000080  ; ETH_TX / Timer2B
SYSCTL_DC7_DMACH6      EQU  0x00000040  ; ETH_RX / Timer2A
SYSCTL_DC7_DMACH5      EQU  0x00000020  ; USB_EP3_TX / Timer2B
SYSCTL_DC7_DMACH4      EQU  0x00000010  ; USB_EP3_RX / Timer2A
SYSCTL_DC7_DMACH3      EQU  0x00000008  ; USB_EP2_TX / Timer3B
SYSCTL_DC7_DMACH2      EQU  0x00000004  ; USB_EP2_RX / Timer3A
SYSCTL_DC7_DMACH1      EQU  0x00000002  ; USB_EP1_TX / UART2_TX
SYSCTL_DC7_DMACH0      EQU  0x00000001  ; USB_EP1_RX / UART2_RX

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC8 register.
;
;*************************************************************
SYSCTL_DC8_ADC1AIN15   EQU  0x80000000  ; ADC Module 1 AIN15 Pin Present
SYSCTL_DC8_ADC1AIN14   EQU  0x40000000  ; ADC Module 1 AIN14 Pin Present
SYSCTL_DC8_ADC1AIN13   EQU  0x20000000  ; ADC Module 1 AIN13 Pin Present
SYSCTL_DC8_ADC1AIN12   EQU  0x10000000  ; ADC Module 1 AIN12 Pin Present
SYSCTL_DC8_ADC1AIN11   EQU  0x08000000  ; ADC Module 1 AIN11 Pin Present
SYSCTL_DC8_ADC1AIN10   EQU  0x04000000  ; ADC Module 1 AIN10 Pin Present
SYSCTL_DC8_ADC1AIN9    EQU  0x02000000  ; ADC Module 1 AIN9 Pin Present
SYSCTL_DC8_ADC1AIN8    EQU  0x01000000  ; ADC Module 1 AIN8 Pin Present
SYSCTL_DC8_ADC1AIN7    EQU  0x00800000  ; ADC Module 1 AIN7 Pin Present
SYSCTL_DC8_ADC1AIN6    EQU  0x00400000  ; ADC Module 1 AIN6 Pin Present
SYSCTL_DC8_ADC1AIN5    EQU  0x00200000  ; ADC Module 1 AIN5 Pin Present
SYSCTL_DC8_ADC1AIN4    EQU  0x00100000  ; ADC Module 1 AIN4 Pin Present
SYSCTL_DC8_ADC1AIN3    EQU  0x00080000  ; ADC Module 1 AIN3 Pin Present
SYSCTL_DC8_ADC1AIN2    EQU  0x00040000  ; ADC Module 1 AIN2 Pin Present
SYSCTL_DC8_ADC1AIN1    EQU  0x00020000  ; ADC Module 1 AIN1 Pin Present
SYSCTL_DC8_ADC1AIN0    EQU  0x00010000  ; ADC Module 1 AIN0 Pin Present
SYSCTL_DC8_ADC0AIN15   EQU  0x00008000  ; ADC Module 0 AIN15 Pin Present
SYSCTL_DC8_ADC0AIN14   EQU  0x00004000  ; ADC Module 0 AIN14 Pin Present
SYSCTL_DC8_ADC0AIN13   EQU  0x00002000  ; ADC Module 0 AIN13 Pin Present
SYSCTL_DC8_ADC0AIN12   EQU  0x00001000  ; ADC Module 0 AIN12 Pin Present
SYSCTL_DC8_ADC0AIN11   EQU  0x00000800  ; ADC Module 0 AIN11 Pin Present
SYSCTL_DC8_ADC0AIN10   EQU  0x00000400  ; ADC Module 0 AIN10 Pin Present
SYSCTL_DC8_ADC0AIN9    EQU  0x00000200  ; ADC Module 0 AIN9 Pin Present
SYSCTL_DC8_ADC0AIN8    EQU  0x00000100  ; ADC Module 0 AIN8 Pin Present
SYSCTL_DC8_ADC0AIN7    EQU  0x00000080  ; ADC Module 0 AIN7 Pin Present
SYSCTL_DC8_ADC0AIN6    EQU  0x00000040  ; ADC Module 0 AIN6 Pin Present
SYSCTL_DC8_ADC0AIN5    EQU  0x00000020  ; ADC Module 0 AIN5 Pin Present
SYSCTL_DC8_ADC0AIN4    EQU  0x00000010  ; ADC Module 0 AIN4 Pin Present
SYSCTL_DC8_ADC0AIN3    EQU  0x00000008  ; ADC Module 0 AIN3 Pin Present
SYSCTL_DC8_ADC0AIN2    EQU  0x00000004  ; ADC Module 0 AIN2 Pin Present
SYSCTL_DC8_ADC0AIN1    EQU  0x00000002  ; ADC Module 0 AIN1 Pin Present
SYSCTL_DC8_ADC0AIN0    EQU  0x00000001  ; ADC Module 0 AIN0 Pin Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PBORCTL register.
;
;*************************************************************
SYSCTL_PBORCTL_BORIOR  EQU  0x00000002  ; BOR Interrupt or Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRCR0 register.
;
;*************************************************************
SYSCTL_SRCR0_WDT1      EQU  0x10000000  ; WDT1 Reset Control
SYSCTL_SRCR0_CAN1      EQU  0x02000000  ; CAN1 Reset Control
SYSCTL_SRCR0_CAN0      EQU  0x01000000  ; CAN0 Reset Control
SYSCTL_SRCR0_PWM0      EQU  0x00100000  ; PWM Reset Control
SYSCTL_SRCR0_ADC1      EQU  0x00020000  ; ADC1 Reset Control
SYSCTL_SRCR0_ADC0      EQU  0x00010000  ; ADC0 Reset Control
SYSCTL_SRCR0_HIB       EQU  0x00000040  ; HIB Reset Control
SYSCTL_SRCR0_WDT0      EQU  0x00000008  ; WDT0 Reset Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRCR1 register.
;
;*************************************************************
SYSCTL_SRCR1_COMP2     EQU  0x04000000  ; Analog Comp 2 Reset Control
SYSCTL_SRCR1_COMP1     EQU  0x02000000  ; Analog Comp 1 Reset Control
SYSCTL_SRCR1_COMP0     EQU  0x01000000  ; Analog Comp 0 Reset Control
SYSCTL_SRCR1_TIMER3    EQU  0x00080000  ; Timer 3 Reset Control
SYSCTL_SRCR1_TIMER2    EQU  0x00040000  ; Timer 2 Reset Control
SYSCTL_SRCR1_TIMER1    EQU  0x00020000  ; Timer 1 Reset Control
SYSCTL_SRCR1_TIMER0    EQU  0x00010000  ; Timer 0 Reset Control
SYSCTL_SRCR1_I2C1      EQU  0x00004000  ; I2C1 Reset Control
SYSCTL_SRCR1_I2C0      EQU  0x00001000  ; I2C0 Reset Control
SYSCTL_SRCR1_QEI1      EQU  0x00000200  ; QEI1 Reset Control
SYSCTL_SRCR1_QEI0      EQU  0x00000100  ; QEI0 Reset Control
SYSCTL_SRCR1_SSI1      EQU  0x00000020  ; SSI1 Reset Control
SYSCTL_SRCR1_SSI0      EQU  0x00000010  ; SSI0 Reset Control
SYSCTL_SRCR1_UART2     EQU  0x00000004  ; UART2 Reset Control
SYSCTL_SRCR1_UART1     EQU  0x00000002  ; UART1 Reset Control
SYSCTL_SRCR1_UART0     EQU  0x00000001  ; UART0 Reset Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRCR2 register.
;
;*************************************************************
SYSCTL_SRCR2_USB0      EQU  0x00010000  ; USB0 Reset Control
SYSCTL_SRCR2_UDMA      EQU  0x00002000  ; Micro-DMA Reset Control
SYSCTL_SRCR2_GPIOJ     EQU  0x00000100  ; Port J Reset Control
SYSCTL_SRCR2_GPIOH     EQU  0x00000080  ; Port H Reset Control
SYSCTL_SRCR2_GPIOG     EQU  0x00000040  ; Port G Reset Control
SYSCTL_SRCR2_GPIOF     EQU  0x00000020  ; Port F Reset Control
SYSCTL_SRCR2_GPIOE     EQU  0x00000010  ; Port E Reset Control
SYSCTL_SRCR2_GPIOD     EQU  0x00000008  ; Port D Reset Control
SYSCTL_SRCR2_GPIOC     EQU  0x00000004  ; Port C Reset Control
SYSCTL_SRCR2_GPIOB     EQU  0x00000002  ; Port B Reset Control
SYSCTL_SRCR2_GPIOA     EQU  0x00000001  ; Port A Reset Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RIS register.
;
;*************************************************************
SYSCTL_RIS_MOSCPUPRIS  EQU  0x00000100  ; MOSC Power Up Raw Interrupt
                                            ; Status
SYSCTL_RIS_USBPLLLRIS  EQU  0x00000080  ; USB PLL Lock Raw Interrupt
                                            ; Status
SYSCTL_RIS_PLLLRIS     EQU  0x00000040  ; PLL Lock Raw Interrupt Status
SYSCTL_RIS_MOFRIS      EQU  0x00000008  ; Main Oscillator Fault Raw
                                            ; Interrupt Status
SYSCTL_RIS_BORRIS      EQU  0x00000002  ; Brown-Out Reset Raw Interrupt
                                            ; Status

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_IMC register.
;
;*************************************************************
SYSCTL_IMC_MOSCPUPIM   EQU  0x00000100  ; MOSC Power Up Interrupt Mask
SYSCTL_IMC_USBPLLLIM   EQU  0x00000080  ; USB PLL Lock Interrupt Mask
SYSCTL_IMC_PLLLIM      EQU  0x00000040  ; PLL Lock Interrupt Mask
SYSCTL_IMC_MOFIM       EQU  0x00000008  ; Main Oscillator Fault Interrupt
                                            ; Mask
SYSCTL_IMC_BORIM       EQU  0x00000002  ; Brown-Out Reset Interrupt Mask

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_MISC register.
;
;*************************************************************
SYSCTL_MISC_MOSCPUPMIS EQU  0x00000100  ; MOSC Power Up Masked Interrupt
                                            ; Status
SYSCTL_MISC_USBPLLLMIS EQU  0x00000080  ; USB PLL Lock Masked Interrupt
                                            ; Status
SYSCTL_MISC_PLLLMIS    EQU  0x00000040  ; PLL Lock Masked Interrupt Status
SYSCTL_MISC_MOFMIS     EQU  0x00000008  ; Main Oscillator Fault Masked
                                            ; Interrupt Status
SYSCTL_MISC_BORMIS     EQU  0x00000002  ; BOR Masked Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RESC register.
;
;*************************************************************
SYSCTL_RESC_MOSCFAIL   EQU  0x00010000  ; MOSC Failure Reset
SYSCTL_RESC_WDT1       EQU  0x00000020  ; Watchdog Timer 1 Reset
SYSCTL_RESC_SW         EQU  0x00000010  ; Software Reset
SYSCTL_RESC_WDT0       EQU  0x00000008  ; Watchdog Timer 0 Reset
SYSCTL_RESC_BOR        EQU  0x00000004  ; Brown-Out Reset
SYSCTL_RESC_POR        EQU  0x00000002  ; Power-On Reset
SYSCTL_RESC_EXT        EQU  0x00000001  ; External Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCC register.
;
;*************************************************************
SYSCTL_RCC_ACG         EQU  0x08000000  ; Auto Clock Gating
SYSCTL_RCC_SYSDIV_M    EQU  0x07800000  ; System Clock Divisor
SYSCTL_RCC_USESYSDIV   EQU  0x00400000  ; Enable System Clock Divider
SYSCTL_RCC_PWRDN       EQU  0x00002000  ; PLL Power Down
SYSCTL_RCC_BYPASS      EQU  0x00000800  ; PLL Bypass
SYSCTL_RCC_XTAL_M      EQU  0x000007C0  ; Crystal Value
SYSCTL_RCC_XTAL_4MHZ   EQU  0x00000180  ; 4 MHz
SYSCTL_RCC_XTAL_4_09MHZ EQU  0x000001C0  ; 4.096 MHz
SYSCTL_RCC_XTAL_4_91MHZ EQU  0x00000200  ; 4.9152 MHz
SYSCTL_RCC_XTAL_5MHZ   EQU  0x00000240  ; 5 MHz
SYSCTL_RCC_XTAL_5_12MHZ EQU  0x00000280  ; 5.12 MHz
SYSCTL_RCC_XTAL_6MHZ   EQU  0x000002C0  ; 6 MHz
SYSCTL_RCC_XTAL_6_14MHZ EQU  0x00000300  ; 6.144 MHz
SYSCTL_RCC_XTAL_7_37MHZ EQU  0x00000340  ; 7.3728 MHz
SYSCTL_RCC_XTAL_8MHZ   EQU  0x00000380  ; 8 MHz
SYSCTL_RCC_XTAL_8_19MHZ EQU  0x000003C0  ; 8.192 MHz
SYSCTL_RCC_XTAL_10MHZ  EQU  0x00000400  ; 10 MHz
SYSCTL_RCC_XTAL_12MHZ  EQU  0x00000440  ; 12 MHz
SYSCTL_RCC_XTAL_12_2MHZ EQU  0x00000480  ; 12.288 MHz
SYSCTL_RCC_XTAL_13_5MHZ EQU  0x000004C0  ; 13.56 MHz
SYSCTL_RCC_XTAL_14_3MHZ EQU  0x00000500  ; 14.31818 MHz
SYSCTL_RCC_XTAL_16MHZ  EQU  0x00000540  ; 16 MHz
SYSCTL_RCC_XTAL_16_3MHZ EQU  0x00000580  ; 16.384 MHz
SYSCTL_RCC_XTAL_18MHZ  EQU  0x000005C0  ; 18.0 MHz
SYSCTL_RCC_XTAL_20MHZ  EQU  0x00000600  ; 20.0 MHz
SYSCTL_RCC_XTAL_24MHZ  EQU  0x00000640  ; 24.0 MHz
SYSCTL_RCC_XTAL_25MHZ  EQU  0x00000680  ; 25.0 MHz
SYSCTL_RCC_OSCSRC_M    EQU  0x00000030  ; Oscillator Source
SYSCTL_RCC_OSCSRC_MAIN EQU  0x00000000  ; MOSC
SYSCTL_RCC_OSCSRC_INT  EQU  0x00000010  ; IOSC
SYSCTL_RCC_OSCSRC_INT4 EQU  0x00000020  ; IOSC/4
SYSCTL_RCC_OSCSRC_30   EQU  0x00000030  ; 30 kHz
SYSCTL_RCC_IOSCDIS     EQU  0x00000002  ; Internal Oscillator Disable
SYSCTL_RCC_MOSCDIS     EQU  0x00000001  ; Main Oscillator Disable
SYSCTL_RCC_SYSDIV_S    EQU  23

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_GPIOHBCTL
; register.
;
;*************************************************************
SYSCTL_GPIOHBCTL_PORTF EQU  0x00000020  ; Port F Advanced High-Performance
                                            ; Bus
SYSCTL_GPIOHBCTL_PORTE EQU  0x00000010  ; Port E Advanced High-Performance
                                            ; Bus
SYSCTL_GPIOHBCTL_PORTD EQU  0x00000008  ; Port D Advanced High-Performance
                                            ; Bus
SYSCTL_GPIOHBCTL_PORTC EQU  0x00000004  ; Port C Advanced High-Performance
                                            ; Bus
SYSCTL_GPIOHBCTL_PORTB EQU  0x00000002  ; Port B Advanced High-Performance
                                            ; Bus
SYSCTL_GPIOHBCTL_PORTA EQU  0x00000001  ; Port A Advanced High-Performance
                                            ; Bus

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCC2 register.
;
;*************************************************************
SYSCTL_RCC2_USERCC2    EQU  0x80000000  ; Use RCC2
SYSCTL_RCC2_DIV400     EQU  0x40000000  ; Divide PLL as 400 MHz vs. 200
                                            ; MHz
SYSCTL_RCC2_SYSDIV2_M  EQU  0x1F800000  ; System Clock Divisor 2
SYSCTL_RCC2_SYSDIV2_2  EQU  0x00800000  ; System clock /2
SYSCTL_RCC2_SYSDIV2_3  EQU  0x01000000  ; System clock /3
SYSCTL_RCC2_SYSDIV2_4  EQU  0x01800000  ; System clock /4
SYSCTL_RCC2_SYSDIV2_5  EQU  0x02000000  ; System clock /5
SYSCTL_RCC2_SYSDIV2_6  EQU  0x02800000  ; System clock /6
SYSCTL_RCC2_SYSDIV2_7  EQU  0x03000000  ; System clock /7
SYSCTL_RCC2_SYSDIV2_8  EQU  0x03800000  ; System clock /8
SYSCTL_RCC2_SYSDIV2_9  EQU  0x04000000  ; System clock /9
SYSCTL_RCC2_SYSDIV2_10 EQU  0x04800000  ; System clock /10
SYSCTL_RCC2_SYSDIV2_11 EQU  0x05000000  ; System clock /11
SYSCTL_RCC2_SYSDIV2_12 EQU  0x05800000  ; System clock /12
SYSCTL_RCC2_SYSDIV2_13 EQU  0x06000000  ; System clock /13
SYSCTL_RCC2_SYSDIV2_14 EQU  0x06800000  ; System clock /14
SYSCTL_RCC2_SYSDIV2_15 EQU  0x07000000  ; System clock /15
SYSCTL_RCC2_SYSDIV2_16 EQU  0x07800000  ; System clock /16
SYSCTL_RCC2_SYSDIV2_17 EQU  0x08000000  ; System clock /17
SYSCTL_RCC2_SYSDIV2_18 EQU  0x08800000  ; System clock /18
SYSCTL_RCC2_SYSDIV2_19 EQU  0x09000000  ; System clock /19
SYSCTL_RCC2_SYSDIV2_20 EQU  0x09800000  ; System clock /20
SYSCTL_RCC2_SYSDIV2_21 EQU  0x0A000000  ; System clock /21
SYSCTL_RCC2_SYSDIV2_22 EQU  0x0A800000  ; System clock /22
SYSCTL_RCC2_SYSDIV2_23 EQU  0x0B000000  ; System clock /23
SYSCTL_RCC2_SYSDIV2_24 EQU  0x0B800000  ; System clock /24
SYSCTL_RCC2_SYSDIV2_25 EQU  0x0C000000  ; System clock /25
SYSCTL_RCC2_SYSDIV2_26 EQU  0x0C800000  ; System clock /26
SYSCTL_RCC2_SYSDIV2_27 EQU  0x0D000000  ; System clock /27
SYSCTL_RCC2_SYSDIV2_28 EQU  0x0D800000  ; System clock /28
SYSCTL_RCC2_SYSDIV2_29 EQU  0x0E000000  ; System clock /29
SYSCTL_RCC2_SYSDIV2_30 EQU  0x0E800000  ; System clock /30
SYSCTL_RCC2_SYSDIV2_31 EQU  0x0F000000  ; System clock /31
SYSCTL_RCC2_SYSDIV2_32 EQU  0x0F800000  ; System clock /32
SYSCTL_RCC2_SYSDIV2_33 EQU  0x10000000  ; System clock /33
SYSCTL_RCC2_SYSDIV2_34 EQU  0x10800000  ; System clock /34
SYSCTL_RCC2_SYSDIV2_35 EQU  0x11000000  ; System clock /35
SYSCTL_RCC2_SYSDIV2_36 EQU  0x11800000  ; System clock /36
SYSCTL_RCC2_SYSDIV2_37 EQU  0x12000000  ; System clock /37
SYSCTL_RCC2_SYSDIV2_38 EQU  0x12800000  ; System clock /38
SYSCTL_RCC2_SYSDIV2_39 EQU  0x13000000  ; System clock /39
SYSCTL_RCC2_SYSDIV2_40 EQU  0x13800000  ; System clock /40
SYSCTL_RCC2_SYSDIV2_41 EQU  0x14000000  ; System clock /41
SYSCTL_RCC2_SYSDIV2_42 EQU  0x14800000  ; System clock /42
SYSCTL_RCC2_SYSDIV2_43 EQU  0x15000000  ; System clock /43
SYSCTL_RCC2_SYSDIV2_44 EQU  0x15800000  ; System clock /44
SYSCTL_RCC2_SYSDIV2_45 EQU  0x16000000  ; System clock /45
SYSCTL_RCC2_SYSDIV2_46 EQU  0x16800000  ; System clock /46
SYSCTL_RCC2_SYSDIV2_47 EQU  0x17000000  ; System clock /47
SYSCTL_RCC2_SYSDIV2_48 EQU  0x17800000  ; System clock /48
SYSCTL_RCC2_SYSDIV2_49 EQU  0x18000000  ; System clock /49
SYSCTL_RCC2_SYSDIV2_50 EQU  0x18800000  ; System clock /50
SYSCTL_RCC2_SYSDIV2_51 EQU  0x19000000  ; System clock /51
SYSCTL_RCC2_SYSDIV2_52 EQU  0x19800000  ; System clock /52
SYSCTL_RCC2_SYSDIV2_53 EQU  0x1A000000  ; System clock /53
SYSCTL_RCC2_SYSDIV2_54 EQU  0x1A800000  ; System clock /54
SYSCTL_RCC2_SYSDIV2_55 EQU  0x1B000000  ; System clock /55
SYSCTL_RCC2_SYSDIV2_56 EQU  0x1B800000  ; System clock /56
SYSCTL_RCC2_SYSDIV2_57 EQU  0x1C000000  ; System clock /57
SYSCTL_RCC2_SYSDIV2_58 EQU  0x1C800000  ; System clock /58
SYSCTL_RCC2_SYSDIV2_59 EQU  0x1D000000  ; System clock /59
SYSCTL_RCC2_SYSDIV2_60 EQU  0x1D800000  ; System clock /60
SYSCTL_RCC2_SYSDIV2_61 EQU  0x1E000000  ; System clock /61
SYSCTL_RCC2_SYSDIV2_62 EQU  0x1E800000  ; System clock /62
SYSCTL_RCC2_SYSDIV2_63 EQU  0x1F000000  ; System clock /63
SYSCTL_RCC2_SYSDIV2_64 EQU  0x1F800000  ; System clock /64
SYSCTL_RCC2_SYSDIV2LSB EQU  0x00400000  ; Additional LSB for SYSDIV2
SYSCTL_RCC2_USBPWRDN   EQU  0x00004000  ; Power-Down USB PLL
SYSCTL_RCC2_PWRDN2     EQU  0x00002000  ; Power-Down PLL 2
SYSCTL_RCC2_BYPASS2    EQU  0x00000800  ; PLL Bypass 2
SYSCTL_RCC2_OSCSRC2_M  EQU  0x00000070  ; Oscillator Source 2
SYSCTL_RCC2_OSCSRC2_MO EQU  0x00000000  ; MOSC
SYSCTL_RCC2_OSCSRC2_IO EQU  0x00000010  ; PIOSC
SYSCTL_RCC2_OSCSRC2_IO4 EQU  0x00000020  ; PIOSC/4
SYSCTL_RCC2_OSCSRC2_30 EQU  0x00000030  ; 30 kHz
SYSCTL_RCC2_OSCSRC2_32 EQU  0x00000070  ; 32.768 kHz
SYSCTL_RCC2_SYSDIV2_S    EQU 23

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_MOSCCTL register.
;
;*************************************************************
SYSCTL_MOSCCTL_NOXTAL  EQU  0x00000004  ; No Crystal Connected
SYSCTL_MOSCCTL_MOSCIM  EQU  0x00000002  ; MOSC Failure Action
SYSCTL_MOSCCTL_CVAL    EQU  0x00000001  ; Clock Validation for MOSC

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGC0 register.
;
;*************************************************************
SYSCTL_RCGC0_WDT1      EQU  0x10000000  ; WDT1 Clock Gating Control
SYSCTL_RCGC0_CAN1      EQU  0x02000000  ; CAN1 Clock Gating Control
SYSCTL_RCGC0_CAN0      EQU  0x01000000  ; CAN0 Clock Gating Control
SYSCTL_RCGC0_PWM0      EQU  0x00100000  ; PWM Clock Gating Control
SYSCTL_RCGC0_ADC1      EQU  0x00020000  ; ADC1 Clock Gating Control
SYSCTL_RCGC0_ADC0      EQU  0x00010000  ; ADC0 Clock Gating Control
SYSCTL_RCGC0_ADC1SPD_M EQU  0x00000C00  ; ADC1 Sample Speed
SYSCTL_RCGC0_ADC1SPD_125K EQU  0x00000000  ; 125K samples/second
SYSCTL_RCGC0_ADC1SPD_250K EQU  0x00000400  ; 250K samples/second
SYSCTL_RCGC0_ADC1SPD_500K EQU  0x00000800  ; 500K samples/second
SYSCTL_RCGC0_ADC1SPD_1M EQU  0x00000C00  ; 1M samples/second
SYSCTL_RCGC0_ADC0SPD_M EQU  0x00000300  ; ADC0 Sample Speed
SYSCTL_RCGC0_ADC0SPD_125K EQU  0x00000000  ; 125K samples/second
SYSCTL_RCGC0_ADC0SPD_250K EQU  0x00000100  ; 250K samples/second
SYSCTL_RCGC0_ADC0SPD_500K EQU  0x00000200  ; 500K samples/second
SYSCTL_RCGC0_ADC0SPD_1M EQU  0x00000300  ; 1M samples/second
SYSCTL_RCGC0_HIB       EQU  0x00000040  ; HIB Clock Gating Control
SYSCTL_RCGC0_WDT0      EQU  0x00000008  ; WDT0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGC1 register.
;
;*************************************************************
SYSCTL_RCGC1_COMP2     EQU  0x04000000  ; Analog Comparator 2 Clock Gating
SYSCTL_RCGC1_COMP1     EQU  0x02000000  ; Analog Comparator 1 Clock Gating
SYSCTL_RCGC1_COMP0     EQU  0x01000000  ; Analog Comparator 0 Clock Gating
SYSCTL_RCGC1_TIMER3    EQU  0x00080000  ; Timer 3 Clock Gating Control
SYSCTL_RCGC1_TIMER2    EQU  0x00040000  ; Timer 2 Clock Gating Control
SYSCTL_RCGC1_TIMER1    EQU  0x00020000  ; Timer 1 Clock Gating Control
SYSCTL_RCGC1_TIMER0    EQU  0x00010000  ; Timer 0 Clock Gating Control
SYSCTL_RCGC1_I2C1      EQU  0x00004000  ; I2C1 Clock Gating Control
SYSCTL_RCGC1_I2C0      EQU  0x00001000  ; I2C0 Clock Gating Control
SYSCTL_RCGC1_QEI1      EQU  0x00000200  ; QEI1 Clock Gating Control
SYSCTL_RCGC1_QEI0      EQU  0x00000100  ; QEI0 Clock Gating Control
SYSCTL_RCGC1_SSI1      EQU  0x00000020  ; SSI1 Clock Gating Control
SYSCTL_RCGC1_SSI0      EQU  0x00000010  ; SSI0 Clock Gating Control
SYSCTL_RCGC1_UART2     EQU  0x00000004  ; UART2 Clock Gating Control
SYSCTL_RCGC1_UART1     EQU  0x00000002  ; UART1 Clock Gating Control
SYSCTL_RCGC1_UART0     EQU  0x00000001  ; UART0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGC2 register.
;
;*************************************************************
SYSCTL_RCGC2_USB0      EQU  0x00010000  ; USB0 Clock Gating Control
SYSCTL_RCGC2_UDMA      EQU  0x00002000  ; Micro-DMA Clock Gating Control
SYSCTL_RCGC2_GPIOJ     EQU  0x00000100  ; Port J Clock Gating Control
SYSCTL_RCGC2_GPIOH     EQU  0x00000080  ; Port H Clock Gating Control
SYSCTL_RCGC2_GPIOG     EQU  0x00000040  ; Port G Clock Gating Control
SYSCTL_RCGC2_GPIOF     EQU  0x00000020  ; Port F Clock Gating Control
SYSCTL_RCGC2_GPIOE     EQU  0x00000010  ; Port E Clock Gating Control
SYSCTL_RCGC2_GPIOD     EQU  0x00000008  ; Port D Clock Gating Control
SYSCTL_RCGC2_GPIOC     EQU  0x00000004  ; Port C Clock Gating Control
SYSCTL_RCGC2_GPIOB     EQU  0x00000002  ; Port B Clock Gating Control
SYSCTL_RCGC2_GPIOA     EQU  0x00000001  ; Port A Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGC0 register.
;
;*************************************************************
SYSCTL_SCGC0_WDT1      EQU  0x10000000  ; WDT1 Clock Gating Control
SYSCTL_SCGC0_CAN1      EQU  0x02000000  ; CAN1 Clock Gating Control
SYSCTL_SCGC0_CAN0      EQU  0x01000000  ; CAN0 Clock Gating Control
SYSCTL_SCGC0_PWM0      EQU  0x00100000  ; PWM Clock Gating Control
SYSCTL_SCGC0_ADC1      EQU  0x00020000  ; ADC1 Clock Gating Control
SYSCTL_SCGC0_ADC0      EQU  0x00010000  ; ADC0 Clock Gating Control
SYSCTL_SCGC0_HIB       EQU  0x00000040  ; HIB Clock Gating Control
SYSCTL_SCGC0_WDT0      EQU  0x00000008  ; WDT0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGC1 register.
;
;*************************************************************
SYSCTL_SCGC1_COMP2     EQU  0x04000000  ; Analog Comparator 2 Clock Gating
SYSCTL_SCGC1_COMP1     EQU  0x02000000  ; Analog Comparator 1 Clock Gating
SYSCTL_SCGC1_COMP0     EQU  0x01000000  ; Analog Comparator 0 Clock Gating
SYSCTL_SCGC1_TIMER3    EQU  0x00080000  ; Timer 3 Clock Gating Control
SYSCTL_SCGC1_TIMER2    EQU  0x00040000  ; Timer 2 Clock Gating Control
SYSCTL_SCGC1_TIMER1    EQU  0x00020000  ; Timer 1 Clock Gating Control
SYSCTL_SCGC1_TIMER0    EQU  0x00010000  ; Timer 0 Clock Gating Control
SYSCTL_SCGC1_I2C1      EQU  0x00004000  ; I2C1 Clock Gating Control
SYSCTL_SCGC1_I2C0      EQU  0x00001000  ; I2C0 Clock Gating Control
SYSCTL_SCGC1_QEI1      EQU  0x00000200  ; QEI1 Clock Gating Control
SYSCTL_SCGC1_QEI0      EQU  0x00000100  ; QEI0 Clock Gating Control
SYSCTL_SCGC1_SSI1      EQU  0x00000020  ; SSI1 Clock Gating Control
SYSCTL_SCGC1_SSI0      EQU  0x00000010  ; SSI0 Clock Gating Control
SYSCTL_SCGC1_UART2     EQU  0x00000004  ; UART2 Clock Gating Control
SYSCTL_SCGC1_UART1     EQU  0x00000002  ; UART1 Clock Gating Control
SYSCTL_SCGC1_UART0     EQU  0x00000001  ; UART0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGC2 register.
;
;*************************************************************
SYSCTL_SCGC2_USB0      EQU  0x00010000  ; USB0 Clock Gating Control
SYSCTL_SCGC2_UDMA      EQU  0x00002000  ; Micro-DMA Clock Gating Control
SYSCTL_SCGC2_GPIOJ     EQU  0x00000100  ; Port J Clock Gating Control
SYSCTL_SCGC2_GPIOH     EQU  0x00000080  ; Port H Clock Gating Control
SYSCTL_SCGC2_GPIOG     EQU  0x00000040  ; Port G Clock Gating Control
SYSCTL_SCGC2_GPIOF     EQU  0x00000020  ; Port F Clock Gating Control
SYSCTL_SCGC2_GPIOE     EQU  0x00000010  ; Port E Clock Gating Control
SYSCTL_SCGC2_GPIOD     EQU  0x00000008  ; Port D Clock Gating Control
SYSCTL_SCGC2_GPIOC     EQU  0x00000004  ; Port C Clock Gating Control
SYSCTL_SCGC2_GPIOB     EQU  0x00000002  ; Port B Clock Gating Control
SYSCTL_SCGC2_GPIOA     EQU  0x00000001  ; Port A Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGC0 register.
;
;*************************************************************
SYSCTL_DCGC0_WDT1      EQU  0x10000000  ; WDT1 Clock Gating Control
SYSCTL_DCGC0_CAN1      EQU  0x02000000  ; CAN1 Clock Gating Control
SYSCTL_DCGC0_CAN0      EQU  0x01000000  ; CAN0 Clock Gating Control
SYSCTL_DCGC0_PWM0      EQU  0x00100000  ; PWM Clock Gating Control
SYSCTL_DCGC0_ADC1      EQU  0x00020000  ; ADC1 Clock Gating Control
SYSCTL_DCGC0_ADC0      EQU  0x00010000  ; ADC0 Clock Gating Control
SYSCTL_DCGC0_HIB       EQU  0x00000040  ; HIB Clock Gating Control
SYSCTL_DCGC0_WDT0      EQU  0x00000008  ; WDT0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGC1 register.
;
;*************************************************************
SYSCTL_DCGC1_COMP2     EQU  0x04000000  ; Analog Comparator 2 Clock Gating
SYSCTL_DCGC1_COMP1     EQU  0x02000000  ; Analog Comparator 1 Clock Gating
SYSCTL_DCGC1_COMP0     EQU  0x01000000  ; Analog Comparator 0 Clock Gating
SYSCTL_DCGC1_TIMER3    EQU  0x00080000  ; Timer 3 Clock Gating Control
SYSCTL_DCGC1_TIMER2    EQU  0x00040000  ; Timer 2 Clock Gating Control
SYSCTL_DCGC1_TIMER1    EQU  0x00020000  ; Timer 1 Clock Gating Control
SYSCTL_DCGC1_TIMER0    EQU  0x00010000  ; Timer 0 Clock Gating Control
SYSCTL_DCGC1_I2C1      EQU  0x00004000  ; I2C1 Clock Gating Control
SYSCTL_DCGC1_I2C0      EQU  0x00001000  ; I2C0 Clock Gating Control
SYSCTL_DCGC1_QEI1      EQU  0x00000200  ; QEI1 Clock Gating Control
SYSCTL_DCGC1_QEI0      EQU  0x00000100  ; QEI0 Clock Gating Control
SYSCTL_DCGC1_SSI1      EQU  0x00000020  ; SSI1 Clock Gating Control
SYSCTL_DCGC1_SSI0      EQU  0x00000010  ; SSI0 Clock Gating Control
SYSCTL_DCGC1_UART2     EQU  0x00000004  ; UART2 Clock Gating Control
SYSCTL_DCGC1_UART1     EQU  0x00000002  ; UART1 Clock Gating Control
SYSCTL_DCGC1_UART0     EQU  0x00000001  ; UART0 Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGC2 register.
;
;*************************************************************
SYSCTL_DCGC2_USB0      EQU  0x00010000  ; USB0 Clock Gating Control
SYSCTL_DCGC2_UDMA      EQU  0x00002000  ; Micro-DMA Clock Gating Control
SYSCTL_DCGC2_GPIOJ     EQU  0x00000100  ; Port J Clock Gating Control
SYSCTL_DCGC2_GPIOH     EQU  0x00000080  ; Port H Clock Gating Control
SYSCTL_DCGC2_GPIOG     EQU  0x00000040  ; Port G Clock Gating Control
SYSCTL_DCGC2_GPIOF     EQU  0x00000020  ; Port F Clock Gating Control
SYSCTL_DCGC2_GPIOE     EQU  0x00000010  ; Port E Clock Gating Control
SYSCTL_DCGC2_GPIOD     EQU  0x00000008  ; Port D Clock Gating Control
SYSCTL_DCGC2_GPIOC     EQU  0x00000004  ; Port C Clock Gating Control
SYSCTL_DCGC2_GPIOB     EQU  0x00000002  ; Port B Clock Gating Control
SYSCTL_DCGC2_GPIOA     EQU  0x00000001  ; Port A Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DSLPCLKCFG
; register.
;
;*************************************************************
SYSCTL_DSLPCLKCFG_D_M  EQU  0x1F800000  ; Divider Field Override
SYSCTL_DSLPCLKCFG_D_1  EQU  0x00000000  ; System clock /1
SYSCTL_DSLPCLKCFG_D_2  EQU  0x00800000  ; System clock /2
SYSCTL_DSLPCLKCFG_D_3  EQU  0x01000000  ; System clock /3
SYSCTL_DSLPCLKCFG_D_4  EQU  0x01800000  ; System clock /4
SYSCTL_DSLPCLKCFG_D_64 EQU  0x1F800000  ; System clock /64
SYSCTL_DSLPCLKCFG_O_M  EQU  0x00000070  ; Clock Source
SYSCTL_DSLPCLKCFG_O_IGN EQU  0x00000000  ; MOSC
SYSCTL_DSLPCLKCFG_O_IO EQU  0x00000010  ; PIOSC
SYSCTL_DSLPCLKCFG_O_30 EQU  0x00000030  ; 30 kHz
SYSCTL_DSLPCLKCFG_O_32 EQU  0x00000070  ; 32.768 kHz

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SYSPROP register.
;
;*************************************************************
SYSCTL_SYSPROP_FPU     EQU  0x00000001  ; FPU Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PIOSCCAL
; register.
;
;*************************************************************
SYSCTL_PIOSCCAL_UTEN   EQU  0x80000000  ; Use User Trim Value
SYSCTL_PIOSCCAL_CAL    EQU  0x00000200  ; Start Calibration
SYSCTL_PIOSCCAL_UPDATE EQU  0x00000100  ; Update Trim
SYSCTL_PIOSCCAL_UT_M   EQU  0x0000007F  ; User Trim Value
SYSCTL_PIOSCCAL_UT_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PIOSCSTAT
; register.
;
;*************************************************************
SYSCTL_PIOSCSTAT_DT_M  EQU  0x007F0000  ; Default Trim Value
SYSCTL_PIOSCSTAT_CR_M  EQU  0x00000300  ; Calibration Result
SYSCTL_PIOSCSTAT_CRNONE EQU  0x00000000  ; Calibration has not been
                                            ; attempted
SYSCTL_PIOSCSTAT_CRPASS EQU  0x00000100  ; The last calibration operation
                                            ; completed to meet 1% accuracy
SYSCTL_PIOSCSTAT_CRFAIL EQU  0x00000200  ; The last calibration operation
                                            ; failed to meet 1% accuracy
SYSCTL_PIOSCSTAT_CT_M  EQU  0x0000007F  ; Calibration Trim Value
SYSCTL_PIOSCSTAT_DT_S    EQU 16
SYSCTL_PIOSCSTAT_CT_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PLLFREQ0
; register.
;
;*************************************************************
SYSCTL_PLLFREQ0_MFRAC_M EQU  0x000FFC00  ; PLL M Fractional Value
SYSCTL_PLLFREQ0_MINT_M EQU  0x000003FF  ; PLL M Integer Value
SYSCTL_PLLFREQ0_MFRAC_S EQU 10
SYSCTL_PLLFREQ0_MINT_S EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PLLFREQ1
; register.
;
;*************************************************************
SYSCTL_PLLFREQ1_Q_M    EQU  0x00001F00  ; PLL Q Value
SYSCTL_PLLFREQ1_N_M    EQU  0x0000001F  ; PLL N Value
SYSCTL_PLLFREQ1_Q_S    EQU  8
SYSCTL_PLLFREQ1_N_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PLLSTAT register.
;
;*************************************************************
SYSCTL_PLLSTAT_LOCK    EQU  0x00000001  ; PLL Lock

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DC9 register.
;
;*************************************************************
SYSCTL_DC9_ADC1DC7     EQU  0x00800000  ; ADC1 DC7 Present
SYSCTL_DC9_ADC1DC6     EQU  0x00400000  ; ADC1 DC6 Present
SYSCTL_DC9_ADC1DC5     EQU  0x00200000  ; ADC1 DC5 Present
SYSCTL_DC9_ADC1DC4     EQU  0x00100000  ; ADC1 DC4 Present
SYSCTL_DC9_ADC1DC3     EQU  0x00080000  ; ADC1 DC3 Present
SYSCTL_DC9_ADC1DC2     EQU  0x00040000  ; ADC1 DC2 Present
SYSCTL_DC9_ADC1DC1     EQU  0x00020000  ; ADC1 DC1 Present
SYSCTL_DC9_ADC1DC0     EQU  0x00010000  ; ADC1 DC0 Present
SYSCTL_DC9_ADC0DC7     EQU  0x00000080  ; ADC0 DC7 Present
SYSCTL_DC9_ADC0DC6     EQU  0x00000040  ; ADC0 DC6 Present
SYSCTL_DC9_ADC0DC5     EQU  0x00000020  ; ADC0 DC5 Present
SYSCTL_DC9_ADC0DC4     EQU  0x00000010  ; ADC0 DC4 Present
SYSCTL_DC9_ADC0DC3     EQU  0x00000008  ; ADC0 DC3 Present
SYSCTL_DC9_ADC0DC2     EQU  0x00000004  ; ADC0 DC2 Present
SYSCTL_DC9_ADC0DC1     EQU  0x00000002  ; ADC0 DC1 Present
SYSCTL_DC9_ADC0DC0     EQU  0x00000001  ; ADC0 DC0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_NVMSTAT register.
;
;*************************************************************
SYSCTL_NVMSTAT_TPSW    EQU  0x00000010  ; Third Party Software Present
SYSCTL_NVMSTAT_FWB     EQU  0x00000001  ; 32 Word Flash Write Buffer
                                            ; Active

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPWD register.
;
;*************************************************************
SYSCTL_PPWD_P1         EQU  0x00000002  ; Watchdog Timer 1 Present
SYSCTL_PPWD_P0         EQU  0x00000001  ; Watchdog Timer 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPTIMER register.
;
;*************************************************************
SYSCTL_PPTIMER_P5      EQU  0x00000020  ; Timer 5 Present
SYSCTL_PPTIMER_P4      EQU  0x00000010  ; Timer 4 Present
SYSCTL_PPTIMER_P3      EQU  0x00000008  ; Timer 3 Present
SYSCTL_PPTIMER_P2      EQU  0x00000004  ; Timer 2 Present
SYSCTL_PPTIMER_P1      EQU  0x00000002  ; Timer 1 Present
SYSCTL_PPTIMER_P0      EQU  0x00000001  ; Timer 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPGPIO register.
;
;*************************************************************
SYSCTL_PPGPIO_P14      EQU  0x00004000  ; GPIO Port Q Present
SYSCTL_PPGPIO_P13      EQU  0x00002000  ; GPIO Port P Present
SYSCTL_PPGPIO_P12      EQU  0x00001000  ; GPIO Port N Present
SYSCTL_PPGPIO_P11      EQU  0x00000800  ; GPIO Port M Present
SYSCTL_PPGPIO_P10      EQU  0x00000400  ; GPIO Port L Present
SYSCTL_PPGPIO_P9       EQU  0x00000200  ; GPIO Port K Present
SYSCTL_PPGPIO_P8       EQU  0x00000100  ; GPIO Port J Present
SYSCTL_PPGPIO_P7       EQU  0x00000080  ; GPIO Port H Present
SYSCTL_PPGPIO_P6       EQU  0x00000040  ; GPIO Port G Present
SYSCTL_PPGPIO_P5       EQU  0x00000020  ; GPIO Port F Present
SYSCTL_PPGPIO_P4       EQU  0x00000010  ; GPIO Port E Present
SYSCTL_PPGPIO_P3       EQU  0x00000008  ; GPIO Port D Present
SYSCTL_PPGPIO_P2       EQU  0x00000004  ; GPIO Port C Present
SYSCTL_PPGPIO_P1       EQU  0x00000002  ; GPIO Port B Present
SYSCTL_PPGPIO_P0       EQU  0x00000001  ; GPIO Port A Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPDMA register.
;
;*************************************************************
SYSCTL_PPDMA_P0        EQU  0x00000001  ; uDMA Module Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPHIB register.
;
;*************************************************************
SYSCTL_PPHIB_P0        EQU  0x00000001  ; Hibernation Module Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPUART register.
;
;*************************************************************
SYSCTL_PPUART_P7       EQU  0x00000080  ; UART Module 7 Present
SYSCTL_PPUART_P6       EQU  0x00000040  ; UART Module 6 Present
SYSCTL_PPUART_P5       EQU  0x00000020  ; UART Module 5 Present
SYSCTL_PPUART_P4       EQU  0x00000010  ; UART Module 4 Present
SYSCTL_PPUART_P3       EQU  0x00000008  ; UART Module 3 Present
SYSCTL_PPUART_P2       EQU  0x00000004  ; UART Module 2 Present
SYSCTL_PPUART_P1       EQU  0x00000002  ; UART Module 1 Present
SYSCTL_PPUART_P0       EQU  0x00000001  ; UART Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPSSI register.
;
;*************************************************************
SYSCTL_PPSSI_P3        EQU  0x00000008  ; SSI Module 3 Present
SYSCTL_PPSSI_P2        EQU  0x00000004  ; SSI Module 2 Present
SYSCTL_PPSSI_P1        EQU  0x00000002  ; SSI Module 1 Present
SYSCTL_PPSSI_P0        EQU  0x00000001  ; SSI Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPI2C register.
;
;*************************************************************
SYSCTL_PPI2C_P5        EQU  0x00000020  ; I2C Module 5 Present
SYSCTL_PPI2C_P4        EQU  0x00000010  ; I2C Module 4 Present
SYSCTL_PPI2C_P3        EQU  0x00000008  ; I2C Module 3 Present
SYSCTL_PPI2C_P2        EQU  0x00000004  ; I2C Module 2 Present
SYSCTL_PPI2C_P1        EQU  0x00000002  ; I2C Module 1 Present
SYSCTL_PPI2C_P0        EQU  0x00000001  ; I2C Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPUSB register.
;
;*************************************************************
SYSCTL_PPUSB_P0        EQU  0x00000001  ; USB Module Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPCAN register.
;
;*************************************************************
SYSCTL_PPCAN_P1        EQU  0x00000002  ; CAN Module 1 Present
SYSCTL_PPCAN_P0        EQU  0x00000001  ; CAN Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPADC register.
;
;*************************************************************
SYSCTL_PPADC_P1        EQU  0x00000002  ; ADC Module 1 Present
SYSCTL_PPADC_P0        EQU  0x00000001  ; ADC Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPACMP register.
;
;*************************************************************
SYSCTL_PPACMP_P0       EQU  0x00000001  ; Analog Comparator Module Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPPWM register.
;
;*************************************************************
SYSCTL_PPPWM_P1        EQU  0x00000002  ; PWM Module 1 Present
SYSCTL_PPPWM_P0        EQU  0x00000001  ; PWM Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPQEI register.
;
;*************************************************************
SYSCTL_PPQEI_P1        EQU  0x00000002  ; QEI Module 1 Present
SYSCTL_PPQEI_P0        EQU  0x00000001  ; QEI Module 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPEEPROM
; register.
;
;*************************************************************
SYSCTL_PPEEPROM_P0     EQU  0x00000001  ; EEPROM Module Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PPWTIMER
; register.
;
;*************************************************************
SYSCTL_PPWTIMER_P5     EQU  0x00000020  ; Wide Timer 5 Present
SYSCTL_PPWTIMER_P4     EQU  0x00000010  ; Wide Timer 4 Present
SYSCTL_PPWTIMER_P3     EQU  0x00000008  ; Wide Timer 3 Present
SYSCTL_PPWTIMER_P2     EQU  0x00000004  ; Wide Timer 2 Present
SYSCTL_PPWTIMER_P1     EQU  0x00000002  ; Wide Timer 1 Present
SYSCTL_PPWTIMER_P0     EQU  0x00000001  ; Wide Timer 0 Present

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRWD register.
;
;*************************************************************
SYSCTL_SRWD_R1         EQU  0x00000002  ; Watchdog Timer 1 Software Reset
SYSCTL_SRWD_R0         EQU  0x00000001  ; Watchdog Timer 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRTIMER register.
;
;*************************************************************
SYSCTL_SRTIMER_R5      EQU  0x00000020  ; Timer 5 Software Reset
SYSCTL_SRTIMER_R4      EQU  0x00000010  ; Timer 4 Software Reset
SYSCTL_SRTIMER_R3      EQU  0x00000008  ; Timer 3 Software Reset
SYSCTL_SRTIMER_R2      EQU  0x00000004  ; Timer 2 Software Reset
SYSCTL_SRTIMER_R1      EQU  0x00000002  ; Timer 1 Software Reset
SYSCTL_SRTIMER_R0      EQU  0x00000001  ; Timer 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRGPIO register.
;
;*************************************************************
SYSCTL_SRGPIO_R14      EQU  0x00004000  ; GPIO Port Q Software Reset
SYSCTL_SRGPIO_R13      EQU  0x00002000  ; GPIO Port P Software Reset
SYSCTL_SRGPIO_R12      EQU  0x00001000  ; GPIO Port N Software Reset
SYSCTL_SRGPIO_R11      EQU  0x00000800  ; GPIO Port M Software Reset
SYSCTL_SRGPIO_R10      EQU  0x00000400  ; GPIO Port L Software Reset
SYSCTL_SRGPIO_R9       EQU  0x00000200  ; GPIO Port K Software Reset
SYSCTL_SRGPIO_R8       EQU  0x00000100  ; GPIO Port J Software Reset
SYSCTL_SRGPIO_R7       EQU  0x00000080  ; GPIO Port H Software Reset
SYSCTL_SRGPIO_R6       EQU  0x00000040  ; GPIO Port G Software Reset
SYSCTL_SRGPIO_R5       EQU  0x00000020  ; GPIO Port F Software Reset
SYSCTL_SRGPIO_R4       EQU  0x00000010  ; GPIO Port E Software Reset
SYSCTL_SRGPIO_R3       EQU  0x00000008  ; GPIO Port D Software Reset
SYSCTL_SRGPIO_R2       EQU  0x00000004  ; GPIO Port C Software Reset
SYSCTL_SRGPIO_R1       EQU  0x00000002  ; GPIO Port B Software Reset
SYSCTL_SRGPIO_R0       EQU  0x00000001  ; GPIO Port A Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRDMA register.
;
;*************************************************************
SYSCTL_SRDMA_R0        EQU  0x00000001  ; uDMA Module Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRHIB register.
;
;*************************************************************
SYSCTL_SRHIB_R0        EQU  0x00000001  ; Hibernation Module Software
                                            ; Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRUART register.
;
;*************************************************************
SYSCTL_SRUART_R7       EQU  0x00000080  ; UART Module 7 Software Reset
SYSCTL_SRUART_R6       EQU  0x00000040  ; UART Module 6 Software Reset
SYSCTL_SRUART_R5       EQU  0x00000020  ; UART Module 5 Software Reset
SYSCTL_SRUART_R4       EQU  0x00000010  ; UART Module 4 Software Reset
SYSCTL_SRUART_R3       EQU  0x00000008  ; UART Module 3 Software Reset
SYSCTL_SRUART_R2       EQU  0x00000004  ; UART Module 2 Software Reset
SYSCTL_SRUART_R1       EQU  0x00000002  ; UART Module 1 Software Reset
SYSCTL_SRUART_R0       EQU  0x00000001  ; UART Module 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRSSI register.
;
;*************************************************************
SYSCTL_SRSSI_R3        EQU  0x00000008  ; SSI Module 3 Software Reset
SYSCTL_SRSSI_R2        EQU  0x00000004  ; SSI Module 2 Software Reset
SYSCTL_SRSSI_R1        EQU  0x00000002  ; SSI Module 1 Software Reset
SYSCTL_SRSSI_R0        EQU  0x00000001  ; SSI Module 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRI2C register.
;
;*************************************************************
SYSCTL_SRI2C_R5        EQU  0x00000020  ; I2C Module 5 Software Reset
SYSCTL_SRI2C_R4        EQU  0x00000010  ; I2C Module 4 Software Reset
SYSCTL_SRI2C_R3        EQU  0x00000008  ; I2C Module 3 Software Reset
SYSCTL_SRI2C_R2        EQU  0x00000004  ; I2C Module 2 Software Reset
SYSCTL_SRI2C_R1        EQU  0x00000002  ; I2C Module 1 Software Reset
SYSCTL_SRI2C_R0        EQU  0x00000001  ; I2C Module 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRUSB register.
;
;*************************************************************
SYSCTL_SRUSB_R0        EQU  0x00000001  ; USB Module Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRCAN register.
;
;*************************************************************
SYSCTL_SRCAN_R1        EQU  0x00000002  ; CAN Module 1 Software Reset
SYSCTL_SRCAN_R0        EQU  0x00000001  ; CAN Module 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRADC register.
;
;*************************************************************
SYSCTL_SRADC_R1        EQU  0x00000002  ; ADC Module 1 Software Reset
SYSCTL_SRADC_R0        EQU  0x00000001  ; ADC Module 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRACMP register.
;
;*************************************************************
SYSCTL_SRACMP_R0       EQU  0x00000001  ; Analog Comparator Module 0
                                            ; Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SREEPROM
; register.
;
;*************************************************************
SYSCTL_SREEPROM_R0     EQU  0x00000001  ; EEPROM Module Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SRWTIMER
; register.
;
;*************************************************************
SYSCTL_SRWTIMER_R5     EQU  0x00000020  ; Wide Timer 5 Software Reset
SYSCTL_SRWTIMER_R4     EQU  0x00000010  ; Wide Timer 4 Software Reset
SYSCTL_SRWTIMER_R3     EQU  0x00000008  ; Wide Timer 3 Software Reset
SYSCTL_SRWTIMER_R2     EQU  0x00000004  ; Wide Timer 2 Software Reset
SYSCTL_SRWTIMER_R1     EQU  0x00000002  ; Wide Timer 1 Software Reset
SYSCTL_SRWTIMER_R0     EQU  0x00000001  ; Wide Timer 0 Software Reset

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCWD register.
;
;*************************************************************
SYSCTL_RCGCWD_R1       EQU  0x00000002  ; Watchdog Timer 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWD_R0       EQU  0x00000001  ; Watchdog Timer 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCTIMER
; register.
;
;*************************************************************
SYSCTL_RCGCTIMER_R5    EQU  0x00000020  ; Timer 5 Run Mode Clock Gating
                                            ; Control
SYSCTL_RCGCTIMER_R4    EQU  0x00000010  ; Timer 4 Run Mode Clock Gating
                                            ; Control
SYSCTL_RCGCTIMER_R3    EQU  0x00000008  ; Timer 3 Run Mode Clock Gating
                                            ; Control
SYSCTL_RCGCTIMER_R2    EQU  0x00000004  ; Timer 2 Run Mode Clock Gating
                                            ; Control
SYSCTL_RCGCTIMER_R1    EQU  0x00000002  ; Timer 1 Run Mode Clock Gating
                                            ; Control
SYSCTL_RCGCTIMER_R0    EQU  0x00000001  ; Timer 0 Run Mode Clock Gating
                                            ; Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCGPIO
; register.
;
;*************************************************************
SYSCTL_RCGCGPIO_R14    EQU  0x00004000  ; GPIO Port Q Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R13    EQU  0x00002000  ; GPIO Port P Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R12    EQU  0x00001000  ; GPIO Port N Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R11    EQU  0x00000800  ; GPIO Port M Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R10    EQU  0x00000400  ; GPIO Port L Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R9     EQU  0x00000200  ; GPIO Port K Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R8     EQU  0x00000100  ; GPIO Port J Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R7     EQU  0x00000080  ; GPIO Port H Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R6     EQU  0x00000040  ; GPIO Port G Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R5     EQU  0x00000020  ; GPIO Port F Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R4     EQU  0x00000010  ; GPIO Port E Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R3     EQU  0x00000008  ; GPIO Port D Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R2     EQU  0x00000004  ; GPIO Port C Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R1     EQU  0x00000002  ; GPIO Port B Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCGPIO_R0     EQU  0x00000001  ; GPIO Port A Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCDMA register.
;
;*************************************************************
SYSCTL_RCGCDMA_R0      EQU  0x00000001  ; uDMA Module Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCHIB register.
;
;*************************************************************
SYSCTL_RCGCHIB_R0      EQU  0x00000001  ; Hibernation Module Run Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCUART
; register.
;
;*************************************************************
SYSCTL_RCGCUART_R7     EQU  0x00000080  ; UART Module 7 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R6     EQU  0x00000040  ; UART Module 6 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R5     EQU  0x00000020  ; UART Module 5 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R4     EQU  0x00000010  ; UART Module 4 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R3     EQU  0x00000008  ; UART Module 3 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R2     EQU  0x00000004  ; UART Module 2 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R1     EQU  0x00000002  ; UART Module 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCUART_R0     EQU  0x00000001  ; UART Module 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCSSI register.
;
;*************************************************************
SYSCTL_RCGCSSI_R3      EQU  0x00000008  ; SSI Module 3 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCSSI_R2      EQU  0x00000004  ; SSI Module 2 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCSSI_R1      EQU  0x00000002  ; SSI Module 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCSSI_R0      EQU  0x00000001  ; SSI Module 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCI2C register.
;
;*************************************************************
SYSCTL_RCGCI2C_R5      EQU  0x00000020  ; I2C Module 5 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCI2C_R4      EQU  0x00000010  ; I2C Module 4 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCI2C_R3      EQU  0x00000008  ; I2C Module 3 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCI2C_R2      EQU  0x00000004  ; I2C Module 2 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCI2C_R1      EQU  0x00000002  ; I2C Module 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCI2C_R0      EQU  0x00000001  ; I2C Module 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCUSB register.
;
;*************************************************************
SYSCTL_RCGCUSB_R0      EQU  0x00000001  ; USB Module Run Mode Clock Gating
                                            ; Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCCAN register.
;
;*************************************************************
SYSCTL_RCGCCAN_R1      EQU  0x00000002  ; CAN Module 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCCAN_R0      EQU  0x00000001  ; CAN Module 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCADC register.
;
;*************************************************************
SYSCTL_RCGCADC_R1      EQU  0x00000002  ; ADC Module 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCADC_R0      EQU  0x00000001  ; ADC Module 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCACMP
; register.
;
;*************************************************************
SYSCTL_RCGCACMP_R0     EQU  0x00000001  ; Analog Comparator Module 0 Run
                                            ; Mode Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCEEPROM
; register.
;
;*************************************************************
SYSCTL_RCGCEEPROM_R0   EQU  0x00000001  ; EEPROM Module Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_RCGCWTIMER
; register.
;
;*************************************************************
SYSCTL_RCGCWTIMER_R5   EQU  0x00000020  ; Wide Timer 5 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWTIMER_R4   EQU  0x00000010  ; Wide Timer 4 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWTIMER_R3   EQU  0x00000008  ; Wide Timer 3 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWTIMER_R2   EQU  0x00000004  ; Wide Timer 2 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWTIMER_R1   EQU  0x00000002  ; Wide Timer 1 Run Mode Clock
                                            ; Gating Control
SYSCTL_RCGCWTIMER_R0   EQU  0x00000001  ; Wide Timer 0 Run Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCWD register.
;
;*************************************************************
SYSCTL_SCGCWD_S1       EQU  0x00000002  ; Watchdog Timer 1 Sleep Mode
                                            ; Clock Gating Control
SYSCTL_SCGCWD_S0       EQU  0x00000001  ; Watchdog Timer 0 Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCTIMER
; register.
;
;*************************************************************
SYSCTL_SCGCTIMER_S5    EQU  0x00000020  ; Timer 5 Sleep Mode Clock Gating
                                            ; Control
SYSCTL_SCGCTIMER_S4    EQU  0x00000010  ; Timer 4 Sleep Mode Clock Gating
                                            ; Control
SYSCTL_SCGCTIMER_S3    EQU  0x00000008  ; Timer 3 Sleep Mode Clock Gating
                                            ; Control
SYSCTL_SCGCTIMER_S2    EQU  0x00000004  ; Timer 2 Sleep Mode Clock Gating
                                            ; Control
SYSCTL_SCGCTIMER_S1    EQU  0x00000002  ; Timer 1 Sleep Mode Clock Gating
                                            ; Control
SYSCTL_SCGCTIMER_S0    EQU  0x00000001  ; Timer 0 Sleep Mode Clock Gating
                                            ; Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCGPIO
; register.
;
;*************************************************************
SYSCTL_SCGCGPIO_S14    EQU  0x00004000  ; GPIO Port Q Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S13    EQU  0x00002000  ; GPIO Port P Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S12    EQU  0x00001000  ; GPIO Port N Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S11    EQU  0x00000800  ; GPIO Port M Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S10    EQU  0x00000400  ; GPIO Port L Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S9     EQU  0x00000200  ; GPIO Port K Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S8     EQU  0x00000100  ; GPIO Port J Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S7     EQU  0x00000080  ; GPIO Port H Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S6     EQU  0x00000040  ; GPIO Port G Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S5     EQU  0x00000020  ; GPIO Port F Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S4     EQU  0x00000010  ; GPIO Port E Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S3     EQU  0x00000008  ; GPIO Port D Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S2     EQU  0x00000004  ; GPIO Port C Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S1     EQU  0x00000002  ; GPIO Port B Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCGPIO_S0     EQU  0x00000001  ; GPIO Port A Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCDMA register.
;
;*************************************************************
SYSCTL_SCGCDMA_S0      EQU  0x00000001  ; uDMA Module Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCHIB register.
;
;*************************************************************
SYSCTL_SCGCHIB_S0      EQU  0x00000001  ; Hibernation Module Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCUART
; register.
;
;*************************************************************
SYSCTL_SCGCUART_S7     EQU  0x00000080  ; UART Module 7 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S6     EQU  0x00000040  ; UART Module 6 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S5     EQU  0x00000020  ; UART Module 5 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S4     EQU  0x00000010  ; UART Module 4 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S3     EQU  0x00000008  ; UART Module 3 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S2     EQU  0x00000004  ; UART Module 2 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S1     EQU  0x00000002  ; UART Module 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCUART_S0     EQU  0x00000001  ; UART Module 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCSSI register.
;
;*************************************************************
SYSCTL_SCGCSSI_S3      EQU  0x00000008  ; SSI Module 3 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCSSI_S2      EQU  0x00000004  ; SSI Module 2 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCSSI_S1      EQU  0x00000002  ; SSI Module 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCSSI_S0      EQU  0x00000001  ; SSI Module 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCI2C register.
;
;*************************************************************
SYSCTL_SCGCI2C_S5      EQU  0x00000020  ; I2C Module 5 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCI2C_S4      EQU  0x00000010  ; I2C Module 4 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCI2C_S3      EQU  0x00000008  ; I2C Module 3 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCI2C_S2      EQU  0x00000004  ; I2C Module 2 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCI2C_S1      EQU  0x00000002  ; I2C Module 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCI2C_S0      EQU  0x00000001  ; I2C Module 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCUSB register.
;
;*************************************************************
SYSCTL_SCGCUSB_S0      EQU  0x00000001  ; USB Module Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCCAN register.
;
;*************************************************************
SYSCTL_SCGCCAN_S1      EQU  0x00000002  ; CAN Module 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCCAN_S0      EQU  0x00000001  ; CAN Module 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCADC register.
;
;*************************************************************
SYSCTL_SCGCADC_S1      EQU  0x00000002  ; ADC Module 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCADC_S0      EQU  0x00000001  ; ADC Module 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCACMP
; register.
;
;*************************************************************
SYSCTL_SCGCACMP_S0     EQU  0x00000001  ; Analog Comparator Module 0 Sleep
                                            ; Mode Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCEEPROM
; register.
;
;*************************************************************
SYSCTL_SCGCEEPROM_S0   EQU  0x00000001  ; EEPROM Module Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_SCGCWTIMER
; register.
;
;*************************************************************
SYSCTL_SCGCWTIMER_S5   EQU  0x00000020  ; Wide Timer 5 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCWTIMER_S4   EQU  0x00000010  ; Wide Timer 4 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCWTIMER_S3   EQU  0x00000008  ; Wide Timer 3 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCWTIMER_S2   EQU  0x00000004  ; Wide Timer 2 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCWTIMER_S1   EQU  0x00000002  ; Wide Timer 1 Sleep Mode Clock
                                            ; Gating Control
SYSCTL_SCGCWTIMER_S0   EQU  0x00000001  ; Wide Timer 0 Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCWD register.
;
;*************************************************************
SYSCTL_DCGCWD_D1       EQU  0x00000002  ; Watchdog Timer 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWD_D0       EQU  0x00000001  ; Watchdog Timer 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCTIMER
; register.
;
;*************************************************************
SYSCTL_DCGCTIMER_D5    EQU  0x00000020  ; Timer 5 Deep-Sleep Mode Clock
                                            ; Gating Control
SYSCTL_DCGCTIMER_D4    EQU  0x00000010  ; Timer 4 Deep-Sleep Mode Clock
                                            ; Gating Control
SYSCTL_DCGCTIMER_D3    EQU  0x00000008  ; Timer 3 Deep-Sleep Mode Clock
                                            ; Gating Control
SYSCTL_DCGCTIMER_D2    EQU  0x00000004  ; Timer 2 Deep-Sleep Mode Clock
                                            ; Gating Control
SYSCTL_DCGCTIMER_D1    EQU  0x00000002  ; Timer 1 Deep-Sleep Mode Clock
                                            ; Gating Control
SYSCTL_DCGCTIMER_D0    EQU  0x00000001  ; Timer 0 Deep-Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCGPIO
; register.
;
;*************************************************************
SYSCTL_DCGCGPIO_D14    EQU  0x00004000  ; GPIO Port Q Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D13    EQU  0x00002000  ; GPIO Port P Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D12    EQU  0x00001000  ; GPIO Port N Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D11    EQU  0x00000800  ; GPIO Port M Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D10    EQU  0x00000400  ; GPIO Port L Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D9     EQU  0x00000200  ; GPIO Port K Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D8     EQU  0x00000100  ; GPIO Port J Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D7     EQU  0x00000080  ; GPIO Port H Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D6     EQU  0x00000040  ; GPIO Port G Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D5     EQU  0x00000020  ; GPIO Port F Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D4     EQU  0x00000010  ; GPIO Port E Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D3     EQU  0x00000008  ; GPIO Port D Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D2     EQU  0x00000004  ; GPIO Port C Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D1     EQU  0x00000002  ; GPIO Port B Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCGPIO_D0     EQU  0x00000001  ; GPIO Port A Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCDMA register.
;
;*************************************************************
SYSCTL_DCGCDMA_D0      EQU  0x00000001  ; uDMA Module Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCHIB register.
;
;*************************************************************
SYSCTL_DCGCHIB_D0      EQU  0x00000001  ; Hibernation Module Deep-Sleep
                                            ; Mode Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCUART
; register.
;
;*************************************************************
SYSCTL_DCGCUART_D7     EQU  0x00000080  ; UART Module 7 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D6     EQU  0x00000040  ; UART Module 6 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D5     EQU  0x00000020  ; UART Module 5 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D4     EQU  0x00000010  ; UART Module 4 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D3     EQU  0x00000008  ; UART Module 3 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D2     EQU  0x00000004  ; UART Module 2 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D1     EQU  0x00000002  ; UART Module 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCUART_D0     EQU  0x00000001  ; UART Module 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCSSI register.
;
;*************************************************************
SYSCTL_DCGCSSI_D3      EQU  0x00000008  ; SSI Module 3 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCSSI_D2      EQU  0x00000004  ; SSI Module 2 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCSSI_D1      EQU  0x00000002  ; SSI Module 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCSSI_D0      EQU  0x00000001  ; SSI Module 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCI2C register.
;
;*************************************************************
SYSCTL_DCGCI2C_D5      EQU  0x00000020  ; I2C Module 5 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCI2C_D4      EQU  0x00000010  ; I2C Module 4 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCI2C_D3      EQU  0x00000008  ; I2C Module 3 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCI2C_D2      EQU  0x00000004  ; I2C Module 2 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCI2C_D1      EQU  0x00000002  ; I2C Module 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCI2C_D0      EQU  0x00000001  ; I2C Module 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCUSB register.
;
;*************************************************************
SYSCTL_DCGCUSB_D0      EQU  0x00000001  ; USB Module Deep-Sleep Mode Clock
                                            ; Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCCAN register.
;
;*************************************************************
SYSCTL_DCGCCAN_D1      EQU  0x00000002  ; CAN Module 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCCAN_D0      EQU  0x00000001  ; CAN Module 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCADC register.
;
;*************************************************************
SYSCTL_DCGCADC_D1      EQU  0x00000002  ; ADC Module 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCADC_D0      EQU  0x00000001  ; ADC Module 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCACMP
; register.
;
;*************************************************************
SYSCTL_DCGCACMP_D0     EQU  0x00000001  ; Analog Comparator Module 0
                                            ; Deep-Sleep Mode Clock Gating
                                            ; Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCEEPROM
; register.
;
;*************************************************************
SYSCTL_DCGCEEPROM_D0   EQU  0x00000001  ; EEPROM Module Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_DCGCWTIMER
; register.
;
;*************************************************************
SYSCTL_DCGCWTIMER_D5   EQU  0x00000020  ; Wide Timer 5 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWTIMER_D4   EQU  0x00000010  ; Wide Timer 4 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWTIMER_D3   EQU  0x00000008  ; Wide Timer 3 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWTIMER_D2   EQU  0x00000004  ; Wide Timer 2 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWTIMER_D1   EQU  0x00000002  ; Wide Timer 1 Deep-Sleep Mode
                                            ; Clock Gating Control
SYSCTL_DCGCWTIMER_D0   EQU  0x00000001  ; Wide Timer 0 Deep-Sleep Mode
                                            ; Clock Gating Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCWD register.
;
;*************************************************************
SYSCTL_PCWD_P1         EQU  0x00000002  ; Watchdog Timer 1 Power Control
SYSCTL_PCWD_P0         EQU  0x00000001  ; Watchdog Timer 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCTIMER register.
;
;*************************************************************
SYSCTL_PCTIMER_P5      EQU  0x00000020  ; Timer 5 Power Control
SYSCTL_PCTIMER_P4      EQU  0x00000010  ; Timer 4 Power Control
SYSCTL_PCTIMER_P3      EQU  0x00000008  ; Timer 3 Power Control
SYSCTL_PCTIMER_P2      EQU  0x00000004  ; Timer 2 Power Control
SYSCTL_PCTIMER_P1      EQU  0x00000002  ; Timer 1 Power Control
SYSCTL_PCTIMER_P0      EQU  0x00000001  ; Timer 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCGPIO register.
;
;*************************************************************
SYSCTL_PCGPIO_P14      EQU  0x00004000  ; GPIO Port Q Power Control
SYSCTL_PCGPIO_P13      EQU  0x00002000  ; GPIO Port P Power Control
SYSCTL_PCGPIO_P12      EQU  0x00001000  ; GPIO Port N Power Control
SYSCTL_PCGPIO_P11      EQU  0x00000800  ; GPIO Port M Power Control
SYSCTL_PCGPIO_P10      EQU  0x00000400  ; GPIO Port L Power Control
SYSCTL_PCGPIO_P9       EQU  0x00000200  ; GPIO Port K Power Control
SYSCTL_PCGPIO_P8       EQU  0x00000100  ; GPIO Port J Power Control
SYSCTL_PCGPIO_P7       EQU  0x00000080  ; GPIO Port H Power Control
SYSCTL_PCGPIO_P6       EQU  0x00000040  ; GPIO Port G Power Control
SYSCTL_PCGPIO_P5       EQU  0x00000020  ; GPIO Port F Power Control
SYSCTL_PCGPIO_P4       EQU  0x00000010  ; GPIO Port E Power Control
SYSCTL_PCGPIO_P3       EQU  0x00000008  ; GPIO Port D Power Control
SYSCTL_PCGPIO_P2       EQU  0x00000004  ; GPIO Port C Power Control
SYSCTL_PCGPIO_P1       EQU  0x00000002  ; GPIO Port B Power Control
SYSCTL_PCGPIO_P0       EQU  0x00000001  ; GPIO Port A Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCDMA register.
;
;*************************************************************
SYSCTL_PCDMA_P0        EQU  0x00000001  ; uDMA Module Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCHIB register.
;
;*************************************************************
SYSCTL_PCHIB_P0        EQU  0x00000001  ; Hibernation Module Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCUART register.
;
;*************************************************************
SYSCTL_PCUART_P7       EQU  0x00000080  ; UART Module 7 Power Control
SYSCTL_PCUART_P6       EQU  0x00000040  ; UART Module 6 Power Control
SYSCTL_PCUART_P5       EQU  0x00000020  ; UART Module 5 Power Control
SYSCTL_PCUART_P4       EQU  0x00000010  ; UART Module 4 Power Control
SYSCTL_PCUART_P3       EQU  0x00000008  ; UART Module 3 Power Control
SYSCTL_PCUART_P2       EQU  0x00000004  ; UART Module 2 Power Control
SYSCTL_PCUART_P1       EQU  0x00000002  ; UART Module 1 Power Control
SYSCTL_PCUART_P0       EQU  0x00000001  ; UART Module 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCSSI register.
;
;*************************************************************
SYSCTL_PCSSI_P3        EQU  0x00000008  ; SSI Module 3 Power Control
SYSCTL_PCSSI_P2        EQU  0x00000004  ; SSI Module 2 Power Control
SYSCTL_PCSSI_P1        EQU  0x00000002  ; SSI Module 1 Power Control
SYSCTL_PCSSI_P0        EQU  0x00000001  ; SSI Module 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCI2C register.
;
;*************************************************************
SYSCTL_PCI2C_P5        EQU  0x00000020  ; I2C Module 5 Power Control
SYSCTL_PCI2C_P4        EQU  0x00000010  ; I2C Module 4 Power Control
SYSCTL_PCI2C_P3        EQU  0x00000008  ; I2C Module 3 Power Control
SYSCTL_PCI2C_P2        EQU  0x00000004  ; I2C Module 2 Power Control
SYSCTL_PCI2C_P1        EQU  0x00000002  ; I2C Module 1 Power Control
SYSCTL_PCI2C_P0        EQU  0x00000001  ; I2C Module 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCUSB register.
;
;*************************************************************
SYSCTL_PCUSB_P0        EQU  0x00000001  ; USB Module Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCCAN register.
;
;*************************************************************
SYSCTL_PCCAN_P1        EQU  0x00000002  ; CAN Module 1 Power Control
SYSCTL_PCCAN_P0        EQU  0x00000001  ; CAN Module 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCADC register.
;
;*************************************************************
SYSCTL_PCADC_P1        EQU  0x00000002  ; ADC Module 1 Power Control
SYSCTL_PCADC_P0        EQU  0x00000001  ; ADC Module 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCACMP register.
;
;*************************************************************
SYSCTL_PCACMP_P0       EQU  0x00000001  ; Analog Comparator Module 0 Power
                                            ; Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCEEPROM
; register.
;
;*************************************************************
SYSCTL_PCEEPROM_P0     EQU  0x00000001  ; EEPROM Module Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PCWTIMER
; register.
;
;*************************************************************
SYSCTL_PCWTIMER_P5     EQU  0x00000020  ; Wide Timer 5 Power Control
SYSCTL_PCWTIMER_P4     EQU  0x00000010  ; Wide Timer 4 Power Control
SYSCTL_PCWTIMER_P3     EQU  0x00000008  ; Wide Timer 3 Power Control
SYSCTL_PCWTIMER_P2     EQU  0x00000004  ; Wide Timer 2 Power Control
SYSCTL_PCWTIMER_P1     EQU  0x00000002  ; Wide Timer 1 Power Control
SYSCTL_PCWTIMER_P0     EQU  0x00000001  ; Wide Timer 0 Power Control

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRWD register.
;
;*************************************************************
SYSCTL_PRWD_R1         EQU  0x00000002  ; Watchdog Timer 1 Peripheral
                                            ; Ready
SYSCTL_PRWD_R0         EQU  0x00000001  ; Watchdog Timer 0 Peripheral
                                            ; Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRTIMER register.
;
;*************************************************************
SYSCTL_PRTIMER_R5      EQU  0x00000020  ; Timer 5 Peripheral Ready
SYSCTL_PRTIMER_R4      EQU  0x00000010  ; Timer 4 Peripheral Ready
SYSCTL_PRTIMER_R3      EQU  0x00000008  ; Timer 3 Peripheral Ready
SYSCTL_PRTIMER_R2      EQU  0x00000004  ; Timer 2 Peripheral Ready
SYSCTL_PRTIMER_R1      EQU  0x00000002  ; Timer 1 Peripheral Ready
SYSCTL_PRTIMER_R0      EQU  0x00000001  ; Timer 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRGPIO register.
;
;*************************************************************
SYSCTL_PRGPIO_R14      EQU  0x00004000  ; GPIO Port Q Peripheral Ready
SYSCTL_PRGPIO_R13      EQU  0x00002000  ; GPIO Port P Peripheral Ready
SYSCTL_PRGPIO_R12      EQU  0x00001000  ; GPIO Port N Peripheral Ready
SYSCTL_PRGPIO_R11      EQU  0x00000800  ; GPIO Port M Peripheral Ready
SYSCTL_PRGPIO_R10      EQU  0x00000400  ; GPIO Port L Peripheral Ready
SYSCTL_PRGPIO_R9       EQU  0x00000200  ; GPIO Port K Peripheral Ready
SYSCTL_PRGPIO_R8       EQU  0x00000100  ; GPIO Port J Peripheral Ready
SYSCTL_PRGPIO_R7       EQU  0x00000080  ; GPIO Port H Peripheral Ready
SYSCTL_PRGPIO_R6       EQU  0x00000040  ; GPIO Port G Peripheral Ready
SYSCTL_PRGPIO_R5       EQU  0x00000020  ; GPIO Port F Peripheral Ready
SYSCTL_PRGPIO_R4       EQU  0x00000010  ; GPIO Port E Peripheral Ready
SYSCTL_PRGPIO_R3       EQU  0x00000008  ; GPIO Port D Peripheral Ready
SYSCTL_PRGPIO_R2       EQU  0x00000004  ; GPIO Port C Peripheral Ready
SYSCTL_PRGPIO_R1       EQU  0x00000002  ; GPIO Port B Peripheral Ready
SYSCTL_PRGPIO_R0       EQU  0x00000001  ; GPIO Port A Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRDMA register.
;
;*************************************************************
SYSCTL_PRDMA_R0        EQU  0x00000001  ; uDMA Module Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRHIB register.
;
;*************************************************************
SYSCTL_PRHIB_R0        EQU  0x00000001  ; Hibernation Module Peripheral
                                            ; Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRUART register.
;
;*************************************************************
SYSCTL_PRUART_R7       EQU  0x00000080  ; UART Module 7 Peripheral Ready
SYSCTL_PRUART_R6       EQU  0x00000040  ; UART Module 6 Peripheral Ready
SYSCTL_PRUART_R5       EQU  0x00000020  ; UART Module 5 Peripheral Ready
SYSCTL_PRUART_R4       EQU  0x00000010  ; UART Module 4 Peripheral Ready
SYSCTL_PRUART_R3       EQU  0x00000008  ; UART Module 3 Peripheral Ready
SYSCTL_PRUART_R2       EQU  0x00000004  ; UART Module 2 Peripheral Ready
SYSCTL_PRUART_R1       EQU  0x00000002  ; UART Module 1 Peripheral Ready
SYSCTL_PRUART_R0       EQU  0x00000001  ; UART Module 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRSSI register.
;
;*************************************************************
SYSCTL_PRSSI_R3        EQU  0x00000008  ; SSI Module 3 Peripheral Ready
SYSCTL_PRSSI_R2        EQU  0x00000004  ; SSI Module 2 Peripheral Ready
SYSCTL_PRSSI_R1        EQU  0x00000002  ; SSI Module 1 Peripheral Ready
SYSCTL_PRSSI_R0        EQU  0x00000001  ; SSI Module 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRI2C register.
;
;*************************************************************
SYSCTL_PRI2C_R5        EQU  0x00000020  ; I2C Module 5 Peripheral Ready
SYSCTL_PRI2C_R4        EQU  0x00000010  ; I2C Module 4 Peripheral Ready
SYSCTL_PRI2C_R3        EQU  0x00000008  ; I2C Module 3 Peripheral Ready
SYSCTL_PRI2C_R2        EQU  0x00000004  ; I2C Module 2 Peripheral Ready
SYSCTL_PRI2C_R1        EQU  0x00000002  ; I2C Module 1 Peripheral Ready
SYSCTL_PRI2C_R0        EQU  0x00000001  ; I2C Module 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRUSB register.
;
;*************************************************************
SYSCTL_PRUSB_R0        EQU  0x00000001  ; USB Module Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRCAN register.
;
;*************************************************************
SYSCTL_PRCAN_R1        EQU  0x00000002  ; CAN Module 1 Peripheral Ready
SYSCTL_PRCAN_R0        EQU  0x00000001  ; CAN Module 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRADC register.
;
;*************************************************************
SYSCTL_PRADC_R1        EQU  0x00000002  ; ADC Module 1 Peripheral Ready
SYSCTL_PRADC_R0        EQU  0x00000001  ; ADC Module 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRACMP register.
;
;*************************************************************
SYSCTL_PRACMP_R0       EQU  0x00000001  ; Analog Comparator Module 0
                                            ; Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PREEPROM
; register.
;
;*************************************************************
SYSCTL_PREEPROM_R0     EQU  0x00000001  ; EEPROM Module Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the SYSCTL_PRWTIMER
; register.
;
;*************************************************************
SYSCTL_PRWTIMER_R5     EQU  0x00000020  ; Wide Timer 5 Peripheral Ready
SYSCTL_PRWTIMER_R4     EQU  0x00000010  ; Wide Timer 4 Peripheral Ready
SYSCTL_PRWTIMER_R3     EQU  0x00000008  ; Wide Timer 3 Peripheral Ready
SYSCTL_PRWTIMER_R2     EQU  0x00000004  ; Wide Timer 2 Peripheral Ready
SYSCTL_PRWTIMER_R1     EQU  0x00000002  ; Wide Timer 1 Peripheral Ready
SYSCTL_PRWTIMER_R0     EQU  0x00000001  ; Wide Timer 0 Peripheral Ready

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_STAT register.
;
;*************************************************************
UDMA_STAT_DMACHANS_M   EQU  0x001F0000  ; Available uDMA Channels Minus 1
UDMA_STAT_STATE_M      EQU  0x000000F0  ; Control State Machine Status
UDMA_STAT_STATE_IDLE   EQU  0x00000000  ; Idle
UDMA_STAT_STATE_RD_CTRL EQU  0x00000010  ; Reading channel controller data
UDMA_STAT_STATE_RD_SRCENDP EQU  0x00000020  ; Reading source end pointer
UDMA_STAT_STATE_RD_DSTENDP EQU  0x00000030  ; Reading destination end pointer
UDMA_STAT_STATE_RD_SRCDAT EQU  0x00000040  ; Reading source data
UDMA_STAT_STATE_WR_DSTDAT EQU  0x00000050  ; Writing destination data
UDMA_STAT_STATE_WAIT   EQU  0x00000060  ; Waiting for uDMA request to
                                            ; clear
UDMA_STAT_STATE_WR_CTRL EQU  0x00000070  ; Writing channel controller data
UDMA_STAT_STATE_STALL  EQU  0x00000080  ; Stalled
UDMA_STAT_STATE_DONE   EQU  0x00000090  ; Done
UDMA_STAT_STATE_UNDEF  EQU  0x000000A0  ; Undefined
UDMA_STAT_MASTEN       EQU  0x00000001  ; Master Enable Status
UDMA_STAT_DMACHANS_S    EQU 16

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CFG register.
;
;*************************************************************
UDMA_CFG_MASTEN        EQU  0x00000001  ; Controller Master Enable

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CTLBASE register.
;
;*************************************************************
UDMA_CTLBASE_ADDR_M    EQU  0xFFFFFC00  ; Channel Control Base Address
UDMA_CTLBASE_ADDR_S    EQU  10

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ALTBASE register.
;
;*************************************************************
UDMA_ALTBASE_ADDR_M    EQU  0xFFFFFFFF  ; Alternate Channel Address
                                            ; Pointer
UDMA_ALTBASE_ADDR_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_WAITSTAT register.
;
;*************************************************************
UDMA_WAITSTAT_WAITREQ_M EQU  0xFFFFFFFF  ; Channel [n] Wait Status

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_SWREQ register.
;
;*************************************************************
UDMA_SWREQ_M           EQU  0xFFFFFFFF  ; Channel [n] Software Request

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_USEBURSTSET
; register.
;
;*************************************************************
UDMA_USEBURSTSET_SET_M EQU  0xFFFFFFFF  ; Channel [n] Useburst Set

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_USEBURSTCLR
; register.
;
;*************************************************************
UDMA_USEBURSTCLR_CLR_M EQU  0xFFFFFFFF  ; Channel [n] Useburst Clear

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_REQMASKSET
; register.
;
;*************************************************************
UDMA_REQMASKSET_SET_M  EQU  0xFFFFFFFF  ; Channel [n] Request Mask Set

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_REQMASKCLR
; register.
;
;*************************************************************
UDMA_REQMASKCLR_CLR_M  EQU  0xFFFFFFFF  ; Channel [n] Request Mask Clear

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ENASET register.
;
;*************************************************************
UDMA_ENASET_SET_M      EQU  0xFFFFFFFF  ; Channel [n] Enable Set

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ENACLR register.
;
;*************************************************************
UDMA_ENACLR_CLR_M      EQU  0xFFFFFFFF  ; Clear Channel [n] Enable Clear

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ALTSET register.
;
;*************************************************************
UDMA_ALTSET_SET_M      EQU  0xFFFFFFFF  ; Channel [n] Alternate Set

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ALTCLR register.
;
;*************************************************************
UDMA_ALTCLR_CLR_M      EQU  0xFFFFFFFF  ; Channel [n] Alternate Clear

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_PRIOSET register.
;
;*************************************************************
UDMA_PRIOSET_SET_M     EQU  0xFFFFFFFF  ; Channel [n] Priority Set

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_PRIOCLR register.
;
;*************************************************************
UDMA_PRIOCLR_CLR_M     EQU  0xFFFFFFFF  ; Channel [n] Priority Clear

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_ERRCLR register.
;
;*************************************************************
UDMA_ERRCLR_ERRCLR     EQU  0x00000001  ; uDMA Bus Error Status

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHASGN register.
;
;*************************************************************
UDMA_CHASGN_M          EQU  0xFFFFFFFF  ; Channel [n] Assignment Select
UDMA_CHASGN_PRIMARY    EQU  0x00000000  ; Use the primary channel
                                            ; assignment
UDMA_CHASGN_SECONDARY  EQU  0x00000001  ; Use the secondary channel
                                            ; assignment

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHIS register.
;
;*************************************************************
UDMA_CHIS_M            EQU  0xFFFFFFFF  ; Channel [n] Interrupt Status

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHMAP0 register.
;
;*************************************************************
UDMA_CHMAP0_CH7SEL_M   EQU  0xF0000000  ; uDMA Channel 7 Source Select
UDMA_CHMAP0_CH6SEL_M   EQU  0x0F000000  ; uDMA Channel 6 Source Select
UDMA_CHMAP0_CH5SEL_M   EQU  0x00F00000  ; uDMA Channel 5 Source Select
UDMA_CHMAP0_CH4SEL_M   EQU  0x000F0000  ; uDMA Channel 4 Source Select
UDMA_CHMAP0_CH3SEL_M   EQU  0x0000F000  ; uDMA Channel 3 Source Select
UDMA_CHMAP0_CH2SEL_M   EQU  0x00000F00  ; uDMA Channel 2 Source Select
UDMA_CHMAP0_CH1SEL_M   EQU  0x000000F0  ; uDMA Channel 1 Source Select
UDMA_CHMAP0_CH0SEL_M   EQU  0x0000000F  ; uDMA Channel 0 Source Select
UDMA_CHMAP0_CH7SEL_S    EQU 28
UDMA_CHMAP0_CH6SEL_S    EQU 24
UDMA_CHMAP0_CH5SEL_S    EQU 20
UDMA_CHMAP0_CH4SEL_S    EQU 16
UDMA_CHMAP0_CH3SEL_S    EQU 12
UDMA_CHMAP0_CH2SEL_S    EQU 8
UDMA_CHMAP0_CH1SEL_S    EQU 4
UDMA_CHMAP0_CH0SEL_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHMAP1 register.
;
;*************************************************************
UDMA_CHMAP1_CH15SEL_M  EQU  0xF0000000  ; uDMA Channel 15 Source Select
UDMA_CHMAP1_CH14SEL_M  EQU  0x0F000000  ; uDMA Channel 14 Source Select
UDMA_CHMAP1_CH13SEL_M  EQU  0x00F00000  ; uDMA Channel 13 Source Select
UDMA_CHMAP1_CH12SEL_M  EQU  0x000F0000  ; uDMA Channel 12 Source Select
UDMA_CHMAP1_CH11SEL_M  EQU  0x0000F000  ; uDMA Channel 11 Source Select
UDMA_CHMAP1_CH10SEL_M  EQU  0x00000F00  ; uDMA Channel 10 Source Select
UDMA_CHMAP1_CH9SEL_M   EQU  0x000000F0  ; uDMA Channel 9 Source Select
UDMA_CHMAP1_CH8SEL_M   EQU  0x0000000F  ; uDMA Channel 8 Source Select
UDMA_CHMAP1_CH15SEL_S  EQU 28
UDMA_CHMAP1_CH14SEL_S    EQU 24
UDMA_CHMAP1_CH13SEL_S    EQU 20
UDMA_CHMAP1_CH12SEL_S    EQU 16
UDMA_CHMAP1_CH11SEL_S    EQU 12
UDMA_CHMAP1_CH10SEL_S    EQU 8
UDMA_CHMAP1_CH9SEL_S    EQU  4
UDMA_CHMAP1_CH8SEL_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHMAP2 register.
;
;*************************************************************
UDMA_CHMAP2_CH23SEL_M  EQU  0xF0000000  ; uDMA Channel 23 Source Select
UDMA_CHMAP2_CH22SEL_M  EQU  0x0F000000  ; uDMA Channel 22 Source Select
UDMA_CHMAP2_CH21SEL_M  EQU  0x00F00000  ; uDMA Channel 21 Source Select
UDMA_CHMAP2_CH20SEL_M  EQU  0x000F0000  ; uDMA Channel 20 Source Select
UDMA_CHMAP2_CH19SEL_M  EQU  0x0000F000  ; uDMA Channel 19 Source Select
UDMA_CHMAP2_CH18SEL_M  EQU  0x00000F00  ; uDMA Channel 18 Source Select
UDMA_CHMAP2_CH17SEL_M  EQU  0x000000F0  ; uDMA Channel 17 Source Select
UDMA_CHMAP2_CH16SEL_M  EQU  0x0000000F  ; uDMA Channel 16 Source Select
UDMA_CHMAP2_CH23SEL_S    EQU 28
UDMA_CHMAP2_CH22SEL_S    EQU 24
UDMA_CHMAP2_CH21SEL_S    EQU 20
UDMA_CHMAP2_CH20SEL_S    EQU 16
UDMA_CHMAP2_CH19SEL_S    EQU 12
UDMA_CHMAP2_CH18SEL_S    EQU 8
UDMA_CHMAP2_CH17SEL_S    EQU 4
UDMA_CHMAP2_CH16SEL_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_CHMAP3 register.
;
;*************************************************************
UDMA_CHMAP3_CH31SEL_M  EQU  0xF0000000  ; uDMA Channel 31 Source Select
UDMA_CHMAP3_CH30SEL_M  EQU  0x0F000000  ; uDMA Channel 30 Source Select
UDMA_CHMAP3_CH29SEL_M  EQU  0x00F00000  ; uDMA Channel 29 Source Select
UDMA_CHMAP3_CH28SEL_M  EQU  0x000F0000  ; uDMA Channel 28 Source Select
UDMA_CHMAP3_CH27SEL_M  EQU  0x0000F000  ; uDMA Channel 27 Source Select
UDMA_CHMAP3_CH26SEL_M  EQU  0x00000F00  ; uDMA Channel 26 Source Select
UDMA_CHMAP3_CH25SEL_M  EQU  0x000000F0  ; uDMA Channel 25 Source Select
UDMA_CHMAP3_CH24SEL_M  EQU  0x0000000F  ; uDMA Channel 24 Source Select
UDMA_CHMAP3_CH31SEL_S    EQU 28
UDMA_CHMAP3_CH30SEL_S    EQU 24
UDMA_CHMAP3_CH29SEL_S    EQU 20
UDMA_CHMAP3_CH28SEL_S    EQU 16
UDMA_CHMAP3_CH27SEL_S    EQU 12
UDMA_CHMAP3_CH26SEL_S    EQU 8
UDMA_CHMAP3_CH25SEL_S    EQU 4
UDMA_CHMAP3_CH24SEL_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_O_SRCENDP register.
;
;*************************************************************
UDMA_SRCENDP_ADDR_M    EQU  0xFFFFFFFF  ; Source Address End Pointer
UDMA_SRCENDP_ADDR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_O_DSTENDP register.
;
;*************************************************************
UDMA_DSTENDP_ADDR_M    EQU  0xFFFFFFFF  ; Destination Address End Pointer
UDMA_DSTENDP_ADDR_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the UDMA_O_CHCTL register.
;
;*************************************************************
UDMA_CHCTL_DSTINC_M    EQU  0xC0000000  ; Destination Address Increment
UDMA_CHCTL_DSTINC_8    EQU  0x00000000  ; Byte
UDMA_CHCTL_DSTINC_16   EQU  0x40000000  ; Half-word
UDMA_CHCTL_DSTINC_32   EQU  0x80000000  ; Word
UDMA_CHCTL_DSTINC_NONE EQU  0xC0000000  ; No increment
UDMA_CHCTL_DSTSIZE_M   EQU  0x30000000  ; Destination Data Size
UDMA_CHCTL_DSTSIZE_8   EQU  0x00000000  ; Byte
UDMA_CHCTL_DSTSIZE_16  EQU  0x10000000  ; Half-word
UDMA_CHCTL_DSTSIZE_32  EQU  0x20000000  ; Word
UDMA_CHCTL_SRCINC_M    EQU  0x0C000000  ; Source Address Increment
UDMA_CHCTL_SRCINC_8    EQU  0x00000000  ; Byte
UDMA_CHCTL_SRCINC_16   EQU  0x04000000  ; Half-word
UDMA_CHCTL_SRCINC_32   EQU  0x08000000  ; Word
UDMA_CHCTL_SRCINC_NONE EQU  0x0C000000  ; No increment
UDMA_CHCTL_SRCSIZE_M   EQU  0x03000000  ; Source Data Size
UDMA_CHCTL_SRCSIZE_8   EQU  0x00000000  ; Byte
UDMA_CHCTL_SRCSIZE_16  EQU  0x01000000  ; Half-word
UDMA_CHCTL_SRCSIZE_32  EQU  0x02000000  ; Word
UDMA_CHCTL_ARBSIZE_M   EQU  0x0003C000  ; Arbitration Size
UDMA_CHCTL_ARBSIZE_1   EQU  0x00000000  ; 1 Transfer
UDMA_CHCTL_ARBSIZE_2   EQU  0x00004000  ; 2 Transfers
UDMA_CHCTL_ARBSIZE_4   EQU  0x00008000  ; 4 Transfers
UDMA_CHCTL_ARBSIZE_8   EQU  0x0000C000  ; 8 Transfers
UDMA_CHCTL_ARBSIZE_16  EQU  0x00010000  ; 16 Transfers
UDMA_CHCTL_ARBSIZE_32  EQU  0x00014000  ; 32 Transfers
UDMA_CHCTL_ARBSIZE_64  EQU  0x00018000  ; 64 Transfers
UDMA_CHCTL_ARBSIZE_128 EQU  0x0001C000  ; 128 Transfers
UDMA_CHCTL_ARBSIZE_256 EQU  0x00020000  ; 256 Transfers
UDMA_CHCTL_ARBSIZE_512 EQU  0x00024000  ; 512 Transfers
UDMA_CHCTL_ARBSIZE_1024 EQU  0x00028000  ; 1024 Transfers
UDMA_CHCTL_XFERSIZE_M  EQU  0x00003FF0  ; Transfer Size (minus 1)
UDMA_CHCTL_NXTUSEBURST EQU  0x00000008  ; Next Useburst
UDMA_CHCTL_XFERMODE_M  EQU  0x00000007  ; uDMA Transfer Mode
UDMA_CHCTL_XFERMODE_STOP EQU  0x00000000  ; Stop
UDMA_CHCTL_XFERMODE_BASIC EQU  0x00000001  ; Basic
UDMA_CHCTL_XFERMODE_AUTO EQU  0x00000002  ; Auto-Request
UDMA_CHCTL_XFERMODE_PINGPONG EQU  0x00000003  ; Ping-Pong
UDMA_CHCTL_XFERMODE_MEM_SG EQU  0x00000004  ; Memory Scatter-Gather
UDMA_CHCTL_XFERMODE_MEM_SGA EQU  0x00000005  ; Alternate Memory Scatter-Gather
UDMA_CHCTL_XFERMODE_PER_SG EQU  0x00000006  ; Peripheral Scatter-Gather
UDMA_CHCTL_XFERMODE_PER_SGA EQU  0x00000007  ; Alternate Peripheral
                                            ; Scatter-Gather
UDMA_CHCTL_XFERSIZE_S    EQU 4

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_INT_TYPE register.
;
;*************************************************************
NVIC_INT_TYPE_LINES_M  EQU  0x0000001F  ; Number of interrupt lines (x32)
NVIC_INT_TYPE_LINES_S    EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTLR register.
;
;*************************************************************
NVIC_ACTLR_DISOOFP     EQU  0x00000200  ; Disable Out-Of-Order Floating
                                            ; Point
NVIC_ACTLR_DISFPCA     EQU  0x00000100  ; Disable CONTROL
NVIC_ACTLR_DISFOLD     EQU  0x00000004  ; Disable IT Folding
NVIC_ACTLR_DISWBUF     EQU  0x00000002  ; Disable Write Buffer
NVIC_ACTLR_DISMCYC     EQU  0x00000001  ; Disable Interrupts of Multiple
                                            ; Cycle Instructions

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ST_CTRL register.
;
;*************************************************************
NVIC_ST_CTRL_COUNT     EQU  0x00010000  ; Count Flag
NVIC_ST_CTRL_CLK_SRC   EQU  0x00000004  ; Clock Source
NVIC_ST_CTRL_INTEN     EQU  0x00000002  ; Interrupt Enable
NVIC_ST_CTRL_ENABLE    EQU  0x00000001  ; Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ST_RELOAD register.
;
;*************************************************************
NVIC_ST_RELOAD_M       EQU  0x00FFFFFF  ; Reload Value
NVIC_ST_RELOAD_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ST_CURRENT
; register.
;
;*************************************************************
NVIC_ST_CURRENT_M      EQU  0x00FFFFFF  ; Current Value
NVIC_ST_CURRENT_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ST_CAL register.
;
;*************************************************************
NVIC_ST_CAL_NOREF      EQU  0x80000000  ; No reference clock
NVIC_ST_CAL_SKEW       EQU  0x40000000  ; Clock skew
NVIC_ST_CAL_ONEMS_M    EQU  0x00FFFFFF  ; 1ms reference value
NVIC_ST_CAL_ONEMS_S    EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_EN0 register.
;
;*************************************************************
NVIC_EN0_INT_M         EQU  0xFFFFFFFF  ; Interrupt Enable
NVIC_EN0_INT0          EQU  0x00000001  ; Interrupt 0 enable
NVIC_EN0_INT1          EQU  0x00000002  ; Interrupt 1 enable
NVIC_EN0_INT2          EQU  0x00000004  ; Interrupt 2 enable
NVIC_EN0_INT3          EQU  0x00000008  ; Interrupt 3 enable
NVIC_EN0_INT4          EQU  0x00000010  ; Interrupt 4 enable
NVIC_EN0_INT5          EQU  0x00000020  ; Interrupt 5 enable
NVIC_EN0_INT6          EQU  0x00000040  ; Interrupt 6 enable
NVIC_EN0_INT7          EQU  0x00000080  ; Interrupt 7 enable
NVIC_EN0_INT8          EQU  0x00000100  ; Interrupt 8 enable
NVIC_EN0_INT9          EQU  0x00000200  ; Interrupt 9 enable
NVIC_EN0_INT10         EQU  0x00000400  ; Interrupt 10 enable
NVIC_EN0_INT11         EQU  0x00000800  ; Interrupt 11 enable
NVIC_EN0_INT12         EQU  0x00001000  ; Interrupt 12 enable
NVIC_EN0_INT13         EQU  0x00002000  ; Interrupt 13 enable
NVIC_EN0_INT14         EQU  0x00004000  ; Interrupt 14 enable
NVIC_EN0_INT15         EQU  0x00008000  ; Interrupt 15 enable
NVIC_EN0_INT16         EQU  0x00010000  ; Interrupt 16 enable
NVIC_EN0_INT17         EQU  0x00020000  ; Interrupt 17 enable
NVIC_EN0_INT18         EQU  0x00040000  ; Interrupt 18 enable
NVIC_EN0_INT19         EQU  0x00080000  ; Interrupt 19 enable
NVIC_EN0_INT20         EQU  0x00100000  ; Interrupt 20 enable
NVIC_EN0_INT21         EQU  0x00200000  ; Interrupt 21 enable
NVIC_EN0_INT22         EQU  0x00400000  ; Interrupt 22 enable
NVIC_EN0_INT23         EQU  0x00800000  ; Interrupt 23 enable
NVIC_EN0_INT24         EQU  0x01000000  ; Interrupt 24 enable
NVIC_EN0_INT25         EQU  0x02000000  ; Interrupt 25 enable
NVIC_EN0_INT26         EQU  0x04000000  ; Interrupt 26 enable
NVIC_EN0_INT27         EQU  0x08000000  ; Interrupt 27 enable
NVIC_EN0_INT28         EQU  0x10000000  ; Interrupt 28 enable
NVIC_EN0_INT29         EQU  0x20000000  ; Interrupt 29 enable
NVIC_EN0_INT30         EQU  0x40000000  ; Interrupt 30 enable
NVIC_EN0_INT31         EQU  0x80000000  ; Interrupt 31 enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_EN1 register.
;
;*************************************************************
NVIC_EN1_INT_M         EQU  0xFFFFFFFF  ; Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_EN2 register.
;
;*************************************************************
NVIC_EN2_INT_M         EQU  0xFFFFFFFF  ; Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_EN3 register.
;
;*************************************************************
NVIC_EN3_INT_M         EQU  0xFFFFFFFF  ; Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_EN4 register.
;
;*************************************************************
NVIC_EN4_INT_M         EQU  0x000007FF  ; Interrupt Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DIS0 register.
;
;*************************************************************
NVIC_DIS0_INT_M        EQU  0xFFFFFFFF  ; Interrupt Disable
NVIC_DIS0_INT0         EQU  0x00000001  ; Interrupt 0 disable
NVIC_DIS0_INT1         EQU  0x00000002  ; Interrupt 1 disable
NVIC_DIS0_INT2         EQU  0x00000004  ; Interrupt 2 disable
NVIC_DIS0_INT3         EQU  0x00000008  ; Interrupt 3 disable
NVIC_DIS0_INT4         EQU  0x00000010  ; Interrupt 4 disable
NVIC_DIS0_INT5         EQU  0x00000020  ; Interrupt 5 disable
NVIC_DIS0_INT6         EQU  0x00000040  ; Interrupt 6 disable
NVIC_DIS0_INT7         EQU  0x00000080  ; Interrupt 7 disable
NVIC_DIS0_INT8         EQU  0x00000100  ; Interrupt 8 disable
NVIC_DIS0_INT9         EQU  0x00000200  ; Interrupt 9 disable
NVIC_DIS0_INT10        EQU  0x00000400  ; Interrupt 10 disable
NVIC_DIS0_INT11        EQU  0x00000800  ; Interrupt 11 disable
NVIC_DIS0_INT12        EQU  0x00001000  ; Interrupt 12 disable
NVIC_DIS0_INT13        EQU  0x00002000  ; Interrupt 13 disable
NVIC_DIS0_INT14        EQU  0x00004000  ; Interrupt 14 disable
NVIC_DIS0_INT15        EQU  0x00008000  ; Interrupt 15 disable
NVIC_DIS0_INT16        EQU  0x00010000  ; Interrupt 16 disable
NVIC_DIS0_INT17        EQU  0x00020000  ; Interrupt 17 disable
NVIC_DIS0_INT18        EQU  0x00040000  ; Interrupt 18 disable
NVIC_DIS0_INT19        EQU  0x00080000  ; Interrupt 19 disable
NVIC_DIS0_INT20        EQU  0x00100000  ; Interrupt 20 disable
NVIC_DIS0_INT21        EQU  0x00200000  ; Interrupt 21 disable
NVIC_DIS0_INT22        EQU  0x00400000  ; Interrupt 22 disable
NVIC_DIS0_INT23        EQU  0x00800000  ; Interrupt 23 disable
NVIC_DIS0_INT24        EQU  0x01000000  ; Interrupt 24 disable
NVIC_DIS0_INT25        EQU  0x02000000  ; Interrupt 25 disable
NVIC_DIS0_INT26        EQU  0x04000000  ; Interrupt 26 disable
NVIC_DIS0_INT27        EQU  0x08000000  ; Interrupt 27 disable
NVIC_DIS0_INT28        EQU  0x10000000  ; Interrupt 28 disable
NVIC_DIS0_INT29        EQU  0x20000000  ; Interrupt 29 disable
NVIC_DIS0_INT30        EQU  0x40000000  ; Interrupt 30 disable
NVIC_DIS0_INT31        EQU  0x80000000  ; Interrupt 31 disable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DIS1 register.
;
;*************************************************************
NVIC_DIS1_INT_M        EQU  0xFFFFFFFF  ; Interrupt Disable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DIS2 register.
;
;*************************************************************
NVIC_DIS2_INT_M        EQU  0xFFFFFFFF  ; Interrupt Disable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DIS3 register.
;
;*************************************************************
NVIC_DIS3_INT_M        EQU  0xFFFFFFFF  ; Interrupt Disable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DIS4 register.
;
;*************************************************************
NVIC_DIS4_INT_M        EQU  0x000007FF  ; Interrupt Disable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PEND0 register.
;
;*************************************************************
NVIC_PEND0_INT_M       EQU  0xFFFFFFFF  ; Interrupt Set Pending
NVIC_PEND0_INT0        EQU  0x00000001  ; Interrupt 0 pend
NVIC_PEND0_INT1        EQU  0x00000002  ; Interrupt 1 pend
NVIC_PEND0_INT2        EQU  0x00000004  ; Interrupt 2 pend
NVIC_PEND0_INT3        EQU  0x00000008  ; Interrupt 3 pend
NVIC_PEND0_INT4        EQU  0x00000010  ; Interrupt 4 pend
NVIC_PEND0_INT5        EQU  0x00000020  ; Interrupt 5 pend
NVIC_PEND0_INT6        EQU  0x00000040  ; Interrupt 6 pend
NVIC_PEND0_INT7        EQU  0x00000080  ; Interrupt 7 pend
NVIC_PEND0_INT8        EQU  0x00000100  ; Interrupt 8 pend
NVIC_PEND0_INT9        EQU  0x00000200  ; Interrupt 9 pend
NVIC_PEND0_INT10       EQU  0x00000400  ; Interrupt 10 pend
NVIC_PEND0_INT11       EQU  0x00000800  ; Interrupt 11 pend
NVIC_PEND0_INT12       EQU  0x00001000  ; Interrupt 12 pend
NVIC_PEND0_INT13       EQU  0x00002000  ; Interrupt 13 pend
NVIC_PEND0_INT14       EQU  0x00004000  ; Interrupt 14 pend
NVIC_PEND0_INT15       EQU  0x00008000  ; Interrupt 15 pend
NVIC_PEND0_INT16       EQU  0x00010000  ; Interrupt 16 pend
NVIC_PEND0_INT17       EQU  0x00020000  ; Interrupt 17 pend
NVIC_PEND0_INT18       EQU  0x00040000  ; Interrupt 18 pend
NVIC_PEND0_INT19       EQU  0x00080000  ; Interrupt 19 pend
NVIC_PEND0_INT20       EQU  0x00100000  ; Interrupt 20 pend
NVIC_PEND0_INT21       EQU  0x00200000  ; Interrupt 21 pend
NVIC_PEND0_INT22       EQU  0x00400000  ; Interrupt 22 pend
NVIC_PEND0_INT23       EQU  0x00800000  ; Interrupt 23 pend
NVIC_PEND0_INT24       EQU  0x01000000  ; Interrupt 24 pend
NVIC_PEND0_INT25       EQU  0x02000000  ; Interrupt 25 pend
NVIC_PEND0_INT26       EQU  0x04000000  ; Interrupt 26 pend
NVIC_PEND0_INT27       EQU  0x08000000  ; Interrupt 27 pend
NVIC_PEND0_INT28       EQU  0x10000000  ; Interrupt 28 pend
NVIC_PEND0_INT29       EQU  0x20000000  ; Interrupt 29 pend
NVIC_PEND0_INT30       EQU  0x40000000  ; Interrupt 30 pend
NVIC_PEND0_INT31       EQU  0x80000000  ; Interrupt 31 pend

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PEND1 register.
;
;*************************************************************
NVIC_PEND1_INT_M       EQU  0xFFFFFFFF  ; Interrupt Set Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PEND2 register.
;
;*************************************************************
NVIC_PEND2_INT_M       EQU  0xFFFFFFFF  ; Interrupt Set Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PEND3 register.
;
;*************************************************************
NVIC_PEND3_INT_M       EQU  0xFFFFFFFF  ; Interrupt Set Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PEND4 register.
;
;*************************************************************
NVIC_PEND4_INT_M       EQU  0x000007FF  ; Interrupt Set Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_UNPEND0 register.
;
;*************************************************************
NVIC_UNPEND0_INT_M     EQU  0xFFFFFFFF  ; Interrupt Clear Pending
NVIC_UNPEND0_INT0      EQU  0x00000001  ; Interrupt 0 unpend
NVIC_UNPEND0_INT1      EQU  0x00000002  ; Interrupt 1 unpend
NVIC_UNPEND0_INT2      EQU  0x00000004  ; Interrupt 2 unpend
NVIC_UNPEND0_INT3      EQU  0x00000008  ; Interrupt 3 unpend
NVIC_UNPEND0_INT4      EQU  0x00000010  ; Interrupt 4 unpend
NVIC_UNPEND0_INT5      EQU  0x00000020  ; Interrupt 5 unpend
NVIC_UNPEND0_INT6      EQU  0x00000040  ; Interrupt 6 unpend
NVIC_UNPEND0_INT7      EQU  0x00000080  ; Interrupt 7 unpend
NVIC_UNPEND0_INT8      EQU  0x00000100  ; Interrupt 8 unpend
NVIC_UNPEND0_INT9      EQU  0x00000200  ; Interrupt 9 unpend
NVIC_UNPEND0_INT10     EQU  0x00000400  ; Interrupt 10 unpend
NVIC_UNPEND0_INT11     EQU  0x00000800  ; Interrupt 11 unpend
NVIC_UNPEND0_INT12     EQU  0x00001000  ; Interrupt 12 unpend
NVIC_UNPEND0_INT13     EQU  0x00002000  ; Interrupt 13 unpend
NVIC_UNPEND0_INT14     EQU  0x00004000  ; Interrupt 14 unpend
NVIC_UNPEND0_INT15     EQU  0x00008000  ; Interrupt 15 unpend
NVIC_UNPEND0_INT16     EQU  0x00010000  ; Interrupt 16 unpend
NVIC_UNPEND0_INT17     EQU  0x00020000  ; Interrupt 17 unpend
NVIC_UNPEND0_INT18     EQU  0x00040000  ; Interrupt 18 unpend
NVIC_UNPEND0_INT19     EQU  0x00080000  ; Interrupt 19 unpend
NVIC_UNPEND0_INT20     EQU  0x00100000  ; Interrupt 20 unpend
NVIC_UNPEND0_INT21     EQU  0x00200000  ; Interrupt 21 unpend
NVIC_UNPEND0_INT22     EQU  0x00400000  ; Interrupt 22 unpend
NVIC_UNPEND0_INT23     EQU  0x00800000  ; Interrupt 23 unpend
NVIC_UNPEND0_INT24     EQU  0x01000000  ; Interrupt 24 unpend
NVIC_UNPEND0_INT25     EQU  0x02000000  ; Interrupt 25 unpend
NVIC_UNPEND0_INT26     EQU  0x04000000  ; Interrupt 26 unpend
NVIC_UNPEND0_INT27     EQU  0x08000000  ; Interrupt 27 unpend
NVIC_UNPEND0_INT28     EQU  0x10000000  ; Interrupt 28 unpend
NVIC_UNPEND0_INT29     EQU  0x20000000  ; Interrupt 29 unpend
NVIC_UNPEND0_INT30     EQU  0x40000000  ; Interrupt 30 unpend
NVIC_UNPEND0_INT31     EQU  0x80000000  ; Interrupt 31 unpend

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_UNPEND1 register.
;
;*************************************************************
NVIC_UNPEND1_INT_M     EQU  0xFFFFFFFF  ; Interrupt Clear Pending
NVIC_UNPEND1_INT32     EQU  0x00000001  ; Interrupt 32 unpend
NVIC_UNPEND1_INT33     EQU  0x00000002  ; Interrupt 33 unpend
NVIC_UNPEND1_INT34     EQU  0x00000004  ; Interrupt 34 unpend
NVIC_UNPEND1_INT35     EQU  0x00000008  ; Interrupt 35 unpend
NVIC_UNPEND1_INT36     EQU  0x00000010  ; Interrupt 36 unpend
NVIC_UNPEND1_INT37     EQU  0x00000020  ; Interrupt 37 unpend
NVIC_UNPEND1_INT38     EQU  0x00000040  ; Interrupt 38 unpend
NVIC_UNPEND1_INT39     EQU  0x00000080  ; Interrupt 39 unpend
NVIC_UNPEND1_INT40     EQU  0x00000100  ; Interrupt 40 unpend
NVIC_UNPEND1_INT41     EQU  0x00000200  ; Interrupt 41 unpend
NVIC_UNPEND1_INT42     EQU  0x00000400  ; Interrupt 42 unpend
NVIC_UNPEND1_INT43     EQU  0x00000800  ; Interrupt 43 unpend
NVIC_UNPEND1_INT44     EQU  0x00001000  ; Interrupt 44 unpend
NVIC_UNPEND1_INT45     EQU  0x00002000  ; Interrupt 45 unpend
NVIC_UNPEND1_INT46     EQU  0x00004000  ; Interrupt 46 unpend
NVIC_UNPEND1_INT47     EQU  0x00008000  ; Interrupt 47 unpend
NVIC_UNPEND1_INT48     EQU  0x00010000  ; Interrupt 48 unpend
NVIC_UNPEND1_INT49     EQU  0x00020000  ; Interrupt 49 unpend
NVIC_UNPEND1_INT50     EQU  0x00040000  ; Interrupt 50 unpend
NVIC_UNPEND1_INT51     EQU  0x00080000  ; Interrupt 51 unpend
NVIC_UNPEND1_INT52     EQU  0x00100000  ; Interrupt 52 unpend
NVIC_UNPEND1_INT53     EQU  0x00200000  ; Interrupt 53 unpend
NVIC_UNPEND1_INT54     EQU  0x00400000  ; Interrupt 54 unpend
NVIC_UNPEND1_INT55     EQU  0x00800000  ; Interrupt 55 unpend

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_UNPEND2 register.
;
;*************************************************************
NVIC_UNPEND2_INT_M     EQU  0xFFFFFFFF  ; Interrupt Clear Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_UNPEND3 register.
;
;*************************************************************
NVIC_UNPEND3_INT_M     EQU  0xFFFFFFFF  ; Interrupt Clear Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_UNPEND4 register.
;
;*************************************************************
NVIC_UNPEND4_INT_M     EQU  0x000007FF  ; Interrupt Clear Pending

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTIVE0 register.
;
;*************************************************************
NVIC_ACTIVE0_INT_M     EQU  0xFFFFFFFF  ; Interrupt Active
NVIC_ACTIVE0_INT0      EQU  0x00000001  ; Interrupt 0 active
NVIC_ACTIVE0_INT1      EQU  0x00000002  ; Interrupt 1 active
NVIC_ACTIVE0_INT2      EQU  0x00000004  ; Interrupt 2 active
NVIC_ACTIVE0_INT3      EQU  0x00000008  ; Interrupt 3 active
NVIC_ACTIVE0_INT4      EQU  0x00000010  ; Interrupt 4 active
NVIC_ACTIVE0_INT5      EQU  0x00000020  ; Interrupt 5 active
NVIC_ACTIVE0_INT6      EQU  0x00000040  ; Interrupt 6 active
NVIC_ACTIVE0_INT7      EQU  0x00000080  ; Interrupt 7 active
NVIC_ACTIVE0_INT8      EQU  0x00000100  ; Interrupt 8 active
NVIC_ACTIVE0_INT9      EQU  0x00000200  ; Interrupt 9 active
NVIC_ACTIVE0_INT10     EQU  0x00000400  ; Interrupt 10 active
NVIC_ACTIVE0_INT11     EQU  0x00000800  ; Interrupt 11 active
NVIC_ACTIVE0_INT12     EQU  0x00001000  ; Interrupt 12 active
NVIC_ACTIVE0_INT13     EQU  0x00002000  ; Interrupt 13 active
NVIC_ACTIVE0_INT14     EQU  0x00004000  ; Interrupt 14 active
NVIC_ACTIVE0_INT15     EQU  0x00008000  ; Interrupt 15 active
NVIC_ACTIVE0_INT16     EQU  0x00010000  ; Interrupt 16 active
NVIC_ACTIVE0_INT17     EQU  0x00020000  ; Interrupt 17 active
NVIC_ACTIVE0_INT18     EQU  0x00040000  ; Interrupt 18 active
NVIC_ACTIVE0_INT19     EQU  0x00080000  ; Interrupt 19 active
NVIC_ACTIVE0_INT20     EQU  0x00100000  ; Interrupt 20 active
NVIC_ACTIVE0_INT21     EQU  0x00200000  ; Interrupt 21 active
NVIC_ACTIVE0_INT22     EQU  0x00400000  ; Interrupt 22 active
NVIC_ACTIVE0_INT23     EQU  0x00800000  ; Interrupt 23 active
NVIC_ACTIVE0_INT24     EQU  0x01000000  ; Interrupt 24 active
NVIC_ACTIVE0_INT25     EQU  0x02000000  ; Interrupt 25 active
NVIC_ACTIVE0_INT26     EQU  0x04000000  ; Interrupt 26 active
NVIC_ACTIVE0_INT27     EQU  0x08000000  ; Interrupt 27 active
NVIC_ACTIVE0_INT28     EQU  0x10000000  ; Interrupt 28 active
NVIC_ACTIVE0_INT29     EQU  0x20000000  ; Interrupt 29 active
NVIC_ACTIVE0_INT30     EQU  0x40000000  ; Interrupt 30 active
NVIC_ACTIVE0_INT31     EQU  0x80000000  ; Interrupt 31 active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTIVE1 register.
;
;*************************************************************
NVIC_ACTIVE1_INT_M     EQU  0xFFFFFFFF  ; Interrupt Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTIVE2 register.
;
;*************************************************************
NVIC_ACTIVE2_INT_M     EQU  0xFFFFFFFF  ; Interrupt Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTIVE3 register.
;
;*************************************************************
NVIC_ACTIVE3_INT_M     EQU  0xFFFFFFFF  ; Interrupt Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_ACTIVE4 register.
;
;*************************************************************
NVIC_ACTIVE4_INT_M     EQU  0x000007FF  ; Interrupt Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI0 register.
;
;*************************************************************
NVIC_PRI0_INT3_M       EQU  0xE0000000  ; Interrupt 3 Priority Mask
NVIC_PRI0_INT2_M       EQU  0x00E00000  ; Interrupt 2 Priority Mask
NVIC_PRI0_INT1_M       EQU  0x0000E000  ; Interrupt 1 Priority Mask
NVIC_PRI0_INT0_M       EQU  0x000000E0  ; Interrupt 0 Priority Mask
NVIC_PRI0_INT3_S    EQU      29
NVIC_PRI0_INT2_S    EQU      21
NVIC_PRI0_INT1_S    EQU      13
NVIC_PRI0_INT0_S    EQU      5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI1 register.
;
;*************************************************************
NVIC_PRI1_INT7_M       EQU  0xE0000000  ; Interrupt 7 Priority Mask
NVIC_PRI1_INT6_M       EQU  0x00E00000  ; Interrupt 6 Priority Mask
NVIC_PRI1_INT5_M       EQU  0x0000E000  ; Interrupt 5 Priority Mask
NVIC_PRI1_INT4_M       EQU  0x000000E0  ; Interrupt 4 Priority Mask
NVIC_PRI1_INT7_S    EQU      29
NVIC_PRI1_INT6_S    EQU      21
NVIC_PRI1_INT5_S    EQU      13
NVIC_PRI1_INT4_S    EQU      5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI2 register.
;
;*************************************************************
NVIC_PRI2_INT11_M      EQU  0xE0000000  ; Interrupt 11 Priority Mask
NVIC_PRI2_INT10_M      EQU  0x00E00000  ; Interrupt 10 Priority Mask
NVIC_PRI2_INT9_M       EQU  0x0000E000  ; Interrupt 9 Priority Mask
NVIC_PRI2_INT8_M       EQU  0x000000E0  ; Interrupt 8 Priority Mask
NVIC_PRI2_INT11_S    EQU     29
NVIC_PRI2_INT10_S    EQU     21
NVIC_PRI2_INT9_S    EQU      13
NVIC_PRI2_INT8_S    EQU      5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI3 register.
;
;*************************************************************
NVIC_PRI3_INT15_M      EQU  0xE0000000  ; Interrupt 15 Priority Mask
NVIC_PRI3_INT14_M      EQU  0x00E00000  ; Interrupt 14 Priority Mask
NVIC_PRI3_INT13_M      EQU  0x0000E000  ; Interrupt 13 Priority Mask
NVIC_PRI3_INT12_M      EQU  0x000000E0  ; Interrupt 12 Priority Mask
NVIC_PRI3_INT15_S    EQU     29
NVIC_PRI3_INT14_S    EQU     21
NVIC_PRI3_INT13_S    EQU     13
NVIC_PRI3_INT12_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI4 register.
;
;*************************************************************
NVIC_PRI4_INT19_M      EQU  0xE0000000  ; Interrupt 19 Priority Mask
NVIC_PRI4_INT18_M      EQU  0x00E00000  ; Interrupt 18 Priority Mask
NVIC_PRI4_INT17_M      EQU  0x0000E000  ; Interrupt 17 Priority Mask
NVIC_PRI4_INT16_M      EQU  0x000000E0  ; Interrupt 16 Priority Mask
NVIC_PRI4_INT19_S    EQU     29
NVIC_PRI4_INT18_S    EQU     21
NVIC_PRI4_INT17_S    EQU     13
NVIC_PRI4_INT16_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI5 register.
;
;*************************************************************
NVIC_PRI5_INT23_M      EQU  0xE0000000  ; Interrupt 23 Priority Mask
NVIC_PRI5_INT22_M      EQU  0x00E00000  ; Interrupt 22 Priority Mask
NVIC_PRI5_INT21_M      EQU  0x0000E000  ; Interrupt 21 Priority Mask
NVIC_PRI5_INT20_M      EQU  0x000000E0  ; Interrupt 20 Priority Mask
NVIC_PRI5_INT23_S    EQU     29
NVIC_PRI5_INT22_S    EQU     21
NVIC_PRI5_INT21_S    EQU     13
NVIC_PRI5_INT20_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI6 register.
;
;*************************************************************
NVIC_PRI6_INT27_M      EQU  0xE0000000  ; Interrupt 27 Priority Mask
NVIC_PRI6_INT26_M      EQU  0x00E00000  ; Interrupt 26 Priority Mask
NVIC_PRI6_INT25_M      EQU  0x0000E000  ; Interrupt 25 Priority Mask
NVIC_PRI6_INT24_M      EQU  0x000000E0  ; Interrupt 24 Priority Mask
NVIC_PRI6_INT27_S    EQU     29
NVIC_PRI6_INT26_S    EQU     21
NVIC_PRI6_INT25_S    EQU     13
NVIC_PRI6_INT24_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI7 register.
;
;*************************************************************
NVIC_PRI7_INT31_M      EQU  0xE0000000  ; Interrupt 31 Priority Mask
NVIC_PRI7_INT30_M      EQU  0x00E00000  ; Interrupt 30 Priority Mask
NVIC_PRI7_INT29_M      EQU  0x0000E000  ; Interrupt 29 Priority Mask
NVIC_PRI7_INT28_M      EQU  0x000000E0  ; Interrupt 28 Priority Mask
NVIC_PRI7_INT31_S    EQU     29
NVIC_PRI7_INT30_S    EQU     21
NVIC_PRI7_INT29_S    EQU     13
NVIC_PRI7_INT28_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI8 register.
;
;*************************************************************
NVIC_PRI8_INT35_M      EQU  0xE0000000  ; Interrupt 35 Priority Mask
NVIC_PRI8_INT34_M      EQU  0x00E00000  ; Interrupt 34 Priority Mask
NVIC_PRI8_INT33_M      EQU  0x0000E000  ; Interrupt 33 Priority Mask
NVIC_PRI8_INT32_M      EQU  0x000000E0  ; Interrupt 32 Priority Mask
NVIC_PRI8_INT35_S    EQU     29
NVIC_PRI8_INT34_S    EQU     21
NVIC_PRI8_INT33_S    EQU     13
NVIC_PRI8_INT32_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI9 register.
;
;*************************************************************
NVIC_PRI9_INT39_M      EQU  0xE0000000  ; Interrupt 39 Priority Mask
NVIC_PRI9_INT38_M      EQU  0x00E00000  ; Interrupt 38 Priority Mask
NVIC_PRI9_INT37_M      EQU  0x0000E000  ; Interrupt 37 Priority Mask
NVIC_PRI9_INT36_M      EQU  0x000000E0  ; Interrupt 36 Priority Mask
NVIC_PRI9_INT39_S    EQU     29
NVIC_PRI9_INT38_S    EQU     21
NVIC_PRI9_INT37_S    EQU     13
NVIC_PRI9_INT36_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI10 register.
;
;*************************************************************
NVIC_PRI10_INT43_M     EQU  0xE0000000  ; Interrupt 43 Priority Mask
NVIC_PRI10_INT42_M     EQU  0x00E00000  ; Interrupt 42 Priority Mask
NVIC_PRI10_INT41_M     EQU  0x0000E000  ; Interrupt 41 Priority Mask
NVIC_PRI10_INT40_M     EQU  0x000000E0  ; Interrupt 40 Priority Mask
NVIC_PRI10_INT43_S    EQU    29
NVIC_PRI10_INT42_S    EQU    21
NVIC_PRI10_INT41_S    EQU    13
NVIC_PRI10_INT40_S    EQU    5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI11 register.
;
;*************************************************************
NVIC_PRI11_INT47_M     EQU  0xE0000000  ; Interrupt 47 Priority Mask
NVIC_PRI11_INT46_M     EQU  0x00E00000  ; Interrupt 46 Priority Mask
NVIC_PRI11_INT45_M     EQU  0x0000E000  ; Interrupt 45 Priority Mask
NVIC_PRI11_INT44_M     EQU  0x000000E0  ; Interrupt 44 Priority Mask
NVIC_PRI11_INT47_S    EQU    29
NVIC_PRI11_INT46_S    EQU    21
NVIC_PRI11_INT45_S    EQU    13
NVIC_PRI11_INT44_S    EQU    5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI12 register.
;
;*************************************************************
NVIC_PRI12_INT51_M     EQU  0xE0000000  ; Interrupt 51 Priority Mask
NVIC_PRI12_INT50_M     EQU  0x00E00000  ; Interrupt 50 Priority Mask
NVIC_PRI12_INT49_M     EQU  0x0000E000  ; Interrupt 49 Priority Mask
NVIC_PRI12_INT48_M     EQU  0x000000E0  ; Interrupt 48 Priority Mask
NVIC_PRI12_INT51_S    EQU    29
NVIC_PRI12_INT50_S    EQU    21
NVIC_PRI12_INT49_S    EQU    13
NVIC_PRI12_INT48_S    EQU    5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI13 register.
;
;*************************************************************
NVIC_PRI13_INT55_M     EQU  0xE0000000  ; Interrupt 55 Priority Mask
NVIC_PRI13_INT54_M     EQU  0x00E00000  ; Interrupt 54 Priority Mask
NVIC_PRI13_INT53_M     EQU  0x0000E000  ; Interrupt 53 Priority Mask
NVIC_PRI13_INT52_M     EQU  0x000000E0  ; Interrupt 52 Priority Mask
NVIC_PRI13_INT55_S    EQU    29
NVIC_PRI13_INT54_S    EQU    21
NVIC_PRI13_INT53_S    EQU    13
NVIC_PRI13_INT52_S    EQU    5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI14 register.
;
;*************************************************************
NVIC_PRI14_INTD_M      EQU  0xE0000000  ; Interrupt 59 Priority Mask
NVIC_PRI14_INTC_M      EQU  0x00E00000  ; Interrupt 58 Priority Mask
NVIC_PRI14_INTB_M      EQU  0x0000E000  ; Interrupt 57 Priority Mask
NVIC_PRI14_INTA_M      EQU  0x000000E0  ; Interrupt 56 Priority Mask
NVIC_PRI14_INTD_S    EQU     29
NVIC_PRI14_INTC_S    EQU     21
NVIC_PRI14_INTB_S    EQU     13
NVIC_PRI14_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI15 register.
;
;*************************************************************
NVIC_PRI15_INTD_M      EQU  0xE0000000  ; Interrupt 63 Priority Mask
NVIC_PRI15_INTC_M      EQU  0x00E00000  ; Interrupt 62 Priority Mask
NVIC_PRI15_INTB_M      EQU  0x0000E000  ; Interrupt 61 Priority Mask
NVIC_PRI15_INTA_M      EQU  0x000000E0  ; Interrupt 60 Priority Mask
NVIC_PRI15_INTD_S    EQU     29
NVIC_PRI15_INTC_S    EQU     21
NVIC_PRI15_INTB_S    EQU     13
NVIC_PRI15_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI16 register.
;
;*************************************************************
NVIC_PRI16_INTD_M      EQU  0xE0000000  ; Interrupt 67 Priority Mask
NVIC_PRI16_INTC_M      EQU  0x00E00000  ; Interrupt 66 Priority Mask
NVIC_PRI16_INTB_M      EQU  0x0000E000  ; Interrupt 65 Priority Mask
NVIC_PRI16_INTA_M      EQU  0x000000E0  ; Interrupt 64 Priority Mask
NVIC_PRI16_INTD_S    EQU     29
NVIC_PRI16_INTC_S    EQU     21
NVIC_PRI16_INTB_S    EQU     13
NVIC_PRI16_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI17 register.
;
;*************************************************************
NVIC_PRI17_INTD_M      EQU  0xE0000000  ; Interrupt 71 Priority Mask
NVIC_PRI17_INTC_M      EQU  0x00E00000  ; Interrupt 70 Priority Mask
NVIC_PRI17_INTB_M      EQU  0x0000E000  ; Interrupt 69 Priority Mask
NVIC_PRI17_INTA_M      EQU  0x000000E0  ; Interrupt 68 Priority Mask
NVIC_PRI17_INTD_S    EQU     29
NVIC_PRI17_INTC_S    EQU     21
NVIC_PRI17_INTB_S    EQU     13
NVIC_PRI17_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI18 register.
;
;*************************************************************
NVIC_PRI18_INTD_M      EQU  0xE0000000  ; Interrupt 75 Priority Mask
NVIC_PRI18_INTC_M      EQU  0x00E00000  ; Interrupt 74 Priority Mask
NVIC_PRI18_INTB_M      EQU  0x0000E000  ; Interrupt 73 Priority Mask
NVIC_PRI18_INTA_M      EQU  0x000000E0  ; Interrupt 72 Priority Mask
NVIC_PRI18_INTD_S    EQU     29
NVIC_PRI18_INTC_S    EQU     21
NVIC_PRI18_INTB_S    EQU     13
NVIC_PRI18_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI19 register.
;
;*************************************************************
NVIC_PRI19_INTD_M      EQU  0xE0000000  ; Interrupt 79 Priority Mask
NVIC_PRI19_INTC_M      EQU  0x00E00000  ; Interrupt 78 Priority Mask
NVIC_PRI19_INTB_M      EQU  0x0000E000  ; Interrupt 77 Priority Mask
NVIC_PRI19_INTA_M      EQU  0x000000E0  ; Interrupt 76 Priority Mask
NVIC_PRI19_INTD_S    EQU     29
NVIC_PRI19_INTC_S    EQU     21
NVIC_PRI19_INTB_S    EQU     13
NVIC_PRI19_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI20 register.
;
;*************************************************************
NVIC_PRI20_INTD_M      EQU  0xE0000000  ; Interrupt 83 Priority Mask
NVIC_PRI20_INTC_M      EQU  0x00E00000  ; Interrupt 82 Priority Mask
NVIC_PRI20_INTB_M      EQU  0x0000E000  ; Interrupt 81 Priority Mask
NVIC_PRI20_INTA_M      EQU  0x000000E0  ; Interrupt 80 Priority Mask
NVIC_PRI20_INTD_S    EQU     29
NVIC_PRI20_INTC_S    EQU     21
NVIC_PRI20_INTB_S    EQU     13
NVIC_PRI20_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI21 register.
;
;*************************************************************
NVIC_PRI21_INTD_M      EQU  0xE0000000  ; Interrupt 87 Priority Mask
NVIC_PRI21_INTC_M      EQU  0x00E00000  ; Interrupt 86 Priority Mask
NVIC_PRI21_INTB_M      EQU  0x0000E000  ; Interrupt 85 Priority Mask
NVIC_PRI21_INTA_M      EQU  0x000000E0  ; Interrupt 84 Priority Mask
NVIC_PRI21_INTD_S    EQU     29
NVIC_PRI21_INTC_S    EQU     21
NVIC_PRI21_INTB_S    EQU     13
NVIC_PRI21_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI22 register.
;
;*************************************************************
NVIC_PRI22_INTD_M      EQU  0xE0000000  ; Interrupt 91 Priority Mask
NVIC_PRI22_INTC_M      EQU  0x00E00000  ; Interrupt 90 Priority Mask
NVIC_PRI22_INTB_M      EQU  0x0000E000  ; Interrupt 89 Priority Mask
NVIC_PRI22_INTA_M      EQU  0x000000E0  ; Interrupt 88 Priority Mask
NVIC_PRI22_INTD_S    EQU     29
NVIC_PRI22_INTC_S    EQU     21
NVIC_PRI22_INTB_S    EQU     13
NVIC_PRI22_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI23 register.
;
;*************************************************************
NVIC_PRI23_INTD_M      EQU  0xE0000000  ; Interrupt 95 Priority Mask
NVIC_PRI23_INTC_M      EQU  0x00E00000  ; Interrupt 94 Priority Mask
NVIC_PRI23_INTB_M      EQU  0x0000E000  ; Interrupt 93 Priority Mask
NVIC_PRI23_INTA_M      EQU  0x000000E0  ; Interrupt 92 Priority Mask
NVIC_PRI23_INTD_S    EQU     29
NVIC_PRI23_INTC_S    EQU     21
NVIC_PRI23_INTB_S    EQU     13
NVIC_PRI23_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI24 register.
;
;*************************************************************
NVIC_PRI24_INTD_M      EQU  0xE0000000  ; Interrupt 99 Priority Mask
NVIC_PRI24_INTC_M      EQU  0x00E00000  ; Interrupt 98 Priority Mask
NVIC_PRI24_INTB_M      EQU  0x0000E000  ; Interrupt 97 Priority Mask
NVIC_PRI24_INTA_M      EQU  0x000000E0  ; Interrupt 96 Priority Mask
NVIC_PRI24_INTD_S    EQU     29
NVIC_PRI24_INTC_S    EQU     21
NVIC_PRI24_INTB_S    EQU     13
NVIC_PRI24_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI25 register.
;
;*************************************************************
NVIC_PRI25_INTD_M      EQU  0xE0000000  ; Interrupt 103 Priority Mask
NVIC_PRI25_INTC_M      EQU  0x00E00000  ; Interrupt 102 Priority Mask
NVIC_PRI25_INTB_M      EQU  0x0000E000  ; Interrupt 101 Priority Mask
NVIC_PRI25_INTA_M      EQU  0x000000E0  ; Interrupt 100 Priority Mask
NVIC_PRI25_INTD_S    EQU     29
NVIC_PRI25_INTC_S    EQU     21
NVIC_PRI25_INTB_S    EQU     13
NVIC_PRI25_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI26 register.
;
;*************************************************************
NVIC_PRI26_INTD_M      EQU  0xE0000000  ; Interrupt 107 Priority Mask
NVIC_PRI26_INTC_M      EQU  0x00E00000  ; Interrupt 106 Priority Mask
NVIC_PRI26_INTB_M      EQU  0x0000E000  ; Interrupt 105 Priority Mask
NVIC_PRI26_INTA_M      EQU  0x000000E0  ; Interrupt 104 Priority Mask
NVIC_PRI26_INTD_S    EQU     29
NVIC_PRI26_INTC_S    EQU     21
NVIC_PRI26_INTB_S    EQU     13
NVIC_PRI26_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI27 register.
;
;*************************************************************
NVIC_PRI27_INTD_M      EQU  0xE0000000  ; Interrupt 111 Priority Mask
NVIC_PRI27_INTC_M      EQU  0x00E00000  ; Interrupt 110 Priority Mask
NVIC_PRI27_INTB_M      EQU  0x0000E000  ; Interrupt 109 Priority Mask
NVIC_PRI27_INTA_M      EQU  0x000000E0  ; Interrupt 108 Priority Mask
NVIC_PRI27_INTD_S    EQU     29
NVIC_PRI27_INTC_S    EQU     21
NVIC_PRI27_INTB_S    EQU     13
NVIC_PRI27_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI28 register.
;
;*************************************************************
NVIC_PRI28_INTD_M      EQU  0xE0000000  ; Interrupt 115 Priority Mask
NVIC_PRI28_INTC_M      EQU  0x00E00000  ; Interrupt 114 Priority Mask
NVIC_PRI28_INTB_M      EQU  0x0000E000  ; Interrupt 113 Priority Mask
NVIC_PRI28_INTA_M      EQU  0x000000E0  ; Interrupt 112 Priority Mask
NVIC_PRI28_INTD_S    EQU     29
NVIC_PRI28_INTC_S    EQU     21
NVIC_PRI28_INTB_S    EQU     13
NVIC_PRI28_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI29 register.
;
;*************************************************************
NVIC_PRI29_INTD_M      EQU  0xE0000000  ; Interrupt 119 Priority Mask
NVIC_PRI29_INTC_M      EQU  0x00E00000  ; Interrupt 118 Priority Mask
NVIC_PRI29_INTB_M      EQU  0x0000E000  ; Interrupt 117 Priority Mask
NVIC_PRI29_INTA_M      EQU  0x000000E0  ; Interrupt 116 Priority Mask
NVIC_PRI29_INTD_S    EQU     29
NVIC_PRI29_INTC_S    EQU     21
NVIC_PRI29_INTB_S    EQU     13
NVIC_PRI29_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI30 register.
;
;*************************************************************
NVIC_PRI30_INTD_M      EQU  0xE0000000  ; Interrupt 123 Priority Mask
NVIC_PRI30_INTC_M      EQU  0x00E00000  ; Interrupt 122 Priority Mask
NVIC_PRI30_INTB_M      EQU  0x0000E000  ; Interrupt 121 Priority Mask
NVIC_PRI30_INTA_M      EQU  0x000000E0  ; Interrupt 120 Priority Mask
NVIC_PRI30_INTD_S    EQU     29
NVIC_PRI30_INTC_S    EQU     21
NVIC_PRI30_INTB_S    EQU     13
NVIC_PRI30_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI31 register.
;
;*************************************************************
NVIC_PRI31_INTD_M      EQU  0xE0000000  ; Interrupt 127 Priority Mask
NVIC_PRI31_INTC_M      EQU  0x00E00000  ; Interrupt 126 Priority Mask
NVIC_PRI31_INTB_M      EQU  0x0000E000  ; Interrupt 125 Priority Mask
NVIC_PRI31_INTA_M      EQU  0x000000E0  ; Interrupt 124 Priority Mask
NVIC_PRI31_INTD_S    EQU     29
NVIC_PRI31_INTC_S    EQU     21
NVIC_PRI31_INTB_S    EQU     13
NVIC_PRI31_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI32 register.
;
;*************************************************************
NVIC_PRI32_INTD_M      EQU  0xE0000000  ; Interrupt 131 Priority Mask
NVIC_PRI32_INTC_M      EQU  0x00E00000  ; Interrupt 130 Priority Mask
NVIC_PRI32_INTB_M      EQU  0x0000E000  ; Interrupt 129 Priority Mask
NVIC_PRI32_INTA_M      EQU  0x000000E0  ; Interrupt 128 Priority Mask
NVIC_PRI32_INTD_S    EQU     29
NVIC_PRI32_INTC_S    EQU     21
NVIC_PRI32_INTB_S    EQU     13
NVIC_PRI32_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI33 register.
;
;*************************************************************
NVIC_PRI33_INTD_M      EQU  0xE0000000  ; Interrupt Priority for Interrupt
                                            ; [4n+3]
NVIC_PRI33_INTC_M      EQU  0x00E00000  ; Interrupt Priority for Interrupt
                                            ; [4n+2]
NVIC_PRI33_INTB_M      EQU  0x0000E000  ; Interrupt Priority for Interrupt
                                            ; [4n+1]
NVIC_PRI33_INTA_M      EQU  0x000000E0  ; Interrupt Priority for Interrupt
                                            ; [4n]
NVIC_PRI33_INTD_S    EQU     29
NVIC_PRI33_INTC_S    EQU     21
NVIC_PRI33_INTB_S    EQU     13
NVIC_PRI33_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_PRI34 register.
;
;*************************************************************
NVIC_PRI34_INTD_M      EQU  0xE0000000  ; Interrupt Priority for Interrupt
                                            ; [4n+3]
NVIC_PRI34_INTC_M      EQU  0x00E00000  ; Interrupt Priority for Interrupt
                                            ; [4n+2]
NVIC_PRI34_INTB_M      EQU  0x0000E000  ; Interrupt Priority for Interrupt
                                            ; [4n+1]
NVIC_PRI34_INTA_M      EQU  0x000000E0  ; Interrupt Priority for Interrupt
                                            ; [4n]
NVIC_PRI34_INTD_S    EQU     29
NVIC_PRI34_INTC_S    EQU     21
NVIC_PRI34_INTB_S    EQU     13
NVIC_PRI34_INTA_S    EQU     5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_CPUID register.
;
;*************************************************************
NVIC_CPUID_IMP_M       EQU  0xFF000000  ; Implementer Code
NVIC_CPUID_IMP_ARM     EQU  0x41000000  ; ARM
NVIC_CPUID_VAR_M       EQU  0x00F00000  ; Variant Number
NVIC_CPUID_CON_M       EQU  0x000F0000  ; Constant
NVIC_CPUID_PARTNO_M    EQU  0x0000FFF0  ; Part Number
NVIC_CPUID_PARTNO_CM4  EQU  0x0000C240  ; Cortex-M4 processor
NVIC_CPUID_REV_M       EQU  0x0000000F  ; Revision Number

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_INT_CTRL register.
;
;*************************************************************
NVIC_INT_CTRL_NMI_SET  EQU  0x80000000  ; NMI Set Pending
NVIC_INT_CTRL_PEND_SV  EQU  0x10000000  ; PendSV Set Pending
NVIC_INT_CTRL_UNPEND_SV EQU  0x08000000  ; PendSV Clear Pending
NVIC_INT_CTRL_PENDSTSET EQU  0x04000000  ; SysTick Set Pending
NVIC_INT_CTRL_PENDSTCLR EQU  0x02000000  ; SysTick Clear Pending
NVIC_INT_CTRL_ISR_PRE  EQU  0x00800000  ; Debug Interrupt Handling
NVIC_INT_CTRL_ISR_PEND EQU  0x00400000  ; Interrupt Pending
NVIC_INT_CTRL_VEC_PEN_M EQU  0x000FF000  ; Interrupt Pending Vector Number
NVIC_INT_CTRL_VEC_PEN_NMI EQU  0x00002000  ; NMI
NVIC_INT_CTRL_VEC_PEN_HARD EQU  0x00003000  ; Hard fault
NVIC_INT_CTRL_VEC_PEN_MEM EQU  0x00004000  ; Memory management fault
NVIC_INT_CTRL_VEC_PEN_BUS EQU  0x00005000  ; Bus fault
NVIC_INT_CTRL_VEC_PEN_USG EQU  0x00006000  ; Usage fault
NVIC_INT_CTRL_VEC_PEN_SVC EQU  0x0000B000  ; SVCall
NVIC_INT_CTRL_VEC_PEN_PNDSV EQU  0x0000E000  ; PendSV
NVIC_INT_CTRL_VEC_PEN_TICK EQU  0x0000F000  ; SysTick
NVIC_INT_CTRL_RET_BASE EQU  0x00000800  ; Return to Base
NVIC_INT_CTRL_VEC_ACT_M EQU  0x000000FF  ; Interrupt Pending Vector Number
NVIC_INT_CTRL_VEC_ACT_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_VTABLE register.
;
;*************************************************************
NVIC_VTABLE_BASE       EQU  0x20000000  ; Vector Table Base
NVIC_VTABLE_OFFSET_M   EQU  0x1FFFFC00  ; Vector Table Offset
NVIC_VTABLE_OFFSET_S    EQU  10

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_APINT register.
;
;*************************************************************
NVIC_APINT_VECTKEY_M   EQU  0xFFFF0000  ; Register Key
NVIC_APINT_VECTKEY     EQU  0x05FA0000  ; Vector key
NVIC_APINT_ENDIANESS   EQU  0x00008000  ; Data Endianess
NVIC_APINT_PRIGROUP_M  EQU  0x00000700  ; Interrupt Priority Grouping
NVIC_APINT_PRIGROUP_7_1 EQU  0x00000000  ; Priority group 7.1 split
NVIC_APINT_PRIGROUP_6_2 EQU  0x00000100  ; Priority group 6.2 split
NVIC_APINT_PRIGROUP_5_3 EQU  0x00000200  ; Priority group 5.3 split
NVIC_APINT_PRIGROUP_4_4 EQU  0x00000300  ; Priority group 4.4 split
NVIC_APINT_PRIGROUP_3_5 EQU  0x00000400  ; Priority group 3.5 split
NVIC_APINT_PRIGROUP_2_6 EQU  0x00000500  ; Priority group 2.6 split
NVIC_APINT_PRIGROUP_1_7 EQU  0x00000600  ; Priority group 1.7 split
NVIC_APINT_PRIGROUP_0_8 EQU  0x00000700  ; Priority group 0.8 split
NVIC_APINT_SYSRESETREQ EQU  0x00000004  ; System Reset Request
NVIC_APINT_VECT_CLR_ACT EQU  0x00000002  ; Clear Active NMI / Fault
NVIC_APINT_VECT_RESET  EQU  0x00000001  ; System Reset

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SYS_CTRL register.
;
;*************************************************************
NVIC_SYS_CTRL_SEVONPEND EQU  0x00000010  ; Wake Up on Pending
NVIC_SYS_CTRL_SLEEPDEEP EQU  0x00000004  ; Deep Sleep Enable
NVIC_SYS_CTRL_SLEEPEXIT EQU  0x00000002  ; Sleep on ISR Exit

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_CFG_CTRL register.
;
;*************************************************************
NVIC_CFG_CTRL_STKALIGN EQU  0x00000200  ; Stack Alignment on Exception
                                            ; Entry
NVIC_CFG_CTRL_BFHFNMIGN EQU  0x00000100  ; Ignore Bus Fault in NMI and
                                            ; Fault
NVIC_CFG_CTRL_DIV0     EQU  0x00000010  ; Trap on Divide by 0
NVIC_CFG_CTRL_UNALIGNED EQU  0x00000008  ; Trap on Unaligned Access
NVIC_CFG_CTRL_MAIN_PEND EQU  0x00000002  ; Allow Main Interrupt Trigger
NVIC_CFG_CTRL_BASE_THR EQU  0x00000001  ; Thread State Control

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SYS_PRI1 register.
;
;*************************************************************
NVIC_SYS_PRI1_USAGE_M  EQU  0x00E00000  ; Usage Fault Priority
NVIC_SYS_PRI1_BUS_M    EQU  0x0000E000  ; Bus Fault Priority
NVIC_SYS_PRI1_MEM_M    EQU  0x000000E0  ; Memory Management Fault Priority
NVIC_SYS_PRI1_USAGE_S    EQU 21
NVIC_SYS_PRI1_BUS_S    EQU   13
NVIC_SYS_PRI1_MEM_S    EQU   5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SYS_PRI2 register.
;
;*************************************************************
NVIC_SYS_PRI2_SVC_M    EQU  0xE0000000  ; SVCall Priority
NVIC_SYS_PRI2_SVC_S    EQU   29

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SYS_PRI3 register.
;
;*************************************************************
NVIC_SYS_PRI3_TICK_M   EQU  0xE0000000  ; SysTick Exception Priority
NVIC_SYS_PRI3_PENDSV_M EQU  0x00E00000  ; PendSV Priority
NVIC_SYS_PRI3_DEBUG_M  EQU  0x000000E0  ; Debug Priority
NVIC_SYS_PRI3_TICK_S    EQU  29
NVIC_SYS_PRI3_PENDSV_S  EQU  21
NVIC_SYS_PRI3_DEBUG_S    EQU 5

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SYS_HND_CTRL
; register.
;
;*************************************************************
NVIC_SYS_HND_CTRL_USAGE EQU  0x00040000  ; Usage Fault Enable
NVIC_SYS_HND_CTRL_BUS  EQU  0x00020000  ; Bus Fault Enable
NVIC_SYS_HND_CTRL_MEM  EQU  0x00010000  ; Memory Management Fault Enable
NVIC_SYS_HND_CTRL_SVC  EQU  0x00008000  ; SVC Call Pending
NVIC_SYS_HND_CTRL_BUSP EQU  0x00004000  ; Bus Fault Pending
NVIC_SYS_HND_CTRL_MEMP EQU  0x00002000  ; Memory Management Fault Pending
NVIC_SYS_HND_CTRL_USAGEP EQU  0x00001000  ; Usage Fault Pending
NVIC_SYS_HND_CTRL_TICK EQU  0x00000800  ; SysTick Exception Active
NVIC_SYS_HND_CTRL_PNDSV EQU  0x00000400  ; PendSV Exception Active
NVIC_SYS_HND_CTRL_MON  EQU  0x00000100  ; Debug Monitor Active
NVIC_SYS_HND_CTRL_SVCA EQU  0x00000080  ; SVC Call Active
NVIC_SYS_HND_CTRL_USGA EQU  0x00000008  ; Usage Fault Active
NVIC_SYS_HND_CTRL_BUSA EQU  0x00000002  ; Bus Fault Active
NVIC_SYS_HND_CTRL_MEMA EQU  0x00000001  ; Memory Management Fault Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_FAULT_STAT
; register.
;
;*************************************************************
NVIC_FAULT_STAT_DIV0   EQU  0x02000000  ; Divide-by-Zero Usage Fault
NVIC_FAULT_STAT_UNALIGN EQU  0x01000000  ; Unaligned Access Usage Fault
NVIC_FAULT_STAT_NOCP   EQU  0x00080000  ; No Coprocessor Usage Fault
NVIC_FAULT_STAT_INVPC  EQU  0x00040000  ; Invalid PC Load Usage Fault
NVIC_FAULT_STAT_INVSTAT EQU  0x00020000  ; Invalid State Usage Fault
NVIC_FAULT_STAT_UNDEF  EQU  0x00010000  ; Undefined Instruction Usage
                                            ; Fault
NVIC_FAULT_STAT_BFARV  EQU  0x00008000  ; Bus Fault Address Register Valid
NVIC_FAULT_STAT_BLSPERR EQU  0x00002000  ; Bus Fault on Floating-Point Lazy
                                            ; State Preservation
NVIC_FAULT_STAT_BSTKE  EQU  0x00001000  ; Stack Bus Fault
NVIC_FAULT_STAT_BUSTKE EQU  0x00000800  ; Unstack Bus Fault
NVIC_FAULT_STAT_IMPRE  EQU  0x00000400  ; Imprecise Data Bus Error
NVIC_FAULT_STAT_PRECISE EQU  0x00000200  ; Precise Data Bus Error
NVIC_FAULT_STAT_IBUS   EQU  0x00000100  ; Instruction Bus Error
NVIC_FAULT_STAT_MMARV  EQU  0x00000080  ; Memory Management Fault Address
                                            ; Register Valid
NVIC_FAULT_STAT_MLSPERR EQU  0x00000020  ; Memory Management Fault on
                                            ; Floating-Point Lazy State
                                            ; Preservation
NVIC_FAULT_STAT_MSTKE  EQU  0x00000010  ; Stack Access Violation
NVIC_FAULT_STAT_MUSTKE EQU  0x00000008  ; Unstack Access Violation
NVIC_FAULT_STAT_DERR   EQU  0x00000002  ; Data Access Violation
NVIC_FAULT_STAT_IERR   EQU  0x00000001  ; Instruction Access Violation

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_HFAULT_STAT
; register.
;
;*************************************************************
NVIC_HFAULT_STAT_DBG   EQU  0x80000000  ; Debug Event
NVIC_HFAULT_STAT_FORCED EQU  0x40000000  ; Forced Hard Fault
NVIC_HFAULT_STAT_VECT  EQU  0x00000002  ; Vector Table Read Fault

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DEBUG_STAT
; register.
;
;*************************************************************
NVIC_DEBUG_STAT_EXTRNL EQU  0x00000010  ; EDBGRQ asserted
NVIC_DEBUG_STAT_VCATCH EQU  0x00000008  ; Vector catch
NVIC_DEBUG_STAT_DWTTRAP EQU  0x00000004  ; DWT match
NVIC_DEBUG_STAT_BKPT   EQU  0x00000002  ; Breakpoint instruction
NVIC_DEBUG_STAT_HALTED EQU  0x00000001  ; Halt request

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MM_ADDR register.
;
;*************************************************************
NVIC_MM_ADDR_M         EQU  0xFFFFFFFF  ; Fault Address
NVIC_MM_ADDR_S    EQU    0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_FAULT_ADDR
; register.
;
;*************************************************************
NVIC_FAULT_ADDR_M      EQU  0xFFFFFFFF  ; Fault Address
NVIC_FAULT_ADDR_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_CPAC register.
;
;*************************************************************
NVIC_CPAC_CP11_M       EQU  0x00C00000  ; CP11 Coprocessor Access
                                            ; Privilege
NVIC_CPAC_CP11_DIS     EQU  0x00000000  ; Access Denied
NVIC_CPAC_CP11_PRIV    EQU  0x00400000  ; Privileged Access Only
NVIC_CPAC_CP11_FULL    EQU  0x00C00000  ; Full Access
NVIC_CPAC_CP10_M       EQU  0x00300000  ; CP10 Coprocessor Access
                                            ; Privilege
NVIC_CPAC_CP10_DIS     EQU  0x00000000  ; Access Denied
NVIC_CPAC_CP10_PRIV    EQU  0x00100000  ; Privileged Access Only
NVIC_CPAC_CP10_FULL    EQU  0x00300000  ; Full Access

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_TYPE register.
;
;*************************************************************
NVIC_MPU_TYPE_IREGION_M EQU  0x00FF0000  ; Number of I Regions
NVIC_MPU_TYPE_DREGION_M EQU  0x0000FF00  ; Number of D Regions
NVIC_MPU_TYPE_SEPARATE EQU  0x00000001  ; Separate or Unified MPU
NVIC_MPU_TYPE_IREGION_S EQU 16
NVIC_MPU_TYPE_DREGION_S EQU 8

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_CTRL register.
;
;*************************************************************
NVIC_MPU_CTRL_PRIVDEFEN EQU  0x00000004  ; MPU Default Region
NVIC_MPU_CTRL_HFNMIENA EQU  0x00000002  ; MPU Enabled During Faults
NVIC_MPU_CTRL_ENABLE   EQU  0x00000001  ; MPU Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_NUMBER
; register.
;
;*************************************************************
NVIC_MPU_NUMBER_M      EQU  0x00000007  ; MPU Region to Access
NVIC_MPU_NUMBER_S   EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_BASE register.
;
;*************************************************************
NVIC_MPU_BASE_ADDR_M   EQU  0xFFFFFFE0  ; Base Address Mask
NVIC_MPU_BASE_VALID    EQU  0x00000010  ; Region Number Valid
NVIC_MPU_BASE_REGION_M EQU  0x00000007  ; Region Number
NVIC_MPU_BASE_ADDR_S    EQU  5
NVIC_MPU_BASE_REGION_S  EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_ATTR register.
;
;*************************************************************
NVIC_MPU_ATTR_XN       EQU  0x10000000  ; Instruction Access Disable
NVIC_MPU_ATTR_AP_M     EQU  0x07000000  ; Access Privilege
NVIC_MPU_ATTR_TEX_M    EQU  0x00380000  ; Type Extension Mask
NVIC_MPU_ATTR_SHAREABLE EQU  0x00040000  ; Shareable
NVIC_MPU_ATTR_CACHEABLE EQU  0x00020000  ; Cacheable
NVIC_MPU_ATTR_BUFFRABLE EQU  0x00010000  ; Bufferable
NVIC_MPU_ATTR_SRD_M    EQU  0x0000FF00  ; Subregion Disable Bits
NVIC_MPU_ATTR_SIZE_M   EQU  0x0000003E  ; Region Size Mask
NVIC_MPU_ATTR_ENABLE   EQU  0x00000001  ; Region Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_BASE1 register.
;
;*************************************************************
NVIC_MPU_BASE1_ADDR_M  EQU  0xFFFFFFE0  ; Base Address Mask
NVIC_MPU_BASE1_VALID   EQU  0x00000010  ; Region Number Valid
NVIC_MPU_BASE1_REGION_M EQU  0x00000007  ; Region Number
NVIC_MPU_BASE1_ADDR_S    EQU 5
NVIC_MPU_BASE1_REGION_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_ATTR1 register.
;
;*************************************************************
NVIC_MPU_ATTR1_XN      EQU  0x10000000  ; Instruction Access Disable
NVIC_MPU_ATTR1_AP_M    EQU  0x07000000  ; Access Privilege
NVIC_MPU_ATTR1_TEX_M   EQU  0x00380000  ; Type Extension Mask
NVIC_MPU_ATTR1_SHAREABLE EQU  0x00040000  ; Shareable
NVIC_MPU_ATTR1_CACHEABLE EQU  0x00020000  ; Cacheable
NVIC_MPU_ATTR1_BUFFRABLE EQU  0x00010000  ; Bufferable
NVIC_MPU_ATTR1_SRD_M   EQU  0x0000FF00  ; Subregion Disable Bits
NVIC_MPU_ATTR1_SIZE_M  EQU  0x0000003E  ; Region Size Mask
NVIC_MPU_ATTR1_ENABLE  EQU  0x00000001  ; Region Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_BASE2 register.
;
;*************************************************************
NVIC_MPU_BASE2_ADDR_M  EQU  0xFFFFFFE0  ; Base Address Mask
NVIC_MPU_BASE2_VALID   EQU  0x00000010  ; Region Number Valid
NVIC_MPU_BASE2_REGION_M EQU  0x00000007  ; Region Number
NVIC_MPU_BASE2_ADDR_S  EQU  5
NVIC_MPU_BASE2_REGION_S EQU 0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_ATTR2 register.
;
;*************************************************************
NVIC_MPU_ATTR2_XN      EQU  0x10000000  ; Instruction Access Disable
NVIC_MPU_ATTR2_AP_M    EQU  0x07000000  ; Access Privilege
NVIC_MPU_ATTR2_TEX_M   EQU  0x00380000  ; Type Extension Mask
NVIC_MPU_ATTR2_SHAREABLE EQU  0x00040000  ; Shareable
NVIC_MPU_ATTR2_CACHEABLE EQU  0x00020000  ; Cacheable
NVIC_MPU_ATTR2_BUFFRABLE EQU  0x00010000  ; Bufferable
NVIC_MPU_ATTR2_SRD_M   EQU  0x0000FF00  ; Subregion Disable Bits
NVIC_MPU_ATTR2_SIZE_M  EQU  0x0000003E  ; Region Size Mask
NVIC_MPU_ATTR2_ENABLE  EQU  0x00000001  ; Region Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_BASE3 register.
;
;*************************************************************
NVIC_MPU_BASE3_ADDR_M  EQU  0xFFFFFFE0  ; Base Address Mask
NVIC_MPU_BASE3_VALID   EQU  0x00000010  ; Region Number Valid
NVIC_MPU_BASE3_REGION_M EQU  0x00000007  ; Region Number
NVIC_MPU_BASE3_ADDR_S  EQU  5
NVIC_MPU_BASE3_REGION_S EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_MPU_ATTR3 register.
;
;*************************************************************
NVIC_MPU_ATTR3_XN      EQU  0x10000000  ; Instruction Access Disable
NVIC_MPU_ATTR3_AP_M    EQU  0x07000000  ; Access Privilege
NVIC_MPU_ATTR3_TEX_M   EQU  0x00380000  ; Type Extension Mask
NVIC_MPU_ATTR3_SHAREABLE EQU  0x00040000  ; Shareable
NVIC_MPU_ATTR3_CACHEABLE EQU  0x00020000  ; Cacheable
NVIC_MPU_ATTR3_BUFFRABLE EQU  0x00010000  ; Bufferable
NVIC_MPU_ATTR3_SRD_M   EQU  0x0000FF00  ; Subregion Disable Bits
NVIC_MPU_ATTR3_SIZE_M  EQU  0x0000003E  ; Region Size Mask
NVIC_MPU_ATTR3_ENABLE  EQU  0x00000001  ; Region Enable

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DBG_CTRL register.
;
;*************************************************************
NVIC_DBG_CTRL_DBGKEY_M EQU  0xFFFF0000  ; Debug key mask
NVIC_DBG_CTRL_DBGKEY   EQU  0xA05F0000  ; Debug key
NVIC_DBG_CTRL_S_RESET_ST EQU  0x02000000  ; Core has reset since last read
NVIC_DBG_CTRL_S_RETIRE_ST EQU  0x01000000  ; Core has executed insruction
                                            ; since last read
NVIC_DBG_CTRL_S_LOCKUP EQU  0x00080000  ; Core is locked up
NVIC_DBG_CTRL_S_SLEEP  EQU  0x00040000  ; Core is sleeping
NVIC_DBG_CTRL_S_HALT   EQU  0x00020000  ; Core status on halt
NVIC_DBG_CTRL_S_REGRDY EQU  0x00010000  ; Register read/write available
NVIC_DBG_CTRL_C_SNAPSTALL EQU  0x00000020  ; Breaks a stalled load/store
NVIC_DBG_CTRL_C_MASKINT EQU  0x00000008  ; Mask interrupts when stepping
NVIC_DBG_CTRL_C_STEP   EQU  0x00000004  ; Step the core
NVIC_DBG_CTRL_C_HALT   EQU  0x00000002  ; Halt the core
NVIC_DBG_CTRL_C_DEBUGEN EQU  0x00000001  ; Enable debug

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DBG_XFER register.
;
;*************************************************************
NVIC_DBG_XFER_REG_WNR  EQU  0x00010000  ; Write or not read
NVIC_DBG_XFER_REG_SEL_M EQU  0x0000001F  ; Register
NVIC_DBG_XFER_REG_R0   EQU  0x00000000  ; Register R0
NVIC_DBG_XFER_REG_R1   EQU  0x00000001  ; Register R1
NVIC_DBG_XFER_REG_R2   EQU  0x00000002  ; Register R2
NVIC_DBG_XFER_REG_R3   EQU  0x00000003  ; Register R3
NVIC_DBG_XFER_REG_R4   EQU  0x00000004  ; Register R4
NVIC_DBG_XFER_REG_R5   EQU  0x00000005  ; Register R5
NVIC_DBG_XFER_REG_R6   EQU  0x00000006  ; Register R6
NVIC_DBG_XFER_REG_R7   EQU  0x00000007  ; Register R7
NVIC_DBG_XFER_REG_R8   EQU  0x00000008  ; Register R8
NVIC_DBG_XFER_REG_R9   EQU  0x00000009  ; Register R9
NVIC_DBG_XFER_REG_R10  EQU  0x0000000A  ; Register R10
NVIC_DBG_XFER_REG_R11  EQU  0x0000000B  ; Register R11
NVIC_DBG_XFER_REG_R12  EQU  0x0000000C  ; Register R12
NVIC_DBG_XFER_REG_R13  EQU  0x0000000D  ; Register R13
NVIC_DBG_XFER_REG_R14  EQU  0x0000000E  ; Register R14
NVIC_DBG_XFER_REG_R15  EQU  0x0000000F  ; Register R15
NVIC_DBG_XFER_REG_FLAGS EQU  0x00000010  ; xPSR/Flags register
NVIC_DBG_XFER_REG_MSP  EQU  0x00000011  ; Main SP
NVIC_DBG_XFER_REG_PSP  EQU  0x00000012  ; Process SP
NVIC_DBG_XFER_REG_DSP  EQU  0x00000013  ; Deep SP
NVIC_DBG_XFER_REG_CFBP EQU  0x00000014  ; Control/Fault/BasePri/PriMask

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DBG_DATA register.
;
;*************************************************************
NVIC_DBG_DATA_M        EQU  0xFFFFFFFF  ; Data temporary cache
NVIC_DBG_DATA_S     EQU   0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_DBG_INT register.
;
;*************************************************************
NVIC_DBG_INT_HARDERR   EQU  0x00000400  ; Debug trap on hard fault
NVIC_DBG_INT_INTERR    EQU  0x00000200  ; Debug trap on interrupt errors
NVIC_DBG_INT_BUSERR    EQU  0x00000100  ; Debug trap on bus error
NVIC_DBG_INT_STATERR   EQU  0x00000080  ; Debug trap on usage fault state
NVIC_DBG_INT_CHKERR    EQU  0x00000040  ; Debug trap on usage fault check
NVIC_DBG_INT_NOCPERR   EQU  0x00000020  ; Debug trap on coprocessor error
NVIC_DBG_INT_MMERR     EQU  0x00000010  ; Debug trap on mem manage fault
NVIC_DBG_INT_RESET     EQU  0x00000008  ; Core reset status
NVIC_DBG_INT_RSTPENDCLR EQU  0x00000004  ; Clear pending core reset
NVIC_DBG_INT_RSTPENDING EQU  0x00000002  ; Core reset is pending
NVIC_DBG_INT_RSTVCATCH EQU  0x00000001  ; Reset vector catch

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_SW_TRIG register.
;
;*************************************************************
NVIC_SW_TRIG_INTID_M   EQU  0x000000FF  ; Interrupt ID
NVIC_SW_TRIG_INTID_S    EQU  0

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_FPCC register.
;
;*************************************************************
NVIC_FPCC_ASPEN        EQU  0x80000000  ; Automatic State Preservation
                                            ; Enable
NVIC_FPCC_LSPEN        EQU  0x40000000  ; Lazy State Preservation Enable
NVIC_FPCC_MONRDY       EQU  0x00000100  ; Monitor Ready
NVIC_FPCC_BFRDY        EQU  0x00000040  ; Bus Fault Ready
NVIC_FPCC_MMRDY        EQU  0x00000020  ; Memory Management Fault Ready
NVIC_FPCC_HFRDY        EQU  0x00000010  ; Hard Fault Ready
NVIC_FPCC_THREAD       EQU  0x00000008  ; Thread Mode
NVIC_FPCC_USER         EQU  0x00000002  ; User Privilege Level
NVIC_FPCC_LSPACT       EQU  0x00000001  ; Lazy State Preservation Active

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_FPCA register.
;
;*************************************************************
NVIC_FPCA_ADDRESS_M    EQU  0xFFFFFFF8  ; Address
NVIC_FPCA_ADDRESS_S    EQU   3

;*************************************************************
;
; The following are defines for the bit fields in the NVIC_FPDSC register.
;
;*************************************************************
NVIC_FPDSC_AHP         EQU  0x04000000  ; AHP Bit Default
NVIC_FPDSC_DN          EQU  0x02000000  ; DN Bit Default
NVIC_FPDSC_FZ          EQU  0x01000000  ; FZ Bit Default
NVIC_FPDSC_RMODE_M     EQU  0x00C00000  ; RMODE Bit Default
NVIC_FPDSC_RMODE_RN    EQU  0x00000000  ; Round to Nearest (RN) mode
NVIC_FPDSC_RMODE_RP    EQU  0x00400000  ; Round towards Plus Infinity (RP)
                                            ; mode
NVIC_FPDSC_RMODE_RM    EQU  0x00800000  ; Round towards Minus Infinity
                                            ; (RM) mode
NVIC_FPDSC_RMODE_RZ    EQU  0x00C00000  ; Round towards Zero (RZ) mode

;*************************************************************
;
; The following definitions are deprecated.
;
;*************************************************************


;*************************************************************
;
; Deprecated defines for the EEPROM register offsets.
;
;*************************************************************
EEPROM_EEPROMPP_R       EQU    0x400AFFC0

;*************************************************************
;
; Deprecated defines for the bit fields in the EEPROM_EEPROMPP register.
;
;*************************************************************
EEPROM_EEPROMPP_SIZE_M EQU  0x0000001F  ; EEPROM Size
EEPROM_EEPROMPP_SIZE_S EQU  0

  END
  
