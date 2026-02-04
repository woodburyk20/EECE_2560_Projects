#include "response.h"  

/*
 * Constructor for a Response object.
 *
 * A Response represents the codemaker’s feedback for a single guess:
 * correct   = number of digits that are the right digit in the right location
 * incorrect = number of digits that are the right digit in the wrong  location
 *
 * Parameters:
 *   c : value to store in correct
 *   i : value to store in incorrect
 */
Response::Response(int c, int i) : correct(c), incorrect(i) {}

/*
 * Mutator that updates the "correct" count.
 * Used to modify an existing Response object after creation.
 * Parameter:
 *   c : new count for digits that are correct in both value and position
 */
void Response::setCorrect(int c) { correct = c; }

/*
 * Mutator that updates the "incorrect" count.
 * Parameter:
 *   i : new count for digits that are correct in value but wrong position
 */
void Response::setIncorrect(int i) { incorrect = i; }

/*
 * Accessor for the "correct" count.
 *
 * Returns: The number of digits that are the right digit in the right location.
 */
int Response::getCorrect() const { return correct; }

/*
 * Accessor for the "incorrect" count.
 *
 * Returns: The number of digits that are the right digit in the wrong location.
 */
int Response::getIncorrect() const { return incorrect; }

/*
 * Overloads the equality operator so two Response objects can be compared.
 *
 * Two Response objects are considered equal if BOTH fields match:
 *   - correct counts are the same
 *   - incorrect counts are the same
 *
 * Parameters:
 *   r1, r2 : the two Response objects being compared
 * Returns:
 *   true if r1 and r2 represent the same response, false otherwise
 */
bool operator==(const Response& r1, const Response& r2)
{
    return (r1.getCorrect() == r2.getCorrect()) &&
           (r1.getIncorrect() == r2.getIncorrect());
}

/*
 * Overloads the stream insertion operator so a Response can be printed with cout.
 * This prints a human-readable summary of the codemaker's response.
 * 
 * Parameters:
 *   os : the output stream to write to (e.g., cout or an ofstream)
 *   r  : the Response object being printed
 */
std::ostream& operator<<(std::ostream& os, const Response& r)
{
    os << "  Right digit in the right location: " << r.getCorrect() << "\n"
       << "  Right digit in the wrong location: " << r.getIncorrect();
    return os;
}
