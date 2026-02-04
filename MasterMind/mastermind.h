#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "code.h"
#include "response.h"

class Mastermind
{
private:
    Code secret; // secret game code
    int n; // code length
    int m; // code range (0-(m-1))

public:
    // default constructor: n=5, m=10
    Mastermind();

    /*
    * Parameterized constructor -- Allows the user to choose custom game 
    * settings:
    *   - n_in: the length of the secret code (must be > 0 to make sense)
    *   - m_in: the number of possible values per digit (valid digits are 0..
    * m_in-1)
    */
    Mastermind(int n_in, int m_in);

    // prints the secret code -- for debugging
    void printSecret() const;

    /*
    * Prompts the user to enter an entire guess in one line.
    *
    * Input format expected:
    *   - Exactly n integers separated by spaces
    *   - Each integer must be a valid digit in the range [0, m-1]
    * Returns:
    *   - A Code object representing the user's validated guess.
    */
    Code humanGuess() const;

    /*
    * Computes the codemaker's response to a guess by comparing it to the 
    * secret code.
    *   - No digit is counted more than once.
    *   - Exact matches are accounted for first, then misplaced matches are 
    * counted.
    * Returns: A Response object containing the two counts.
    */
    Response getResponse(const Code& guess) const;

    // Determines if the codebreaker has solved the secret code.
    // The game is solved when the number of exact matches equals the code 
    // length.
    bool isSolved(const Response& r) const;
    
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
    void playGame();
};

#endif
