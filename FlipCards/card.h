// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Header file for the Card class. Contains declarations for Card,
// getValue, setValue, getSuit, setSuit, and operator<<.
//

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

class Card
{
   public:

      Card(int value = 1, string suit = "Clubs");
      // Constructs a Card with the given numeric value and suit string.
      // Default: Ace of Clubs. Expected suits: "Clubs", "Diamonds",
      // "Hearts", "Spades". Expected values: 1–13.

      Card(const Card& newCard);
      // Copy constructor. Initializes this Card as a copy of newCard.

      Card& operator=(const Card& newCard);
      // Assignment operator. Copies value and suit from newCard into
      // this Card. Returns a reference to this Card.

      int getValue() const;
      // Returns the numeric value of this card (1–13).

      void setValue(int newValue);
      // Sets the numeric value of this card to newValue.

      string getSuit() const;
      // Returns the suit of this card as a string.

      void setSuit(const string& suit);
      // Sets the suit of this card to the given string.

      friend ostream& operator<<(ostream& os, const Card& c);
      // Prints a human-readable representation of this card to os.
      // Returns os to support stream chaining.

   private:

      int value;     // numeric value of the card (1–13)
      string suit;   // suit of the card: Clubs, Diamonds, Hearts, Spades

}; // end class Card

#endif // CARD_H