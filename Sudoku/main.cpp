// EECE 2560 – Sudoku
// Katherine Woodbury, Nathan Tan
//
// main.cpp
// Entry point. Reads Sudoku boards from input files, solves each one,
// and reports recursive call counts and the overall average.

#include "board.h"

// main

int main()
{
   // All three input files to process in sequence.
   string fileNames[] = {"sudoku1.txt", "sudoku2.txt", "sudoku3.txt"};
   int numFiles = 3;

   // Accumulators for the final average calculation.
   int totalCalls = 0;
   int totalBoards = 0;

   // Process each file one at a time.
   for (int f = 0; f < numFiles; f++)
   {
      ifstream fin;
      fin.open(fileNames[f].c_str());
      if (!fin)
      {
         cerr << "Cannot open " << fileNames[f] << endl;
         continue; // skip missing files and move to the next
      }

      try
      {
         board b(SquareSize);

         // Each file may contain multiple boards; 'Z' marks the end of the file.
         while (fin && fin.peek() != 'Z')
         {
            b.initialize(fin);

            cout << "\n=== Board " << totalBoards + 1
                 << " (from " << fileNames[f] << ") ===" << endl;
            cout << "Initial board:" << endl;
            b.print();

            // Solve and count recursive calls for this board.
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

   // Print summary statistics across all boards.
   if (totalBoards > 0)
      cout << "\nTotal boards solved: " << totalBoards
           << "\nTotal recursive calls: " << totalCalls
           << "\nAverage recursive calls: "
           << (double)totalCalls / totalBoards << endl;

   return 0;
}
