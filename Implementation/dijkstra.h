#ifndef DIJKSTRA_H
#define DIJKSTRA_H


class edge;

class vertex {
public:
	char name;
	//int index;
	edge* edges[];
};

class edge {
public:
	int weight;
	int source;
	int destination;
	//vertex source;
	//vertex destination;
};

#endif