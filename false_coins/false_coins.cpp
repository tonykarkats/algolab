#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;


void printSet (set<int> &s) {

	set<int>::iterator it;
	for (it=s.begin(); it != s.end(); it++)
		cout << *it << " ";
	cout << endl;

}
void testcase() {

	int n, k;
	cin >> n >> k;

	set<int> low_suspects;
	set<int> high_suspects;
	set<int> equals;

	vector<int> left[k];
	vector<int> right[k];
	set<int> weighted;
	char comp[k];

	// Read Input
	for (int i=0; i<k; i++) {
		int coins;
		cin >> coins;
		
		for (int j=0; j<coins; j++) {
			int coin;
			cin >> coin;
			left[i].push_back(coin);
			weighted.insert(coin);
		}

		for (int j=0; j<coins; j++) {
			int coin;
			cin >> coin;
			right[i].push_back(coin);
			weighted.insert(coin);
		}

		cin >> comp[i];
	}

	for (int i=0; i<k; i++) {
		if (comp[i] == '=') {
			for (int j=0; j<left[i].size(); j++) {
				equals.insert(left[i][j]);
				equals.insert(right[i][j]);
			}
		}
	}

	//printSet(equals);

	int occurences[n];
	for (int i=0; i<n; i++)
		occurences[i] = 0;
	for (int i=0; i<k; i++) {
		if (comp[i] == '<') {
			for (int j=0; j<left[i].size(); j++) {
				if (equals.find(left[i][j]) == equals.end()) {
	//				cout << "Inserted low : " << left[i][j] << endl;
					low_suspects.insert(left[i][j]);
					occurences[left[i][j]]++;
				}
				
				if (equals.find(right[i][j]) == equals.end()) {
	//				cout << "Inserted high : " << right[i][j] << endl;
					high_suspects.insert(right[i][j]);
					occurences[right[i][j]]++;
				}
			}

		}
		else if (comp[i] == '>') {
			for (int j=0; j<left[i].size(); j++) {
				if (equals.find(left[i][j]) == equals.end()) {
	//				cout << "Inserted high : " << left[i][j] << endl;
					high_suspects.insert(left[i][j]);
					occurences[left[i][j]]++;
				}
				
				if (equals.find(right[i][j]) == equals.end()) {
	//				cout << "Inserted low : " << right[i][j] << endl;
					low_suspects.insert(right[i][j]);
					occurences[right[i][j]]++;
				}
			}

		}
	}

	//Remove highs found in lows
	set<int> high_suspects1;
	set<int> low_suspects1;

	set_difference(high_suspects.begin(), high_suspects.end(),
				   low_suspects.begin(), low_suspects.end(),
				   inserter(high_suspects1, high_suspects1.begin()));

	set_difference(low_suspects.begin(), low_suspects.end(),
				   high_suspects.begin(), high_suspects.end(),
				   inserter(low_suspects1, low_suspects1.begin()));

//	cout << "H "; printSet(high_suspects1);
//	cout << "L "; printSet(low_suspects1);
	set<int> suspects;

	set_union(high_suspects1.begin(), high_suspects1.end(),
			  low_suspects1.begin(), low_suspects1.end(),
			  inserter(suspects, suspects.begin()));

	//printSet(suspects);

	if (suspects.size() == 0) {
		set<int> all_coins;
		set<int> unweighted;
		for (int i=1; i<=n; i++)
			all_coins.insert(i);

		set_difference(all_coins.begin(), all_coins.end(),
					   weighted.begin(), weighted.end(),
					   inserter(unweighted, unweighted.begin()));

		if (unweighted.size() == 1)
			cout << *(unweighted.begin()) << endl;
		else 
			cout << 0 << endl;
	}
	else if (suspects.size() == 1) {
		cout << *(suspects.begin()) << endl;
	}
	else {
		set<int>::iterator it, max_it, sec_max_it;
		int max = -1;
		int second_max = -1;
		for (it=suspects.begin(); it != suspects.end(); it++) {
//			cout << *it << "-> " << occurences[*it] << endl;
			if (occurences[*it] > max) {
				max = occurences[*it];
				max_it = it;
			}
			else if ((occurences[*it] <= max) && (occurences[*it] > second_max)) {
				second_max = occurences[*it];
				sec_max_it = it;
			}
		}
		
		if (max == second_max)
			cout << 0 << endl;
		else
			cout << *max_it << endl;

	}


}


int main() {

	std::ios_base::sync_with_stdio(false);	
	int t;
	cin >> t;
	while (t--)
		testcase();

	return 0;
}


