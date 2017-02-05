#include <stdio.h>

//struct datatype definition for printing data
struct printData{
	void (*dataFunc)(void);
	int output;
}; typedef const struct printData output;

//struct dataype definition for calculating data
struct calcData{
	int (*calcFunc)(int, int);
	int input[2];
}; typedef const struct calcData computer;



//struct datatypes that take no argument
void hWorld(void);
void name(void);
output Option[2] = {
	{&hWorld, 0},
	{&name, 1}
};

//struct datatypes that takes arguments
int add(int, int);
int multiply(int, int);
computer Calculator[2] = {
	{&add, {1,2}},
	{&multiply, {3,4}}
};






/*************
	MAIN
**************/
int main(){ int result;

	//(Option[0].dataFunc)();
	//(Option[1].dataFunc)();
	//result = (Calculator[0].calcFunc)(Calculator[0].input[1], Calculator[1].input[0]);
	result = (Calculator[1].calcFunc)(Calculator[1].input[1], Calculator[0].input[1]);
	printf("Result: %i\n", result);

	printf("\n");
	return 0;
}






/*************
	FUNCTION
**************/
void hWorld(void){
	printf("Hello world!\n");
}
void name(void){
	printf("What is your name again?\n");
}

int add(int a, int b){
	return a + b;
}
int multiply(int a, int b){
	return (a * b);
}
