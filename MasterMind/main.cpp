// EECE 2560 – Project Mastermind (Part B)
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// This file contains the main driver for the Mastermind game.
// It prompts the user to choose between default or custom game
// parameters and then runs the game loop.

#include "mastermind.h"

#include <iostream>
#include <limits>

using namespace std;

/*
 * Helper function to safely read a positive integer from the user.
 * Continues prompting until a valid integer greater than zero is entered.
 */
static int readPositiveInt(const string& prompt)
{
    while (true)
    {
        cout << prompt;
        int x;

        if (!(cin >> x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter an integer.\n";
            continue;
        }

        if (x <= 0)
        {
            cout << "Please enter a positive integer.\n";
            continue;
        }

        return x;
    }
}

int main()
{
    cout << "=============================\n";
    cout << "     Mastermind (Part B)     \n";
    cout << "=============================\n\n";

    cout << "Use custom code length and range? (y/n): ";
    char choice;
    cin >> choice;

    if (choice == 'y' || choice == 'Y')
    {
        int n = readPositiveInt("Enter n (code length): ");
        int m = readPositiveInt("Enter m (digit range size): ");

        Mastermind game(n, m);
        game.playGame();
    }
    else
    {
        // Default game: n = 5, m = 10
        Mastermind game;
        game.playGame();
    }

    return 0;
}
