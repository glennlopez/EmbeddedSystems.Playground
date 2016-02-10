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
	 unsigned long side;	//size of the wall in meters
	 unsigned long area; //size of the room in m^2
	UART_Init();   // call subroutine to init uart lib
	side = 3;				//3 meters
	area = side * side; //in square meters 
	//printf("This program calculates areas of square shaped rooms");
	 printf("This room with %ld by %ld is %ld meters squared \n", side, side, area);
}
 
