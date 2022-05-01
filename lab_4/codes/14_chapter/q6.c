//gcc -o q6   q6.c 

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int sz = 100;
	int* data = malloc(sz * sizeof(int));

	free(data);
	printf("%d\n", data[5]);

	printf("Hello\n");
	return 0;
}