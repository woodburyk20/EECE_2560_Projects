#include "mastermind.h"

#include <iostream>  
#include <vector>    
#include <limits>    // numeric_limits used to safely clear/discard invalid input
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time() used for seeding RNG 
#include <string>    // string and to_string() for building prompt text

using namespace std;

/*
 * Default constructor - Initializes the game with "standard" parameters:
 *   - n = 5 : the secret code length (5 digits)
 *   - m = 10: the digit range size (valid digits are 0 through 9)
 */
Mastermind::Mastermind() : secret(5, 10), n(5), m(10) { }

/*
 * Parameterized constructor -- Allows the user to choose custom game settings:
 *   - n_in: the length of the secret code (must be > 0 to make sense)
 *   - m_in: the number of possible values per digit (valid digits are 0..m_in-1)
 */
Mastermind::Mastermind(int n_in, int m_in) : secret(n_in, m_in), n(n_in), m(m_in) { }


 // Prints the scecret code to the console -- for debugging
void Mastermind::printSecret() const
{
    cout << "Secret code: ";
    secret.print();
}

/*
 * Prompts the user to enter an entire guess in one line.
 *
 * Input format expected:
 *   - Exactly n integers separated by spaces
 *   - Each integer must be a valid digit in the range [0, m-1]
 * Returns:
 *   - A Code object representing the user's validated guess.
 */
Code Mastermind::humanGuess() const
{
    // Repeat until a valid guess is entered and returned
    while (true)
    {
        cout << "Enter your guess as " << n
             << " digits separated by spaces (each 0 to "
             << (m - 1) << "):\n";

        vector<int> d; // Will hold the user's guess digits as they are read

        // Attempt to read exactly n integers from the user.
        for (int i = 0; i < n; i++)
        {
            int x; // temporary variable that stores ONE digit read from input

            // Try to read an integer from cin into x.
            // If the user entered non-integer input, cin enters a fail state 
            if (!(cin >> x))
            {
                // Clear the fail state so future reads can work again
                cin.clear();

                // Discard the rest of the input line 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter integers only.\n";

                // Clear any partially-read digits so size != n
                d.clear();

                break; // Exit for loop -- stop reading integers
            }

            
            d.push_back(x); // valid integer stored as part of the guess
            
            // If user pressed Enter early, stop reading
            if (cin.peek() == '\n' && i < n - 1)
            {
                break;
            }
        }

        
        // discard anything left on the line, prevents from affecting the next guess attempt.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // If we did not read exactly n integers, reject and restart the while-loop.
        if ((int)d.size() != n)
        {
            cout << "Please enter exactly " << n << " digits.\n";
            continue; 
        }

        // Validate that each digit is within the allowed range [0, m-1].
        // This ensures the guess matches the game's digit rules.
        bool inRange = true;
        for (int x : d)
        {
            if (x < 0 || x >= m)
            {
                inRange = false; // mark invalid
                break;           // stop checking further digits once we know 
            }
        }

        // If any digit was out of range, reject and restart the while-loop.
        if (!inRange)
        {
            cout << "Digits must be between 0 and "
                 << (m - 1) << ".\n";
            continue; 
        }

        Code guess(n, m); // build a Code object to represent this guess.

        // If setDigits succeeds, we return the guess and exit the function.
        if (guess.setDigits(d))
        {
            return guess;
        }

      
        // Backup if setDigits doesnt work
        cout << "Guess invalid. Try again.\n";
    }
}

/*
 * Computes the codemaker's response to a guess by comparing it to the secret code.
 *   - No digit is counted more than once.
 *   - Exact matches are accounted for first, then misplaced matches are counted.
 * Returns: A Response object containing the two counts.
 */
Response Mastermind::getResponse(const Code& guess) const
{
    // Count digits that match in both value AND position
    int c = secret.checkCorrect(guess);

    // Count digits that match in value but are in a DIFFERENT position
    int ic = secret.checkIncorrect(guess);

    // Pack the two values into a Response object and return it
    return Response(c, ic);
}


// Determines if the codebreaker has solved the secret code.
// The game is solved when the number of exact matches equals the code length.
bool Mastermind::isSolved(const Response& r) const
{
    return r.getCorrect() == n;
}

/*
 * Runs the main game loop.
 *   1) Generates a random secret code.
 *   2) (maybe) Prints the secret code (for debugging).
 *   3) Repeats for a fixed number of turns:
 *        - prompts the user for a guess
 *        - computes and prints the response (two values)
 *        - checks for win condition (solved)
 *   4) If the user does not solve within maxTurns, codemaker wins.
 */
void Mastermind::playGame()
{

    // Maximum number of guesses allowed
    const int maxTurns = 10;

    // Generate a random secret code
    secret.initRandom();

    // Print the secret for testing/grading (uncomment if wanted)
    // printSecret();

    // Main turn loop: user gets up to maxTurns attempts
    for (int turn = 1; turn <= maxTurns; turn++)
    {
        cout << "\nTurn " << turn << " of " << maxTurns << "\n";

        // Read a validated guess from the user
        Code guess = humanGuess();

        // Compute the codemaker’s response to that guess
        Response r = getResponse(guess);

        // Print response
        cout << "Codemaker response:\n";
        cout << r << "\n";

        // If the guess is fully correct, end the game immediately
        if (isSolved(r))
        {
            cout << "Codebreaker wins! Solved in "
                 << turn << " turns.\n";
            return; // exit playGame() early on success
        }
    }

    // If we reach here, the user did not solve within maxTurns
    cout << "\nCodemaker wins! You did not solve the code in time.\n";
    cout << "The secret was: ";
    secret.print();
}
