#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <cmath>
#include <stack>


#include <boost/graph/adjacency_list.hpp>

class myInt {
	public:
		static int global_counter = 1;
		static const int INFINITE_VERTEX = 0;
		int vertex_id;
		myInt() {
			vertex_id = -1;
		}
		static int get_global_counter() {
			return global_counter++;
		}
}

// For CGAL Triangulation
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K,Tds>  Triangulation;
typedef Triangulation::Finite_edges_iterator Edge_Iterator;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<myInt,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;

using namespace std;

struct Edge {
	int destination;
	int capacity;
	Edge(int destination, int capacity) : destination(destination), capacity(capacity) {}
}

class Graph {
	int nodes;
	vector<vector<Edge> > adj_list;
	vector<bool> visited;
	queue<unsigned int> Q;
	int target;
public:
	Graph(int n, int target) {
		this->nodes = n;
		this->adj_list.resize(n);
		this->visited.resize(n, false);
		this->target = target;
	}
	
	void addEdge(int s, int t, int capacity) {
		adj_list[s].push_back(Edge(s, t, capacity));
	}
	
	bool bfs(int source, int d);
}

bool Graph::bfs(int source, int d) {
	Q.push(source);
	
	while(!Q.empty()) {
		int current = Q.front();
		visited[current] = true;
        Q.pop();
		if (current == target)
			return true;
		for(auto it=adj_list[current].begin(); it!=adj_list[current].end(); it++){
            if(!visited[it->destination] && capacity <= d){
                Q.push(it->destination);
            }
        }
	}
	return false;
}




void testcase(size_t n) {
	//Store points, so that they can be inserted more efficiently later
	vector<K::Point_2> pts;
	pts.reserve(n);

	for (size_t i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		pts.push_back(K::Point_2(x, y));
	}

	//Construct the triangulation
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	

	//Construct our graph

	
	Graph G(t.number_of_faces()+1, myInt::INFINITE_VERTEX);

	for (Edge_iterator e = t.finite_edges_begin(); e != finite_edges_end(); e++) {
		CGAL::Face_handle f1 = e.first;
		//Vertex_handle v2 = e.first->vertex(e.second);
		if (is_infinite(f1))
			f1->info().vertex_id = myInt::INFINITE_VERTEX;
		CGAL::Face_handle f2 = f1.neighbor(e.second);
		
		if (is_infinite(f2))
			f2->info().vertex_id = myInt::INFINITE_VERTEX;

		Triangulation::Vertex_handle v1 = e.first->vertex((e.second + 1) % 3);
		Triangulation::Vertex_handle v2 = e.first->vertex((e.second + 2) % 3);
		double sq_distance = CGAL::squared_distance(v1->point(), v2->point());
		if (f1->info().vertex_id == -1) {
			f1->info().vertex_id = get_global_counter();
		}			

		if (f2->info().vertex_id == -1) {
			f2->info().vertex_id = get_global_counter();
		}		

		addEdge(f1->info().vertex_id, f2->info().vertex_id, sq_distance);

		addEdge(f2->info().vertex_id, f1->info().vertex_id, sq_distance);

	}	

	//Number of users asking for escape route
	size_t m;
	cin >> m;
	

	for (size_t i=0; i<m; i++) {
		//Motion planning for each user
		int x, y;	
		double d;	
		cin >> x >> y;
		cin >> d;
		K::Point_2 start_p(x,y);
		Face_handle start_face = locate(start_p);

		Vertex bfs_source = start_face->info().vertex_id;

		if(bfs(bfs_source, d)) 
			cout << "Yes" << endl;
		else
			cout << "No" << endl;		
		
	}

}


int main() {

	size_t n;
	cin >> n;
	while(n!=0) {
		testcase(n);
		cin >> n;
	}

	return 0;
}



