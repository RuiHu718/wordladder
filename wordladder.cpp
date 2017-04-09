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

using namespace std;

int main() {
  cout << "Welcome to CS 106B Word Ladder." << endl;
  cout << "Please give two English words, and I will change the" << endl;
  cout << "first into the second by changing one letter at a time" << endl;
  cout << endl;
  cout << endl;
  
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

  }


  cout << "Have a nice day." << endl;
  return 0;
}
