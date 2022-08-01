// File name: trie.h
// Name: Vanessa Miller


#include <iostream>
#include <cstddef> //for NULL
#include <cassert>
#include <new>
#include "trienode.h"
using namespace std;

#ifndef TRIE_H
#define TRIE_H

class Trie
{
public:

	//Default Constructor
	//post: a Trie is initialized
	Trie();
	//Copy Constructor
	//pre: a valid Trie is passed
	//post: a new Trie is created that is a copy of the given Trie
	Trie(const Trie& aTrie);
	//Destructor
	//pre: the Trie exists
	//post: the Trie is destroyed and any dynamic memory is returned to the system
	~Trie();
	//Assignment Operator
	// pre: A valid Trie is placed on the either side of an "=".
	// post: The Trie on the right is copied to the Trie on the left.
	const Trie& operator=(const Trie& aTrie);
	//insert
	//pre: a valid string is passed
	//post: string word is inserted into the Trie
	void insert(string word);
	//loadFromFile
	//pre: a valid filename is passed
	//post: all words in the file are inserted into the Trie
	void loadFromFile(string filename);
	//isWord
	//pre: a valid string is passed
	//post: returns true if the word is in the Trie, else returns false
	bool isWord(string word) const;
	//isPrefix
	//pre: a valid string is passed
	//post: returns true if "pre" is a prefix of a word in the Trie, else returns false
	bool isPrefix(string pre) const;
	//print
	//post: all words in the Trie are printed, one per line, in alphabetical order
	void print()const;
	//wordCount
	//post: all words in the Trie are counted and this number is returned
	int wordCount()const;

private:

	typedef TrieNode* TrieNodePtr;
	TrieNodePtr myRoot;
};
//#include "trie.cpp"
#endif
