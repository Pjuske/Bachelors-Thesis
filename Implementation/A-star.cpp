#include <climits>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define di pair<float, int>
#define VERTEX_AMOUNT 41    //41 , 160 , 638 , 2542
#define EDGE_AMOUNT 533    //533 , 4240 , 34644 , 262844

vector<di> graph[VERTEX_AMOUNT];
vector<ii> predecessor[VERTEX_AMOUNT];

float dist[VERTEX_AMOUNT];
float target_dist[VERTEX_AMOUNT];
bool visited[VERTEX_AMOUNT];
int edge_lookups = 0;

/* Runs A* search algorithm until target vertex is found */
void a_star(int vertices, int source, int target){
	//define priority queue pq
	set<di> pq;
	
	//insert source vertex and mark it as visited
	pq.insert(di(0, source));
	predecessor[source].push_back(ii(source, source));
	dist[source] = 0;
	visited[source] = 1;

	//While pq != Ø
	while(!pq.empty()){
		//extract vertex u from priority queue
		di u = *pq.begin();	
		int vertex_u = u.second;
		
		//if target found
		if (vertex_u == target){
			return;
		}

		pq.erase(u);
		visited[vertex_u] = 1;

		//For each vertex v adjacent to u:
		for(int i = 0; i < graph[vertex_u].size(); i++){
			edge_lookups++;
			//define vertex v and w(u,v)
			int   vertex_v = graph[vertex_u][i].second;
			float weight_v = graph[vertex_u][i].first;

			//if v has not been visited
			if(visited[vertex_v] == 0){
				//mark as visited and update pq + distance.
				visited[vertex_v] = 1;
				float sum = dist[vertex_u] + weight_v + target_dist[vertex_v];
				pq.insert(di(sum, vertex_v));
				dist[vertex_v] = dist[vertex_u] + weight_v;

				//insert predecessor
				predecessor[vertex_v].push_back(ii(vertex_u, vertex_v));
			}

			//if v has been visited, but another possible path (edge) was found
			else {
				if (dist[vertex_v] > dist[vertex_u] + weight_v){
					//update pq + distance
					float sum = dist[vertex_u] + weight_v + target_dist[vertex_v];
					pq.erase(di(dist[vertex_v], vertex_v));
					pq.insert(di(sum, vertex_v));
					dist[vertex_v] = dist[vertex_u] + weight_v;
				
					//update predecessor		
					predecessor[vertex_v].back().first = vertex_u;
				}
			}
		}
	}

}

/* Print distance from source to target vertex*/
void print_dist(float dist[], int target){
	cout << dist[target] << endl << endl;

	for (int i = 0; i < VERTEX_AMOUNT; i++){
		if (visited[i]){	
			dist[i] = INT_MAX;
		}
	}
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
	int source   =  7; int target = 17;
	fstream data;

	//read edge data
	data.open("data_0.txt", ios::in);
	int u, v;
	float w;

	//add edges to graph
	for (int i = 0; i < EDGE_AMOUNT; i++){
		data >> u >> v >> w;
		graph[u].push_back(di(w,v));
	}

	//save distance to target for each vertex in graph
	for (int i = 0; i < VERTEX_AMOUNT; i++){
		data >> w;
		target_dist[i] = w;
	}

	//run A* search
	const clock_t begin_time = clock();
	a_star(VERTEX_AMOUNT, source, target);
	
	//print runtime
	const clock_t end_time = clock();
	cout << "Time:" << endl;
	cout << float(end_time - begin_time) / (CLOCKS_PER_SEC/1000) << endl;

	//print path and total distance	
	cout << endl << "Path: " << endl;
	print_path(source, target);
	cout << endl << "Total distance: " << endl;
	print_dist(dist, target);
	
	//print amount of edge lookups
	cout << "Lookups:" << endl << edge_lookups << endl;
	
	return 0;
}