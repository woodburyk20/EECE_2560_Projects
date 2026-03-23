#include "grid.h"

grid::grid() {
    rows = 0;
    cols = 0;
}

void grid::readGrid(const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error opening grid file." << endl;
        return
    }

    inFile >> rows >> cols;

    letters.resize(rows, vector<char>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            inFile >> letters[i][j];
        }
    }

    inFile.close()
}

int grid::getRows() const {
    return rows;
}

int grid::getCols() const {
    return cols;
}

char grid::getChar(int row, int col) const {
    return letters[row][col];
}
    
ostream& operator <<(ostream& out, const grid& g) {
    out << g.rows << " " << g.cols << endl;

    for (int i = 0; i < g.rows; i++) {
        for (int j = 0; i < g.cols; j++) {
            out << g.letters[i][j] << " ";
        }

        out << endl;
    }
 
    return out;
}