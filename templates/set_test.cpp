#include <iostream>
#include <set>

using namespace std;

int main() {

	set<int> set_a, set_b, result;

	set_a.insert(1);
	set_a.insert(2);
	set_a.insert(3);
	set_a.insert(4);

	set<int>::iterator it;
	for (it = set_a.begin(); it != set_a.end(); it++)
		cout << *it << endl;

	set_a.erase(1);

	for (it = set_a.begin(); it != set_a.end(); it++)
		cout << *it << endl;

}
