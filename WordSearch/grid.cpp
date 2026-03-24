// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// grid.cpp
// Implements the grid class functions.

#include "grid.h"

grid::grid() {
    rows = 0;
    cols = 0;
} //endif

void grid::readGrid(const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error opening grid file." << endl;
        return;
    } //endif

    inFile >> rows >> cols;

    letters.resize(rows, vector<char>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inFile >> letters[i][j];
        } //endif
    } //endif

    inFile.close();
} //endif

int grid::getRows() const {
    return rows;
} //endif

int grid::getCols() const {
    return cols;
} //endif

char grid::getChar(int row, int col) const {
    return letters[row][col];
} //endif

char grid::getWrappedChar(int row, int col) const {
    int wrappedRow = (row % rows + rows) % rows;
    int wrappedCol = (col % cols + cols) % cols;

    return letters[wrappedRow][wrappedCol];
} //endif

ostream& operator<<(ostream& out, const grid& g) {
    out << g.rows << " " << g.cols << endl;

    for (int i = 0; i < g.rows; i++) {
        for (int j = 0; j < g.cols; j++) {
            out << g.letters[i][j] << " ";
        } //endif
        out << endl;
    } //endif

    return out;
} //endif