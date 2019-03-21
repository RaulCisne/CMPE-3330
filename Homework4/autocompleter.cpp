//Raul Cisneros
//Abner Campos

#include "autocompleter.h"
#include <fstream>
#include <vector>
#include <iostream>

// Creates a new Autocompleter with an empty dictionary.
//
// Must run in O(1) time.
Autocompleter::Autocompleter() {
	root = new Node();
	count = 0;

}

// Adds a string x to the dictionary.
// If x is already in the dictionary, does nothing.
//
// Must run in O(1) time.
void Autocompleter::insert(string x, int freq) {

	int i = 0;
	Node* current = root;

	Entry n;
	n.s = x;
	n.freq = freq;

	while (i < x.length()) {
		//Insert the word as top three and compare and do shifting
		top_three(current, n);

		if (current->children[x[i] - 'a'] == nullptr) {
			//If the path didn't exist yet,
			current->children[x[i] - 'a'] = new Node();

		}

		current = current->children[x[i] - 'a']; //points to next node
		i++; //move to next char
	}

	current->marked = true; //mark true
	current->markedFreq = freq;
	count++; //Update Number of marked nodes

	top_three(current, n);

}

// Returns the number of strings in the dictionary.
//
// Must run in O(1) time.
int Autocompleter::size() {
	return count;
}

// Fills the vector T with the three most-frequent completions of x.
// If x has less than three completions, then
// T is filled with all completions of x.
// The completions appear in T from most to least frequent.
//
// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string> &T) {
	T.clear();
	Node* curr = root;
	for (int i = 0; i < x.length(); i++) {
		curr = curr->children[x[i] - 'a'];

		if (curr == NULL) {
			return;
		}
	}

	for (int j = 0; j < curr->top.size(); j++) {
		T.push_back(curr->top[j].s);

		if (T.size() == 3) {
			break;
		}
	}
}




// query the frequence of the given word
// Must run in O(1) time.
int Autocompleter::query(string x) {
	int i = 0;
	Node* current = root;

	while (i < x.length()) {
		if (current->children[x[i] - 'a'] == nullptr)
			return -1;

		current = current->children[x[i] - 'a']; //points to next node
		i++;
	}

	if (current->marked == false)
		return -1;
	else
		return current->markedFreq;
}


// replace the frequence of the word x in trie.
// Must run in O(1) time.
void Autocompleter::freqReplace(string x, int freq) {
	
	 int i = 0;
	 Node* current = root;

	 while (i < x.length()) {

		 for (int b = 0; b < current->top.size(); b++) {
			 if (x == current->top[b].s)
				 current->top[b].freq = freq;
		 }

		 current = current->children[x[i]-'a']; //points to next node
		 i++; //move to next char
	 }

	 current->markedFreq = freq;
	 
}

//Helper function to sort top three runs O(1)
void Autocompleter::top_three(Node* current, Entry n) {
	if (current->top.size() == 0) {
		current->top.push_back(n);
	}
	else if (current->top.size() == 1) {
		if (current->top[0].freq < n.freq) {
			current->top.push_back(current->top[0]);
			current->top[0] = n;
		}
		else {
			current->top.push_back(n);
		}
	}
	else if (current->top.size() == 2) {
		if (current->top[0].freq < n.freq) {
			Entry temp = current->top[0];
			current->top.push_back(current->top[1]);
			current->top[0] = n;
			current->top[1] = temp;
		}
		else if (current->top[1].freq < n.freq) {
			current->top.push_back(current->top[1]);
			current->top[1] = n;
		}
		else {
			current->top.push_back(n);
		}
	}
	else if (current->top.size() == 3) {
		if (current->top[0].freq < n.freq) {
			for (int i = 2; i > 0; i--) {
				current->top[i] = current->top[i - 1];
			}
			current->top[0] = n;
		}
		else if (current->top[1].freq < n.freq) {
			for (int i = 2; i < 3; i++) {
				current->top[i] = current->top[i - 1];
			}
			current->top[1] = n;
		}
		else if (current->top[2].freq < n.freq) {
			current->top[2] = n;
		}
	}
}



