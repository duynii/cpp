#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static const int LEN = 6;


void swap(string& s, int i, int j) {
    char c = s[i];
    s[i] = s[j];
    s[j] = c;
}
void reverse(string& str) {

    int length = str.length();

    int i, j;
    for(i=0, j=str.length()-1; i < j; i++, j--) {
        swap(str, i, j);

        cout << "iter i " << i << " j " << j << ": " << str << endl;
    }
}

int main()
{

    string test = "123456789";
    cout << "Before: " << test << endl << endl;
    reverse(test);

    return 0;
}
