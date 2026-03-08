// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Implementation file for the Card class.
// This file defines all member functions for creating,
// validating, accessing, and printing a playing card.

#include "Card.h"
#include <stdexcept>   // For out_of_range and invalid_argument

using namespace std;

// Constructor
// Initializes a Card object with a given value and suit.
// Uses setter functions to ensure validation logic is applied.
Card::Card(int value, std::string suit) {
    setValue(value);   // Validate and set card value
    setSuit(suit);     // Validate and set card suit
}

Card::Card(const Card& newCard) {
    value = newCard.getValue();
    suit = newCard.getSuit();
}

Card& Card::operator=(const Card& newCard) {
    
    value = newCard.value;
    suit = newCard.suit;
    return *this;
}

// Sets the numeric value of the card.
// Valid values are 1–13
// Throws out_of_range if value is invalid.
void Card::setValue(int v) {
    if (v < 1 || v > 13) {
        throw out_of_range("Card value must be between 1 and 13.");
    } // endif

    value = v;   // Store validated value
}

// Sets the suit of the card.
// Valid suits: "Clubs", "Diamonds", "Hearts", "Spades".
// Throws invalid_argument if suit is invalid.
void Card::setSuit(const std::string& s) {
    if (s != "Clubs" && s != "Diamonds" && s != "Hearts" && s != "Spades") {
        throw invalid_argument("Invalid suit.");
    } // endif

    suit = s;   // Store validated suit
}

// Returns the numeric value of the card.
int Card::getValue() const {
    return value;
}

// Returns the suit of the card.
string Card::getSuit() const {
    return suit;
}

// Overloaded << operator
// Prints the card in readable format:
ostream& operator<<(ostream& os, const Card& c) {
    string valueStr;

    // Convert numeric value into face name if needed
    if (c.value == 1) {
        valueStr = "Ace";
    } // endif
    else if (c.value == 11) {
        valueStr = "Jack";
    } // endif
    else if (c.value == 12) {
        valueStr = "Queen";
    } // endif
    else if (c.value == 13) {
        valueStr = "King";
    } // endif
    else {
        valueStr = to_string(c.value);   // Number cards (2–10)
    }

    // Output formatted card description
    os << valueStr << " of " << c.suit;

    return os;   // Return stream for chaining
}