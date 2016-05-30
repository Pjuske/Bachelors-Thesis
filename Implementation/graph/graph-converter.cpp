#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ii pair<int,int>
//define number of vertices in graph
vector<ii> vertex[2542];


float euclidean_dist(int index_1, int index_2){
	int x_1 = vertex[index_1][0].first;
	int x_2 = vertex[index_2][0].first;
	int y_1 = vertex[index_1][0].second;
	int y_2 = vertex[index_2][0].second;

	float dist = sqrt(pow(x_1 - x_2,2) + pow(y_1 - y_2,2)); 
	return dist;
}


int main(){
	int vertices, edges;
	int u, v;

	//retrieve the information and save the vertices in an array of tuples
	fstream txt("graph03.txt", ios_base::in);
	txt >> vertices >> edges;
	for (int i = 0; i < vertices; i++){
		txt >> u >> v;
		vertex[i].push_back(ii(u,v));
	}

	//write the vertices and edge-weights to a new file
	ofstream file;
	file.open("graph03-new.txt");
	for (int i = 0; i < edges; i++){
		txt >> u >> v;
		file << u << " " << v << " " << euclidean_dist(u, v) << endl;
	}
	file.close();

	return 0;
}