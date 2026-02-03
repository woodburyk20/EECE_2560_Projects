#include "response.h"

using namespace std;

/**
 * Default constructor.
 * Initializes a response with zero correct and zero incorrect.
 */
Response::Response() 
    : correct(0), incorrect(0) 
{
}

/**
 * Parameterized constructor.
 * Initializes a response with specified correct and incorrect counts.
 * 
 * @param c Number of correct digits (right value, right position)
 * @param i Number of incorrect digits (right value, wrong position)
 */
Response::Response(int c, int i) 
    : correct(c), incorrect(i) 
{
}

/**
 * Gets the number of correct digits.
 * 
 * @return Number of digits in correct position with correct value
 */
int Response::getCorrect() const
{
    return correct;
}

/**
 * Gets the number of incorrect digits.
 * 
 * @return Number of digits with correct value but wrong position
 */
int Response::getIncorrect() const
{
    return incorrect;
}

/**
 * Sets the number of correct digits.
 * 
 * @param c Number of correct digits
 */
void Response::setCorrect(int c)
{
    correct = c;
}

/**
 * Sets the number of incorrect digits.
 * 
 * @param i Number of incorrect digits
 */
void Response::setIncorrect(int i)
{
    incorrect = i;
}

/**
 * Equality comparison operator (global function).
 * Compares two Response objects for equality.
 * 
 * @param r1 First response
 * @param r2 Second response
 * @return true if both correct and incorrect counts are equal
 */
bool operator==(const Response& r1, const Response& r2)
{
    return (r1.getCorrect() == r2.getCorrect() && 
            r1.getIncorrect() == r2.getIncorrect());
}

/**
 * Stream insertion operator (global function).
 * Formats and outputs a Response object to a stream.
 * 
 * @param os Output stream
 * @param r Response to output
 * @return Reference to the output stream for chaining
 */
ostream& operator<<(ostream& os, const Response& r)
{
    os << "  Right digit in the right location: " << r.getCorrect() << "\n";
    os << "  Right digit in the wrong location: " << r.getIncorrect() << "\n";
    return os;
}
