#include "dictionary.h"

dictionary::dictionary() {
}

void dictionary::readWords(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening dictionary file." << endl;
        return;
    }
    string word;
    while (inFile >> word) {
        words.push_back(word);
    }
    inFile.close();
}

void dictionary::selectionSort() {
    int n = (int)words.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (words[j] < words[minIdx])
                minIdx = j;
        }
        if (minIdx != i)
            swap(words[i], words[minIdx]);
    }
}

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

int dictionary::size() const {
    return (int)words.size();
}

ostream& operator<<(ostream& out, const dictionary& d) {
    for (int i = 0; i < (int)d.words.size(); i++) {
        out << d.words[i] << endl;
    }
    return out;
}
