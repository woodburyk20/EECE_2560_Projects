#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>

using namespace std;

class heap
{
public:
    int parent () const;
    int left () const;
    int right () const;
    int getItem(int n) const;

    void initializeMaxHeap();
    void maxHeapify();
    void buildMaxHeap();

    vector<string> heapSort();

private:
    vector<string> heap;



}


#endif