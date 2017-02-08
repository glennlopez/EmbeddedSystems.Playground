//**** Documentation Section
// This Program calculates the area of  square shaped rooms
// Author: Ramesh Yerraballi  and Jon Valavano
// Date:   6/28/2013

// Pre-processorr Directives Section
//  INCLUDES: Lists any external libraries we will refer to using
//  a #include tag
#include <stdio.h>  // Diamond braces for sys lib: Standard I/O
#include "uart.h"   // Quotes for user lib: UART lib

// Subroutines section
// MAIN: Mandatory subroutine for a C Program to be executable
int main(void) {
	UART_Init();   // call subroutine to init uart lib
	
	printf("This program calculates areas of square shaped rooms");
}
