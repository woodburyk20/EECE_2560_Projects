// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Implementation file for the Card class. Contains definitions for
// Card, getValue, setValue, getSuit, setSuit, and operator<<.
//

#include "Card.h"
#include <stdexcept>

using namespace std;

Card::Card(int value, std::string suit)
// Constructs a Card with the given value and suit. Uses setter
// functions so that validation logic is applied on construction.
{
   setValue(value);
   setSuit(suit);

} // end Card constructor

Card::Card(const Card& newCard)
// Copy constructor. Initializes this Card as a copy of newCard.
{
   value = newCard.getValue();
   suit = newCard.getSuit();

} // end Card copy constructor

Card& Card::operator=(const Card& newCard)
// Assignment operator. Copies value and suit from newCard into this
// Card. Returns a reference to this Card.
{
   value = newCard.value;
   suit = newCard.suit;
   return *this;

} // end operator=

int Card::getValue() const
// Returns the numeric value of this card (1–13).
{
   return value;

} // end getValue

string Card::getSuit() const
// Returns the suit of this card as a string.
{
   return suit;

} // end getSuit

void Card::setValue(int v)
// Sets the numeric value of this card to v.
// Throws out_of_range if v is not between 1 and 13.
{
   if (v < 1 || v > 13)
   {
      throw out_of_range("Card value must be between 1 and 13.");
   } // end if

   value = v;

} // end setValue

void Card::setSuit(const std::string& s)
// Sets the suit of this card to s.
// Throws invalid_argument if s is not one of: "Clubs", "Diamonds",
// "Hearts", "Spades".
{
   if (s != "Clubs" && s != "Diamonds" && s != "Hearts" && s != "Spades")
   {
      throw invalid_argument("Invalid suit.");
   } // end if

   suit = s;

} // end setSuit

ostream& operator<<(ostream& os, const Card& c)
// Prints the card in human-readable format (e.g. "Ace of Spades",
// "7 of Diamonds"). Returns os to support stream chaining.
{
   string valueStr;

   // convert numeric value to face name where applicable
   if (c.value == 1)
   {
      valueStr = "Ace";
   }
   else if (c.value == 11)
   {
      valueStr = "Jack";
   }
   else if (c.value == 12)
   {
      valueStr = "Queen";
   }
   else if (c.value == 13)
   {
      valueStr = "King";
   }
   else
   {
      valueStr = to_string(c.value);  // number cards print as digits
   } // end if

   os << valueStr << " of " << c.suit;

   return os;

} // end operator