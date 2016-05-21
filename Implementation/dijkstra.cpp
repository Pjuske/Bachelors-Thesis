#include <algorithm> 
#include <iostream>
using namespace std;
#include <queue>
#include <set>
#include <vector>

#define ii pair<int,int>

vector<ii> graph[100];
int dist[100];
bool visited[100];

void dijkstra_modified(int vertices, int source){
	//define priority queue pq
	set<ii> pq;
	//queue containing predecessor. First arg: predecessor, second arg: current vertex
	set<ii> predecessor;
	//insert source vertex and mark it as visited
	pq.insert(ii(0,source));
	predecessor.insert(ii(source, source));

	dist[source] = 0;
	visited[source] = 1;

	//While pq != Ø
	while(!pq.empty()){
		//extract vertex u from priority queue by letting iterator point to beginning
		ii u = *pq.begin();	
		pq.erase(u);
		visited[u.second] = 1;

		//for each vertex v adjacent to u
		for(int i = 0; i < graph[u.second].size(); i++){
			//if v has not been visited
			if(visited[graph[u.second][i].second] == 0){
				pq.insert(ii(dist[u.second]+graph[u.second][i].first , graph[u.second][i].second));
				//mark as visited
				visited[graph[u.second][i].second] = 1;
				dist[graph[u.second][i].second] = dist[u.second] + graph[u.second][i].first;
			}
			//if v has been visited
			else if(visited[graph[u.second][i].second]==1 && dist[graph[u.second][i].second] > dist[u.second]+graph[u.second][i].first){
				pq.erase(ii(dist[graph[u.second][i].second],graph[u.second][i].second));
				pq.insert(ii(dist[u.second]+graph[u.second][i].first,graph[u.second][i].second));
				dist[graph[u.second][i].second] =  dist[u.second]+graph[u.second][i].first;
			} 
		}
	}
}

//void print_path(int dist[], int vertices, int source, int target){
void print_path(int dist[], int vertices) {
	cout << "The shortest path for the vertices are:" << endl;

	for (int i = 1; i <= vertices; i++){
		cout << dist[i] << " to vertex " << i << endl; 
	}
}


int main(){
	int vertices, edges, source;

	cout << "Choose number of vertices:\n";
	cin >> vertices;
	
	cout << "Choose number of edges\n";
	cin >> edges;
	
	cout << "Enter the edges and their weights:\n";
	for(int i = 0; i < edges ;i++){
		int x,y,w;
		cin >> x >> y >> w;
		//http://www.cplusplus.com/reference/vector/vector/push_back/
		graph[x].push_back(ii(w,y));
	}

	source = 1;
	dijkstra_modified(vertices, source);
	print_path(dist, vertices);
	return 0;
}