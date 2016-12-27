#include <iostream>
#include <vector>
#include <boost/tuple/tuple.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
					   no_property,
					   property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor 		  Edge;
typedef graph_traits<Graph>::edge_iterator			  EdgeIt;
typedef graph_traits<Graph>::vertex_descriptor  	  Vertex;

typedef property_map<Graph, edge_weight_t>::type WeightMap;

void testcase() {

	int n, c, f;
	cin >> n >> c >> f;

	Graph G(n);
	WeightMap wm = get(edge_weight, G);

	vector<string> chars[n];
	for (int i=0; i<n; i++) {
		//Add name strings to the nodes
		string characteristic;
		for (int j=0; j<c; j++) {
			cin >> characteristic;
//			cout << "Read characteristic: " << characteristic << endl;
			chars[i].push_back(characteristic);
		}
	}

	for (int i=0; i<n; i++){
		for (int j=i+1; j<n; j++) {
			int common=0;
			vector<string>::iterator it;
			for (it = chars[i].begin(); it != chars[i].end(); ++it) {
				if (find (chars[j].begin(), chars[j].end(), *it) != chars[j].end())
					common++;
			}
			//cout << "Common elements between " << i << " and " << j << " = " << common << endl;
			//If common >f add edge to the graph
			if (common > f){
				Edge e;
				tie(e, tuples::ignore) = add_edge(i, j, G);
				//wm[e] = common;
			}
		}
	}

	//Calculate maximum matching of students with more than f characteristics
	
	vector<Vertex> mate(n);
	const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

	edmonds_maximum_cardinality_matching(G, &mate[0]);
	
//	cout << "Mate size = " << mate.size() << endl;
	int nr_mates = 0;

	for (int i=0; i<n; i++)
		if (mate[i] != NULL_VERTEX && i<mate[i]){
		//	cout << i << " - " << mate[i] << endl;
			nr_mates ++;
			}
//	cout << "Nr. of mates = " << nr_mates << endl;
	
	if (nr_mates == n/2)
		cout << "not optimal" << endl;
	else
		cout << "optimal" << endl;
}

int main() {
	int T;
	cin >> T;
	while (T--)
		testcase();
	return 0;
}
