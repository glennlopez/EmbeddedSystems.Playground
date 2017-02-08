// ***** 0. Documentation Section *****
// main.c
//     Runs on TM4C123
//     UART runs at 115,200 baud rate 
//     Daniel Valvano
//     June 17, 2013
// First C Program showing the structure of a C Program
//    - Sections
//    - Variable and constants
//    - The Assignment operation 
//    - UART Output using printf library function
//    - Functions with one input/output
//      Jon Valvano and Ramesh Yerraballi
//      June 27, 2013

// ***** 1. Pre-processor Directives Section *****
//  INCLUDES: Lists any external libraries we will refer to using 
//  a #include tag
#include <stdio.h>  // If a library is standard C library use the <> braces
#include "uart.h"    // If the library is user defined use quotes " "

// ***** 2. Global Declarations Section *****
// GLOBAL VARIABLES: Lists variables that can be accessed in all parts 
// of the program, including other files.
unsigned long error = 0; //A global error count

// FUNCTION PROTOTYPES: Each subroutine defined
//  in the program must have its prototype specified
//  in this section. Function prototypes are used for
//  "type checking" by the compiler

unsigned long Calc_Area(unsigned long); // says Calc_Area subroutine 
                    // takes an unsigned long as
                    // input and returns unsigned long
void Initialize(void);  // says Initialize takes no input returns none

// ***** 3. Subroutines Section *****

// MAIN: The Mandatory subroutine "main". This is where
// the program starts when executed.

int main (void) {
  // All variables used inside the main subroutine have to be
  // declared first before we can write code. 
  unsigned long side, area;
  
  Initialize();   // One time program initialization  
  UART_Init();    // call the subroutine defined in "uart.h"
                  // to initialize UART for printing
  printf("\nThis program calculates areas of square rooms\n");
  side = 3;       // side is a variable that is currently set to 3 meters
  
  while(side != 0) {
    printf("\nGive room side (Type zero to quit): ");  // Prompt user
    scanf("%ld", &side);         // Get user input
    area = Calc_Area(side);
    if (area != 0) {
      printf("\nArea of a square room of side %ld is %ld\n",  side, area);
    } else {
      printf("\nSide cannot exceed  25\n");
    }
  }
}

// OTHER: For each subroutine provide the body of the subroutine

// Every subroutine should be preceded by a short description that
// gives the purpose and use of the subroutine:
// Purpose: This subroutine does "this and that but not other..."
// Input: Expected inputs
// Output: Expected outputs
// Notes: Any additional notes for the caller to know.

// Called once to initialize program 
// Input:  None
// Output: None
// Notes:  
void Initialize(void) {
  error = 0;      // Access global error count and set it to zero
}

// Computes the Area of a square room whose side is given
// Input:  the side of the square
// Output: the area of the square whose side is less than 25
// Notes:  The side has to be positive and less than or equal to 25
unsigned long Calc_Area(unsigned long side) {
  unsigned long result;

  if (side <= 25) {
    result = side * side;    // compute valid area
  } else {
    result = 0;       // indicate invalid area
    error = error+1;  // increment gloabal error count 
  }
  return(result);
}
