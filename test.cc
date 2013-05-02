#include <iostream>
#include <sstream>
#include <exception>
#include <string>

#include <iostream>

using namespace std;

struct Foo {
    Foo(int i) { std::cout << "i"; }
    Foo(char c) { std::cout << "c"; }
    Foo(long l) { std::cout << "l"; }
    Foo(float f) { std::cout << "f"; }
};

class A {
    int _a;

public:
    A(int a) : _a(a) {}

    void print() const
    {
        cout << "\na: " << _a << endl;
    }

};

int main()
{
    Foo f1('a');
    Foo f2('a' + 1);
    Foo f3(1);
    Foo f4(0x01);
    Foo f5(0x0001L);
    Foo f6(1.0f);

    const A& obj = A(4);

    obj.print();

    return 0;
}

