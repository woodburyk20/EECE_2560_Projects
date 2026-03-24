// EECE 2560 – Word Search
// Katherine Woodbury, Nathan Tan
//
// findMatches.cpp
// Searches the grid in all 8 directions and writes dictionary matches.

#include <iostream>
#include <fstream>
#include <string>
#include "grid.h"
#include "dictionary.h"

using namespace std;

void findMatches(const dictionary& dict, const grid& g, const string& outputFileName) {
    ofstream outFile(outputFileName);

    if (!outFile.is_open()) {
        cout << "Error opening output file." << endl;
        return;
    } 

    int rows = g.getRows();
    int cols = g.getCols();

    int rowDir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colDir[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    int maxLength = rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            // Check all 8 directions
            for (int d = 0; d < 8; d++) {
                string currentWord = "";

                for (int step = 0; step < maxLength; step++) {
                    int currentRow = i + step * rowDir[d];
                    int currentCol = j + step * colDir[d];

                    currentWord += g.getWrappedChar(currentRow, currentCol);

                    if ((int)currentWord.length() >= 5) {
                        int foundIndex = dict.binarySearch(currentWord);

                        if (foundIndex != -1) {
                            outFile << currentWord << " "
                                    << "(" << i << "," << j << ") "
                                    << foundIndex << endl;
                        } 
                    } 
                } 
            } 
        } 
    } 

    outFile.close();
} 