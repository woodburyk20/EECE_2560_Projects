// EECE 2560 – Sudoku
// Katherine Woodbury, Nathan Tan
//
// board.cpp
// Implements the board class. Manages a 9x9 Sudoku grid with
// conflict tracking across rows, columns, and 3x3 squares.

#include "board.h"


// squareNumber
// Return the square number of cell i,j (counting left to right, top to bottom).
// i and j each go from 1 to BoardSize.

int squareNumber(int i, int j)
{
   return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}


// Overloaded output operator for vector<int>

ostream &operator<<(ostream &ostr, vector<int> &v)
{
   for (int i = 0; i < (int)v.size(); i++)
      ostr << v[i] << " ";
   cout << endl;
   return ostr;
}


// board constructor

board::board(int sqSize)
   : value(BoardSize + 1, BoardSize + 1),
     conflictRow(BoardSize + 1, MaxValue + 1, false),
     conflictCol(BoardSize + 1, MaxValue + 1, false),
     conflictSq(BoardSize + 1, MaxValue + 1, false)
{
   clear();
}


// clear
// Reset all cells to Blank and clear all conflict flags.

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


// initialize
// Read a Sudoku board from the input file and update conflicts.

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


// getCell
// Returns the value stored in a cell. Throws rangeError for bad indices.

ValueType board::getCell(int i, int j)
{
   if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
      return value[i][j];
   else
      throw rangeError("bad value in getCell");
}


// isBlank
// Returns true if cell i,j is blank, false otherwise.

bool board::isBlank(int i, int j)
{
   if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
      throw rangeError("bad value in isBlank");

   return (getCell(i, j) == Blank);
}


// setCell
// Places digit v into cell (i, j) and marks it as a conflict in the
// corresponding row, column, and square. Throws if the value is out of range.

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


// clearCell
// Removes the digit from cell (i, j) and clears the conflict flags,
// but only if no other cell in the same row/col/square still holds that digit.

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


// print
// Prints the current board with grid lines.

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


// printConflicts
// Prints which digits are already placed in each row, column, and square.

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


// isSolved
// Returns true if every digit 1-9 appears in every row, column, and square.
// Prints the result to the screen.

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


// findBlank  —  MRV (Minimum Remaining Values) heuristic
//
// Instead of always picking the first empty cell in row-major order, we scan
// every blank cell and count how many digits are still legal for it.  We then
// return the cell with the FEWEST legal options (the "most constrained" cell).
//
// Why:
//   Choosing a cell that already has only 1 or 2 candidates means wrong guesses
//   are detected almost immediately, collapsing large branches of the search
//   tree before they are explored.  Picking an unconstrained cell first lets
//   bad guesses propagate many levels deep before a contradiction is found.
//
// This technique comes from constraint-satisfaction theory and is described in:
//   Russell, S. & Norvig, P. "Artificial Intelligence: A Modern Approach",
//   Chapter 6 — Constraint Satisfaction Problems.
//   See also: https://en.wikipedia.org/wiki/Sudoku_solving_algorithms
//
// Returns true if at least one blank cell was found (sets i, j to that cell).
// Returns false when the board is completely filled (base case for solve).

bool board::findBlank(int &i, int &j)
{
   // Track the best cell found so far.
   int minCandidates = MaxValue + 1; // higher than any real count
   bool foundAny = false;

   for (int r = 1; r <= BoardSize; r++)
   {
      for (int c = 1; c <= BoardSize; c++)
      {
         if (!isBlank(r, c))
            continue; // skip filled cells

         // Count how many digits are still legal for cell (r, c).
         int count = 0;
         for (int v = MinValue; v <= MaxValue; v++)
            if (isLegal(r, c, v))
               count++;

         // A cell with 0 legal values is an immediate dead end — return it
         // right away so solve() backtracks without trying any digit.
         if (count == 0)
         {
            i = r; j = c;
            return true;
         }

         // Otherwise keep the cell with the fewest remaining candidates.
         if (count < minCandidates)
         {
            minCandidates = count;
            i = r;
            j = c;
            foundAny = true;
         }
      }
   }

   return foundAny;
}


// isLegal
// Returns true if digit v can legally be placed at cell (i, j) —
// i.e., v is not already present in the same row, column, or square.
// The conflict matrices make this an O(1) lookup.

bool board::isLegal(int i, int j, ValueType v)
{
   int sq = squareNumber(i, j);
   return !conflictRow[i][v] && !conflictCol[j][v] && !conflictSq[sq][v];
}


// solve  —  recursive backtracking with MRV + implicit forward checking
//
// Algorithm:
//   1. Use findBlank (MRV) to pick the most constrained empty cell.
//      If none exists, the board is solved — return true.
//   2. Try each digit 1–9 that is legal for that cell.
//   3. Place the digit, recurse.  If the recursive call succeeds, propagate
//      the success upward.
//   4. If no digit works (or the recursion fails), undo the placement and
//      return false so the caller can try its next candidate (backtrack).
//
// Implicit forward checking:
//   Because findBlank uses MRV, it will immediately return any blank cell
//   that has 0 legal candidates after a placement.  The for-loop below then
//   finds no legal digit and returns false without going deeper — equivalent
//   to forward checking but without a separate pass.
//
// Increments recursiveCalls on every entry so the caller can report effort.

bool board::solve(int &recursiveCalls)
{
   recursiveCalls++;

   int i, j;
   // Base case: no blank cells left means the puzzle is complete.
   if (!findBlank(i, j))
      return true;

   // Try every digit for the chosen cell (MRV already picked the best cell).
   for (int v = MinValue; v <= MaxValue; v++)
   {
      if (!isLegal(i, j, v))
         continue; // skip illegal digits immediately

      setCell(i, j, v);             // tentatively place the digit
      if (solve(recursiveCalls))    // recurse; if it works, we're done
         return true;
      clearCell(i, j);              // undo and try the next candidate
   }

   // No digit worked, signal the caller to backtrack.
   return false;
}
