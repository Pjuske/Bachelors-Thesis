//#include <algorithm> 
#include <iostream>
using namespace std;
#include <queue>
#include <set>
#include <vector>

#define ii pair<int,int>

vector<ii> graph[100];
vector<ii> predecessor[100];
bool visited[100];
int dist[100];


/* Runs Dijkstra's algorithm until target vertex is found */
void dijkstra_modified(int vertices, int source, int target){
	//define priority queue pq
	set<ii> pq;
	
	//insert source vertex and mark it as visited
	pq.insert(ii(0, source));
	predecessor[source].push_back(ii(source, source));
	dist[source] = 0;
	visited[source] = 1;

	//While pq != Ø
	while(!pq.empty()){
		//extract vertex u from priority queue
		ii u = *pq.begin();	
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
			int vertex_v = graph[vertex_u][i].second;
			int weight_v = graph[vertex_u][i].first;

			//if v has not been visited
			if(visited[vertex_v] == 0){
				//mark as visited and update pq + distance.
				visited[vertex_v] = 1;
				pq.insert(ii(dist[vertex_u] + weight_v , vertex_v));
				dist[vertex_v] = dist[vertex_u] + weight_v;

				//update predecessor
				predecessor[vertex_v].push_back(ii(vertex_u, vertex_v));
			}

			//if v has been visited, but another possible path (edge) was found
			else {
				if (dist[vertex_v] > dist[vertex_u] + weight_v){
					//update pq + distance
					pq.erase(ii(dist[vertex_v], vertex_v));
					pq.insert(ii(dist[vertex_u] + weight_v , vertex_v));
					dist[vertex_v] = dist[vertex_u] + weight_v;
				
					//update predecessor		
					predecessor[vertex_v].pop_back();
					predecessor[vertex_v].push_back(ii(vertex_u, vertex_v));		
				}
			}
		}
	}
}

/* Print distance from source to target vertex*/
void print_dist(int dist[], int target){
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
	int vertices, edges, source, target;

	cout << "How many vertices in the graph?" << endl;
	cin >> vertices;
	
	cout << "How many edges in the graph?" << endl;
	cin >> edges;
	
	cout << "Weight of the edges?" << endl;
	for(int i = 0; i < edges ;i++){
		int x,y,w;
		cin >> x >> y >> w;
		graph[x].push_back(ii(w,y));
	}

	source = 1;
	target = 5;
	dijkstra_modified(vertices, source, target);
	
	cout << endl << "Path: " << endl;
	print_path(source, target);
	cout << endl << "Total distance: " << endl;
	print_dist(dist, target);
	
	return 0;
}