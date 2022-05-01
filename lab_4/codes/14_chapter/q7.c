//gcc -o q7   q7.c 

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sz = 100;
	int* data = malloc(sz * sizeof(int));

	int* ptr = data + sz/2;

	free(ptr);

	printf("Hello\n");
	return 0;
}