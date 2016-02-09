// TExaSscope.c
// Runs on LM4F120/TM4C123
// Periodic timer 4A interrupt data collection
// PLL must be on for ADC to work (turned on in TExaSInit)
// ADC1 PD3 Ain continuous sampling (turned on in TExaSInit)
//

// Uses Timer4 to copy PD3 data from ADC1 to UART0.
// Jonathan Valvano, Daniel Valvano
// February 18, 2015

#define SYSCTL_RCGC0_R          (*((volatile unsigned long *)0x400FE100))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCGCTIMER_R      (*((volatile unsigned long *)0x400FE604))
#define SYSCTL_RCGCADC_R        (*((volatile unsigned long *)0x400FE638))
#define TIMER4_CFG_R            (*((volatile unsigned long *)0x40034000))
#define TIMER4_TAMR_R           (*((volatile unsigned long *)0x40034004))
#define TIMER4_TBMR_R           (*((volatile unsigned long *)0x40034008))
#define TIMER4_CTL_R            (*((volatile unsigned long *)0x4003400C))
#define TIMER4_SYNC_R           (*((volatile unsigned long *)0x40034010))
#define TIMER4_IMR_R            (*((volatile unsigned long *)0x40034018))
#define TIMER4_RIS_R            (*((volatile unsigned long *)0x4003401C))
#define TIMER4_MIS_R            (*((volatile unsigned long *)0x40034020))
#define TIMER4_ICR_R            (*((volatile unsigned long *)0x40034024))
#define TIMER4_TAILR_R          (*((volatile unsigned long *)0x40034028))
#define TIMER4_TBILR_R          (*((volatile unsigned long *)0x4003402C))
#define TIMER4_TAMATCHR_R       (*((volatile unsigned long *)0x40034030))
#define TIMER4_TBMATCHR_R       (*((volatile unsigned long *)0x40034034))
#define TIMER4_TAPR_R           (*((volatile unsigned long *)0x40034038))
#define TIMER4_TBPR_R           (*((volatile unsigned long *)0x4003403C))
#define TIMER4_TAPMR_R          (*((volatile unsigned long *)0x40034040))
#define TIMER4_TBPMR_R          (*((volatile unsigned long *)0x40034044))
#define TIMER4_TAR_R            (*((volatile unsigned long *)0x40034048))
#define TIMER4_TBR_R            (*((volatile unsigned long *)0x4003404C))
#define TIMER4_TAV_R            (*((volatile unsigned long *)0x40034050))
#define TIMER4_TBV_R            (*((volatile unsigned long *)0x40034054))
#define TIMER4_RTCPD_R          (*((volatile unsigned long *)0x40034058))
#define TIMER4_TAPS_R           (*((volatile unsigned long *)0x4003405C))
#define TIMER4_TBPS_R           (*((volatile unsigned long *)0x40034060))
#define TIMER4_TAPV_R           (*((volatile unsigned long *)0x40034064))
#define TIMER4_TBPV_R           (*((volatile unsigned long *)0x40034068))
#define TIMER4_PP_R             (*((volatile unsigned long *)0x40034FC0))
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *)0x400073FC))
#define PD2                     (*((volatile unsigned long *)0x40007010))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *)0x40007400))
#define GPIO_PORTD_IS_R         (*((volatile unsigned long *)0x40007404))
#define GPIO_PORTD_IBE_R        (*((volatile unsigned long *)0x40007408))
#define GPIO_PORTD_IEV_R        (*((volatile unsigned long *)0x4000740C))
#define GPIO_PORTD_IM_R         (*((volatile unsigned long *)0x40007410))
#define GPIO_PORTD_RIS_R        (*((volatile unsigned long *)0x40007414))
#define GPIO_PORTD_MIS_R        (*((volatile unsigned long *)0x40007418))
#define GPIO_PORTD_ICR_R        (*((volatile unsigned long *)0x4000741C))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *)0x40007420))
#define GPIO_PORTD_DR2R_R       (*((volatile unsigned long *)0x40007500))
#define GPIO_PORTD_DR4R_R       (*((volatile unsigned long *)0x40007504))
#define GPIO_PORTD_DR8R_R       (*((volatile unsigned long *)0x40007508))
#define GPIO_PORTD_ODR_R        (*((volatile unsigned long *)0x4000750C))
#define GPIO_PORTD_PUR_R        (*((volatile unsigned long *)0x40007510))
#define GPIO_PORTD_PDR_R        (*((volatile unsigned long *)0x40007514))
#define GPIO_PORTD_SLR_R        (*((volatile unsigned long *)0x40007518))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *)0x4000751C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *)0x40007520))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *)0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *)0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *)0x4000752C))
#define GPIO_PORTD_ADCCTL_R     (*((volatile unsigned long *)0x40007530))
#define GPIO_PORTD_DMACTL_R     (*((volatile unsigned long *)0x40007534))
#define GPIO_PORTD_SI_R         (*((volatile unsigned long *)0x40007538))
#define ADC1_ACTSS_R            (*((volatile unsigned long *)0x40039000))
#define ADC1_RIS_R              (*((volatile unsigned long *)0x40039004))
#define ADC1_IM_R               (*((volatile unsigned long *)0x40039008))
#define ADC1_ISC_R              (*((volatile unsigned long *)0x4003900C))
#define ADC1_OSTAT_R            (*((volatile unsigned long *)0x40039010))
#define ADC1_EMUX_R             (*((volatile unsigned long *)0x40039014))
#define ADC1_USTAT_R            (*((volatile unsigned long *)0x40039018))
#define ADC1_SSPRI_R            (*((volatile unsigned long *)0x40039020))
#define ADC1_SPC_R              (*((volatile unsigned long *)0x40039024))
#define ADC1_PSSI_R             (*((volatile unsigned long *)0x40039028))
#define ADC1_SAC_R              (*((volatile unsigned long *)0x40039030))
#define ADC1_DCISC_R            (*((volatile unsigned long *)0x40039034))
#define ADC1_SSMUX0_R           (*((volatile unsigned long *)0x40039040))
#define ADC1_SSCTL0_R           (*((volatile unsigned long *)0x40039044))
#define ADC1_SSFIFO0_R          (*((volatile unsigned long *)0x40039048))
#define ADC1_SSFSTAT0_R         (*((volatile unsigned long *)0x4003904C))
#define ADC1_SSOP0_R            (*((volatile unsigned long *)0x40039050))
#define ADC1_SSDC0_R            (*((volatile unsigned long *)0x40039054))
#define ADC1_SSMUX1_R           (*((volatile unsigned long *)0x40039060))
#define ADC1_SSCTL1_R           (*((volatile unsigned long *)0x40039064))
#define ADC1_SSFIFO1_R          (*((volatile unsigned long *)0x40039068))
#define ADC1_SSFSTAT1_R         (*((volatile unsigned long *)0x4003906C))
#define ADC1_SSOP1_R            (*((volatile unsigned long *)0x40039070))
#define ADC1_SSDC1_R            (*((volatile unsigned long *)0x40039074))
#define ADC1_SSMUX2_R           (*((volatile unsigned long *)0x40039080))
#define ADC1_SSCTL2_R           (*((volatile unsigned long *)0x40039084))
#define ADC1_SSFIFO2_R          (*((volatile unsigned long *)0x40039088))
#define ADC1_SSFSTAT2_R         (*((volatile unsigned long *)0x4003908C))
#define ADC1_SSOP2_R            (*((volatile unsigned long *)0x40039090))
#define ADC1_SSDC2_R            (*((volatile unsigned long *)0x40039094))
#define ADC1_SSMUX3_R           (*((volatile unsigned long *)0x400390A0))
#define ADC1_SSCTL3_R           (*((volatile unsigned long *)0x400390A4))
#define ADC1_SSFIFO3_R          (*((volatile unsigned long *)0x400390A8))
#define ADC1_SSFSTAT3_R         (*((volatile unsigned long *)0x400390AC))
#define ADC1_PP_R               (*((volatile unsigned long *)0x40039FC0))
#define ADC1_PC_R               (*((volatile unsigned long *)0x40039FC4))
#define ADC1_CC_R               (*((volatile unsigned long *)0x40039FC8))
#define NVIC_PRI17_R            (*((volatile unsigned long *)0xE000E444))
#define NVIC_PRI23_R            (*((volatile unsigned long *)0xE000E45C))
#define NVIC_EN2_R              (*((volatile unsigned long *)0xE000E108))
#define NVIC_DIS2_R             (*((volatile unsigned long *)0xE000E188))

#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define UART0_FR_R              (*((volatile unsigned long *)0x4000C018))
#define UART0_IBRD_R            (*((volatile unsigned long *)0x4000C024))
#define UART0_FBRD_R            (*((volatile unsigned long *)0x4000C028))
#define UART0_LCRH_R            (*((volatile unsigned long *)0x4000C02C))
#define UART0_CTL_R             (*((volatile unsigned long *)0x4000C030))
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_LCRH_WLEN_8        0x00000060  // 8 bit word length
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOA      0x00000001  // port A Clock Gating Control

//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
                                        // configure PA1-0 as UART
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA
}


void TExaS_Scope(void){
  SYSCTL_RCGCTIMER_R |= 0x30;      // 0) activate timer4 and timer5
  UART_Init(); // UART0 is connected to TExaSdisplay
  TIMER4_CTL_R = 0x00000000;       // 1) disable timer4A during setup
  TIMER4_CFG_R = 0x00000000;       // 2) configure for 32-bit mode
  TIMER4_TAMR_R = 0x00000002;      // 3) configure for periodic mode, default down-count settings
  TIMER4_TAILR_R = 7999;           // 4) 100us reload value
  TIMER4_TAPR_R = 0;               // 5) bus clock resolution
  TIMER4_ICR_R = 0x00000001;       // 6) clear timer5A timeout flag
  TIMER4_IMR_R = 0x00000001;       // 7) arm timeout interrupt
  NVIC_PRI17_R = (NVIC_PRI17_R&0xFF00FFFF)|0x00E00000; // 8) priority 7
// interrupts enabled in the main program after all devices initialized
// vector number 86, interrupt number 70
  NVIC_EN2_R = 0x00000040;         // 9) enable interrupt 70 in NVIC
  TIMER4_CTL_R = 0x00000001;       // 10) enable timer4A
}
#define UART0_DR_R              (*((volatile unsigned long *)0x4000C000))

void Timer4A_Handler(void){
  TIMER4_ICR_R = 0x00000001;        // acknowledge timer5A timeout
  UART0_DR_R = (ADC1_SSFIFO3_R>>4); // send ADC to TExaSdisplay
}

