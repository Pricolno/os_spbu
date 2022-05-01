#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>

void foo(){
	printf("DEB\n");
}

struct Vector{
		int* arr;
		size_t size;
		size_t cp;
};

size_t max_deg2(size_t n){
	size_t val = 2;
	while(val < n){
		val *= 2;
	}
	return val;
}

struct Vector* createVec(size_t sz){
	struct Vector* vec = (struct Vector*) malloc(sizeof(struct Vector));

	vec->cp = max_deg2(sz);
	vec->size = sz;
	vec->arr = (int *)calloc(vec->cp, sizeof(int));

	return vec;
}

void push_back(struct Vector* vec, int val){
	if(vec->size >= vec->cp){
		vec->cp *= 2;
		vec->arr = (int* ) realloc(vec->arr, vec->cp * sizeof(int));
		return;
	}
	
	vec->arr[vec->size] = val;
	vec->size++;


	return;
}


void print_vec(struct Vector* vec){
	printf("\n");
	for(int i= 0; i < vec->size; i++){
		printf("%d ", vec->arr[i]);
	}

	printf("\n");
}

void set(struct Vector* vec, size_t ind, int val){
	vec->arr[ind] = val;
	return;
}

void pop_back(struct Vector* vec){
	vec->size--;
	return;
}


void delete_vec(struct Vector* vec){
	free(vec->arr);
	free(vec);
	return;
}

#endif // __VECTOR_H__