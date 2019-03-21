
#include "autocompleter.h"
#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

Autocompleter::Autocompleter(string filename) {
	ifstream f;
	f.open(filename);
	assert(f.is_open());
	string line;
	Entry A;

	while (getline(f, line))
	{
		bool done = false;

		string str_num = line.substr(line.find(',') + 1, line.size() - 1);
		A.s = line.substr(0, line.find(','));
		A.freq = std::stoi(str_num, nullptr, 10);
		if (root == nullptr) {
			root = new Node(A);
			TreeSize++;
		}
		else {
			Node * Current = root;
			while (done != true) {
				if (A.s < Current->e.s) {
					if (Current->left == nullptr) {
						Current->left = new Node(A);
						done = true;
						TreeSize++;
					}
					else
						Current = Current->left;
				}
				if (A.s > Current->e.s) {
					if (Current->right == nullptr) {
						Current->right = new Node(A);
						done = true;
						TreeSize++;
					}
					else
						Current = Current->right;
				}
			}
		}
	}
	f.close();
}

Autocompleter::Node *Autocompleter::insert(Node* node, string s, int freq) {

	if (node != nullptr) {
		if (s == node->e.s)
			return root;
		

		if (node->left != nullptr && s < node->e.s)
			insert(node->left, s, freq);

		if (node->right != nullptr && s > node->e.s)
			insert(node->right, s, freq);

		if (node->right == nullptr && s > node->e.s) {
			Entry A;
			A.s = s;
			A.freq = freq;
			node->right = new Node(A);
		}

		if (node->left == nullptr && s < node->e.s) {
			Entry A;
			A.s = s;
			A.freq = freq;
			node->left = new Node(A);
		}
	}

	return root;
}

string Autocompleter::completions(string x) {
	int l = x.length();
	bool done = false;
	Entry end;
	end.s = "a";
	Node * Current = root;

	if (Current != nullptr) {

		while (done != true) {
			if (x.substr(0, l) < Current->e.s.substr(0, l) && Current->left != nullptr) {
				Current = Current->left;
			}
			else if (x.substr(0, l) > Current->e.s.substr(0, l) && Current->right != nullptr) {
				Current = Current->right;
			}
			else if (x.substr(0, l) == Current->e.s.substr(0, l)) {
				end = Current->e;
				done = true;
			}
			else done = true;
			//cout << "hi5" << endl;
		}
		Node * Current2 = Current;
		done = false;

		while (done != true) {
			if (Current->e.freq > end.freq)
				end = Current->e;

			if (Current->left != nullptr && x.substr(0, l) == Current->e.s.substr(0, l)) {
				if (x.substr(0, l) == Current->left->e.s.substr(0, l)) {
					Current = Current->left;
					
				}
				else
					done = true;
			}
			else
				done = true;
		
		}
		done = false;
		while (done != true) {
			if (Current2->e.freq > end.freq)
				end = Current2->e;

			if (Current2->right != nullptr && x.substr(0, l) == Current2->e.s.substr(0, l)) {
				if (x.substr(0, l) == Current2->right->e.s.substr(0, l))
					Current2 = Current2->right;
				else done = true;
			}
			else
				done = true;
		}

	}
	return end.s;
}




