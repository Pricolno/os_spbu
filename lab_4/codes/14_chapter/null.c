//gcc -o null   null.c 

#include <stdio.h>

int main()
{
	int* a = NULL;
	//*a;
	int c = *a;


	printf("Hello\n");
	return 0;
}