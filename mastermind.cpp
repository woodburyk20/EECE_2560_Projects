#include "mastermind.h"

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * Default constructor.
 * Initializes the game with standard Mastermind parameters:
 *  - n = 5 digits
 *  - m = 10 possible values per digit (0–9)
 */
Mastermind::Mastermind() 
    : secret(5, 10), n(5), m(10) 
{
}

/**
 * Parameterized constructor.
 * Allows the user to specify custom values for:
 *  - n: length of the code
 *  - m: range of valid digit values [0, m-1]
 */
Mastermind::Mastermind(int n_in, int m_in) 
    : secret(n_in, m_in), n(n_in), m(m_in) 
{
}

/**
 * Prints the secret code to the console.
 * This is primarily included to allow TAs to easily verify
 * correctness during grading.
 */
void Mastermind::printSecret() const 
{
    cout << "Secret code: ";
    secret.print();
}

/**
 * Prompts the user to enter a guess.
 * The guess must contain exactly n integers, each in the range [0, m-1].
 * Input is re-requested until a valid guess is entered.
 * 
 * @return A valid Code object representing the user's guess
 */
Code Mastermind::humanGuess() const
{
    while (true)
    {
        cout << "Enter your guess as " << n
             << " digit" << (n != 1 ? "s" : "")
             << " separated by spaces (each 0 to " << (m - 1) << "):\n> ";

        vector<int> digits;
        digits.reserve(n);

        // Attempt to read n integers from input
        bool validInput = true;
        for (int i = 0; i < n; i++)
        {
            int value;
            if (!(cin >> value))
            {
                // Non-integer input encountered
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter integers only.\n\n";
                validInput = false;
                break;
            }
            digits.push_back(value);
        }

        // Skip remaining validation if input was non-numeric
        if (!validInput)
        {
            continue;
        }

        // Clear any remaining input on the line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Verify correct number of digits were entered
        if (static_cast<int>(digits.size()) != n)
        {
            cout << "Please enter exactly " << n << " digit" 
                 << (n != 1 ? "s" : "") << ".\n\n";
            continue;
        }

        // Validate that all digits are within valid range
        bool inRange = true;
        for (int value : digits)
        {
            if (value < 0 || value >= m)
            {
                cout << "All digits must be between 0 and " << (m - 1) << ".\n";
                cout << "Invalid digit: " << value << "\n\n";
                inRange = false;
                break;
            }
        }

        if (!inRange)
        {
            continue;
        }

        // Create and return the validated guess
        Code guess(n, m);
        if (guess.setDigits(digits))
        {
            return guess;
        }

        // Defensive fallback (should not occur with proper validation)
        cout << "Unable to create valid guess. Please try again.\n\n";
    }
}

/**
 * Computes the response to a given guess by comparing it
 * to the secret code.
 *
 * The response includes:
 *  - number of digits correct in both value and position
 *  - number of digits correct in value but in the wrong position
 *
 * @param guess The code to evaluate
 * @return Response object containing feedback
 */
Response Mastermind::getResponse(const Code& guess) const
{
    int correct = secret.checkCorrect(guess);
    int incorrect = secret.checkIncorrect(guess);
    return Response(correct, incorrect);
}

/**
 * Determines whether the game has been solved.
 * The code is considered solved when the number of
 * correct digits equals the code length.
 *
 * @param r Response to evaluate
 * @return true if all digits are correct and in correct positions
 */
bool Mastermind::isSolved(const Response& r) const
{
    return r.getCorrect() == n;
}

/**
 * Runs the main Mastermind game loop.
 *  - Initializes the secret code randomly
 *  - Prints the secret (for grading/debugging)
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
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    // Generate a random secret code
    secret.initRandom();

    // Display welcome message and game rules
    cout << "\n========================================\n";
    cout << "       MASTERMIND GAME\n";
    cout << "========================================\n";
    cout << "Code length: " << n << " digits\n";
    cout << "Digit range: 0 to " << (m - 1) << "\n";
    cout << "Max turns: 10\n";
    cout << "========================================\n\n";

    // Print secret for grading/debugging purposes
    printSecret();
    cout << endl;

    const int maxTurns = 10;

    // Main game loop
    for (int turn = 1; turn <= maxTurns; turn++)
    {
        cout << "\n--- Turn " << turn << " of " << maxTurns << " ---\n";

        // Get validated guess from player
        Code guess = humanGuess();
        
        // Evaluate guess and generate response
        Response r = getResponse(guess);

        // Display feedback
        cout << "\nCodemaker response:\n";
        cout << r;  // Uses overloaded operator<<

        // Check for win condition
        if (isSolved(r))
        {
            cout << "\n========================================\n";
            cout << "   CODEBREAKER WINS!\n";
            cout << "   Solved in " << turn << " turn" 
                 << (turn != 1 ? "s" : "") << "!\n";
            cout << "========================================\n";
            return;
        }
    }

    // If the loop exits without a solution, the codemaker wins
    cout << "\n========================================\n";
    cout << "   CODEMAKER WINS!\n";
    cout << "   You did not solve the code in time.\n";
    cout << "========================================\n";
    cout << "The secret was: ";
    secret.print();
}
