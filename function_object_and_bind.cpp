#include <functional>
#include <iostream>

using namespace std;

int main()
{
	// plus take two arguments _1 and 10
	auto plus10 = bind(plus<int>(), std::placeholders::_1, 10);

	// _1 is to be 7
	cout << "plus ten: " << plus10(7) << endl;

	// 'auto' means compile to automaticall deduce type, you can do 'auto x = 5;' for int - but dont do it
	// _1 and _2 are not needed to fully qualified by name space, hence _1 has left out, something about nameless namespace
	auto inversDivide = std::bind(std::divides<double>(),
                                  std::placeholders::_2,
                                  std::placeholders::_1);
    std::cout << "invdiv: " << inversDivide(7,49.5) << std::endl;

    // Bind on bind - two FO (function objects)
    auto plus10times2 = std::bind(std::multiplies<int>(),
                                  std::bind(std::plus<int>(),
                                            std::placeholders::_1,
                                            10),
                                  2);
    std::cout << "+10 *2: " << plus10times2(7) << std::endl;

	return 0;
}
