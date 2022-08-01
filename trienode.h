// File name: trienode.h
// Name: Vanessa Miller


#include <iostream>
#include <cstddef> //for NULL
#include <cassert>
#include <new>
using namespace std;

#ifndef TRIENODE_H
#define TRIENODE_H

class TrieNode
{
public:

	//Note, there is no default constructor

	//Constructor
	//pre: a valid char and bool are passed
	//post: a TrieNode is created with the given values
	TrieNode(char c, bool b);
	//Copy Constructor
	//pre: a valid TrieNode is passed
	//post: a new TrieNode is created and is identical to the given TrieNode
	TrieNode(const TrieNode& aNode);
	//Destructor
	//pre: a TrieNode exists
	//post: the TrieNode is destroyed and any dynamic memory is returned to the system
	~TrieNode();
	//Assignment Operator
	//pre: a valid TrieNode is placed on either side of an "="
	//post: the TrieNode on the right is copied to the TrieNode on the left
	const TrieNode& operator=(const TrieNode& aNode);
	//insert
	//pre: a valid string is passed
	//post: the string word is inserted, starting with the given TrieNode. 
	//		New TrieNodes are created as needed
	void insert(string word);
	//isWord
	//pre: a valid string is passed
	//post: returns true if the string word was in the sub-Trie starting at the given TrieNode, else returns false
	bool isWord(string word) const;
	//isPrefix
	//pre: a valid string is passed
	//post: returns true if "pre" is a prefix of a word in the sub-Trie starting at the given TrieNode, else returns false
	bool isPrefix(string pre) const;
	//print
	//pre: a valid string is passed
	//post: all words are printed to the screen, starting at the given TrieNode. 
	//     The string "pre" represents the letters of all ancestors of the given TrieNode.
	void print(string pre) const;
	//wordCount
	//post: all nodes in the sub-Trie that end a word are counted and the total is returned
	int wordCount() const;

	char myLetter; //The letter the Node holds
	bool endWord; //True if this node ends a word, otherwise false
	TrieNode* myArray[26]; //Array of pointers to next nodes

	typedef TrieNode* TrieNodePtr;

};
//#include "trienode.cpp"
#endif

