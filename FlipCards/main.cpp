// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Main driver file for the Flip Card project.
// This program creates a Deck object, displays the deck
// before shuffling, shuffles it multiple times,
// then displays the shuffled deck.

#include <iostream>
#include "Deck.h"

int main() {

    // Create a standard 52-card deck.
    // The Deck constructor automatically builds all cards.
    Deck deck;

    // Print the deck before shuffling.
    // Uses overloaded << operator for Deck.
    std::cout << "Deck BEFORE shuffle:\n";
    std::cout << deck << "\n";

    // Shuffle the deck three times.
    deck.shuffle();
    deck.shuffle();
    deck.shuffle();

    // Print the deck after shuffling.
    std::cout << "Deck AFTER shuffle:\n";
    std::cout << deck << "\n";

    // End program successfully.
    return 0;
}