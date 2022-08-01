// File name: boggle.cpp
// Name: Vanessa Miller


#include <iostream>
#include <cstddef>
#include <cassert>
#include <new>
#include <string>
#include <fstream>
#include "trie.h"
using namespace std;



//isValidWord
//pre: A valid string is passed.
//post: If the word is valid according to the rules of boggle, true is returned, otherwise false is returned.
//      The word must be at least 4 letters, be defined in the lexicon, occur legally on the board, and have not already been found.
bool isValidWord(string word, const Trie &wordList, const Trie &lexicon)
{
	if(word.length()>=4 && lexicon.isWord(word) && !wordList.isWord(word))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//searchAndAdd - basic version
//This version of searchAndAdd is used to find all possible words in a given boggle configuration.
//pre: Two valid Tries, a board configuration, a string, two ints, and a bool array are passed.
//post: The given board configuration is searched and valid words are added to the first given Trie (our word list).
//		The words are checked against the second Trie (our lexicon). 
//		The user's first call should pass an empty string, an all-false bool array and 0 for both ints, if they intend to search the entire board.
void searchAndAdd(Trie &wordList, const Trie &lexicon, char board[4][4], string pre, int i, int j, bool boggleCheck[4][4])
{
	if (i>=0 && i<4 && j>=0 && j<4 && !boggleCheck[i][j]) //at a valid index
	{
		pre = pre + board[i][j];
		boggleCheck[i][j] = true;
		if(lexicon.isWord(pre))
		{
			if(isValidWord(pre, wordList, lexicon))
			{
				wordList.insert(pre);
			}
		}
		if(lexicon.isPrefix(pre))
		{
			searchAndAdd(wordList, lexicon, board, pre, i+1, j, boggleCheck); //one down
			searchAndAdd(wordList, lexicon, board, pre, i-1, j, boggleCheck); //one up
			searchAndAdd(wordList, lexicon, board, pre, i, j+1, boggleCheck); //one right
			searchAndAdd(wordList, lexicon, board, pre, i, j-1, boggleCheck); //one left
			searchAndAdd(wordList, lexicon, board, pre, i+1, j+1, boggleCheck); //one right and down
			searchAndAdd(wordList, lexicon, board, pre, i+1, j-1, boggleCheck); //one left and down
			searchAndAdd(wordList, lexicon, board, pre, i-1, j+1, boggleCheck); //one right and up
			searchAndAdd(wordList, lexicon, board, pre, i-1, j-1, boggleCheck); //one left and up
		}
		boggleCheck[i][j] = false;
	}
}

//searchAndAdd - competitive version
//This overloaded version of searchAndAdd is used by the computer during the boggle game. It does the same thing
//As the regular searchAndAdd, but it takes an extra parameter, another Trie (the user's list of words), to ensure 
//that the computer does not find words the user already found.
//pre: Three valid Tries, a board configuration, a string, two ints, and a bool array are passed.
//post: The given board configuration is searched and valid words are added to the second given Trie (our word list).
//		The words are checked against the first and third given Tries (the user's word list and the lexicon, respectively). 
//		The user's first call should pass an empty string, an all-false bool array and 0 for both ints, if they intend to search the entire board.
void searchAndAdd(const Trie &userWords, Trie &wordList, const Trie &lexicon, char board[4][4], string pre, int i, int j, bool boggleCheck[4][4])
{
	if (i>=0 && i<4 && j>=0 && j<4 && !boggleCheck[i][j]) //at a valid index
	{
		pre = pre + board[i][j];
		boggleCheck[i][j] = true;
		if(lexicon.isWord(pre))
		{
			if(isValidWord(pre, wordList, lexicon) && !userWords.isWord(pre))
			{
				wordList.insert(pre);
			}
		}
		if(lexicon.isPrefix(pre))
		{
			searchAndAdd(userWords, wordList, lexicon, board, pre, i+1, j, boggleCheck); //one down
			searchAndAdd(userWords, wordList, lexicon, board, pre, i-1, j, boggleCheck); //one up
			searchAndAdd(userWords, wordList, lexicon, board, pre, i, j+1, boggleCheck); //one right
			searchAndAdd(userWords, wordList, lexicon, board, pre, i, j-1, boggleCheck); //one left
			searchAndAdd(userWords, wordList, lexicon, board, pre, i+1, j+1, boggleCheck); //one right and down
			searchAndAdd(userWords, wordList, lexicon, board, pre, i+1, j-1, boggleCheck); //one left and down
			searchAndAdd(userWords, wordList, lexicon, board, pre, i-1, j+1, boggleCheck); //one right and up
			searchAndAdd(userWords, wordList, lexicon, board, pre, i-1, j-1, boggleCheck); //one left and up
		}
		boggleCheck[i][j] = false;
	}
}





int main()
{
	char input = 'y';
	while(input == 'y')
	{
		Trie lexicon, foundWords, userWords, possibleWords;
		lexicon.loadFromFile("ospd.txt");
		char boggleBoard[4][4];
		bool boggleCheck[4][4];

		//set the check array all to false
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				boggleCheck[i][j] = false;
			}
		}

		//read in boggle board configuration
		ifstream infile;
		string filename = "boggle.txt";
		infile.open(filename.c_str());    // open the file
		if (infile.fail()) 
		{
			cout << "Error opening input file: " << filename << endl;
			exit(1);
		}
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				infile >> boggleBoard[i][j];
			}
		}
		infile.close();

		//creates a reference list of possible words
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				searchAndAdd(possibleWords, lexicon, boggleBoard, "", i, j, boggleCheck);
			}
		}

		cout << " " << endl << "Welcome to the game of Boggle!" << endl;
		cout << "The board will be displayed below. Find all the words you can!" << endl;
		cout << "1. To enter a word, type in words one per line." << endl;
		cout << "2. When you are finished entering words, enter the single letter 'q' or 'Q'" << endl;
		cout << " " << endl;
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				cout << boggleBoard[i][j];
			}
			cout << endl;
		}
		cout << endl << "Begin entering words now!" << endl << " " << endl;
		string in;
		cin >> in;
		bool stillInputting = true;
		if(tolower(in[0]) == 'q' && in.length()== 1)
		{
			stillInputting = false;
		}
		while(stillInputting)
		{
			if(isValidWord(in, userWords, lexicon) && possibleWords.isWord(in))
			{
				userWords.insert(in);
			}
			else if(in.length()<4)
			{
				cout << "Error. Word is too short." << endl;
			}
			else if(userWords.isWord(in))
			{
				cout << "Error. You've already found that word." << endl;
			}
			else if(!lexicon.isWord(in))
			{
				cout << "Error. Not a valid word according to our dictionary." << endl;
			}
			else if(!possibleWords.isWord(in))
			{
				cout << "Error. Word doesn't occur legally on the board!" << endl;
			}
			cin >> in;
			if(tolower(in[0]) == 'q' && in.length()== 1)
			{
				stillInputting = false;
			}
		}

		//begin computer's search
		for(int i=0; i<4; i++)
		{
			for(int j=0; j<4; j++)
			{
				searchAndAdd(userWords, foundWords, lexicon, boggleBoard, "", i, j, boggleCheck);
			}
		}

		cout << endl;
		cout<< "Here are the words you found: " << endl;
		userWords.print();
		cout << " " << endl << userWords.wordCount() << " words found." << endl;
		cout<< " " << endl << "Here are the words the computer found: " << endl;
		foundWords.print();
		cout << " " << endl << foundWords.wordCount() << " words found." << endl << " " << endl;
		if(foundWords.wordCount()< userWords.wordCount())
		{
			cout << "You beat the computer!" << endl;
		}
		else if(foundWords.wordCount()> userWords.wordCount())
		{
			cout << "You lost to the computer." << endl;
		}
		else
		{
			cout << "You and the computer tied!" << endl;
		}
		cout << "Would you like to play again?" << endl;
		cout << "If so, enter 'y'" << endl;
		cin >> input;
		tolower(input);
	}
	return 0;
}