// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan
//
// main.cpp
// Entry point. Prompts the user to select a sorting algorithm, then
// calls search(int) to run the word search.

#include <iostream>

using namespace std;

void search(int sortChoice);
// Drives the word search: loads the dictionary and grid, sorts the
// dictionary using the algorithm indicated by sortChoice, then finds
// and outputs all matches.
// sortChoice: 1 = selection sort, 2 = quicksort, 3 = heapsort

int main()
{
   int sortChoice;

   cout << "Select sorting algorithm:" << endl;
   cout << "  1 - Selection sort" << endl;
   cout << "  2 - Quicksort" << endl;
   cout << "  3 - Heapsort" << endl;
   cout << "Enter choice: ";
   cin >> sortChoice;

   search(sortChoice);

   return 0;

} // end main
