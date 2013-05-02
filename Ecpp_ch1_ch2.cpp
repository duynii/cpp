#include <iostream>
#include <sstream>
#include <exception>
#include <string>

using namespace std;


class Ch1 {
public:
    static const int _integral = 5; // static integral init 
    static string _static;

    Ch1() : _str("testing") {
    }

    void print() {
        cout << endl;
        cout << "_str: " << _str << endl;
        cout << "_static: " << _static << endl;
    }

    Ch1& operator=(const Ch1& rhs) {}
private:
    const string _str;
};


class Derived : public Ch1 {
public:
    //Default constructor, member initialisation list
    Derived() : Ch1(), _b(0) {}

    Derived(int a) : Ch1(), _b(a) {}

    // Copy constructor
    //  calls the parent's one
    Derived(const Derived& rhs) : Ch1(rhs), _b(rhs._b) {
        cout << "Derived copy ctor" << endl;
    }

    // Assignment operator
    //  calls the base's one
    Derived& operator=(const Derived& rhs) 
    {
        cout << "Derived's operator =" << endl;
        if(this == &rhs) return *this;

        Ch1::operator=(rhs);
        _b = rhs._b;
        return *this;
    }

    void print() {
        Ch1::print();
        cout << "_b: " << _b << endl; 
    }
private:
    int _b;
};

string Ch1::_static = "static string";

int main(int argc, char const * argv[])
{
    Ch1 ch;

    const char* const a = "const data const pointer";
    char const * b = "const data const pointer";
    char const c = 'c';
    b = "blah";

    ch.print();

    Ch1 obj2(ch);
    obj2.print();


    Derived d(4);
    d.print();

    Derived d2(d); // copy ctor
    d2.print();

    Derived d3 = d; // copy ctor

    Derived d4(10);
    d4 = d;
    d4.print();
    
    return 0;
}
