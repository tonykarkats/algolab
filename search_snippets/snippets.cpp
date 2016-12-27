#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <climits>

using namespace std;

void testcase() {

	int n; // Nr of words in document;
	cin >> n;

	vector<int> occurs(n);
	for (int i=0; i<n; i++) {
		cin >> occurs[i];
	}

	vector<vector<int>> position(n);
	for (int i=0; i<n; i++) {
		position[i] = vector<int>(occurs[i]);
		for (int j=0; j<occurs[i]; j++) {
			cin >> position[i][j];
		}
	}

	// We keep a priority queue for all the positions of the words (ordered)
	// O(1) to remove from the top

	priority_queue<pair<int, int>, vector<pair<int, int>>> pos; // position, word
	for (int i=0; i<n; i++) {
		for (int j=0; j<position[i].size(); j++) {
			pos.push(make_pair(position[i][j], i));
		}
	}

	// We keep a vector for the chosen position of each word
	vector<int> chosen_position(n, -1);

	// We also keep a set of all the chosen (position, word) pairs
	set<pair<int, int>> chosen;

	int min_dist = INT_MAX;
	int found_words = 0;	

	while (!pos.empty()) {
	
		pair<int, int> tuple = pos.top();
		pos.pop();

		int t_pos  = tuple.first;
		int t_word = tuple.second;

		if (chosen_position[t_word] == -1) {
			// Word has not been discovered yet
			found_words++;
		}
		else {
			// Erase the old tuple since the new one is bound to be better
			chosen.erase(make_pair(chosen_position[t_word], t_word));
		}		

		chosen_position[t_word] = t_pos;
		chosen.insert(tuple);

		if (found_words == n) {
			//cout << "Found all words!" << endl;
			// All the words have been discovered so we can now examine the distance
			int a = chosen.begin()->first;
			int b = (--chosen.end())->first;

			int dist = b - a;
			min_dist = min(min_dist, dist);

		}


	}

	cout << min_dist + 1 << endl;	

}


int main() {
	
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--) {
		testcase();
	}

	return 0;
}
