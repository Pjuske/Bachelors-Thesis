#include "minheap.h"


int parent(int i){
	return (i/2);
}
int left(int i){
	return 2*i;
}
int right(int i){
	return 2*i + 1;
}

//auxiliary function that swaps two vertices in the minheap
void swap(vertex u, vertex v){
	vertex tmp = u;
	u = v;
	v = tmp;
}


//skal i returneres?
void decrease_key(vertex minheap[], int i, int key){
	minheap[i].estimate = key;
	while (i > 0 && minheap[parent(i)] > minheap[i]){
		swap(minheap[i], minheap[parent(i)]);
		i                  =  parent(i);

		//vertex tmp         =  minheap[i];
		//minheap[i]         =  minheap[parent(i)];
		//minheap[parent(i)] =  tmp;
	}
}

void insert(vertex minheap[], int key){
	int next_vertex               = sizeof(minheap) / sizeof(minheap[0]);
	minheap[next_vertex]          = (vertex*) malloc(sizeof(vertex));
	minheap[next_vertex].estimate = 0;
	decrease_key(minheap, next_vertex, key);
}

void balance_min_heap(vertex minheap[], int i){
	int left, right, size, minimum;

	left  = left(i);
	right = right(i);
	size = sizeof(minheap) / sizeof(minheap[0]);
	//find vertex with minimum estimate
	if (left <= size && minheap[left].estimate < min.heap[i].estimate){
		minimum = left;
	}
	else {
		minimum = i;
	}
	if (right <= size && minheap[right].estimate < minheap[minimum]){
		minimum = right;
	}
	//swap if vertex at index i does not contain the minimum key
	if (minimum != i){
		swap(minheap[i],minheap[minimum]);
		balance_min_heap(minheap, minimum);
	}
}


vertex extract_min(vertex minheap[]){
	int size = sizeof(minheap) / sizeof(minheap[0]);
	//heap underflow if size is under 1
	assert(size >= 1);

	//extract the vertex with minimum key and decrease size
	vertex min = min_heap[0];
	minheap[0] = minheap[size - 1];
	size--;
	//make sure heap property is withheld
	balance_min_heap(minheap, 0);
	return min;
}
