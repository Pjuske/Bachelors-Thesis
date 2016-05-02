#ifndef DIJKSTRA_H
#define DIJKSTRA_H


class edge;

class vertex {
public:
	char name;
	int estimate;
	vertex* predecessor;
	edge* edges[];
};

class edge {
public:
	int weight;
	vertex src;
	vertex dest;
};

#endif