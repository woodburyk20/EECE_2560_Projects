// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// grid.h
// Header file for the grid class. Declares a 2-D character grid that
// supports reading from a file, direct and wraparound character access,
// and output streaming.

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class grid
{
public:
   grid();
   // Default constructor. Initializes rows and cols to zero.

   void readGrid(const string& filename);
   // Opens filename and reads the grid dimensions and characters.
   // Assumes: the file begins with two integers (rows cols) followed
   // by rows*cols space-separated characters.

   int getRows() const;
   // Returns the number of rows in the grid.

   int getCols() const;
   // Returns the number of columns in the grid.

   char getChar(int row, int col) const;
   // Returns the character at position (row, col).

   char getWrappedChar(int row, int col) const;
   // Returns the character at (row, col) with toroidal wrapping, so
   // out-of-bounds indices wrap around to the opposite edge.

   friend ostream& operator<<(ostream& out, const grid& g);
   // Prints the grid dimensions and all characters to out.

private:
   int rows;                        // number of rows in the grid
   int cols;                        // number of columns in the grid
   vector<vector<char>> letters;    // 2-D array of grid characters

}; // end class grid

#endif
