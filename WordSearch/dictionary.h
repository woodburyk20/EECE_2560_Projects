#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class dictionary {
private:
    vector<string> words;

public:
    dictionary();

    void readWords(const string& filename);
    void selectionSort();
    int binarySearch(const string& word) const;
    int size() const;

    friend ostream& operator<<(ostream& out, const dictionary& d);
};

#endif
