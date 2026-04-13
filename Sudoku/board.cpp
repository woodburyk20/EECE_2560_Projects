// EECE 2560 - Sudoku                                    Katherine Woodbury
// Part a                                                Nathan Tan
//
// board.cpp
// Implements the board class for a 9x9 Sudoku grid. Manages cell
// values and tracks digit conflicts across rows, columns, and 3x3
// squares.

#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType;     // type of the value in a cell
const int Blank = -1;      // indicates that a cell is blank
const int SquareSize = 3;  // cells per side of one small square
const int BoardSize = SquareSize * SquareSize;
const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

class board
// Stores the entire Sudoku board and tracks which digits have been
// placed in each row, column, and 3x3 square.
{
   public:
      board(int sqSize);
      void clear();
      void initialize(ifstream &fin);
      void print();
      void printConflicts();
      bool isBlank(int i, int j);
      ValueType getCell(int i, int j);
      void setCell(int i, int j, ValueType v);
      void clearCell(int i, int j);
      bool isSolved();

   private:
      matrix<ValueType> value;   // cell values [1..BoardSize]^2

      // Conflict flags indexed [1..BoardSize][1..MaxValue]:
      //   conflictRow[i][v] = true if digit v appears in row i
      //   conflictCol[j][v] = true if digit v appears in column j
      //   conflictSq[s][v]  = true if digit v appears in square s
      matrix<bool> conflictRow;
      matrix<bool> conflictCol;
      matrix<bool> conflictSq;

}; // end class board


int squareNumber(int i, int j)
// Returns the square number (1-9) of cell (i,j), numbered left to
// right and top to bottom. Assumes i and j are in [1..BoardSize].
{
   return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}


ostream &operator<<(ostream &ostr, vector<int> &v)
// Outputs each element of v to ostr followed by a space, then endl.
{
   for (int i = 0; i < (int)v.size(); i++)
      ostr << v[i] << " ";

   cout << endl;
   return ostr;
}


board::board(int sqSize)
// Constructor. Initializes all cells to Blank and all conflict flags
// to false via clear(). sqSize is the side length of a small square
// (typically 3, matching the global SquareSize).
   : value(BoardSize + 1, BoardSize + 1),
     conflictRow(BoardSize + 1, MaxValue + 1, false),
     conflictCol(BoardSize + 1, MaxValue + 1, false),
     conflictSq(BoardSize + 1, MaxValue + 1, false)
{
   clear();
}


void board::clear()
// Resets every cell to Blank and clears all conflict flags.
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

} // end clear


void board::initialize(ifstream &fin)
// Reads one Sudoku board from fin one character at a time. '.' is
// treated as Blank; digit characters call setCell to place the value
// and update conflicts. Assumes fin is open and positioned at the
// start of an 81-character line.
{
   char ch;

   clear();

   for (int i = 1; i <= BoardSize; i++)
      for (int j = 1; j <= BoardSize; j++)
      {
         fin >> ch;

         if (ch != '.')
            setCell(i, j, ch - '0');
      }

} // end initialize


ValueType board::getCell(int i, int j)
// Returns the value stored in cell (i,j).
// Throws rangeError if i or j is outside [1..BoardSize].
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}


bool board::isBlank(int i, int j)
// Returns true if cell (i,j) contains no digit, false otherwise.
// Throws rangeError if i or j is outside [1..BoardSize].
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}


void board::setCell(int i, int j, ValueType v)
// Places digit v in cell (i,j) and marks it as a conflict in the
// corresponding row, column, and square conflict matrices.
// Throws rangeError if indices or value are out of range.
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

} // end setCell


void board::clearCell(int i, int j)
// Removes the digit from cell (i,j) and updates conflict flags.
// Each flag is cleared only if no other cell in the same row,
// column, or square still contains that digit. Does nothing if
// the cell is already blank. Throws rangeError for bad indices.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad index in clearCell");

   if (isBlank(i, j))
      return;

   ValueType v = getCell(i, j);
   int sq = squareNumber(i, j);

   value[i][j] = Blank;

   // Re-scan row i to determine if digit v still appears
   bool stillInRow = false;

   for (int col = 1; col <= BoardSize; col++)
      if (value[i][col] == v)
      {
         stillInRow = true;
         break;
      }

   conflictRow[i][v] = stillInRow;

   // Re-scan column j to determine if digit v still appears
   bool stillInCol = false;

   for (int row = 1; row <= BoardSize; row++)
      if (value[row][j] == v)
      {
         stillInCol = true;
         break;
      }

   conflictCol[j][v] = stillInCol;

   // Re-scan square sq to determine if digit v still appears
   bool stillInSq = false;

   for (int r = 1; r <= BoardSize && !stillInSq; r++)
      for (int c = 1; c <= BoardSize && !stillInSq; c++)
         if (squareNumber(r, c) == sq && value[r][c] == v)
            stillInSq = true;

   conflictSq[sq][v] = stillInSq;

} // end clearCell


void board::print()
// Prints the current board state to stdout with grid lines separating
// the 3x3 squares. Blank cells are printed as spaces.
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

} // end print


void board::printConflicts()
// Prints all digits already placed in each row, column, and square.
// For each unit, only digits currently in conflict are listed.
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

} // end printConflicts


bool board::isSolved()
// Returns true if every digit 1-9 appears in every row, column, and
// square (i.e., all conflict flags are set). Prints the result to
// stdout and returns false as soon as any missing digit is found.
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

} // end isSolved


int main()
// Reads Sudoku boards one at a time from sudoku1.txt until 'Z' is
// encountered. For each board, prints the board, its conflicts, and
// whether it has been solved.
{
   ifstream fin;
   string fileName = "sudoku1.txt";

   fin.open(fileName.c_str());

   if (!fin)
   {
      cerr << "Cannot open " << fileName << endl;
      exit(1);
   }

   try
   {
      board b1(SquareSize);

      while (fin && fin.peek() != 'Z')
      {
         b1.initialize(fin);
         b1.print();
         b1.printConflicts();
         b1.isSolved();
      }

   } // end try
   catch (indexRangeError &ex)
   {
      cout << ex.what() << endl;
      exit(1);
   }

   return 0;

} // end main
