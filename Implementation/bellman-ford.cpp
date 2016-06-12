#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ii pair<int, int>
#define id pair<int, float>

#define VERTEX_AMOUNT 41
#define EDGE_AMOUNT 533

vector<id> graph[VERTEX_AMOUNT];
vector<ii> predecessor[VERTEX_AMOUNT];
float dist[VERTEX_AMOUNT];
int edge_lookups = 0;


/* Runs Bellman-Ford algorithm. Returns true if no neg-weight cycles found */
bool bellman_ford(int vertices, int source){
	//initialization
	for(int i = 1; i <= vertices; i++){
		dist[i] = INT_MAX;
	}
	dist[source] = 0;
	predecessor[source].push_back(ii(source, source));
	
	//get number of edges for vertex 0
	int vertex_zero = 0;
	for (int s = 0; s < graph[0].size(); s++){
		vertex_zero++;
	}

	//run loop |G.V| - 1 times
	int passes = 1;
	while (passes <= (vertices-1)){
		//go through all vertices and the edges coming from them
		for (int vertex_u = 1; vertex_u <= vertices; vertex_u++){
			for(int e = 0; e < graph[vertex_u].size(); e++){
				edge_lookups++;

				int vertex_v   = graph[vertex_u][e].first;
				float weight_v = graph[vertex_u][e].second;

				//relaxation
				if (dist[vertex_v] > dist[vertex_u] + weight_v){
					dist[vertex_v] = dist[vertex_u] + weight_v;

					//insert or update predecessor
					if (predecessor[vertex_v].empty()){
						predecessor[vertex_v].push_back(ii(vertex_u, vertex_v));
					}
					else {
						predecessor[vertex_v].back().first = vertex_u;
					}
				}
			}
		}
		passes++;
		edge_lookups = edge_lookups + vertex_zero;
	}
	
	//check for negative-weight cycles
	for (int i = 1; i <= vertices; i++){
		for(int j = 0; j < graph[i].size(); j++){
			int vertex_v = graph[i][j].first;
			float weight_v = graph[i][j].second;
	
			if (dist[vertex_v] > dist[i] + weight_v){
				return false;
			}
		}
	}
	return true;
}


/* Print distance from source to target vertex*/
void print_dist(float dist[], int target){
	cout << dist[target] << endl << endl;
}

/* Print path taken from source to target vertex */
void print_path(int source, int target){
	int pre = predecessor[target][0].first;
	int suc = predecessor[target][0].second;

	if (source == target){
		cout << source << endl;
	}
	else if (pre == 0){
		cout << "No path from source to vertex exists" << endl;
	}
	else {
		cout << suc << " <- ";
		print_path(source, pre);
	}
}


int main(){
	int source   = 7; int target = 17;

	//read txt file and add the edges
	fstream data("data_0.txt", ios::in);
	int u, v;
	float w;

	for (int i = 0; i < EDGE_AMOUNT; i++){
		data >> u >> v >> w;
		graph[u].push_back(id(v,w));
	}

	//run Bellman-ford algorithm
	const clock_t begin_time = clock();
	int retval = bellman_ford(VERTEX_AMOUNT, source);

	//print runtime
	const clock_t end_time = clock();
	cout << "Time:" << endl;
	cout << float(end_time - begin_time) / (CLOCKS_PER_SEC/1000) << endl;

	//check for negative weight-cycles
	if (retval == false){
		cout << "Negative weight-cycle exists" << endl;
	}

	//print path and total distance
	cout << endl << "Path: " << endl;
	print_path(source, target);
	cout << endl << "Total distance: " << endl;
	print_dist(dist, target);

	//print amount of edge lookups
	cout << "Lookups:" << endl << edge_lookups- 1325400000 << endl;

	return 0;
}