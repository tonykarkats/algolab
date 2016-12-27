// A C++ program to find bridges in a given undirected graph
#include<iostream>
#include <list>
#include <vector>
#include <algorithm>
#define NIL -1
using namespace std;

class Bridge {
public:	
	int u;
	int v;
	Bridge(int u, int v);
};

Bridge::Bridge(int u, int v) {
	this->u = u;
	this->v = v;
}

 
// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    void bridgeUtil(int v, bool visited[], int disc[], int low[], int parent[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void bridge();    // prints all bridges
	int bridge_count;
	vector<Bridge> bridges;
	
};
 
Graph::Graph(int V)
{
    this->V = V;
	this->bridge_count = 0;
    adj = new list<int>[V];
	
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}
 
// A recursive function that finds and prints bridges using DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
void Graph::bridgeUtil(int u, bool visited[], int disc[], 
                                       int low[], int parent[])
{
    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static int time = 0;
    // Mark the current node as visited
    visited[u] = true;
 
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
 
    // Go through all vertices aadjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of u
 
        // If v is not visited yet, then recur for it
        if (!visited[v])
        {
            parent[v] = u;
            bridgeUtil(v, visited, disc, low, parent);
 
            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u]  = min(low[u], low[v]);
 
            // If the lowest vertex reachable from subtree under v is 
            // below u in DFS tree, then u-v is a bridge
            if (low[v] > disc[u]) {
			 // this->bridge_count++;
		/*	  if (!this->bridges.empty()) {
				 // cout << "Bridges not empty" << endl;
				  if ((this->bridges.back().u == u)) {
				  	if (this->bridges.back().v >= v)	
				  		this->bridges.push_back(Bridge(u,v));
					else
						{
							Bridge temp = this->bridges.back();
							this->bridges.pop_back();
				  			this->bridges.push_back(Bridge(u,v));
				  			this->bridges.push_back(temp);
						}
					}
					else
				  		this->bridges.push_back(Bridge(u,v));
			  }
			  else */
					if (u<v)
						this->bridges.push_back(Bridge(u,v));
					else
						this->bridges.push_back(Bridge(v,u));
             // cout << u <<" " << v << endl;
			}
        }
 
        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}
 
// DFS based function to find all bridges. It uses recursive function bridgeUtil()
void Graph::bridge()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    // Initialize parent and visited arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
    }
 
    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++)
        if (visited[i] == false)
            bridgeUtil(i, visited, disc, low, parent);
	//cout << this->bridge_count << endl;	
}


bool lex_sort(Bridge a, Bridge b) {
	if (a.u > b.u)
		return false;
	else if (a.u < b.u)
		return true;
	else { //a.u == b.u
		if (a.v > b.v)
			return false;
		else
			return true;	

	}
}

void testcase()
{
	int n, m;
	cin >> n >> m;
	
	Graph g(n+1);
	for (int i=0; i<m; i++){
		int e1, e2;
		cin >> e1 >> e2;
		g.addEdge(e1, e2);
	}
	g.bridge();
	cout << g.bridges.size() << endl;
	//Lexicographically sort the bridges
   //	vector<Bridge> final_bridges = g.bridges;
	std::sort(g.bridges.begin(), g.bridges.end(), lex_sort);

	vector<Bridge>::iterator it;
	for (it = g.bridges.begin() ; it != g.bridges.end(); ++it){
		cout << (*it).u << ' ' << (*it).v << endl;
	}
}


 
// Driver program to test above function
int main()
{

	int T;
	cin >> T;
	for (int i=0; i<T; ++i)
		testcase();
	return 0;

}

