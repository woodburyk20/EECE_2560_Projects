#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

/**
 * @class Response
 * @brief Stores feedback for a Mastermind guess
 * 
 * The Response class encapsulates the codemaker's feedback:
 *  - correct: digits in the correct value AND position
 *  - incorrect: digits with correct value but WRONG position
 */
class Response
{
private:
    int correct;    ///< Number of digits correct in value and position
    int incorrect;  ///< Number of digits correct in value but wrong position

public:
    /**
     * @brief Default constructor
     * Initializes response with zero correct and incorrect
     */
    Response();

    /**
     * @brief Parameterized constructor
     * @param c Number of correct digits (right value, right position)
     * @param i Number of incorrect digits (right value, wrong position)
     */
    Response(int c, int i);

    /**
     * @brief Gets the number of correct digits
     * @return Number of digits in correct position with correct value
     */
    int getCorrect() const;

    /**
     * @brief Gets the number of incorrect digits
     * @return Number of digits with correct value but wrong position
     */
    int getIncorrect() const;

    /**
     * @brief Sets the number of correct digits
     * @param c Number of correct digits
     */
    void setCorrect(int c);

    /**
     * @brief Sets the number of incorrect digits
     * @param i Number of incorrect digits
     */
    void setIncorrect(int i);
};

/**
 * @brief Equality comparison operator for Response objects
 * @param r1 First response
 * @param r2 Second response
 * @return true if both correct and incorrect counts match
 */
bool operator==(const Response& r1, const Response& r2);

/**
 * @brief Stream insertion operator for Response objects
 * @param os Output stream
 * @param r Response to output
 * @return Reference to the output stream
 */
std::ostream& operator<<(std::ostream& os, const Response& r);

#endif // RESPONSE_H
