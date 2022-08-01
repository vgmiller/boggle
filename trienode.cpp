// File name: trienode.cpp
// Name: Vanessa Miller


#include <iostream>
#include <cstddef> //for NULL
#include <cassert>
#include <new>
#include <string>
#include "trienode.h"
using namespace std;

//Note, there is no default constructor

//Constructor
//pre: a valid char and bool are passed
//post: a TrieNode is created with the given values
TrieNode::TrieNode(char c, bool b)
{
	myLetter = tolower(c);
	endWord = b;
	for(int i=0; i<26; i++)
	{
		myArray[i] = NULL;
	}
}

//Copy Constructor
//pre: a valid TrieNode is passed
//post: a new TrieNode is created and is identical to the given TrieNode
TrieNode::TrieNode(const TrieNode& aNode)
{
	myLetter = aNode.myLetter;
	endWord = aNode.endWord;
	for(int i=0; i<26; i++)
	{
		if(aNode.myArray[i]!=NULL)
		{
			myArray[i] = new TrieNode(*(aNode.myArray[i]));
			assert(myArray[i]);
		}
		else
		{
			myArray[i] =NULL;
		}
	}
}

//Destructor
//pre: a TrieNode exists
//post: the TrieNode is destroyed and any dynamic memory is returned to the system
TrieNode::~TrieNode()
{
	for(int i=0; i<26; i++)
	{
		if(myArray[i] != NULL)
		{
		delete myArray[i];
		myArray[i] = NULL;
		}
	}
}

//Assignment Operator
//pre: a valid TrieNode is placed on either side of an "="
//post: the TrieNode on the right is copied to the TrieNode on the left
const TrieNode& TrieNode::operator=(const TrieNode& aNode)
{
	if(this != &aNode) //check for self assignment
	{
		this->~TrieNode(); //call to clean up

		myLetter = aNode.myLetter;
		endWord = aNode.endWord;
		for(int i=0; i<26; i++)
		{
			if(aNode.myArray[i]!=NULL)
			{
				myArray[i] = new TrieNode(*(aNode.myArray[i]));
				assert(myArray[i]);
			}
			else
			{
				myArray[i] = NULL;
			}
		}
	}
	return *this;
}

//insert
//pre: a valid string is passed
//post: the string word is inserted, starting with the given TrieNode. 
//		New TrieNodes are created as needed
void TrieNode::insert(string word)
{
	if(word.length()>=1)
	{
	for(int i=0; i<(int)word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	if(!isWord(word))
	{
		if(isPrefix(word))
		{
			TrieNodePtr temp = this;
			for(int i=0; i<(int)word.length(); i++)
			{
				temp = temp->myArray[word[i]-'a'];
			}
			temp->endWord = true;
			temp = NULL;
		}
		else
		{
			TrieNodePtr temp = this;
			for(int i=0; i<(int)word.length(); i++)
			{
				if(temp->myArray[word[i] - 'a'] != NULL)
				{
					temp = temp->myArray[word[i]-'a'];
				}
				else
				{
					temp->myArray[word[i]-'a'] = new TrieNode(word[i], false);
					temp = temp->myArray[word[i]-'a'];
				}
			}
			temp->endWord = true;
			temp = NULL;
		}
	}
}
}

//isWord
//pre: a valid string is passed
//post: returns true if the string word was in the sub-Trie starting at the given TrieNode, else returns false
bool TrieNode::isWord(string word) const
{
	if(word.length()>=1)
	{
	for(int i=0; i<(int)word.length(); i++)
	{
		word[i] = tolower(word[i]);
	}
	int i=0;
	TrieNodePtr temp = this->myArray[word[i]-'a']; //points to next node
	if(temp != NULL && temp->myLetter==word[i] && i<(int)word.length())
	{
		i++;
		while(i<(int)word.length() && temp->myArray[word[i]-'a'] != NULL && temp->myArray[word[i]-'a']->myLetter==word[i])
		{
			temp = temp->myArray[word[i]-'a'];
			i++;
		}
	}
	if(i==(int)word.length() && temp->endWord)
	{
		temp = NULL;
		return true;
	}
	else
	{
		temp = NULL;
		return false;
	}
	}
	return false;
}

//isPrefix
//pre: a valid string is passed
//post: returns true if "pre" is a prefix of a word in the sub-Trie starting at the given TrieNode, else returns false
bool TrieNode::isPrefix(string pre) const
{
	if(pre.length()>=1)
	{
	for(int i=0; i<(int)pre.length(); i++)
	{
		pre[i] = tolower(pre[i]);
	}
	int i=0;
	TrieNodePtr temp = this->myArray[pre[i]-'a']; //points to next node
	if(temp != NULL && temp->myLetter==pre[i] && i<(int)pre.length())
	{
		i++;
		while(i<(int)pre.length() && temp->myArray[pre[i]-'a'] != NULL && temp->myArray[pre[i]-'a']->myLetter==pre[i])
		{
			temp = temp->myArray[pre[i]-'a'];
			i++;
		}
	}
	if(i==(int)pre.length())
	{
		temp = NULL;
		return true;
	}
	else
	{
		temp = NULL;
		return false;
	}
	}
	return false;
}

//print
//pre: a valid string is passed
//post: all words are printed to the screen, starting at the given TrieNode. 
//     The string "pre" represents the letters of all ancestors of the given TrieNode.
void TrieNode::print(string pre) const
{
	for(int i=0; i<(int)pre.length(); i++)
	{
		pre[i] = tolower(pre[i]);
	}
	for(int i=0; i<26; i++)
	{
		if(myArray[i]!=NULL)
		{
			if(myArray[i]->endWord)
			{
				cout << pre + myArray[i]->myLetter<< endl;
			}
			myArray[i]->print(pre + myArray[i]->myLetter);
		}
	}
}

//wordCount
//post: all nodes in the sub-Trie that end a word are counted and the total is returned
int TrieNode::wordCount() const
{
	int count = 0;
	if(endWord)
	{
		count++;
	}
	for(int i = 0; i<26; i++)
	{
		if(myArray[i] != NULL)
		{
			count = count + myArray[i]->wordCount();
		}
	}
	return count;
}
