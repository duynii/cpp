#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
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
	return 0;
}