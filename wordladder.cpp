// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "filelib.h"
#include "strlib.h"
#include "stack.h"
#include "queue.h"

using namespace std;

Stack<string> findLadder(string word_1, string word_2, const Lexicon &english);
Lexicon findNeighbors(string word, const Lexicon &english);

int main() {
  cout << "Welcome to CS 106B Word Ladder." << endl;
  cout << "Please give two English words, and I will change the" << endl;
  cout << "first into the second by changing one letter at a time" << endl;
  cout << endl;
  cout << endl;
  
  // load dictionary file
  string filename;
  Lexicon english;
  while (true) {
    cout << "Dictionary file name? ";
    filename = getLine();
    if (fileExists(filename)) {
      english.addWordsFromFile(filename);
      break;
    } else {
      cout << "Unable to open that file, try again " << endl;
    }
  }
  cout << endl;
  cout << endl;

  while (true) {
    cout << "Word #1 (or Enter to quit): ";
    string word_1 = getLine();
    if (word_1 == "") break;

    cout << "Word #2 (or Enter to quit): ";
    string word_2 = getLine();
    if (word_2 == "") break;

    //user input checking
    toLowerCaseInPlace(word_1);
    toLowerCaseInPlace(word_2);
    if (!english.contains(word_1) || !english.contains(word_2)) {
      cout << "the two words must be found in dictionary. " << endl;
      cout << endl;      
      continue;
    }
    if (word_1.length() != word_2.length()) {
      cout << "the two words must be the same length. " << endl;
      cout << endl;      
      continue;
    }
    if (word_1 == word_2) {
      cout << "the two words can't be the same. " << endl;
      cout << endl;      
      continue;
    }

    Stack<string> ladder = findLadder(word_1, word_2, english);

    // print out final results
    if (ladder.isEmpty()) {
      cout << "No ladder found between these two words. " << endl;
    } else {
      while (!ladder.isEmpty()) {
    	cout << ladder.pop() << " ";
      }
    }
    cout << endl;
  }

  cout << "Have a nice day." << endl;
  return 0;
}


/* Function: findLadder
 * Usage:    ladder = findLadder(string1, string2)
 * ------------------------------------------------
 * Finds the minimum length ladder between two English words
 * Use BFS algorithm specified by assignment handout
 * Precondition:
 * Postcondition:
 */
Stack<string> findLadder(string w1, string w2, const Lexicon &english) {
  //this is the main data structure
  Queue<Stack<string> > searchPath;
  Lexicon seenWords;
  Stack<string> current;


  Stack<string> initial;
  initial.push(w1);
  searchPath.enqueue(initial);
  seenWords.add(w1);

  while (!searchPath.isEmpty()) {
    current = searchPath.dequeue();
    Lexicon neighbors; // all enlish words that are one letter from givenword
    neighbors = findNeighbors(current.peek(), english); // where the bug was

    for (string word : neighbors) {
      //cout << word << " " ;
      if (!seenWords.contains(word)) {
	seenWords.add(word);
	if (word == w2) {
	  current.push(word);
	  return current;
	} else {
	  Stack<string> copy = current;
	  copy.push(word);
	  searchPath.enqueue(copy);
	}
      }
    }
  }

  Stack<string> empty;		// indicates no ladder found
  return empty;
}


/* Function: findNeightbors
 * Usage:    lex = findNeighbors(word)
 * -----------------------------------
 * Finds all the english words that are
 * One letter different from the given word
 * Precondition:
 * Postcondition:
 */
Lexicon findNeighbors(string word, const Lexicon &english) {
  Lexicon result;

  for (int i = 0; i < word.length(); i++) {
    for (int j = 0; j < 26; j++) {
      char current = 'a' + j;
      string temp = word.substr(0, i) + current + word.substr(i+1);
      if (english.contains(temp)) {
	result.add(temp);
      }
    }
  }
  return result;
}
