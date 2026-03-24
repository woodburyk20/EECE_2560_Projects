// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// dictionary.cpp
// Implements the dictionary class. Provides word list management
// including file I/O, selection sort, and binary search.

#include "dictionary.h"

dictionary::dictionary()
// Default constructor. No initialization needed beyond the empty vector.
{
} // end constructor

void dictionary::readWords(const string& filename)
// Opens filename and reads each whitespace-delimited token into words.
// Prints an error message and returns early if the file cannot be opened.
// Assumes: filename points to a plain text file with one word per line.
{
   ifstream inFile(filename);

   if (!inFile.is_open())
   {
      cout << "Error opening dictionary file." << endl;
      return;
   } // end if

   string word;

   // Read every word token until end of file
   while (inFile >> word)
   {
      words.push_back(word);
   } // end while

   inFile.close();

} // end readWords

void dictionary::selectionSort()
// Sorts words in place in ascending lexicographic order using
// selection sort. On each pass, finds the minimum element in the
// unsorted suffix and swaps it into position.
{
   int n = (int)words.size();

   for (int i = 0; i < n - 1; i++)
   {
      // Find the index of the smallest word in words[i..n-1]
      int minIdx = i;

      for (int j = i + 1; j < n; j++)
      {
         if (words[j] < words[minIdx])
            minIdx = j;
      } // end for

      // Swap the minimum word into the sorted position
      if (minIdx != i)
         swap(words[i], words[minIdx]);

   } // end for

} // end selectionSort

int dictionary::binarySearch(const string& word) const
// Searches the sorted word list for word using binary search.
// Returns the index of the matching word, or -1 if not found.
// Assumes: words has been sorted in ascending order before calling.
{
   int lo = 0, hi = (int)words.size() - 1;

   while (lo <= hi)
   {
      int mid = lo + (hi - lo) / 2;

      if (words[mid] == word)
         return mid;
      else if (words[mid] < word)
         lo = mid + 1;
      else
         hi = mid - 1;

   } // end while

   return -1;

} // end binarySearch

int dictionary::size() const
// Returns the number of words in the word list.
{
   return (int)words.size();

} // end size

ostream& operator<<(ostream& out, const dictionary& d)
// Prints every word in d to out, one word per line.
{
   for (int i = 0; i < (int)d.words.size(); i++)
   {
      out << d.words[i] << endl;
   } // end for

   return out;

} // end operator<<
