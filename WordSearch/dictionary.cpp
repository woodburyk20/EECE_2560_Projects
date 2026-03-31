// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// dictionary.cpp
// Implements the dictionary class. Provides word list management
// including file I/O, selection sort, quicksort, and binary search.

#include "dictionary.h"
#include "heap.h"

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

// ---------------------------------------------------------------------------
// Quicksort
// ---------------------------------------------------------------------------

int dictionary::partition(int lo, int hi)
// Partitions words[lo..hi] using words[hi] as the pivot (Lomuto scheme).
// Scans left to right; any element <= pivot is swapped into the left
// partition. The pivot is placed in its final sorted position at the end.
// Returns the index where the pivot was placed.
{
   string pivot = words[hi];
   int i = lo - 1;  // rightmost index of the left (<=pivot) partition

   for (int j = lo; j < hi; j++)
   {
      if (words[j] <= pivot)
      {
         i++;
         swap(words[i], words[j]);
      } // end if
   } // end for

   // Place pivot immediately after the left partition
   swap(words[i + 1], words[hi]);

   return i + 1;

} // end partition

void dictionary::quickSortHelper(int lo, int hi)
// Recursively sorts words[lo..hi] using partition().
// Base case: a subarray of size 0 or 1 is already sorted.
{
   if (lo < hi)
   {
      int pivotIdx = partition(lo, hi);

      quickSortHelper(lo, pivotIdx - 1);   // sort left of pivot
      quickSortHelper(pivotIdx + 1, hi);   // sort right of pivot

   } // end if

} // end quickSortHelper

void dictionary::quickSort()
// Sorts words in ascending lexicographic order using quicksort.
// Calls quickSortHelper() to perform the recursive sort over the
// full index range [0, size-1].
{
   if (words.empty())
      return;

   quickSortHelper(0, (int)words.size() - 1);

} // end quickSort

// ---------------------------------------------------------------------------

void dictionary::heapSort()
// Sorts words in ascending lexicographic order using heapsort.
// Creates a local heap<string>, loads the unsorted word list into it,
// runs heapSort(), then copies the sorted result back into words.
{
   heap<string> h;
   h.initializeMaxHeap(words);
   words = h.heapSort();

} // end heapSort

// ---------------------------------------------------------------------------

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
