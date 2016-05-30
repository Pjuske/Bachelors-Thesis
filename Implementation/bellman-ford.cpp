#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#define ii pair<int, int>
#define id pair<int, float>

vector<id> graph[100];
vector<ii> predecessor[100];
float dist[100];

/* Runs Bellman-Ford algorithm. Returns true if no neg-weight cycles found */
bool bellman_ford(int vertices, int source){
	for(int i = 1; i <= vertices; i++){
		dist[i] = INT_MAX;
	}
	dist[source] = 0;
	predecessor[source].push_back(ii(source, source));

	//for i = 1 to |G.V|-1
	int passes = 1;
	while (passes <= (vertices-1)){
		//go through all vertices and the edges coming from them
		for (int vertex_u = 1; vertex_u <= vertices-1; vertex_u++){
			for(int e = 0; e < graph[vertex_u].size(); e++){
				int vertex_v   = graph[vertex_u][e].first;
				float weight_v = graph[vertex_u][e].second;

				//make sure there is an edge from u to v and then relax.
				if (dist[vertex_u] != INT_MAX && dist[vertex_v] > dist[vertex_u] + weight_v){
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
	}

	
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
	cout << dist[target] << endl;
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
	int vertices = 41;
	int source   = 4; int target = 25;

	/* Test for negative weight-cycle
	 *
	 *  graph[1].push_back(ii(2,-20));
	 * 	graph[2].push_back(ii(3,10));
	 *	graph[3].push_back(ii(2,-15));
	 *	graph[3].push_back(ii(1,5));
	 *
	 */

	//read txt file and add the edges
	fstream txt("graph_0.txt", ios::in);
	int u, v;
	float w;

	while (txt >> u >> v >> w){
		graph[u].push_back(id(v,w));
	}

	//check for negative weight-cycles
	int retval = bellman_ford(vertices, source);
	if (retval == false){
		cout << "Negative weight-cycle exists" << endl;
	}

	//print path and total distance
	cout << endl << "Path: " << endl;
	print_path(source, target);
	cout << endl << "Total distance: " << endl;
	print_dist(dist, target);
	
	return 0;
}