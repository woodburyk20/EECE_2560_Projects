// EECE 2560 – Sudoku
// Katherine Woodbury, Nathan Tan
//
// board.cpp
// Implements the board class. Manages a 9x9 Sudoku grid with
// conflict tracking across rows, columns, and 3x3 squares.

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

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

int numSolutions = 0;

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

// ---------------------------------------------------------------------------
// squareNumber
// Return the square number of cell i,j (counting left to right, top to bottom).
// i and j each go from 1 to BoardSize.
// ---------------------------------------------------------------------------
int squareNumber(int i, int j)
{
   return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

// ---------------------------------------------------------------------------
// Overloaded output operator for vector<int>
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, vector<int> &v)
{
   for (int i = 0; i < (int)v.size(); i++)
      ostr << v[i] << " ";
   cout << endl;
   return ostr;
}

// ---------------------------------------------------------------------------
// board constructor
// ---------------------------------------------------------------------------
board::board(int sqSize)
   : value(BoardSize + 1, BoardSize + 1),
     conflictRow(BoardSize + 1, MaxValue + 1, false),
     conflictCol(BoardSize + 1, MaxValue + 1, false),
     conflictSq(BoardSize + 1, MaxValue + 1, false)
{
   clear();
}

// ---------------------------------------------------------------------------
// clear
// Reset all cells to Blank and clear all conflict flags.
// ---------------------------------------------------------------------------
void board::clear()
{
   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
         value[i][j] = Blank;

   for (int i = 1; i <= BoardSize; i++)
      for (int v = 1; v <= MaxValue; v++)
      {
         conflictRow[i][v] = false;
         conflictCol[i][v] = false;
         conflictSq[i][v]  = false;
      }
}

// ---------------------------------------------------------------------------
// initialize
// Read a Sudoku board from the input file and update conflicts.
// ---------------------------------------------------------------------------
void board::initialize(ifstream &fin)
{
   char ch;

   clear();

   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
         fin >> ch;

         if (ch != '.')
            setCell(i, j, ch - '0');   // convert char digit to int
      }
}

// ---------------------------------------------------------------------------
// getCell
// Returns the value stored in a cell. Throws rangeError for bad indices.
// ---------------------------------------------------------------------------
ValueType board::getCell(int i, int j)
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}

// ---------------------------------------------------------------------------
// isBlank
// Returns true if cell i,j is blank, false otherwise.
// ---------------------------------------------------------------------------
bool board::isBlank(int i, int j)
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}

// ---------------------------------------------------------------------------
// setCell
// Places digit v into cell (i, j) and marks it as a conflict in the
// corresponding row, column, and square. Throws if the value is out of range.
// ---------------------------------------------------------------------------
void board::setCell(int i, int j, ValueType v)
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad index in setCell");
   if (v < MinValue || v > MaxValue)
      throw rangeError("bad value in setCell");

   value[i][j] = v;

   int sq = squareNumber(i, j);
   conflictRow[i][v] = true;
   conflictCol[j][v] = true;
   conflictSq[sq][v] = true;
}

// ---------------------------------------------------------------------------
// clearCell
// Removes the digit from cell (i, j) and clears the conflict flags,
// but only if no other cell in the same row/col/square still holds that digit.
// ---------------------------------------------------------------------------
void board::clearCell(int i, int j)
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad index in clearCell");
   if (isBlank(i, j))
      return;

   ValueType v = getCell(i, j);
   int sq = squareNumber(i, j);

   value[i][j] = Blank;

   // Re-check row i for digit v
   bool stillInRow = false;
   for (int col = 1; col <= BoardSize; col++)
      if (value[i][col] == v) { stillInRow = true; break; }
   conflictRow[i][v] = stillInRow;

   // Re-check column j for digit v
   bool stillInCol = false;
   for (int row = 1; row <= BoardSize; row++)
      if (value[row][j] == v) { stillInCol = true; break; }
   conflictCol[j][v] = stillInCol;

   // Re-check square sq for digit v
   bool stillInSq = false;
   for (int r = 1; r <= BoardSize && !stillInSq; r++)
      for (int c = 1; c <= BoardSize && !stillInSq; c++)
         if (squareNumber(r, c) == sq && value[r][c] == v)
            stillInSq = true;
   conflictSq[sq][v] = stillInSq;
}

// ---------------------------------------------------------------------------
// print
// Prints the current board with grid lines.
// ---------------------------------------------------------------------------
void board::print()
{
   for (int i = 1; i <= BoardSize; i++)
   {
      if ((i - 1) % SquareSize == 0)
      {
         cout << " -";
         for (int j = 1; j <= BoardSize; j++)
            cout << "---";
         cout << "-" << endl;
      }
      for (int j = 1; j <= BoardSize; j++)
      {
         if ((j - 1) % SquareSize == 0)
            cout << "|";
         if (!isBlank(i, j))
            cout << " " << getCell(i, j) << " ";
         else
            cout << "   ";
      }
      cout << "|" << endl;
   }

   cout << " -";
   for (int j = 1; j <= BoardSize; j++)
      cout << "---";
   cout << "-" << endl;
}

// ---------------------------------------------------------------------------
// printConflicts
// Prints which digits are already placed in each row, column, and square.
// ---------------------------------------------------------------------------
void board::printConflicts()
{
   cout << "\nConflicts by Row:" << endl;
   for (int i = 1; i <= BoardSize; i++)
   {
      cout << "  Row " << i << ": ";
      for (int v = 1; v <= MaxValue; v++)
         if (conflictRow[i][v])
            cout << v << " ";
      cout << endl;
   }

   cout << "\nConflicts by Column:" << endl;
   for (int j = 1; j <= BoardSize; j++)
   {
      cout << "  Col " << j << ": ";
      for (int v = 1; v <= MaxValue; v++)
         if (conflictCol[j][v])
            cout << v << " ";
      cout << endl;
   }

   cout << "\nConflicts by Square:" << endl;
   for (int s = 1; s <= BoardSize; s++)
   {
      cout << "  Sq  " << s << ": ";
      for (int v = 1; v <= MaxValue; v++)
         if (conflictSq[s][v])
            cout << v << " ";
      cout << endl;
   }
   cout << endl;
}

// ---------------------------------------------------------------------------
// isSolved
// Returns true if every digit 1-9 appears in every row, column, and square.
// Prints the result to the screen.
// ---------------------------------------------------------------------------
bool board::isSolved()
{
   for (int i = 1; i <= BoardSize; i++)
      for (int v = 1; v <= MaxValue; v++)
         if (!conflictRow[i][v] || !conflictCol[i][v] || !conflictSq[i][v])
         {
            cout << "Board is NOT solved." << endl;
            return false;
         }

   cout << "Board is SOLVED!" << endl;
   return true;
}

// ---------------------------------------------------------------------------
// findBlank
// Sets i and j to the first blank cell found (row-major order).
// Returns true if a blank cell exists, false if the board is complete.
// ---------------------------------------------------------------------------
bool board::findBlank(int &i, int &j)
{
   for (i = 1; i <= BoardSize; i++)
      for (j = 1; j <= BoardSize; j++)
         if (isBlank(i, j))
            return true;
   return false;
}

// ---------------------------------------------------------------------------
// isLegal
// Returns true if digit v can legally be placed at cell (i, j) —
// i.e., v is not already present in the same row, column, or square.
// ---------------------------------------------------------------------------
bool board::isLegal(int i, int j, ValueType v)
{
   int sq = squareNumber(i, j);
   return !conflictRow[i][v] && !conflictCol[j][v] && !conflictSq[sq][v];
}

// ---------------------------------------------------------------------------
// solve
// Recursively solves the board using backtracking.
// Increments recursiveCalls on each call. Returns true when solved.
// ---------------------------------------------------------------------------
bool board::solve(int &recursiveCalls)
{
   recursiveCalls++;

   int i, j;
   if (!findBlank(i, j))
      return true;

   for (int v = MinValue; v <= MaxValue; v++)
   {
      if (isLegal(i, j, v))
      {
         setCell(i, j, v);
         if (solve(recursiveCalls))
            return true;
         clearCell(i, j);
      }
   }

   return false;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main()
{
   string fileNames[] = {"sudoku1.txt", "sudoku2.txt", "sudoku3.txt"};
   int numFiles = 3;

   int totalCalls = 0;
   int totalBoards = 0;

   for (int f = 0; f < numFiles; f++)
   {
      ifstream fin;
      fin.open(fileNames[f].c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileNames[f] << endl;
         continue;
      }

      try
      {
         board b(SquareSize);

         while (fin && fin.peek() != 'Z')
         {
            b.initialize(fin);

            cout << "\n=== Board " << totalBoards + 1
                 << " (from " << fileNames[f] << ") ===" << endl;
            cout << "Initial board:" << endl;
            b.print();

            int calls = 0;
            if (b.solve(calls))
            {
               cout << "Solution:" << endl;
               b.print();
               b.isSolved();
            }
            else
            {
               cout << "No solution found." << endl;
            }

            cout << "Recursive calls: " << calls << endl;
            totalCalls += calls;
            totalBoards++;
         }
      }
      catch (indexRangeError &ex)
      {
         cout << ex.what() << endl;
      }

      fin.close();
   }

   if (totalBoards > 0)
      cout << "\nTotal boards solved: " << totalBoards
           << "\nTotal recursive calls: " << totalCalls
           << "\nAverage recursive calls: "
           << (double)totalCalls / totalBoards << endl;

   return 0;
}
