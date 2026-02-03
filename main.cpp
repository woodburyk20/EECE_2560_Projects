#include "mastermind.h"
#include <iostream>

using namespace std;

/**
 * @brief Main driver program for Mastermind game
 * 
 * Initializes a Mastermind game object and starts the game loop.
 * Users can modify the constructor call to use custom parameters
 * (code length and digit range) if desired.
 * 
 * @return 0 on successful completion
 */
int main()
{
    // Option 1: Use default parameters (n=5, m=10)
    Mastermind game;
    
    // Option 2: Use custom parameters (uncomment to use)
    // Example: 4-digit code with values 0-7
    // Mastermind game(4, 8);
    
    // Start the game
    game.playGame();
    
    cout << "\nThank you for playing Mastermind!\n";
    
    return 0;
}
