#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class grid {
private:
    int rows;
    int cols;
    vector<vector<char>> letters;

public:
    grid();
    void readGrid(const string& filename);
    int getRows() const;
    int getCols() const;
    char getChar(int row, int col) const;
    char getWrappedChar(int row, int col) const;

    friend ostream& operator<<(ostream& out, const grid& g);
};

#endif

