#include <iostream>
#include <sstream>
#include <exception>
#include <string>

using namespace std;

class Cpp {
protected:
    int  _v;

    const string _some;

    static int counter;
    static string _static_str;

public:
    Cpp() : _v(0), _some("thing") { counter++; }
    virtual ~Cpp() {
        cout << "Destructing in " << _v << endl;
        cout << "Instances: " << counter << endl;
        counter--;
    }

    Cpp(const Cpp& rhs) : _v(rhs._v), _some(rhs._some) {
        //_v = rhs._v;
        cout << "Cpp copy constructor" << endl;
    }

    Cpp& operator=(const Cpp& rhs) {
        cout << "Cpp assignment operator" << endl;
        if(this == &rhs) return *this;

        _v = rhs._v;
        return *this;
    }

    // Cannot do Cpp p = 3; must Cpp p(3)
    explicit Cpp(int val) : _v(val) { counter++; }

    // Prefix operator
    Cpp& operator++();
    // Postfix operator
    Cpp operator--(int);
    
    // conversion operator
    operator int() const { return _v; }

    // Friend function, global Cpp postfix --
    friend Cpp& operator--(Cpp& p);

    int getValue() const { return _v; }
};

int Cpp::counter = 0;
string Cpp::_static_str = "aaa";

Cpp& Cpp::operator++() {
    ++_v;
    return *this;
}

Cpp Cpp::operator--(int) {
    Cpp copy(getValue());
    --_v;
    return copy;
}

Cpp& operator--(Cpp& p) {
    p._v--;
    return p;   
}

//Templates
// Class with default type
template <class T=int, int SIZE=10> class Templ {
    protected:
        T _v;
        T _array[SIZE];
        int size;

    public:
        Templ() : _v(0), size(0) {}
        Templ(T val);

        operator string() { 
            ostringstream ss;
            ss << "Value is " << _v << " and size is " << size;
            return ss.str();
        }
};


template <class T, int SIZE> Templ<T,SIZE>::Templ(T val) : _v(val) {
    size = SIZE;
} 

//Specialisation
template <> Templ<char>::Templ(char val) {
    _v = int(val);
    size = 11;
    cout << "Specialised constructor used for type 'char'" << endl;
}


int main(int argc, char* argv[])
{
    cout << "Starting now..." << endl;

    Cpp dummy; // for instance counting
    Cpp obj(5);
    cout << "Prefix ++ after 5 is " << (++obj).getValue() << endl;
    cout << "Prefix for prefix -- is " << (obj--).getValue() << endl;
    cout << "Actual value by conversion operator is " << obj << endl;
    cout << "Prefix -- value is << " << --obj << endl;

    Templ<long, 20> templ(15);
    cout << "Template created: " << string(templ) << endl;

    // Use all template defaults
    Templ<> def(5);
    cout << "Template with default types: " << string(def) << endl;

    Templ<char> chTempl('a');
    cout << "Template for char created: " << string(chTempl) << endl;

    Cpp a(10);
    Cpp b = a;
    cout << "b value is " << b << endl;
    Cpp c;
    c = a;
    cout << "c value is " << c << endl;
    return 0;
}
