#include "response.h"

Response::Response(int c, int i) : correct(c), incorrect(i) {}

void Response::setCorrect(int c) { correct = c; }
void Response::setIncorrect(int i) { incorrect = i; }

int Response::getCorrect() const { return correct; }
int Response::getIncorrect() const { return incorrect; }

bool operator==(const Response& r1, const Response& r2)
{
    return (r1.getCorrect() == r2.getCorrect()) &&
           (r1.getIncorrect() == r2.getIncorrect());
}

std::ostream& operator<<(std::ostream& os, const Response& r)
{
    os << "Correct: " << r.getCorrect() << ", Incorrect: " << r.getIncorrect();
    return os;
}
