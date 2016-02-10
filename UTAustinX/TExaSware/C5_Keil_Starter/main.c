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
	  
	unsigned long side = 1;					//size of the wall in meters
	unsigned long area = 0; 				//size of the room in m^2
	 
	UART_Init();   							// call subroutine to init uart lib
	init_global();							// call the default global subroutine
	 
	 
	if(error <= 0){
		printf("\nThis program calculates the square of a number \n");
	}
	 
	while(1){
		if(side == 0){
			printf("\nProgram done!\n");
			break;
		}
		
		printf("\n\nEnter a number to square (+/30 to quit): ");
		scanf("%ld", &side);
		
		if(side <= 30){
			area = calc_area(side);
			printf("\nThe square of %ld is %ld meters squared \n", side, area);
		}
		else{
			printf("\n\nCANNOT GO ABOVE 30 \n\n");
		}
	}
	
}
 
void init_global(){
	error = 0;
}
 
unsigned long calc_area(unsigned long s){
	unsigned long result;
	if(s <= 30){
		result = s * s;
	}
	else{
		result = 0;					//mistake
		error = error + 1;
	}
	return result;
}
 
