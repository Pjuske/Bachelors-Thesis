#include <assert.h>
#include <climits>
#include <iostream>
#include <stdlib.h>
#include "dijkstra.h"
#include "relaxation.h"
using namespace std;


char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
					 'n','o','p','q','r','s','t','u','v','w','x','y','z'};

/*
 ********************************** GRAPH ************************************
 */
int add_vertices(vertex graph[], int amount){
	for (int i = 0; i < amount; i++){
		graph[i].name  = alphabet[i];
	}
	return 0;
}


int add_edges(vertex graph[], char src, char dst[], int weight[], int size) {
	int s = 0;
	//find the position of the src and destionation vertex in graph
	//assumes that a vertex with the given name exists in graph.

	char name = src;
	while (graph[s].name != name){
		s++;
	}
	
	//allocate memory for the edge
	//int e = sizeof(graph[i].edges) / sizeof(graph[i].edges[0]);
	for (int i = 0; i < size; i++) {
		
		graph[s].edges[i] = (edge*) malloc(sizeof(edge));

		int d = 0;
		while (graph[d].name != dst[i]){
			d++;
		}

		//add the edge with the respective src, dst, and weight values.
		graph[s].edges[i]->weight  =  weight[i];
		graph[s].edges[i]->src     =  graph[s];
		graph[s].edges[i]->dest    =  graph[d];

		cout << "source: " << graph[s].name << endl;
		cout << weight[i] << " to " << graph[d].name << endl << endl;
	}
	return 0;
}

/*
 ***************************** HELPER FUNCTIONS ******************************
 */
//return size of vertex array
int find_size(vertex array[]){
	return sizeof(array) / sizeof(array[0]);
}

//returns the weight of the edge between vertex u and v. 
int edge_weight(vertex u, vertex v){
	for (int i = 0; i < sizeof(u.edges); i++){
		if (u.edges[i]->dest.name == v.name){
			return u.edges[i]->weight;
		}
	}
	//return error if there is no path between u and v.
	return -1;
}


//Return 1 if the shortest path to the given vertex has been found.
int path_found(vertex closed_set[], vertex v){
	for (int i = 0; i < sizeof(closed_set); i++){
		if (closed_set[i].name == v.name){
			return 1;
		}
	}
	return 0;
}

/*
 ********************************** HEAPS ************************************
 */
int parent(int i){
	return (i/2);
}
int left(int i){
	return 2*i;
}
int right(int i){
	return 2*i + 1;
}

void heap_swap(vertex u, vertex v){
	vertex tmp = u;
	u = v;
	v = tmp;
}

int heap_decrease_key(vertex heap[], int i, int key){
	if (key > heap[i].estimate) {
		return -1;
	}

	heap[i].estimate = key;
	while (i > 0 && heap[parent(i)].estimate > heap[i].estimate){
		heap_swap(heap[i], heap[parent(i)]);
		i =  parent(i);
	}
	return 0;
}

void heap_insert(vertex heap[], int key){
	//heap.size++;
	int size = find_size(heap);
	heap[size - 1].estimate = INT_MAX;
	heap_decrease_key(heap, size-1, key);
}

void heap_balance_min_heap(vertex heap[], int i){
	int l, r, size, min;

	l  = left(i);
	r = right(i);
	size = find_size(heap);
	//find vertex with minimum estimate
	if (l <= size && heap[l].estimate < heap[i].estimate){
		min = l;
	}
	else {
		min = i;
	}
	if (r <= size && heap[r].estimate < heap[min].estimate){
		min = r;
	}
	//swap if vertex i does not contain minimum key
	if (min != i){
		heap_swap(heap[i], heap[min]);
		heap_balance_min_heap(heap, min);
	}
}

vertex heap_extract_min(vertex heap[]){
	//heap underflow if size below one
	int size = find_size(heap);
	assert(size >= 1);

	//extract the vertex with minimum key and decrease size
	vertex min = heap[0];
	heap[0] = heap[size - 1];
	//heap.size--;
	//make sure heap property is withheld
	heap_balance_min_heap(heap, 0);
	return min;
}


/*
 ********************************* DIJKSTRA **********************************
 */

void dijkstra(vertex graph[], int weight, vertex source, vertex target){
	//initialization
	source.estimate = 0;
	int n = 1;
	vertex closed_set[sizeof(graph)] = {source};
	vertex min_queue[sizeof(graph)] = {source};
	int q_size = find_size(min_queue);


	//while Q != Ø
	while (q_size > 0){
		vertex u = heap_extract_min(min_queue);
		q_size--;

		if (u.name = target.name) {
			return;
		}
		//examine each vertex v adjacent to u
		int edge_size = sizeof(u.edges) / sizeof(u.edges[0]);
		for (int i = 0; i < edge_size; i++){
			vertex v = u.edges[i]->dest;
			if (!path_found(closed_set, v)){
				q_size++;
				//insert vertex v into S and Q
				closed_set[n] = v;
				min_queue[n]  = v;
				
				//update estimate and predecessor for v
				assert(edge_weight(u,v) != -1);
				v.estimate = u.estimate + edge_weight(u,v);
				v.predecessor = &u;
			}
		}
	}
}




int main(){
	int amount = 5;
	//int edge_number = 0;

	//add vertices into the graph
	vertex graph[amount];
	add_vertices(graph, amount);
	
	//print the name of all vertices
	for (int i = 0; i < amount; i++) { 
		cout << "vertex " << i << ": " << graph[i].name << endl;
	}
	cout << endl;
	

	char edge_a[2] = {'b','c'};
	char edge_b[1] = {'e'}; 
	char edge_c[2] = {'b','d'};
	char edge_d[1] = {'e'};

	int weight_a[2] = {10,5};
	int weight_b[1] = {2};
	int weight_c[2] = {2,7};
	int weight_d[1] = {6};

	add_edges(graph, 'a', edge_a, weight_a, 2);
	add_edges(graph, 'b', edge_b, weight_b, 1);
	add_edges(graph, 'c', edge_c, weight_c, 2);
	add_edges(graph, 'd', edge_d, weight_d, 1);

	int size = sizeof(graph) / sizeof(graph[0]);
	//for (int i = 0; i < (size-1); i++) //Print function for printing edges, does only print the first edge in each vertix though!
	//{}


	//dijkstra(graph[], int weight, vertex source, vertex target){
	return 0;
}