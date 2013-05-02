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

void output(int arr[], int left, int right)
{
    for(int i=left; i<right; ++i)
        cout << " " << arr[i];

    cout << endl;
}

void quick_sort(int arr[], int left, int right)
{

    int i = left, j = right;

    int pivot = arr[ (left + right)/2 ];

    //partition
    while(i < j) {
        while(arr[i] < pivot)
            i++;
        while(arr[j] > pivot)
            j--;

        if(i <= j) 
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    cout << "Pivot: " << pivot << endl;
    output(arr, left, right);

    // Recursion
    if(left < j)
        quick_sort(arr, left, j);
    if(i < right)
        quick_sort(arr, i, right);
    
}

int main()
{
    cout << "Before: ";
    int vec[] = { 7, -5, 2, 16, 4, 3}; 
    output(vec, LEN);
    quick_sort(vec, 0, LEN-1);
    cout << "After: ";
    output(vec, LEN);

    return 0;
}
