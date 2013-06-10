#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>   // for ofstream
#include <cstdio>    // for remove()

//taken from book
class FileDeleter
{
    private:
      std::string filename;
    public:
      FileDeleter (const std::string& fn)
       : filename(fn) {
      }
      void operator () (std::ofstream* fp) {
          fp->close();                   // close.file
          std::remove(filename.c_str()); // delete file
      }
};


using namespace std;

int main()
{

	shared_ptr<string> p1(new string("nicole"));
	auto p2 = make_shared<string>("huey");
	shared_ptr<int> p3(new int(5), [](int* p) { delete p;});
	shared_ptr<string> pNico(new string("nico"),
	                         [](string* p) {
	                             cout << "delete " << *p << endl;
	                             delete p;
	                         });

	unique_ptr<int[]> p4(new int[10]); //ok, has only [] operator for manipulation of array
	//shared_ptr<int[]> p5(new int[10]); NOT allowed	
	p4[0] = 5;

	//Gives up ownership and init new pointer
	p1.reset(new string("nicky"));
	p1.swap(p2); //swap

	// Must supply custom deleter as shared_ptr wont delete array correctly
	shared_ptr<int> p5(new int[10], [](int* p) { delete[] p;});



	cout << "str: " << *p1 <<endl;
	cout << "str: " << *p2 <<endl;
	cout << "str: " << *p3 <<endl;
	cout << "str: " << p4[0] <<endl;

	// create and open temporary file:
	std::shared_ptr<std::ofstream> fp(new std::ofstream("/tmp/tmpfile.txt"),
	                                      FileDeleter("/tmp/tmpfile.txt"));

	//Unique ptr
	// create and initialize (pointer to) string:
	std::unique_ptr<std::string> up(new std::string("nico"));

	(*up)[0] = 'N';                // replace first character
	up->append("lai");             // append some characters
	std::cout << *up << std::endl; // print whole string

	// Nothing in ptr
	std::unique_ptr<std::string> up2;
	//You can also assign the nullptr or call reset() :
	up2 = nullptr;
	up2.reset();

	//TRANSFER of ownership
	//auto up3(up2); //not possible
	auto up3(std::move(up));
	auto up4 = std::move(up3);
	cout << "unique: " << *up4 <<endl;


	//Unique_ptr array specialisation
	// only [] operator, no * or ->
	std::unique_ptr<std::string[]> up5(new std::string[10]);  // OK
	up5[0] = "test";
	cout  << "unique: " << up5[0] << endl;


}

