#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "dijkstra.h"
#include "relaxation.h"
#include "minheap.h"

using namespace std;


char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int add_vertices(vertex graph[], int amount){
	for (int i = 0; i < amount; i++){
		graph[i].name  = alphabet[i];
	}
	return 0;
}

int add_edge(vertex graph[], vertex src, vertex dst, int weight) {
	int i = 0;
	//find the position of the src vertex in graph
	//assumes that a vertex with the given name exists in graph.
	while (graph[i].name != src.name){
		i++;
	}
	//allocate memory for the edge
	int e = sizeof(graph[i].edges) / sizeof(graph[i].edges[0]);
	graph[i].edges[e] = (edge*) malloc(sizeof(edge));
	
	//add the edge with the respective src, dst, and weight values.
	graph[i].edges[e]->weight     =  weight;
	graph[i].edges[e]->src   =  src;
	graph[i].edges[e]->dest  =  dst;

	return 0;
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


void dijkstra(vertex graph[], int weight, vertex source, vertex target){
	//initialization
	source.estimate = 0;
	int n = 1;
	vertex closed_set[sizeof(graph)] = {source};
	vertex min_queue[sizeof(graph)]  = {source};
	
	//while Q != Ø
	while (sizeof(min_queue) > 0){
		vertex u = extract_min(min_queue);
		if (u.name = target.name) {
			return;
		}
		//examine each vertex v adjacent to u
		int edge_size = sizeof(u.edges) / sizeof(u.edges[0]);
		for (int i = 0; i < edge_size; i++){
			vertex v = u.edges[i]->dest;
			if (!path_found(closed_set, v)){
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



/*
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
	add_edge(graph, 'a', 'b', 7);
	add_edge(graph, 'a', 'c', 2);

	add_edge(graph, 'b', 'c', 1);
	add_edge(graph, 'b', 'd', 5);
	
	add_edge(graph, 'c', 'd', 3);
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

*/

int main(){
	return 0;
}