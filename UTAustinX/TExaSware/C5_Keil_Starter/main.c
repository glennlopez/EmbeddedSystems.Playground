//**** Documentation Section
// This Program calculates the area of  square shaped rooms
// Author: Ramesh Yerraballi  and Jon Valavano
// Date:   6/28/2013

// Pre-processorr Directives Section
//  INCLUDES: Lists any external libraries we will refer to using
//  a #include tag
#include <stdio.h>  // Diamond braces for sys lib: Standard I/O
#include "uart.h"   // Quotes for user lib: UART lib

//global vars
unsigned long error;


//Function prototypes
void init_global();
unsigned long calc_area(unsigned long);

// Subroutines section
// MAIN: Mandatory subroutine for a C Program to be executable
 int main(void) {
	  
	unsigned long side;					//size of the wall in meters
	unsigned long area; 				//size of the room in m^2
	 
	UART_Init();   							// call subroutine to init uart lib
	init_global();							// call the default global subroutine
	
	side = 1;										//in meters
	area = calc_area(side); 		//in square meters 
	printf("\nThis room with %ld by %ld is %ld meters squared \n", side, side, area);
	 
	while(1){
		if(side >=40){
			break;
		}
		side = side + 1;
		area = calc_area(side); 		//in square meters 
		printf("\nThis room with %ld by %ld is %ld meters squared \n", side, side, area);
	}
	
}
 
void init_global(){
	error = 0;
}
 
unsigned long calc_area(unsigned long s){
	unsigned long result;
	if(s <= 25){
		result = s * s;
	}
	else{
		result = 0;					//mistake
		error = error + 1;
	}
	return result;
}
 
