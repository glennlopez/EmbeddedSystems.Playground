//a simple number to ascii conversion
#include <stdio.h>
/*
	Convert 123 (ascii char) to (ascii hex)
	ie: 123 = 0x31, 0x32, 0x33
*/

int main(){
	unsigned int usrNum, limit, i;

	printf("Number: ");
	scanf("%i", &usrNum);

	//count number of digits
	unsigned int count = 0;
	limit = usrNum;
	while(limit != 0){
		limit = limit / 10;
		count++;
	}

	//convert digits to ascii
	unsigned int buffer[count];
	unsigned int convert[count];
	for(i = 0; i < count; i++){
		buffer[i] = usrNum % 10;
		convert[i] = (usrNum % 10) + 30;
		usrNum = usrNum / 10;
		printf("%i = 0x%i \n", buffer[i], convert[i]);
	}

	printf("\n");	//newline
	return 0;
}
