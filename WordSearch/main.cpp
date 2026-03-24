// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan
//
// main.cpp
// Contains the search driver function and main.

#include <iostream>
#include <string>
#include "dictionary.h"
#include "grid.h"

using namespace std;

void findMatches(const dictionary& dict, const grid& g, const string& outputFileName);

void search() {
    dictionary dict;
    grid g;

    string gridFileName;
    string dictionaryFileName = "dictionary.txt";
    string outputFileName = "output.txt";

    // Ask user for the grid file name
    cout << "Enter the grid file name: ";
    cin >> gridFileName;

    // Read dictionary and grid data
    dict.readWords(dictionaryFileName);
    g.readGrid(gridFileName);

    // Sort dictionary words before binary search
    dict.selectionSort();

    // Find and print all matches to the output file
    findMatches(dict, g, outputFileName);

    cout << "Search complete. Results written to " << outputFileName << endl;
} //endif

int main() {
    search();
    return 0;
} //endif