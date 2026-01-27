// EECE 2560: Fundamentals of Engineering Algorithms
// Mastermind Project Part A
// Nathan Tan
//
// Complete Mastermind program with code class and main function.
// Tests the checkCorrect and checkIncorrect functions with three
// sample guess codes.

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class code
{
public:
    // Constructor
    // Initializes a code object with length n and digit range [0, m-1]
    // Precondition: n > 0 and m > 0
    // Postcondition: code vector is initialized with size n
    code(int n, int m);

    // Initializes the code randomly
    // Precondition: code object has been constructed
    // Postcondition: code vector is filled with random digits in range [0, m-1]
    void initializeRandom();

    // Checks the number of correct digits in correct locations
    // Parameters: guess - the guess code object to compare against
    // Returns: number of digits that match in position and value
    // Precondition: guess has the same length as the secret code
    int checkCorrect(const code& guess) const;

    // Checks the number of correct digits in incorrect locations
    // Parameters: guess - the guess code object to compare against
    // Returns: number of digits that are correct but in wrong position
    // Precondition: guess has the same length as the secret code
    // Note: Digits already counted as correct are not counted again
    int checkIncorrect(const code& guess) const;

    // Prints the code to the console
    // Postcondition: code is displayed as comma-separated values
    void printCode() const;

    // Gets the length of the code
    // Returns: the length n of the code
    int getLength() const;

    // Sets a specific digit in the code (for testing purposes)
    // Parameters: index - position to set, value - digit value to set
    // Precondition: 0 <= index < n and 0 <= value < m
    void setDigit(int index, int value);

private:
    int n;              // length of the code
    int m;              // range of digits [0, m-1]
    vector<int> digits; // the code itself
};

// Implementation of code class member functions

code::code(int n, int m)
// Constructor that initializes a code object with length n and range m
{
    this->n = n;
    this->m = m;
    digits.resize(n);

    // Initialize random seed
    srand(time(0));
}

void code::initializeRandom()
// Fills the code vector with random digits in the range [0, m-1]
{
    for (int i = 0; i < n; i++)
    {
        digits[i] = rand() % m;
    }
}

int code::checkCorrect(const code& guess) const
// Returns the number of digits that are correct and in the correct position
{
    int correctCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            correctCount++;
        }
    }

    return correctCount;
}

int code::checkIncorrect(const code& guess) const
// Returns the number of digits that are correct but in the wrong position
// Note: Digits already counted as correct in position are not counted here
{
    int incorrectCount = 0;

    // Create temporary vectors to track which digits have been matched
    vector<bool> secretUsed(n, false);
    vector<bool> guessUsed(n, false);

    // First pass: mark digits that are correct in the correct position
    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            secretUsed[i] = true;
            guessUsed[i] = true;
        }
    }

    // Second pass: count correct digits in wrong positions
    for (int i = 0; i < n; i++)
    {
        if (!guessUsed[i])
        {
            // Look for this guess digit in other positions of the secret
            for (int j = 0; j < n; j++)
            {
                if (!secretUsed[j] && digits[j] == guess.digits[i])
                {
                    incorrectCount++;
                    secretUsed[j] = true;
                    break; // Move to next guess digit
                }
            }
        }
    }

    return incorrectCount;
}

void code::printCode() const
// Prints the code as comma-separated values
{
    for (int i = 0; i < n; i++)
    {
        cout << digits[i];

        if (i < n - 1)
        {
            cout << ", ";
        }
    }

    cout << endl;
}

int code::getLength() const
// Returns the length of the code
{
    return n;
}

void code::setDigit(int index, int value)
// Sets a specific digit in the code (used for testing)
{
    if (index >= 0 && index < n && value >= 0 && value < m)
    {
        digits[index] = value;
    }
    else
    {
        cout << "Error: Invalid index or value in setDigit" << endl;
    }
}

// Main function

int main()
{
    // Initialize the secret code with length 5 and digit range [0, 6]
    // Secret code will be: 1, 2, 3, 4, 5
    code secret(5, 7);

    // Manually set the secret code to 1, 2, 3, 4, 5
    secret.setDigit(0, 1);
    secret.setDigit(1, 2);
    secret.setDigit(2, 3);
    secret.setDigit(3, 4);
    secret.setDigit(4, 5);

    // Print the secret code
    cout << "Secret code: ";
    secret.printCode();
    cout << endl;

    // Test with first guess: (5, 0, 3, 2, 6)
    code guess1(5, 7);
    guess1.setDigit(0, 5);
    guess1.setDigit(1, 0);
    guess1.setDigit(2, 3);
    guess1.setDigit(3, 2);
    guess1.setDigit(4, 6);

    cout << "Guess 1: ";
    guess1.printCode();
    cout << "Correct: " << secret.checkCorrect(guess1) << endl;
    cout << "Incorrect: " << secret.checkIncorrect(guess1) << endl;
    cout << endl;

    // Test with second guess: (2, 1, 2, 2, 2)
    code guess2(5, 7);
    guess2.setDigit(0, 2);
    guess2.setDigit(1, 1);
    guess2.setDigit(2, 2);
    guess2.setDigit(3, 2);
    guess2.setDigit(4, 2);

    cout << "Guess 2: ";
    guess2.printCode();
    cout << "Correct: " << secret.checkCorrect(guess2) << endl;
    cout << "Incorrect: " << secret.checkIncorrect(guess2) << endl;
    cout << endl;

    // Test with third guess: (1, 3, 3, 4, 5)
    code guess3(5, 7);
    guess3.setDigit(0, 1);
    guess3.setDigit(1, 3);
    guess3.setDigit(2, 3);
    guess3.setDigit(3, 4);
    guess3.setDigit(4, 5);

    cout << "Guess 3: ";
    guess3.printCode();
    cout << "Correct: " << secret.checkCorrect(guess3) << endl;
    cout << "Incorrect: " << secret.checkIncorrect(guess3) << endl;
    cout << endl;

    return 0;
}