#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "code.h"
#include "response.h"

/**
 * @class Mastermind
 * @brief Manages the Mastermind game logic and player interaction
 * 
 * The Mastermind class handles game state, secret code generation,
 * user input validation, and win/loss conditions for the classic
 * codebreaking game.
 */
class Mastermind
{
private:
    Code secret;  ///< The secret code to be guessed
    int n;        ///< Length of the code (number of digits)
    int m;        ///< Range of valid digit values [0, m-1]

public:
    /**
     * @brief Default constructor
     * Initializes game with standard parameters (n=5, m=10)
     */
    Mastermind();

    /**
     * @brief Parameterized constructor
     * @param n_in Length of the code
     * @param m_in Range of valid digit values
     */
    Mastermind(int n_in, int m_in);

    /**
     * @brief Prints the secret code to the console
     * Used for debugging and grading verification
     */
    void printSecret() const;

    /**
     * @brief Prompts user for a guess and validates input
     * @return Valid Code object representing the player's guess
     */
    Code humanGuess() const;

    /**
     * @brief Evaluates a guess against the secret code
     * @param guess The code to evaluate
     * @return Response object with correct/incorrect counts
     */
    Response getResponse(const Code& guess) const;

    /**
     * @brief Checks if the game has been solved
     * @param r Response to check
     * @return true if all digits are correct in correct positions
     */
    bool isSolved(const Response& r) const;

    /**
     * @brief Runs the main game loop
     * Manages turns, user input, feedback, and win/loss conditions
     */
    void playGame();
};

#endif // MASTERMIND_H
