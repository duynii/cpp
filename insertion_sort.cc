#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static const int LEN = 6;

void swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void output(int arr[], int length)
{
    cout << arr[0];
    for(int i=1; i<length; ++i)
        cout << " " << arr[i];

    cout << endl;
}

void insertionSort(int arr[], int length)
{
    int i, j;
    for(i = 1; i <length; i++)
    {
        j = i; // Element unsorted
        while(j > 0 && arr[j-1] > arr[j]) {
            swap(arr[j-1], arr[j]);
            j--;
        }
    
        cout << "Loop one fin with i = " << i <<  ", looking at " << arr[j] << endl;
        output(arr, length);
    } 
}

int main()
{
    cout << "Before: ";
    int vec[] = { 7, -5, 2, 16, 4, 3}; 
    output(vec, LEN);
    insertionSort(vec, LEN);

    return 0;
}
