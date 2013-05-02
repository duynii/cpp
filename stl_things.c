#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// A class comparator
class IntComparator {
public:
    bool operator()(int a, int b) {
        return a > b;
    }
};

bool myfunc(int a, int b) { return a < b; };


int main(int argc, const char* argv[])
{
    set<int, IntComparator> nums;
    nums.insert(4);
    nums.insert(2);
    nums.insert(5);
    nums.insert(4);

    set<int>::const_iterator iter;
    for(iter=nums.begin(); iter!=nums.end(); ++iter)
    {
        cout << *iter << endl;
    }

    cout << endl;

    //Sort: random access iter needed
    // 32 71 12 45 26 80 53 33
    int myints[] = {32,71,12,45,26,80,53,33};
    std::vector<int> myvector (myints, myints+8);               
    // This is O(nlogn)
    sort(myvector.begin(), myvector.end(), IntComparator());
    vector<int>::const_iterator it;
    for(it=myvector.begin(); it!=myvector.end(); ++it) {
        cout << *it << endl;
    }

    // Stable sort (mergesort): random access iter needed
    cout << endl;
    stable_sort(myvector.begin(), myvector.end(), myfunc);
    for(it=myvector.begin(); it!=myvector.end(); ++it) {
        cout << *it << endl;
    }
    
    // heap sort (mergesort): random access iter needed
    cout << endl;
    sort_heap(myvector.begin(), myvector.end(), IntComparator());
    for(it=myvector.begin(); it!=myvector.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}

