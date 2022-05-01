//gcc -o vector   vector.c  vector.h


#include "./vector.h"

int main()
{
	struct Vector* vec = createVec(5);
	set(vec, 1, 2);
	set(vec, 3, 10);
	print_vec(vec);
	push_back(vec, 57);
	print_vec(vec);

	int count = 50;
	for (int i = 0; i < count; ++i)
	{
		push_back(vec, i);
	}

	print_vec(vec);

	delete_vec(vec);
	
	return 0;
}