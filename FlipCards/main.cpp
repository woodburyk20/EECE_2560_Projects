// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Main driver file for the Flip Card project.
// This program creates a Deck object, displays the deck
// before shuffling, shuffles it multiple times,
// then displays the shuffled deck.

#include <iostream>
#include "Deck.h"

void playFlip() {

    int score = 0;
    
    Deck mainDeck(true);
    Deck handDeck(false);

    mainDeck.shuffle();
    mainDeck.shuffle();
    mainDeck.shuffle();

    cout << "Main deck after shuffle: \n";
    cout << mainDeck << endl;

    for (int i = 0; i < 24; i++) {
        node<Card>* dealtCard = mainDeck.deal();
        handDeck.replace(dealtCard);
    }

    cout << "Current hand: \n";
    cout << handDeck << endl;

    cout << "Remaining cards in the main deck: \n";
    cout << mainDeck << endl;


    cout << "Starting main game cycle";

    while (handDeck.size() > 0) {
        cout << "What would you like to do?";
        cout << "   1: Flip Card";
        cout << "   2: End Game";

        int choice;
        cin >> choice;

        if (choice == 2) {
            break;
        }

        node<Card>* flipped = handDeck.deal();
        Card c = flipped->nodeValue;
        cout << "You flipped: " << c << endl;

        int v = c.getValue();
        string s = c.getSuit();

        // Apply scoring rules
        if (v == 1) {
            score += 10;
        } else if (v >= 11) {
            score += 5;
        } else if (v >= 8) {
            score += 0;
        } else {
            score = 0;
        }

        // Heart bonus
        if (s == "heart") {
            score += 1;
        }

        // Print Score
        cout << "Current score: " << score << endl;

        delete flipped;
    }

    // End game message
    cout << "Final Score: " << score << endl;

}

int main() {

    playFlip();

    return 0;
}