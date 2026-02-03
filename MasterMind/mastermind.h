#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "code.h"
#include "response.h"

class Mastermind
{
private:
    Code secret;
    int n;
    int m;

public:
    // default constructor: n=5, m=10
    Mastermind();

    // constructor with user-provided n,m
    Mastermind(int n_in, int m_in);

    void printSecret() const;

    Code humanGuess() const;
    Response getResponse(const Code& guess) const;
    bool isSolved(const Response& r) const;

    void playGame();
};

#endif
