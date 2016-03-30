#include <iostream>
#include <stdlib.h>
#include "dijkstra.h"
#include "relaxation.h"
using namespace std;


char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int add_vertices(vertex graph[], int amount){
	for (int i = 0; i < amount; i++){
		graph[i].name  = alphabet[i];
	}
	return 0;
}

int add_edge(vertex graph[], int src, int dst, int weight, int k_edges) {
	//allocate memory for the edge
	graph[src].edges[k_edges] = (edge*) malloc(sizeof(edge));
	
	//add the edge with the respective src, dst, and weight values.
	graph[src].edges[k_edges]->weight       =  weight;
	graph[src].edges[k_edges]->source       =  src;
	graph[src].edges[k_edges]->destination  =  dst;

	//Update the index in the edges[] array
	k_edges++;

	return 0;
}

void dijkstra(vertex graph[], int weight, vertex source){
	initialize_single_source(graph, source);
	vertex set[] = {};

	//Set the min-priority queue equal to the set of vertices V.
	//Change this?
	vertex *min_queue = graph;

	//while Q != Ø
	while (sizeof(min_queue) != 0) {
		//vertex u = EXTRACT_MIN(min_queue)
	}
}


int main(){
	int amount = 4;
	//int edge_number = 0;

	//add vertices into the graph
	vertex graph[amount];
	add_vertices(graph, amount);
	
	//print the name of all vertices
	for (int i = 0; i < amount; i++) { 
		cout <<  graph[i].name << endl;
	}

	//add edges with weight 7 and 2 from vertex 0

	//Den her graf er den vi talte om, du kan nemt tegne den (hhv. src-knude, dst-knude, vægt)
	add_edge(graph, 0, 1, 7, 0);
	add_edge(graph, 0, 2, 2, 1);

	add_edge(graph, 1, 2, 1, 0);
	add_edge(graph, 1, 3, 5, 1);
	
	add_edge(graph, 2, 3, 2, 0);
	//cout << (sizeof(graph)/sizeof(graph[0])); Returns 4, which is the number of vertices in our graph
	
	for (int i = 0; i < ((sizeof(graph)/sizeof(graph[0]))-1); i++) //Print function for printing edges, does only print the first edge in each vertix though!
	{
		cout << graph[i].edges[0]->weight;
		cout << graph[i].edges[0]->source;
		cout << graph[i].edges[0]->destination << endl;
	}	
	//reset edge_number when all edges going from a vertex has been added?
	//edge_number = 0;

	return 0;
} 

