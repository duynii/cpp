#include <functional>
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	//C++11 initialisation
	vector<int> coll = { 1, 2, 3, 4, 5, 6};
	// New for loop
	for(auto item: coll)
	{
		cout << item << " ";
	}
	cout << endl;

	string str = "abcdef";
	string empty = "aaaaaa";

	reverse(str.begin(), str.end());
	cout << str << endl;

	reverse_copy(str.begin(), str.end(), empty.begin());
	cout << "copied: " << empty << endl;


	auto min_pos = min_element(coll.cbegin(), coll.cend());
	auto max_pos = max_element(coll.cbegin(), coll.cend());

	cout << "min: " << *min_pos << ", max: " << *max_pos << endl;

	//Inserters: back_inserter() calls col.push_back
	//front_insert(col) calls col.push_front
	//inserter(col, pos) works on associative container too but 'pos' is ignored 

	vector<int> coll1;
	copy(coll.cbegin(), coll.cend(), back_inserter(coll1));

	list<int> coll2;
	copy(coll.cbegin(), coll.cend(), front_inserter(coll2));

	set<int> set1;
	copy(coll.cbegin(), coll.cend(), 
		inserter(set1, set1.begin()));
 	return 0;
}