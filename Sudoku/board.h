// EECE 2560 – Sudoku
// Katherine Woodbury, Nathan Tan
//
// board.h
// Class declaration for board, shared constants, and helper function
// declarations. Include this file in any translation unit that needs
// to create or use a board object.

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "d_matrix.h"
#include "d_except.h"

using namespace std;

typedef int ValueType;     // The type of the value in a cell
const int Blank = -1;      // Indicates that a cell is blank

const int SquareSize = 3;  // The number of cells in a small square
                           // (usually 3). The board has
                           // SquareSize^2 rows and SquareSize^2
                           // columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

// Returns the square number (1–9) for cell (i, j), counting left to right,
// top to bottom.
int squareNumber(int i, int j);

// Prints all elements of a vector<int> separated by spaces.
ostream &operator<<(ostream &ostr, vector<int> &v);

class board
// Stores the entire Sudoku board
{
   public:
      board(int);
      void clear();
      void initialize(ifstream &fin);
      void print();
      void printConflicts();
      bool isBlank(int, int);
      ValueType getCell(int, int);
      void setCell(int, int, ValueType);
      void clearCell(int, int);
      bool isSolved();
      bool findBlank(int &i, int &j);
      bool isLegal(int i, int j, ValueType v);
      bool solve(int &recursiveCalls);

   private:
      // The following matrices go from 1 to BoardSize in each
      // dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)
      matrix<ValueType> value;

      // Conflict tracking: rows, cols, squares indexed [1..BoardSize][1..MaxValue]
      // conflictRow[i][v]  = true if digit v is already placed in row i
      // conflictCol[j][v]  = true if digit v is already placed in col j
      // conflictSq[s][v]   = true if digit v is already placed in square s
      matrix<bool> conflictRow;
      matrix<bool> conflictCol;
      matrix<bool> conflictSq;
};
