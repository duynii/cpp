#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void output(const vector<int>& arr)
{
    cout << arr[0];
    for(int i=1; i<arr.size(); ++i)
        cout << " " << arr[i];

    cout << endl;
}

// Binary search of sorted array, returns index of value if found
// returns -1 if not found in array
int binary_search(const vector<int>& vec, int val)
{
    int left = 0;
    int right = vec.size()-1;

    while(left <= right)
    {
        int middle = (left + right) / 2;
    
        if(vec[middle] == val) {
            return middle;
        }
        else if(vec[middle] > val) {
            right = middle - 1;
        }
        else {
            left  = middle + 1;
        }
    }

    return -1;
}


int main()
{

    size_t LEN = 9;
    int d[] = { 1, 3, 4, 8, 10, 15, 18, 30, 40 };
    vector<int> arr(d, d + LEN);

    output(arr);

    int index = binary_search(arr, 4);
    cout << "Searching for 4 returns " << (index >= 0 ? arr[index] : index) << endl;

    index = binary_search(arr, 19);
    cout << "Searching for 19 returns " << (index >= 0 ? arr[index] : index) << endl;

    return 0;
}
