#ifndef dictionary_h
#define dictionary_h

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class dictionary {
public:
    // (a) Read words from the dictionary file
    void readWords(const string& filename);

    // (b) Overloaded output operator
    friend ostream& operator<<(ostream& os, const dictionary& d);

    // (c) Sort words using selection sort
    void selectionSort();

    // (d) Binary search — returns index if found, -1 if not
    int binarySearch(const string& word) const;

    // Accessor
    int size() const { return (int)words.size(); }

private:
    vector<string> words;
};

// ─── (a) readWords ────────────────────────────────────────────────────────────
void dictionary::readWords(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open dictionary file \"" << filename << "\"\n";
        return;
    }
    string word;
    while (fin >> word)
        words.push_back(word);
    fin.close();
}

// ─── (b) operator<< ──────────────────────────────────────────────────────────
ostream& operator<<(ostream& os, const dictionary& d) {
    for (int i = 0; i < (int)d.words.size(); i++)
        os << d.words[i] << "\n";
    return os;
}

// ─── (c) selectionSort ───────────────────────────────────────────────────────
void dictionary::selectionSort() {
    int n = (int)words.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (words[j] < words[minIdx])
                minIdx = j;
        if (minIdx != i)
            swap(words[i], words[minIdx]);
    }
}

// ─── (d) binarySearch ────────────────────────────────────────────────────────
int dictionary::binarySearch(const string& word) const {
    int lo = 0, hi = (int)words.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (words[mid] == word)
            return mid;
        else if (words[mid] < word)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

#endif // dictionary_h
