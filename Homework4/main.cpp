
#include <fstream>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "autocompleter.h"

using namespace std;


inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
	abort();
}
#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


void interactive_mode()
{
	Autocompleter words;

	ifstream f;
	f.open("words2.txt");
	assert(f.is_open()); // If this fails, you're missing words2.txt
	string line;
	int i = 0;
	while (getline(f, line))
	{
		words.insert(line.substr(0, line.find_last_of(" ")),
			stoi(line.substr(line.find_last_of(" ") + 1)));
		++i;
	}
	f.close();
	assert(i == 293147); // If this fails, words2.txt is wrong
	
	vector<string> C;
	while (cin)
	{
		string line;
		getline(cin, line);
		words.completions(line, C);
		for (string s : C)
			cout << "    " << s << endl;
	}
	exit(0);
}

int main()
{
	// Uncomment line below to use your Autocompleter 
	// interactively with words2.txt as the dictionary.
	// 
	// Enter a string and press Enter - the autocompletions
	// results from words.txt are printed.
	// 
	//interactive_mode();


	// Setup
	vector<string> R;
	

	// Test constructor and size()
	Autocompleter animals;
	test(animals.size() == 0);
	
	animals.insert("aardvark", 629356);
	animals.insert("albatross", 553191);
	animals.insert("alpaca", 852363);
	animals.insert("armadillo", 393754);
	animals.insert("crow", 4592109);
	animals.insert("crocodile", 1658300);
	animals.insert("cat", 46839855);
	animals.insert("camel", 11005001);
	animals.insert("goat", 5231735);
	animals.insert("gorilla", 1931906);
	animals.insert("goose", 3739382);
	animals.insert("goatfish", 19984);
	animals.insert("giraffe", 978584);

	test(animals.size() == 13);

	animals.insert("buffalo", 17808542);

	test(animals.size() == 14);

	animals.insert("deer", 10007644);
	test(animals.size() == 15);

	animals.insert("horse", 58453720);
	test(animals.size() == 16);

	animals.insert("bullfrog", 273571);
	test(animals.size() == 17);



	cout << "The frequence of goose is " << animals.query("goose") << endl;

	animals.freqReplace("goose", 4850493);

	cout << "Now the frequence of goose is " << animals.query("goose") << endl;



	cout << "The frequence of alpaca is " << animals.query("alpaca") << endl;

	animals.freqReplace("alpaca", 741252);

	cout << "Now the frequence of alpaca is " << animals.query("alpaca") << endl;


	animals.completions("go", R);
	test(R.size() == 3);
	test(R[0] == "goat");
	test(R[1] == "goose");
	test(R[2] == "gorilla");
	
	animals.completions("cro", R);
	test(R.size() == 2);
	test(R[0] == "crow");
	test(R[1] == "crocodile");

	animals.completions("goat", R);
	test(R.size() == 2);
	test(R[0] == "goat");
	test(R[1] == "goatfish");

	animals.completions("gir", R);
	test(R.size() == 1);
	test(R[0] == "giraffe");

	animals.completions("croc", R);
	test(R.size() == 1);
	test(R[0] == "crocodile");

	animals.completions("crow", R);
	test(R.size() == 1);
	test(R[0] == "crow");

	animals.completions("", R);
	test(R.size() == 3);
	test(R[0] == "horse");
	test(R[1] == "cat");
	test(R[2] == "buffalo");

	/* done with test on animals */



	Autocompleter words;
	test(words.size() == 0);

	ifstream f("words2.txt");
	
	assert(f.is_open()); // If this fails, you're missing words2.txt
	string line;
	while (getline(f, line))
	{
		words.insert(line.substr(0, line.find_last_of(" ")),
			stoi(line.substr(line.find_last_of(" ") + 1)));
	}
	f.close();
	test(words.size() == 293147);


	words.completions("b", R);
	test(R.size() == 3);
	test(R[0] == "by");
	test(R[1] == "be");
	test(R[2] == "but");

	words.completions("!", R);
	test(R.size() == 0);

	words.completions("ba", R);
	test(R.size() == 3);
	test(R[0] == "back");
	test(R[1] == "based");
	test(R[2] == "baby");

	words.completions("be", R);
	test(R.size() == 3);
	test(R[0] == "be");
	test(R[1] == "been");
	test(R[2] == "best");

	words.completions("th", R);
	test(R.size() == 3);
	test(R[0] == "the");
	test(R[1] == "that");
	test(R[2] == "this");

	words.completions("aft", R);
	test(R.size() == 3);
	test(R[0] == "after");
	test(R[1] == "afternoon");
	test(R[2] == "afterwards");

	words.completions("cat", R);
	test(R.size() == 3);
	test(R[0] == "categories");
	test(R[1] == "category");
	test(R[2] == "catalog");

	words.completions("syz", R);
	test(R.size() == 3);
	test(R[0] == "syzygy");
	test(R[1] == "syzygium");
	test(R[2] == "syzhthsh");

	words.completions("sy$", R);
	test(R.size() == 0);

	words.completions("bird", R);
	test(R.size() == 3);
	test(R[0] == "bird");
	test(R[1] == "birds");
	test(R[2] == "birding");

	words.completions("hola", R);
	test(R.size() == 3);
	test(R[0] == "hola");
	test(R[1] == "holabird");
	test(R[2] == "holanda");

	words.completions("word", R);
	test(R.size() == 3);
	test(R[0] == "word");
	test(R[1] == "words");
	test(R[2] == "wordpress");

	words.completions("birdz", R);
	test(R.size() == 0);

	words.completions("yello", R);
	test(R.size() == 3);
	test(R[0] == "yellow");
	test(R[1] == "yellowstone");
	test(R[2] == "yellowpages");


	cout << "The frequence of words is " << words.query("words") << endl;

	words.freqReplace("words", 1962);

	cout << "Now the frequence of words is " << words.query("words") << endl;



	cout << "The frequence of linguist is " << words.query("linguist") << endl;

	words.freqReplace("linguist", 2233);

	cout << "Now the frequence of linguist is " << words.query("linguist") << endl;


	cout << "Assignment complete." << endl;

	system("pause");

}