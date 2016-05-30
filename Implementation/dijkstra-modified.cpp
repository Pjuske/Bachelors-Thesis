#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define ii pair<int,int>
#define di pair<float, int>

vector<di> graph[100];
vector<ii> predecessor[100];
float dist[100];
bool visited[100];

/* Runs Dijkstra's algorithm until target vertex is found */
void dijkstra_modified(int vertices, int source, int target){
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
			//define vertex v and w(u,v)
			int   vertex_v = graph[vertex_u][i].second;
			float weight_v = graph[vertex_u][i].first;

			//if v has not been visited
			if(visited[vertex_v] == 0){
				//mark as visited and update pq + distance.
				visited[vertex_v] = 1;
				pq.insert(di(dist[vertex_u] + weight_v , vertex_v));
				dist[vertex_v] = dist[vertex_u] + weight_v;

				//insert predecessor
				predecessor[vertex_v].push_back(ii(vertex_u, vertex_v));
			}

			//if v has been visited, but another possible path (edge) was found
			else {
				if (dist[vertex_v] > dist[vertex_u] + weight_v){
					//update pq + distance
					pq.erase(di(dist[vertex_v], vertex_v));
					pq.insert(di(dist[vertex_u] + weight_v , vertex_v));
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
	int vertices =  41;
	int source   =  4; int target = 25;


	//read txt file and add the edges
	fstream txt("graph_0.txt", ios::in);
	int u, v;
	float w;

	while (txt >> u >> v >> w){
		graph[u].push_back(di(w,v));
	}

	//call Dijkstra's algorithm
	dijkstra_modified(vertices, source, target);


	//print path and total distance	
	cout << endl << "Path: " << endl;
	print_path(source, target);
	cout << endl << "Total distance: " << endl;
	print_dist(dist, target);
	
	return 0;
}