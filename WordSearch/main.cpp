// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// main.cpp
// Contains the search() driver function and main(). Prompts the user for
// a grid file name, loads the dictionary and grid, sorts the dictionary,
// and calls findMatches() to write all matched words to an output file.

#include <iostream>
#include <string>
#include "dictionary.h"
#include "grid.h"

using namespace std;

void findMatches(const dictionary& dict, const grid& g,
                 const string& outputFileName);
// Searches the grid in all 8 directions for dictionary words and writes
// each match to outputFileName.

void search()
// Drives the word search: loads the dictionary and grid, sorts the
// dictionary using selection sort, then finds and outputs all matches.
// Assumes: "Dictionary" and the user-supplied grid file exist in the
// current working directory.
{
   dictionary dict;
   grid g;

   string gridFileName;
   string dictionaryFileName = "Dictionary";
   string outputFileName = "output.txt";

   // Prompt the user for the grid input file
   cout << "Enter the grid file name: ";
   cin >> gridFileName;

   // Load words from the dictionary file and the grid from the grid file
   dict.readWords(dictionaryFileName);
   g.readGrid(gridFileName);

   // Sort dictionary words alphabetically to enable binary search
   dict.selectionSort();

   // Search the grid and write all matching words to the output file
   findMatches(dict, g, outputFileName);

   cout << "Search complete. Results written to " << outputFileName << endl;

} // end search

int main()
{
   search();
   return 0;

} // end main
