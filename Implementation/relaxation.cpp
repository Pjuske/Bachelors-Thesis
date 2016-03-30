#include <limits>
#include "relaxation.h"


/* Initializes the graph by setting the distance to source vertex 
 * to 0 and ∞ for all other vertices. */
void initialize_single_source(vertex graph[], vertex source){
	int size = sizeof(graph) / sizeof(graph[0]);
	int infinity = std::numeric_limits<int>::max();

	for (int i = 0; i < size; i++){
		graph[i].estimate = infinity;
		graph[i].predecessor = NULL;
	}
	source.estimate = 0;
}

/* Relaxes an edge (u,v) with the weight given. */
void relax(vertex u, vertex v, int weight){
	if (v.estimate > (u.estimate + weight)) {
		v.estimate    =  u.estimate + weight;
		v.predecessor =  &u;
	}
}

void print_path(vertex graph[], vertex source, vertex target){
	if (target.name == source.name){
		cout << source.name;
	}
	else if (v.predecessor == NULL){
		cout << "There exists no path from " source.name << " to " target.name;
	}
	else {
		cout << vertex.name;
		print_path(graph, source, target.predecessor);
	}
}
