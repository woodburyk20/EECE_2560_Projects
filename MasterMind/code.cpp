#include "code.h"      // Declares the Code class and its public interface

#include <iostream>    // Provides cout, cerr, endl for output
#include <cstdlib>     // Provides rand() for random digit generation

using namespace std;

/*
 * Constructor for the Code class.
 *   - n digits (the length of the code)
 *   - m possible values per digit (valid digits are 0 to m-1)
 *
 * Parameters:
 *   length : number of digits in the code
 *   range  : range of allowed digit values
 * The constructor also initializes the internal digits vector so that:
 *   - it contains exactly n elements
 *   - all elements are initially set to 0
 */
Code::Code(int length, int range) : digits(), n(length), m(range)
{
    // Validate constructor parameters.
    // A code with non-positive length or range does not make sense.
    if ((n <= 0) || (m <= 0))
    {
        // Print an error message to standard error
        cerr << "Error: n and m must be positive." << endl;

        n = 0;
        m = 0;
    } // end if

    // Resize the digits vector to hold n digits.
    // All digits are initialized to 0.
    digits.resize(n, 0);
}

/*
 * Randomly initializes the code digits.
 * Each digit is assigned a random value in the range:
 *   0 <= digit < m
 */
void Code::initRandom()
{
    for (int i = 0; i < n; i++)
    {
        // rand() % m produces a value in the range [0, m-1]
        digits[i] = rand() % m;
    }
}

/*
 * Sets the digits of this Code object to the values provided in vector d.
 * Parameters:
 *   d : vector of integers representing the digits of the code
 * Returns:
 *   true  if the digits are valid and successfully stored
 *   false if validation fails (no changes are made)
 */
bool Code::setDigits(const vector<int>& d)
{
    // Check that the number of digits matches the expected code length
    if ((int)d.size() != n)
    {
        cerr << "Error: digit vector has wrong length." << endl;
        return false;
    } // enf if

    // Check that every digit is within the valid range
    for (int x : d)
    {
        if ((x < 0) || (x >= m))
        {
            cerr << "Error: digit out of range." << endl;
            return false;
        } // end if
    }

    // All validation passed; copy the digits into the Code object
    digits = d;
    return true;
}

/*
 * Counts how many digits in the guess match the secret code
 * in BOTH value and position.
 *
 * Parameters:
 *   guess : the Code object representing the user's guess
 * Returns:
 *   The number of exact matches between this code and the guess
 */
int Code::checkCorrect(const Code& guess) const
{
    int exactMatches = 0;

    // Compare each digit position one-by-one
    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            exactMatches++;
        } // end if
    }

    return exactMatches;
}

/*
 * Counts how many digits in the guess match the secret code
 * in VALUE but NOT in the same position.
 *   - No digit in the code or guess is counted more than once.
 *   - Digits that are exact matches must be excluded before counting misplaced 
 *     matches.
 *
 * Parameters:
 *   guess : the Code object representing the user's guess
 * Returns:
 *   The number of digits that are correct in value but incorrect in position
 */
int Code::checkIncorrect(const Code& guess) const
{
    // usedCode[i]  = true if digit i of the secret code has already been 
    //                matched
    // usedGuess[i] = true if digit i of the guess has already been matched
    vector<bool> usedCode(n, false);
    vector<bool> usedGuess(n, false);

    int misMatch = 0;

    // First pass: mark exact matches so they are not counted again
    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            usedCode[i] = true;
            usedGuess[i] = true;
        }
    }

    // Second pass: count digits that match in value but are in a different position
    for (int i = 0; i < n; i++)
    {
        // Skip guess digits that were already used in exact matches
        if (usedGuess[i])
        {
            continue; // restarts loop
        } // end if

        // Look for a matching unused digit in the secret code
        for (int j = 0; j < n; j++)
        {
            if (!usedCode[j] && guess.digits[i] == digits[j])
            {
                misMatch++;         // found a misplaced match
                usedCode[j] = true; // mark this code digit as used
                break;              // prevent double counting
            } // end if
        }
    }

    return misMatch;
}

/*
 * Prints the digits of the code to standard output.
 * Digits are printed on one line, separated by spaces.
 * This function is primarily used for:
 *   - debugging
 *   - grading/testing purposes
 */
void Code::print() const
{
    for (int digit : digits)
    {
        cout << digit << " ";
    }
    cout << endl;
}
