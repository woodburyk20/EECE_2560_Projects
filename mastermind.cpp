// EECE 2560 – Project Mastermind (Part a)
// Katherine Woodbury, Nathan Tan, Yamin Mahmood
//
// This single-file program implements the Code class and a Part (a)
// main() that creates a random secret code, prints it, and prints the
// results of checkCorrect and checkIncorrect for three required sample
// guess codes.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Code
{
private:
   vector<int> digits;            // Stores the digits that make up this code
   int n;                         // Code length (number of digits)
   int m;                         // Digit range size; valid digits are [0, m - 1]

public:
   Code(int length, int range);
   // Constructs a Code object of the given length and digit range.

   void initRandom();
   // Randomly initializes the code digits in the range [0, m - 1].

   bool setDigits(const vector<int> &d);
   // Sets the code digits to the values in d after validating length
   // and range; used to construct guess codes in Part (a).

   int checkCorrect(const Code &guess) const;
   // Returns the number of digits that match in both value and position.

   int checkIncorrect(const Code &guess) const;
   // Returns the number of digits that match in value but appear in a
   // different position, counting each digit at most once.

   void print() const;
   // Prints the digits of the code separated by spaces.
};

Code::Code(int length, int range) : digits(), n(length), m(range)
{
   if ((n <= 0) || (m <= 0))                      // Validate constructor params
   {
      cerr << "Error: n and m must be positive." << endl;
      n = 0;
      m = 0;
   }

   digits.resize(n, 0);                           // Allocate n digits, init to 0
}

void Code::initRandom()
{
   for (int i = 0; i < n; i++)                    // Fill each position i
   {
      digits[i] = rand() % m;                     // Random digit in [0, m - 1]
   }
}

bool Code::setDigits(const vector<int> &d)
{
   if ((int) d.size() != n)                       // Validate length
   {
      cerr << "Error: digit vector has wrong length." << endl;
      return false;
   }

   for (int x : d)                                // Validate digit range
   {
      if ((x < 0) || (x >= m))
      {
         cerr << "Error: digit out of range." << endl;
         return false;
      }
   }

   digits = d;                                    // Copy validated digits
   return true;
}

int Code::checkCorrect(const Code &guess) const
{
   int count = 0;                                 // Number of exact matches

   for (int i = 0; i < n; i++)                    // Compare each position
   {
      if (digits[i] == guess.digits[i])           // Same digit, same position
      {
         count++;
      }
   }

   return count;
}

int Code::checkIncorrect(const Code &guess) const
{
   vector<bool> usedCode(n, false);               // Tracks used secret digits
   vector<bool> usedGuess(n, false);              // Tracks used guess digits
   int count = 0;                                 // Number of misplaced matches

   for (int i = 0; i < n; i++)                    // First mark exact matches
   {
      if (digits[i] == guess.digits[i])
      {
         usedCode[i] = true;
         usedGuess[i] = true;
      }
   }

   for (int i = 0; i < n; i++)                    // Check remaining guess digits
   {
      if (usedGuess[i])
      {
         continue;
      }

      for (int j = 0; j < n; j++)                 // Search unused secret digits
      {
         if ((!usedCode[j]) &&
             (guess.digits[i] == digits[j]))
         {
            count++;
            usedCode[j] = true;
            break;                                // Prevent double counting
         }
      }
   }

   return count;
}

void Code::print() const
{
   for (int x : digits)
   {
      cout << x << " ";
   }

   cout << endl;
}

int main()
{
   srand((unsigned) time(NULL));                  // Seed random generator

   int n = 5;                                     // Code length (Part a)
   int m = 7;                                     // Digit range (allows digit 6)

   Code secret(n, m);                             // Create secret code
   secret.initRandom();                           // Initialize randomly

   cout << "Secret code: ";
   secret.print();

   vector<vector<int>> guesses;                   // Required sample guesses
   guesses.push_back({5, 0, 3, 2, 6});
   guesses.push_back({2, 1, 2, 2, 2});
   guesses.push_back({1, 3, 3, 4, 5});

   for (const vector<int> &g : guesses)
   {
      Code guess(n, m);                           // Create guess code object
      guess.setDigits(g);                         // Set guess digits

      cout << "Guess: ";
      for (int x : g)
      {
         cout << x << " ";
      }

      cout << "-> Correct: " << secret.checkCorrect(guess)
           << ", Incorrect: " << secret.checkIncorrect(guess)
           << endl;
   }

   return 0;
}
