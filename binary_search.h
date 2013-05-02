#include <iostream>
#include <vector>

using namespace std;


// Returns index if found, -1 otherwise
int binary_search(const vector<int>& vals, int tgt, int low, int high /*index*/)
{
    if(low > high) return -1;

    int pivot= vals[(high-low)/2];

    if(vals[pivot] > tgt) {
        return bsearch(vals, tgt, pivot + 1, high);
    }
    else if(vals[pivot] < tgt) {
        return bsearch(vals, tgt, low, pivot - 1);
    }
    else {
        return pivot;
    }
}

//Or just use STL binary_search for random access container eg. vector 
//bool binary_search(beginIter, endIter, const T& tgt, Compare opOptional);

