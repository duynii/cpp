#include <iostream>
#include <string>


using namespace std;

class base
{
  public:
         virtual void display(int i = 10)
         {
           cout<<"Base class display with i = "<<i<<endl;
         }
};

class A
{
int c;
public:
    A() : c(111) {}
    void show()
    {
        cout << "c value is : " << c << endl;
    }
};

class derived : public base, public A
{
  public:
         void display(int i)
         {
           cout<<"Derived class display with i = "<< i <<endl;
         }
};

int main(int argc, char *argv[])
{
    base *bptr = new derived;
    bptr->display();

    derived d;
    base* pbase = &d;

    A* a = dynamic_cast<A*>(pbase);

    cout << "Pointer value is: " << (a != NULL ? 1: 0) << endl;
    a->show();

    return 0;
}
