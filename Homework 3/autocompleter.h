//
//  autocompleterx.h
//  home
//
//  Created by Jingru Zhang on 2/13/19.
//  Copyright © 2019 Jingru Zhang. All rights reserved.
//


#ifndef AUTOCOMPLETER_H
#define AUTOCOMPLETER_H

#include <vector>
#include <string>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;

class Autocompleter
{
    
private:
    // A helper class that stores a string and a frequency.
    struct Entry
    {
    public:
        string s;
        int freq;
    };
    
    // A helper class that implements a BST node.
    class Node
    {
    public:
        Node()
        {
            left = right = nullptr;
        }
        
        Node(Entry e)
        {
            this->e = e;
            left = right = nullptr;
        }
        Node(Entry e, Node* left, Node* right)
        {
            this->e = e;
            left = left;
            right = right;
        }
        
        Entry e;
        Node* left;
        Node* right;
    };
    
    Node* root;
    int TreeSize; //the size of the tree
    
public:
    // Creates a dictionary of strings and associated frequencies,
    // using the file as a source. The file is promised to have
    // the following format:
    //
    // string1,freq1
    // string2,freq2
    // ...
    // stringN,freqN
    //
    // where string1 < string2 < ... < stringN
    //
    // Must run in O(n) time.
    // update the size of the tree
    Autocompleter(string filename);
    
    ~Autocompleter(){free(root);}
    //insert a node to your BST
    // Must run in O(\log n) time
    // remember to update the size of the tree
    void insert(string s, int freq)
    {
		
        root = insert(root, s, freq);
		
        TreeSize++;
    }
    
    
    //insert a node of string s and frequence freq to your BST
    // Must run in O(\log n) time
    Node * insert(Node* node, string s, int freq);
    
    // Returns the number of strings in the dictionary
    //
    // Must run in O(1) time.
    
    int size(){return TreeSize; }
    
    // return the most frequent string which contains prefix x
    // Must run in O(log(n) + k) time,
    // where k is the number of strings with perfix x in the dictionary.
    string completions(string x);
    
    
};


#endif

