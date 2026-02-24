// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Header file for the Card class.
// This class represents a single playing card.
// A card has a numeric value and a suit (Club, Diamond, Heart, Spade).
// The class provides constructors, setters, getters, and an overloaded
// << operator for printing.

#ifndef CARD_H
#define CARD_H

#include <iostream>   // For ostream
#include <string>     // For string

using namespace std;

class Card {
private:
    // Stores the card’s numeric value.
    int value;

    // Stores the suit of the card.
    // Expected values: "Club", "Diamond", "Heart", "Spade"
    string suit;

public:
    // Constructor
    // Initializes a card with a given value and suit.
    // Default: Ace of Clubs.
    Card(int value = 1, string suit = "Clubs");

    // Returns the numeric value of the card.
    int getValue() const;

    // Sets the numeric value of the card.
    void setValue(int newValue);

    // Returns the suit of the card.
    string getSuit() const;

    // Sets the suit of the card.
    void setSuit(const string& suit);

    // Overloaded << operator
    // Allows printing a Card object using:
    // cout << card;
    friend ostream& operator<<(ostream& os, const Card& c);
};

#endif // CARD_H