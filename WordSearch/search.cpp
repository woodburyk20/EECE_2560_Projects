// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan
//
// search.cpp
// Contains the search(int) driver function. Prompts the user for a grid
// file name, loads the dictionary and grid, sorts the dictionary using the
// algorithm selected by the integer parameter, and calls findMatches() to
// write all matched words to an output file.
//
// sortChoice values:
//   1 – selection sort
//   2 – quicksort
//   3 – heapsort

#include <iostream>
#include <string>
#include "dictionary.h"
#include "grid.h"

using namespace std;

void findMatches(const dictionary& dict, const grid& g,
                 const string& outputFileName);
// Searches the grid in all 8 directions for dictionary words and writes
// each match to outputFileName.

void search(int sortChoice)
// Drives the word search: loads the dictionary and grid, sorts the
// dictionary using the algorithm indicated by sortChoice, then finds and
// outputs all matches.
// sortChoice: 1 = selection sort, 2 = quicksort, 3 = heapsort
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
   if (sortChoice == 1)
   {
      cout << "Sorting with selection sort..." << endl;
      dict.selectionSort();
   }
   else if (sortChoice == 2)
   {
      cout << "Sorting with quicksort..." << endl;
      dict.quickSort();
   }
   else if (sortChoice == 3)
   {
      cout << "Sorting with heapsort..." << endl;
      dict.heapSort();
   }
   else
   {
      // Default to quicksort for any unrecognized value
      cout << "Unknown sort choice. Defaulting to quicksort..." << endl;
      dict.quickSort();
   } // end if

   // Search the grid and write all matching words to the output file
   findMatches(dict, g, outputFileName);

   cout << "Search complete. Results written to " << outputFileName << endl;

} // end search
