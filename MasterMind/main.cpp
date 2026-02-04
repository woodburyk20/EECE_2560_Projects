// EECE 2560 – Project Mastermind (Part B)
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// main.cpp
// --------
// This file contains the main() function, which is the program's
// starting point.
//
// Responsibilities of this file:
//   1) Display a simple welcome banner / user prompt.
//   2) Ask whether the user wants default game settings or custom settings.
//   3) Read and validate n (code length) and m (digit range size) if needed.
//   4) Construct a Mastermind game object using either:
//        - the default constructor, or
//        - the parameterized constructor with user-provided n and m.
//   5) Start the actual game loop by calling playGame().
//

#include "mastermind.h"   // Gives access to the Mastermind class interface

#include <iostream>       // cin, cout for console input/output
#include <limits>         // numeric_limits for safely clearing invalid input

using namespace std;

/*
 * readPositiveInt(prompt)
 * -----------------------
 * Safely reads a positive integer from the user.
 * 
 * Repeatedly prompts the user until valid input is entered
 * Uses stream state checks to detect non-integer input
 * lears the error state and discards the rest of the line when invalid
 *
 * Parameters:
 *   prompt : text printed to the user before reading input
 * Returns:
 *   A positive integer (> 0)
 */
static int readPositiveInt(const string& prompt)
{
    while (true) // loop until we successfully return a valid positive integer
    {
        cout << prompt;

        int x; // temporary variable to store the user's input

        // Attempt to read an integer into x.
        // If the user typed something non-numeric , cin enters a failure state 
        // and this condition becomes true.
        if (!(cin >> x))
        {
            cin.clear(); // reset cin's failure state so future input can work

            // Discard the rest of the current input line so the invalid token
            // does not remain in the buffer and immediately fail again.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter an integer.\n";
            continue; // restart the loop and re-prompt
        }

        // validate that integer is positive
        if (x <= 0)
        {
            cout << "Please enter a positive integer.\n";
            continue; // restart the loop and re-prompt
        }

        // Valid input: integer and positive
        return x;
    }
}

int main()
{

    // Seed the random number generator.
    srand((unsigned)time(NULL));

    cout << "=============================\n";
    cout << "          Mastermind         \n";
    cout << "=============================\n\n";

    // Ask the user whether they want to use custom settings for the game.
    cout << "Use custom code length and range? (y/n): ";

    char choice; // holds user response ('y'/'n')
    cin >> choice;

    // If the user answered yes, read n and m and start a game with those values.
    if (choice == 'y' || choice == 'Y')
    {
        int n = readPositiveInt("Enter n (code length): ");

        int m = readPositiveInt("Enter m (digit range size 0-(m-1)): ");

        // Create a Mastermind game with custom settings.
        // This calls the parameterized constructor Mastermind(n, m).
        Mastermind game(n, m);

        // Start the game loop with custom settings.
        game.playGame();
    }
    else
    {
        // Otherwise, use the default constructor (n=5, m=10).
        Mastermind game;

        // Start the game loop with default settings.
        game.playGame();
    }

    return 0;
}
