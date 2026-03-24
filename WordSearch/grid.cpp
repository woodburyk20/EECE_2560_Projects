// EECE 2560 – Word Search      
// Katherine Woodbury, Nathan Tan
//
// grid.cpp
// Implements the grid class functions. Handles reading grid data from a
// file and providing direct and toroidally-wrapped character access.

#include "grid.h"

grid::grid()
// Default constructor. Sets rows and cols to zero before any file is read.
{
   rows = 0;
   cols = 0;

} // end constructor

void grid::readGrid(const string& filename)
// Opens filename, reads the grid dimensions, and fills the letters array.
// Prints an error message and returns early if the file cannot be opened.
// Assumes: the file begins with two integers (rows cols) followed by
// rows*cols space-separated single characters.
{
   ifstream inFile(filename);

   if (!inFile.is_open())
   {
      cout << "Error opening grid file." << endl;
      return;
   } // end if

   // Read the grid dimensions from the first line
   inFile >> rows >> cols;

   // Allocate the 2-D letter array
   letters.resize(rows, vector<char>(cols));

   // Fill each cell with the corresponding character from the file
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < cols; j++)
      {
         inFile >> letters[i][j];
      } // end for
   } // end for

   inFile.close();

} // end readGrid

int grid::getRows() const
// Returns the number of rows in the grid.
{
   return rows;

} // end getRows

int grid::getCols() const
// Returns the number of columns in the grid.
{
   return cols;

} // end getCols

char grid::getChar(int row, int col) const
// Returns the character at grid position (row, col).
// Assumes: row is in [0, rows) and col is in [0, cols).
{
   return letters[row][col];

} // end getChar

char grid::getWrappedChar(int row, int col) const
// Returns the character at (row, col) using toroidal (wraparound)
// indexing, so negative or out-of-range indices wrap to the other side.
// Assumes: rows > 0 and cols > 0.
{
   int wrappedRow = (row % rows + rows) % rows;
   int wrappedCol = (col % cols + cols) % cols;

   return letters[wrappedRow][wrappedCol];

} // end getWrappedChar

ostream& operator<<(ostream& out, const grid& g)
// Prints the grid dimensions followed by all characters, one row per line,
// with a space between each character.
{
   out << g.rows << " " << g.cols << endl;

   for (int i = 0; i < g.rows; i++)
   {
      for (int j = 0; j < g.cols; j++)
      {
         out << g.letters[i][j] << " ";
      } // end for

      out << endl;

   } // end for

   return out;

} // end operator<<
