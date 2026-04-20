// Project Sudoku b                         
// Katherine Woodbury, Nathan Tan
//
// board.cpp
// Implements the board class. Manages a 9x9 Sudoku grid with conflict
// tracking across rows, columns, and 3x3 squares.
//

#include "board.h"


int squareNumber(int i, int j)
// Returns the square number (1-9) of cell (i, j), counting left to
// right, top to bottom. i and j go from 1 to BoardSize.
{
   return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}


ostream &operator<<(ostream &ostr, vector<int> &v)
// Prints all elements of v to ostr separated by spaces.
{
   for (int i = 0; i < (int)v.size(); i++)
      ostr << v[i] << " ";

   cout << endl;
   return ostr;
}


board::board(int sqSize)
// Initializes an empty board with all cells blank and no conflicts.
   : value(BoardSize + 1, BoardSize + 1),
     conflictRow(BoardSize + 1, MaxValue + 1, false),
     conflictCol(BoardSize + 1, MaxValue + 1, false),
     conflictSq(BoardSize + 1, MaxValue + 1, false)
{
   clear();
}


void board::clear()
// Resets all cells to Blank and clears all conflict flags.
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


void board::initialize(ifstream &fin)
// Reads a Sudoku board from fin, placing digits and updating conflicts.
// Assumes fin is open and positioned at the start of a valid board.
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


ValueType board::getCell(int i, int j)
// Returns the value stored in cell (i, j).
// Throws rangeError if indices are out of bounds.
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}


bool board::isBlank(int i, int j)
// Returns true if cell (i, j) is blank.
// Throws rangeError if indices are out of bounds.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}


void board::setCell(int i, int j, ValueType v)
// Places digit v in cell (i, j) and marks it as a conflict in the
// corresponding row, column, and square.
// Throws rangeError for invalid indices or out-of-range digit.
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


void board::clearCell(int i, int j)
// Removes the digit from cell (i, j) and clears the conflict flag
// only if no other cell in the same row, column, or square still
// holds that digit. Throws rangeError for invalid indices.
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad index in clearCell");

   if (isBlank(i, j))
      return;

   ValueType v = getCell(i, j);
   int sq = squareNumber(i, j);

   value[i][j] = Blank;

   // Re-check row i: clear the flag only if v is gone from the row.

   bool stillInRow = false;

   for (int col = 1; col <= BoardSize; col++)
   {
      if (value[i][col] == v)
      {
         stillInRow = true;
         break;
      }
   }

   conflictRow[i][v] = stillInRow;

   // Re-check column j: clear the flag only if v is gone from the col.

   bool stillInCol = false;

   for (int row = 1; row <= BoardSize; row++)
   {
      if (value[row][j] == v)
      {
         stillInCol = true;
         break;
      }
   }

   conflictCol[j][v] = stillInCol;

   // Re-check square sq: clear the flag only if v is gone from sq.

   bool stillInSq = false;

   for (int r = 1; r <= BoardSize && !stillInSq; r++)
   {
      for (int c = 1; c <= BoardSize && !stillInSq; c++)
      {
         if (squareNumber(r, c) == sq && value[r][c] == v)
            stillInSq = true;
      }
   }

   conflictSq[sq][v] = stillInSq;

} // end clearCell


void board::print()
// Prints the current board to cout with grid lines separating the
// 3x3 squares.
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
// Prints which digits are already placed in each row, column, and
// square. Used for debugging.
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
// square, and prints the result to cout.
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


bool board::findBlank(int &i, int &j)
// Finds the blank cell with the fewest legal digits remaining
// (MRV heuristic). Sets i and j to that cell and returns true.
// Returns false if no blank cell exists (board is complete).
//
// MRV (Minimum Remaining Values) is described in:
//   Russell & Norvig, "Artificial Intelligence: A Modern Approach",
//   Chapter 6 - Constraint Satisfaction Problems.
//   See also: https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
{
   int minCandidates = MaxValue + 1;  // sentinel: higher than any count
   bool foundAny = false;

   for (int r = 1; r <= BoardSize; r++)
   {
      for (int c = 1; c <= BoardSize; c++)
      {
         if (!isBlank(r, c))
            continue;

         // Count legal digits remaining for this cell.

         int count = 0;

         for (int v = MinValue; v <= MaxValue; v++)
            if (isLegal(r, c, v))
               count++;

         // A cell with 0 candidates is an immediate dead end; return
         // it so solve() backtracks without trying any digit.

         if (count == 0)
         {
            i = r;
            j = c;
            return true;
         }

         if (count < minCandidates)
         {
            minCandidates = count;
            i = r;
            j = c;
            foundAny = true;
         }

      } // end for c
   } // end for r

   return foundAny;

} // end findBlank


bool board::isLegal(int i, int j, ValueType v)
// Returns true if digit v can legally be placed at cell (i, j),
// i.e., v does not already appear in the same row, column, or square.
// Uses the conflict matrices for an O(1) lookup.
{
   int sq = squareNumber(i, j);
   return !conflictRow[i][v] && !conflictCol[j][v] && !conflictSq[sq][v];
}


bool board::solve(int &recursiveCalls)
// Solves the board recursively using backtracking. Uses findBlank
// (MRV) to pick the most constrained cell, tries each legal digit,
// and recurses. Undoes any placement that leads to a dead end.
// Returns true when solved, false if no solution exists from this
// state. Increments recursiveCalls on every entry.
{
   recursiveCalls++;

   int i, j;

   // Base case: no blank cells means the puzzle is complete.

   if (!findBlank(i, j))
      return true;

   for (int v = MinValue; v <= MaxValue; v++)
   {
      if (!isLegal(i, j, v))
         continue;

      setCell(i, j, v);           // tentatively place the digit

      if (solve(recursiveCalls))  // recurse; propagate success upward
         return true;

      clearCell(i, j);            // undo and try the next candidate
   }

   // No digit worked; signal the caller to backtrack.
   return false;
}
