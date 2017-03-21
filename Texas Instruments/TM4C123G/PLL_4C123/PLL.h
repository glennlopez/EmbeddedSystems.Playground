// PLL.h
// Runs on LM4F120/TM4C123
// A software function to change the bus frequency using the PLL.
// Daniel Valvano
// May 3, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 2.10, Figure 2.37

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// The #define statement SYSDIV2 initializes
// the PLL to the desired frequency.
// SYSDIV = 400/freq -1
// bus frequency is 400MMHz/(SYSDIV+1)

// configure the system to get its clock from the PLL
void PLL_Init(uint32_t freq);
#define Bus80MHz     4
#define Bus80_000MHz 4
#define Bus66_667MHz 5
#define Bus50_000MHz 7
#define Bus50MHz     7
#define Bus44_444MHz 8
#define Bus40_000MHz 9
#define Bus40MHz     9
#define Bus36_364MHz 10
#define Bus33_333MHz 11
#define Bus30_769MHz 12
#define Bus28_571MHz 13
#define Bus26_667MHz 14
#define Bus25_000MHz 15
#define Bus25MHz     15
#define Bus23_529MHz 16
#define Bus22_222MHz 17
#define Bus21_053MHz 18
#define Bus20_000MHz 19
#define Bus20MHz     19
#define Bus19_048MHz 20
#define Bus18_182MHz 21
#define Bus17_391MHz 22
#define Bus16_667MHz 23
#define Bus16_000MHz 24
#define Bus16MHz     24
#define Bus15_385MHz 25
#define Bus14_815MHz 26
#define Bus14_286MHz 27
#define Bus13_793MHz 28
#define Bus13_333MHz 29
#define Bus12_903MHz 30
#define Bus12_500MHz 31
#define Bus12_121MHz 32
#define Bus11_765MHz 33
#define Bus11_429MHz 34
#define Bus11_111MHz 35
#define Bus10_811MHz 36
#define Bus10_526MHz 37
#define Bus10_256MHz 38
#define Bus10_000MHz 39
#define Bus10MHz     39
#define Bus9_756MHz 40
#define Bus9_524MHz 41
#define Bus9_302MHz 42
#define Bus9_091MHz 43
#define Bus8_889MHz 44
#define Bus8_696MHz 45
#define Bus8_511MHz 46
#define Bus8_333MHz 47
#define Bus8_163MHz 48
#define Bus8_000MHz 49
#define Bus8MHz     49
#define Bus7_843MHz 50
#define Bus7_692MHz 51
#define Bus7_547MHz 52
#define Bus7_407MHz 53
#define Bus7_273MHz 54
#define Bus7_143MHz 55
#define Bus7_018MHz 56
#define Bus6_897MHz 57
#define Bus6_780MHz 58
#define Bus6_667MHz 59
#define Bus6_557MHz 60
#define Bus6_452MHz 61
#define Bus6_349MHz 62
#define Bus6_250MHz 63
#define Bus6_154MHz 64
#define Bus6_061MHz 65
#define Bus5_970MHz 66
#define Bus5_882MHz 67
#define Bus5_797MHz 68
#define Bus5_714MHz 69
#define Bus5_634MHz 70
#define Bus5_556MHz 71
#define Bus5_479MHz 72
#define Bus5_405MHz 73
#define Bus5_333MHz 74
#define Bus5_263MHz 75
#define Bus5_195MHz 76
#define Bus5_128MHz 77
#define Bus5_063MHz 78
#define Bus5_000MHz 79
#define Bus4_938MHz 80
#define Bus4_878MHz 81
#define Bus4_819MHz 82
#define Bus4_762MHz 83
#define Bus4_706MHz 84
#define Bus4_651MHz 85
#define Bus4_598MHz 86
#define Bus4_545MHz 87
#define Bus4_494MHz 88
#define Bus4_444MHz 89
#define Bus4_396MHz 90
#define Bus4_348MHz 91
#define Bus4_301MHz 92
#define Bus4_255MHz 93
#define Bus4_211MHz 94
#define Bus4_167MHz 95
#define Bus4_124MHz 96
#define Bus4_082MHz 97
#define Bus4_040MHz 98
#define Bus4_000MHz 99
#define Bus4MHz     99
#define Bus3_960MHz 100
#define Bus3_922MHz 101
#define Bus3_883MHz 102
#define Bus3_846MHz 103
#define Bus3_810MHz 104
#define Bus3_774MHz 105
#define Bus3_738MHz 106
#define Bus3_704MHz 107
#define Bus3_670MHz 108
#define Bus3_636MHz 109
#define Bus3_604MHz 110
#define Bus3_571MHz 111
#define Bus3_540MHz 112
#define Bus3_509MHz 113
#define Bus3_478MHz 114
#define Bus3_448MHz 115
#define Bus3_419MHz 116
#define Bus3_390MHz 117
#define Bus3_361MHz 118
#define Bus3_333MHz 119
#define Bus3_306MHz 120
#define Bus3_279MHz 121
#define Bus3_252MHz 122
#define Bus3_226MHz 123
#define Bus3_200MHz 124
#define Bus3_175MHz 125
#define Bus3_150MHz 126
#define Bus3_125MHz 127




