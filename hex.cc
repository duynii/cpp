#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int main()
{

    string hex = "0x7e";
    char out;
    sscanf(hex.c_str(), "%c", &out);
    int val;
    sscanf(hex.c_str(), "%i", &val);

    cout << hex  << " --> " << out << endl;
    cout << hex  << " --> " << char(val) << endl;

    return 0;
}
