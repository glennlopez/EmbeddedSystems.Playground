#include <stdio.h>
unsigned long factorial(unsigned long n);

int main(){ unsigned long usrNum;

	printf("Get factorial of: ");
	scanf("%lu", &usrNum);
	printf("%lu\n", factorial(usrNum));

	printf("\n");	//newline
	return 0;
}


unsigned long factorial(unsigned long n){
	//base case
	if(n == 1){
		printf("1 = ");
		return 1;
	}
	else{
		printf("%lu x ", n);
		return (n * (factorial(n - 1)));
	}
}
