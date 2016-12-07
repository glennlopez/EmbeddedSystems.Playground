// TExaSscope.h
// Runs on LM4F120/TM4C123
// Periodic timer 4A interrupt data collection
// PLL must be on for ADC to work (turned on in TExaSInit)
// ADC1 PD3 Ain continuous sampling (turned on in TExaSInit)
//

// Uses Timer4 to copy PD3 data from ADC1 to UART0.
// Jonathan Valvano, Daniel Valvano
// February 18, 2015

// enables ADC1, Timer4 and UART0
// call this after TExaSInit (PLL must be on)
void TExaS_Scope(void);

