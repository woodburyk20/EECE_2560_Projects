#include "mastermind.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/*
 * Default constructor.
 * Initializes the game with standard Mastermind parameters:
 *  - n = 5 digits
 *  - m = 10 possible values per digit (0–9)
 */
Mastermind::Mastermind() : secret(5, 10), n(5), m(10) { }

/*
 * Parameterized constructor.
 * Allows the user to specify custom values for:
 *  - n: length of the code
 *  - m: range of valid digit values
 */
Mastermind::Mastermind(int n_in, int m_in) : secret(n_in, m_in), n(n_in), m(m_in) { }

/*
 * Prints the secret code.
 * This is primarily included to allow TAs to easily verify
 * correctness during grading.
 */
void Mastermind::printSecret() const 
{
    cout << "Secret code: ";
    secret.print();
}

/*
 * Prompts the user to enter an entire guess on one line.
 * The guess must contain exactly n integers, each in the range [0, m-1].
 * Input is re-requested until a valid guess is entered.
 */
Code Mastermind::humanGuess() const
{
    while (true)
    {
        cout << "Enter your guess as " << n
             << " digits separated by spaces (each 0 to "
             << (m - 1) << "):\n";

        vector<int> d;
        d.reserve(n);

        // Attempt to read n integers
        for (int i = 0; i < n; i++)
        {
            int x;
            if (!(cin >> x))
            {
                // Non-integer input encountered
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter integers only.\n";
                d.clear();
                break;
            }
            d.push_back(x);
        }

        // Discard any extra input on the line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check correct number of digits
        if ((int)d.size() != n)
        {
            cout << "Please enter exactly " << n << " digits.\n";
            continue;
        }

        // Validate digit range
        bool inRange = true;
        for (int x : d)
        {
            if (x < 0 || x >= m)
            {
                inRange = false;
                break;
            }
        }

        if (!inRange)
        {
            cout << "Digits must be between 0 and "
                 << (m - 1) << ".\n";
            continue;
        }

        Code guess(n, m);
        if (guess.setDigits(d))
        {
            return guess;
        }

        // Defensive fallback (should not occur)
        cout << "Guess invalid. Try again.\n";
    }
}


/*
 * Computes the response to a given guess by comparing it
 * to the secret code.
 *
 * The response includes:
 *  - number of digits correct in both value and position
 *  - number of digits correct in value but in the wrong position
 */
Response Mastermind::getResponse(const Code& guess) const
{
    int c  = secret.checkCorrect(guess);
    int ic = secret.checkIncorrect(guess);
    return Response(c, ic);
}

/*
 * Determines whether the game has been solved.
 * The code is considered solved when the number of
 * correct digits equals the code length.
 */
bool Mastermind::isSolved(const Response& r) const
{
    return r.getCorrect() == n;
}

/*
 * Runs the main Mastermind game loop.
 *  - Initializes the secret code
 *  - Prompts the user for guesses up to a fixed number of turns
 *  - Prints feedback after each guess
 *  - Terminates early if the code is successfully solved
 */
void Mastermind::playGame()
{
    // Seed the random number generator once per program run
    static bool seeded = false;
    if (!seeded)
    {
        srand((unsigned)time(NULL));
        seeded = true;
    }

    // Generate a random secret code
    secret.initRandom();

    // Print secret for grading/debugging purposes
    printSecret();

    const int maxTurns = 10;

    for (int turn = 1; turn <= maxTurns; turn++)
    {
        cout << "\nTurn " << turn << " of " << maxTurns << "\n";

        Code guess = humanGuess();
        Response r = getResponse(guess);

        cout << "Codemaker response:\n";
        cout << "  Right digit in the right location: " << r.getCorrect() << "\n";
        cout << "  Right digit in the wrong location: " << r.getIncorrect() << "\n";


        // Check for win condition
        if (isSolved(r))
        {
            cout << "Codebreaker wins! Solved in "
                 << turn << " turns.\n";
            return;
        }
    }

    // If the loop exits without a solution, the codemaker wins
    cout << "\nCodemaker wins! You did not solve the code in time.\n";
    cout << "The secret was: ";
    secret.print();
}
