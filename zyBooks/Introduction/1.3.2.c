#include "RIMS.h"
/*
	Write a C program for RIM that sets B0 = 1 whenever the numbers of 1s on A2, A1, and A0 is two or more (i.e., when A2 A1 A0 are 011, 110, 101, or 111). Hint: Use logical OR (||) in addition to logical AND. Run the program in RIMS to test the program.
*/
int main(){

	while(1){
		B0 = A0 && A1 || A0 && A2 || A1 && A0 || A1 && A2;
	}

	return 0;
}
