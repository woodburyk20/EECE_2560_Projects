#include "code.h"

#include <iostream>
#include <cstdlib>

Code::Code(int length, int range) : digits(), n(length), m(range)
{
    if ((n <= 0) || (m <= 0))
    {
        std::cerr << "Error: n and m must be positive." << std::endl;
        n = 0;
        m = 0;
    }

    digits.resize(n, 0);
}

void Code::initRandom()
{
    for (int i = 0; i < n; i++)
    {
        digits[i] = std::rand() % m;
    }
}

bool Code::setDigits(const std::vector<int>& d)
{
    if ((int)d.size() != n)
    {
        std::cerr << "Error: digit vector has wrong length." << std::endl;
        return false;
    }

    for (int x : d)
    {
        if ((x < 0) || (x >= m))
        {
            std::cerr << "Error: digit out of range." << std::endl;
            return false;
        }
    }

    digits = d;
    return true;
}

int Code::checkCorrect(const Code& guess) const
{
    int exactMatches = 0;

    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            exactMatches++;
        }
    }

    return exactMatches;
}

int Code::checkIncorrect(const Code& guess) const
{
    std::vector<bool> usedCode(n, false);
    std::vector<bool> usedGuess(n, false);
    int misMatch = 0;

    // Mark exact matches so we don't double count them as "incorrect"
    for (int i = 0; i < n; i++)
    {
        if (digits[i] == guess.digits[i])
        {
            usedCode[i] = true;
            usedGuess[i] = true;
        }
    }

    // Count digits that match in value but not in position
    for (int i = 0; i < n; i++)
    {
        if (usedGuess[i])
        {
            continue;
        }

        for (int j = 0; j < n; j++)
        {
            if ((!usedCode[j]) && (guess.digits[i] == digits[j]))
            {
                misMatch++;
                usedCode[j] = true;
                break;
            }
        }
    }

    return misMatch;
}

void Code::print() const
{
    for (int digit : digits)
    {
        std::cout << digit << " ";
    }
    std::cout << std::endl;
}
