// EECE 2560 – Project Mastermind (Part B)
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Header file for Response class.
// Stores the response to a guess.

#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

class Response
{
private:
    int correct;    // exact matches
    int incorrect;  // value matches, wrong position

public:
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
    Response(int c = 0, int i = 0);

    void setCorrect(int c); // function for setting number of correct digits
    void setIncorrect(int i); // function for setting the number of incorrect digits

    int getCorrect() const; // returns number of correct digits
    int getIncorrect() const; // returns number of incorrect digits
};

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
bool operator==(const Response& r1, const Response& r2);

/*
 * Overloads the stream insertion operator so a Response can be printed with cout.
 * This prints a human-readable summary of the codemaker's response.
 * 
 * Parameters:
 *   os : the output stream to write to (e.g., cout or an ofstream)
 *   r  : the Response object being printed
 */
std::ostream& operator<<(std::ostream& os, const Response& r);

#endif
