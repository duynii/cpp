#include <iostream>
#include <vector>


using namespace std;

void print(const vector<int>& vals)
{
    cout << "values: ";
    for(int i=0; i<vals.size(); ++i)
    {
        cout << vals[i] << ", ";
    }

    cout << endl;

}

void bsort(vector<int>& vals)
{

    const size_t size = vals.size();
    for(int i=0; i<size; i++)
    {
        // Crawling up the list
        bool swapped = false;
        for(int j=1; j<size-i; j++) 
        {
            if(vals[j-1] > vals[j]) {
                std::swap(vals[j-1], vals[j]);
                swapped = true;
                i = i;
            }     
        }
        print(vals);
        if(!swapped)
            return;
    }
    
}


int bsearch(const vector<int>& vals, int a, int b, int tgt)
{
    if (a >= b)
        return 999999;

    int pivot = a + (b - a)/2;

    if(tgt > vals[pivot]) {
        return bsearch(vals, pivot+1, b, tgt);
    }
    else if (tgt < vals[pivot]) {
        return bsearch(vals, a, pivot - 1, tgt);
    }
    else {
        return vals[pivot];
    }
}

void quicksort(vector<int>& vals, int low, int high)
{
    if(vals.size() <= 1)
        return;

    if(low >= high) 
        return;

    int& pivot = vals[high];

    int left = low;
    int right = high - 1;

    while(left <= right) {
        while (left <= right && pivot > vals[left] ) left++; //march till higher
        while (right >= left && pivot < vals[right]) right--; //march till lower
        if(left < right) {
            std::swap(vals[left], vals[right]);
        }
    }

    // Rinse and repeat
    std::swap(vals[left], pivot); 
    print(vals);
    quicksort(vals, low, left-1);
    quicksort(vals, left+1, high); 
}

/**
 * Static method that hashes a RIC using our own internal algorithm, such that the resulting value
 * is a number between 0 and the number of (bucketCount-1)
 * \param ric The zero-terminated string containing the RIC to be hashed.
 * \param bucketCount The number of possible slots that the RIC can be assigned to as a result of the
 * hash.
 * \return A number between greater than or equal to zero, and less than bucketCount.
 */
unsigned short hashRic(const char* ric, const short bucketCount)
{
    int i = 1;
    for (; *ric; ric++)
    {
        i = ((i << 5) + *ric) % bucketCount;
    }
    return i;
}


void merge(const vector<int>& s1, const vector<int>& s2, vector<int>& out)
{
    vector<int>::const_iterator i1 = s1.begin();
    vector<int>::const_iterator i2 = s2.begin();
    while(i1 != s1.end() && i2 != s2.end()) {
        if(*i1 < *i2) {
            out.push_back(*i1++);
        }
        else {
            out.push_back(*i2++);
        }
    }
    while(i1 != s1.end()) {
        out.push_back(*i1++);
    }
    while(i2 != s2.end()) {
        out.push_back(*i2++);
    }
}

void mergeSort(vector<int>& vals)
{
    size_t n = vals.size();
    if(n <= 1) return;

    if(n == 2)
    {
        if(vals[1] < vals[0]) {
            std::swap(vals[0], vals[1]);
        }
        return;
    }

    // Split into two halfs

    vector<int>::iterator half = vals.begin() + n/2;
    //vector<int> s1(vals.begin(), half);
    //vector<int> s2(half + 1, vals.end() + 1);
    vector<int> s1;
    vector<int> s2;   
    for(int i=0; i<n; i++) {
        if(i <= (n/2))
            s1.push_back(vals[i]);
        else
            s2.push_back(vals[i]);

    }
    mergeSort(s1);
    mergeSort(s2);
    print(s1);
    print(s2);
    vals.clear();
    merge(s1, s2, vals);
    print(vals);

}


int main()
{
    const int size = 11;
    int values[] = { 4, 6, 2, 23, 5, 7, 9, 1, 10, 11, 6 };
    vector<int> data(values, values + sizeof(values)/sizeof(int));



    cout << "Before ";
    print(data);
    //bsort(data);
    //quicksort(data, 0, size-1);
    mergeSort(data);
    cout << "Final ";
    print(data);
    cout << "Search 11: " << bsearch(data, 0, size-1, 11) << endl;
    cout << "Search 22: " << bsearch(data, 0, size-1, 22) << endl;
    

    return 0;

}


