//gcc -o q5   q5.c 

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sz = 100;
	int* data = malloc(sz * sizeof(int));

	data[sz] = 0;

	printf("Hello\n");
	return 0;
}