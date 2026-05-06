// Project Sudoku b                         
// Katherine Woodbury, Nathan Tan
//
// board.h
// Class declaration for the board class, shared constants, and helper
// function declarations. Include this file in any translation unit
// that needs to create or use a board object.
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

typedef int ValueType;     // The type of the value in a cell
const int Blank    = -1;   // Indicates that a cell is blank
const int SquareSize = 3;  // The number of cells in a small square
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;

int squareNumber(int i, int j);
// Returns the square number (1-9) of cell (i, j), counting left to
// right, top to bottom. i and j go from 1 to BoardSize.

ostream &operator<<(ostream &ostr, vector<int> &v);
// Prints all elements of v to ostr separated by spaces.

class board
// Stores the entire Sudoku board
{
public:

// Constructors and setup:

   board(int sqSize);
   void clear();
   void initialize(ifstream &fin);

// Output:

   void print();
   void printConflicts();

// Cell access and modification:

   bool isBlank(int i, int j);
   ValueType getCell(int i, int j);
   void setCell(int i, int j, ValueType v);
   void clearCell(int i, int j);

// Solver:

   bool isSolved();
   bool findBlank(int &i, int &j);
   bool isLegal(int i, int j, ValueType v);
   bool solve(int &recursiveCalls);

private:

   // The following matrices go from 1 to BoardSize in each
   // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

   matrix<ValueType> value;

   // Conflict tracking indexed [1..BoardSize][1..MaxValue]:
   // conflictRow[i][v] = true if digit v is already placed in row i
   // conflictCol[j][v] = true if digit v is already placed in col j
   // conflictSq[s][v]  = true if digit v is already placed in square s

   matrix<bool> conflictRow;
   matrix<bool> conflictCol;
   matrix<bool> conflictSq;

}; // end board
