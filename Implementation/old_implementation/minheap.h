#ifndef MINHEAP_H
#define MINHEAP_H

#include "dijkstra.h"

class minheap {
	vertex vertices[];
	int size;
};

//change arguments to be of type minheap heap[] ?
void decrease_key(vertex minheap[], int i, int key);
void insert(vertex minheap[], int key);
vertex extract_min(vertex minheap[]);

#endif

