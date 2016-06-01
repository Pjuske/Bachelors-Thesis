#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define VERTEX_AMOUNT 41
#define EDGE_AMOUNT 533
#define TARGET 35           //only relevant for A*

vector<ii> coordinates[VERTEX_AMOUNT];
float target_distance[VERTEX_AMOUNT];


/* 
 * Calculate Euclidean distance between two vertices.
 * Used for finding edge weight and distance to target.
 */
float euclidean_distance(int index_1, int index_2){
	int x_1 = coordinates[index_1][0].first;
	int y_1 = coordinates[index_1][0].second;
	
	int x_2 = coordinates[index_2][0].first;
	int y_2 = coordinates[index_2][0].second;

	float dist = sqrt(pow(x_1 - x_2,2) + pow(y_1 - y_2,2)); 
	return dist;
}

int main(){
	int u, v;

	//open the text
	fstream read;
	read.open("graph00.txt", ios_base::in);
	read >> u >> v;
	
	//read and save the coordinates of the vertices
	for (int i = 0; i < VERTEX_AMOUNT; i++){
		read >> u >> v;
		coordinates[i].push_back(ii(u,v));
	}

	//open the text
	ofstream write;
	write.open("data_0.txt");
	
	//write the vertices and edge-weights to file
	for (int i = 0; i < EDGE_AMOUNT; i++){
		read >> u >> v;
		write << u << " " << v << " " << euclidean_distance(u, v) << endl;
	}

	//save Euclidean distance from each vertex to target
	for (int i = 0; i < VERTEX_AMOUNT; i++){
		target_distance[i] = euclidean_distance(i, TARGET);
	}
	
	//append Euclidean distance for (v,t) to file
	for (int i = 0; i < VERTEX_AMOUNT; i++){
		write << target_distance[i] << endl; 
	}

	return 0;
}