// EECE 2560 – Word Search                    
// Katherine Woodbury, Nathan Tan
//
// findMatches.cpp
// Searches the grid in all 8 directions for words found in the dictionary
// and writes each match (word, starting position, dictionary index) to an
// output file.

#include <iostream>
#include <fstream>
#include <string>
#include "grid.h"
#include "dictionary.h"

using namespace std;

void findMatches(const dictionary& dict, const grid& g,
                 const string& outputFileName)
// Iterates over every cell and direction in g, building candidate strings
// of length 5 up to the grid row count, and writes any string found in
// dict to outputFileName along with its starting position and dictionary
// index. Uses toroidal (wraparound) indexing so words can cross edges.
// Assumes: dict has been sorted; g has been loaded with valid grid data;
// outputFileName is a writable path.
{
   ofstream outFile(outputFileName);

   if (!outFile.is_open())
   {
      cout << "Error opening output file." << endl;
      return;
   } // end if

   int rows = g.getRows();
   int cols = g.getCols();

   // Row and column deltas for each of the 8 search directions:
   // NW, N, NE, W, E, SW, S, SE
   int rowDir[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
   int colDir[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

   // Maximum word length equals the number of rows (or cols — square grid)
   int maxLength = rows;

   // Check every starting cell
   for (int i = 0; i < rows; i++)
   {
      for (int j = 0; j < cols; j++)
      {
         // Check all 8 directions from cell (i, j)
         for (int d = 0; d < 8; d++)
         {
            string currentWord = "";

            // Extend the candidate string one character at a time
            for (int step = 0; step < maxLength; step++)
            {
               int currentRow = i + step * rowDir[d];
               int currentCol = j + step * colDir[d];

               currentWord += g.getWrappedChar(currentRow, currentCol);

               // Only search dictionary once the word is long enough
               if ((int)currentWord.length() >= 5)
               {
                  int foundIndex = dict.binarySearch(currentWord);

                  if (foundIndex != -1)
                  {
                     // Write the word, its start cell, and dictionary index
                     outFile << currentWord << " "
                             << "(" << i << "," << j << ") "
                             << foundIndex << endl;
                  } // end if

               } // end if

            } // end for step

         } // end for d

      } // end for j

   } // end for i

   outFile.close();

} // end findMatches
