// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// dictionary.h
// Header file for the dictionary class. Declares a container for a list
// of words that supports reading from a file, selection sort, binary
// search, and output streaming.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class dictionary
{
public:
   dictionary();
   // Default constructor. Initializes an empty word list.

   void readWords(const string& filename);
   // Reads words from the file named filename into the word list,
   // one word per line.
   // Assumes: filename is a valid path to a readable text file.

   void selectionSort();
   // Sorts the word list in ascending lexicographic order using
   // selection sort.

   int binarySearch(const string& word) const;
   // Searches the sorted word list for word using binary search.
   // Returns the index of word if found, or -1 if not found.
   // Assumes: the word list has been sorted before calling this.

   int size() const;
   // Returns the number of words currently in the word list.

   friend ostream& operator<<(ostream& out, const dictionary& d);
   // Prints each word in the word list to out, one word per line.

private:
   vector<string> words;    // stores all words loaded from the file

}; // end class dictionary

#endif
