// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan
//
// heap.h
// Template class heap<T> that stores objects in a max-heap backed by a
// vector<T>.  Provides heap navigation helpers, max-heap construction,
// and heapsort.  Template method bodies are defined here because the
// compiler needs the full definition at each instantiation site.
//
// Bonus: templated on T so it works for any comparable type.

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

using namespace std;

// ---------------------------------------------------------------------------
// Template class heap<T>
// ---------------------------------------------------------------------------

template <typename T>
class heap
{
public:

   // --- Navigation helpers  ----------------------------------------

   int parent(int i) const;
   // Returns the index of node i's parent in the heap array.
   // Precondition: i > 0.

   int left(int i) const;
   // Returns the index of node i's left child.

   int right(int i) const;
   // Returns the index of node i's right child.

   T getItem(int n) const;
   // Returns the element stored at index n in the heap array.

   // --- Max-heap construction  -------------------------------------

   void initializeMaxHeap(vector<T> v);
   // Copies v into the internal array and builds a max-heap via
   // buildMaxHeap().

   void maxHeapify(int i);
   // Restores the max-heap property at index i by sifting downward.
   // Precondition: the subtrees rooted at left(i) and right(i) are
   // already valid max-heaps.

   void buildMaxHeap();
   // Converts data[0..heapSize-1] into a max-heap by calling maxHeapify
   // on every non-leaf node in bottom-up order.

   // --- Sorting -------------------------------------------------------

   vector<T> heapSort();
   // Sorts the internal array in ascending order and returns the sorted
   // vector.  Builds a max-heap then repeatedly extracts the maximum.

private:
   vector<T> data;   // backing store for the heap
   int heapSize;     // number of elements currently active in the heap

}; // end class heap<T>

// ---------------------------------------------------------------------------
// Method definitions
// ---------------------------------------------------------------------------

template <typename T>
int heap<T>::parent(int i) const
// Returns floor((i-1)/2), the parent index of node i.
{
   return (i - 1) / 2;

} // end parent

template <typename T>
int heap<T>::left(int i) const
// Returns 2*i + 1, the left-child index of node i.
{
   return 2 * i + 1;

} // end left

template <typename T>
int heap<T>::right(int i) const
// Returns 2*i + 2, the right-child index of node i.
{
   return 2 * i + 2;

} // end right

template <typename T>
T heap<T>::getItem(int n) const
// Returns the element at index n in the heap array.
{
   return data[n];

} // end getItem

template <typename T>
void heap<T>::initializeMaxHeap(vector<T> v)
// Copies v into data, sets heapSize to v.size(), then builds the max-heap.
{
   data = v;
   heapSize = (int)data.size();
   buildMaxHeap();

} // end initializeMaxHeap

template <typename T>
void heap<T>::maxHeapify(int i)
// Sifts the element at index i downward to restore the max-heap property.
// Finds the largest value among node i and its children, swaps it to
// position i, then recurses on the displaced child if a swap occurred.
{
   int l = left(i);
   int r = right(i);
   int largest = i;

   if (l < heapSize && data[l] > data[largest])
      largest = l;

   if (r < heapSize && data[r] > data[largest])
      largest = r;

   if (largest != i)
   {
      swap(data[i], data[largest]);
      maxHeapify(largest);

   } // end if

} // end maxHeapify

template <typename T>
void heap<T>::buildMaxHeap()
// Builds a max-heap from data[0..heapSize-1].
// Leaves are trivial heaps; start from the last non-leaf and heapify upward
// to the root.
{
   int lastNonLeaf = heapSize / 2 - 1;

   for (int i = lastNonLeaf; i >= 0; i--)
      maxHeapify(i);

} // end buildMaxHeap

template <typename T>
vector<T> heap<T>::heapSort()
// Sorts data in ascending order using heapsort and returns the sorted vector.
// Algorithm:
//   1. Build a max-heap (already done by initializeMaxHeap).
//   2. Swap the root (current maximum) with the last active element.
//   3. Shrink the active heap by 1 and restore the max-heap property.
//   4. Repeat until only one element remains.
// After the loop data is sorted in ascending order.
{
   for (int i = (int)data.size() - 1; i >= 1; i--)
   {
      // Move the current maximum to its final sorted position
      swap(data[0], data[i]);

      // Shrink the heap and restore the max-heap property at the root
      heapSize--;
      maxHeapify(0);

   } // end for

   return data;

} // end heapSort

#endif // HEAP_H
