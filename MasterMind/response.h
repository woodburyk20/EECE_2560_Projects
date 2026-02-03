#ifndef RESPONSE_H
#define RESPONSE_H

#include <iostream>

class Response
{
private:
    int correct;    // exact matches
    int incorrect;  // value matches, wrong position

public:
    Response(int c = 0, int i = 0);

    void setCorrect(int c);
    void setIncorrect(int i);

    int getCorrect() const;
    int getIncorrect() const;
};

// global operator overloads (required)
bool operator==(const Response& r1, const Response& r2);
std::ostream& operator<<(std::ostream& os, const Response& r);

#endif
