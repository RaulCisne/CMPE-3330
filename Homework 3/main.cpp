
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include "autocompleter.h"

using namespace std;


inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}
#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))

int main()
{

	Autocompleter animals("animals.txt");

	test(animals.size() == 13);


	// Test completions()
	std::cout << animals.completions("a") << endl;
	//test(R[0] == "alpaca");
	
	std::cout << animals.completions("c") << endl;
	//test(R[0] == "cat");
	
	std::cout << animals.completions("g") << endl;
	//test(R[0] == "goat");

	std::cout << animals.completions("aa") << endl;
	//test(R[0] == "aardvark");

	std::cout << animals.completions("al") << endl;
	//test(R[0] == "alpaca");

	std::cout << animals.completions("go") << endl;
	//test(R[0] == "goat");

	std::cout << animals.completions("cro") << endl;
	//test(R[0] == "crow");

	std::cout << animals.completions("goat") << endl;
	//test(R[0] == "goat");

	std::cout << animals.completions("gir") << endl;
	//test{giraffe}
	animals.insert("bufflo", 17808542);

	test(animals.size() == 14);

	std::cout << animals.completions("b") << endl;



	cout << "Assignment complete." << endl;
	system("pause");
}



