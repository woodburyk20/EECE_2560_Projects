#ifndef CODE_H
#define CODE_H

#include <vector>

class Code
{
private:
    std::vector<int> digits;  // Stores the digits that make up this code
    int n;                    // Code length (number of digits)
    int m;                    // Digit range size; valid digits are [0, m - 1]

public:
    Code(int length, int range);
    // Constructs a Code object of the given length and digit range.

    void initRandom();
    // Randomly initializes the code digits in the range [0, m - 1].

    bool setDigits(const std::vector<int>& d);
    // Sets the code digits to the values in d after validating length
    // and range; used to construct guess codes in Part (a).

    int checkCorrect(const Code& guess) const;
    // Returns the number of digits that match in both value and position.

    int checkIncorrect(const Code& guess) const;
    // Returns the number of digits that match in value but appear in a
    // different position, counting each digit only once.

    void print() const;
    // Prints the digits of the code separated by spaces.
};

#endif
