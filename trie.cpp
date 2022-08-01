// File name: trie.cpp
// Name: Vanessa Miller


#include <iostream>
#include <cstddef> //for NULL
#include <cassert>
#include <new>
#include <fstream>
#include <string>
#include "trie.h"
using namespace std;

//Default Constructor
//post: a Trie is initialized
Trie::Trie()
{
	myRoot = new TrieNode(' ', false);
	assert(myRoot);
}

//Copy Constructor
//pre: a valid Trie is passed
//post: a new Trie is created that is a copy of the given Trie
Trie::Trie(const Trie& aTrie)
{
	if(aTrie.myRoot ==NULL)
	{
		myRoot = NULL;
	}
	else
	{
		myRoot = new TrieNode(*(aTrie.myRoot));
		assert(myRoot);
	}
}

//Destructor
//pre: the Trie exists
//post: the Trie is destroyed and any dynamic memory is returned to the system
Trie::~Trie()
{
	myRoot->~TrieNode();
	myRoot = NULL;
}

//Assignment Operator
// pre: A valid Trie is placed on the either side of an "=".
// post: The Trie on the right is copied to the Trie on the left.
const Trie& Trie::operator=(const Trie& aTrie)
{
	if(this!= &aTrie)
	{
		this->~Trie();
		if(aTrie.myRoot ==NULL)
		{
			myRoot = NULL;
		}
		else
		{
			myRoot = new TrieNode(*(aTrie.myRoot));
			assert(myRoot);
		}
	}
	return *this;
}

//insert
//pre: a valid string is passed
//post: string word is inserted into the Trie
void Trie::insert(string word)
{
	myRoot->insert(word);
}

//loadFromFile
//pre: a valid filename is passed
//post: all words in the file are inserted into the Trie
// This function will open the specified file, read all the words
// from the file, and insert each word into the Trie.
void Trie::loadFromFile(string filename)
{
	ifstream infile;
	infile.open(filename.c_str());    // open the file
	if (infile.fail()) {
	cout << "Error opening input file: " << filename << endl;
	exit(1);
	}

	string word;
	while (infile >> word) {        // extraction will fail when we hit eof
	insert(word);
	}

	infile.close();
}

//isWord
//pre: a valid string is passed
//post: returns true if the word is in the Trie, else returns false
bool Trie::isWord(string word) const
{
	return myRoot->isWord(word);
}

//isPrefix
//pre: a valid string is passed
//post: returns true if "pre" is a prefix of a word in the Trie, else returns false
bool Trie::isPrefix(string pre) const
{
	return myRoot->isPrefix(pre);
}

//print
//post: all words in the Trie are printed, one per line, in alphabetical order
void Trie::print()const
{
	myRoot->print("");
}

//wordCount
//post: all words in the Trie are counted and this number is returned
int Trie::wordCount()const
{
	return myRoot->wordCount();
}
