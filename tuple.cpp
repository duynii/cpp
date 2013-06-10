#include <utility>
#include <tuple>
#include <string>
#include <complex>
#include <iostream>
#include <functional>

using namespace std;


int main()
{
	auto tmp = make_tuple(1, 2.1, string("test"));	

	cout << "int: " << get<0>(tmp) << endl;
	cout << "double: " << get<1>(tmp) << endl;
	cout << "string: " << get<2>(tmp) << endl;

	// Explicit initialisation for fundamental types eg.  = int() means = int(0)
	tuple<double> k;
	cout << "double: " << get<0>(k) << endl;

	// create a four-element tuple
    // - elements are initialized with default value (0 for fundamental types)
    tuple<string,int,int,complex<double>> t;

    // create and initialize a tuple explicitly
    tuple<int,float,string> t1(1,6.3,"nico");

    // ''iterate'' over elements:
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    // create tuple with make_tuple()
    // - auto declares t2 with type of right-hand side
    // - thus, type of t2 is tuple
    auto t2 = make_tuple(22,44,"nicole");

    // assign second value in t2 to t1
    get<1>(t1) = get<1>(t2);

    // comparison and assignment
    // - including type conversion from tuple<int,int,const char*>
    //   to tuple<int,float,string>
    if (t1 < t2) {  // compares value for value
        t1 = t2;    // OK, assigns value for value
        //position 1 has higher priority than position 2 for comparison
    }

    // ''iterate'' over elements:
    cout << get<0>(t1) << " ";
    cout << get<1>(t1) << " ";
    cout << get<2>(t1) << " ";
    cout << endl;

    int i;
    float f;
    std::string s;
    // assign values of t to i, f, and s:
    // Create a tuple with three references, so i, f and s are assigned value of t tuple 
    std::make_tuple(std::ref(i),std::ref(f),std::ref(s)) = t1;
    cout << i << " ";
    cout << f << " ";
    cout << s << " ";
    cout << endl;
}