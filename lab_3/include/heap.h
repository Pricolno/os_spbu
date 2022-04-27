#ifndef __HEAPY_H__
#define __HEAPY_H__

#include <stdlib.h>


struct process{
	int id;
	int nice;
	int runtime;
	int vruntime;
	int actual_runtime;
};


struct process* create_process(
	int vruntime_,
	int id_,
	int nice_,
	int actual_runtime_,
 	int runtime_){

	struct process* pr = malloc(1 * sizeof(struct process));
	pr->vruntime = vruntime_;
	pr->id = id_;
	pr->nice = nice_;
	pr->actual_runtime = actual_runtime_;
	pr->runtime = runtime_;
	return pr;
};

struct Heap{
	int SIZE;
	struct process* arr;
	int HeapSize;
};

struct Heap* create_heap(){
	int SIZE = 1000;
	struct Heap* hp = (struct Heap*) malloc(1 * sizeof(struct Heap)); 
	hp->arr = (struct process*) malloc(SIZE * sizeof(struct process));
	hp->HeapSize = 0;
}


void assign(struct process* b, struct process* a){
	b->vruntime = a->vruntime;
	b->id = a->id;
	b->nice = a->nice;
	b->actual_runtime = a->actual_runtime;
	b->runtime = a->runtime;
	return;
}


void swap(struct process* a, struct process* b){
	struct process* temp = create_process(0, 0, 0, 0, 0);
	assign(temp, a);
 	assign(a, b);
 	assign(b, temp);
 	return;
}





void add(struct Heap* hp, struct process* pr) {
  int i, parent;
  i = hp->HeapSize;

  
  assign(&hp->arr[i],  pr);
  parent = (i-1)/2;

  while(parent >= 0 && i > 0)  {
    if(hp->arr[i].vruntime < hp->arr[parent].vruntime) {
      swap(&hp->arr[i], &hp->arr[parent]);
    }
    i = parent;
    parent = (i-1)/2;
  }
  hp->HeapSize++;
}


void heapify(struct Heap* hp, int i) {
  int left, right;
  struct process* temp = create_process(0, 0, 0, 0, 0);
  left = 2 * i + 1;
  right = 2 * i + 2;
  if(left < hp->HeapSize) {
    if(hp->arr[i].vruntime > hp->arr[left].vruntime) {
      swap(&hp->arr[i], &hp->arr[left]);
      heapify(hp, left);
    }
  }
  if(right < hp->HeapSize) {
    if(hp->arr[i].vruntime > hp->arr[right].vruntime) {
      swap(&hp->arr[i], &hp->arr[right]);
      heapify(hp, right);
    }
  }
}


struct process* get_min(struct Heap* hp) {
  struct process* pr = create_process(0, 0, 0, 0, 0);

  assign(pr, &hp->arr[0]);
  assign(&hp->arr[0], &hp->arr[hp->HeapSize-1]);
  hp->HeapSize--;
  heapify(hp, 0);
  return pr;
}



#endif // __HEAPY_H__