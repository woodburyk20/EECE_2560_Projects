// EECE 2560 – Project Mastermind (Part a)
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin

#include "code.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand((unsigned)std::time(NULL));

    int n = 5;  // Code length
    int m = 7;  // Digit range

    Code secret(n, m);
    secret.initRandom();

    std::cout << "Secret code: ";
    secret.print();

    std::vector<std::vector<int>> guesses;
    guesses.push_back({5, 0, 3, 2, 6});
    guesses.push_back({2, 1, 2, 2, 2});
    guesses.push_back({1, 3, 3, 4, 5});

    for (const std::vector<int>& g : guesses)
    {
        Code guess(n, m);
        guess.setDigits(g);

        std::cout << "Guess: ";
        for (int x : g)
        {
            std::cout << x << " ";
        }

        std::cout << "-> Correct: " << secret.checkCorrect(guess)
                  << ", Incorrect: " << secret.checkIncorrect(guess)
                  << std::endl;
    }

    return 0;
}
