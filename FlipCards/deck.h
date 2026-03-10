// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Header file for the Deck class. Contains declarations for Deck,
// clear, pushBack, shuffle, size, deal, replace, and operator<<.
//

#ifndef DECK_H
#define DECK_H

#include "card.h"    // Card class definition
#include "d_node.h"  // node<T> linked list template

class Deck
{
   public:

      Deck(bool makeStandardDeck);
      // Constructs a Deck object. If makeStandardDeck is true, builds
      // a standard 52-card deck (4 suits x 13 values) stored as a
      // linked list. If false, initializes an empty deck.

      ~Deck();
      // Destructor. Frees all dynamically allocated node memory.

      void shuffle();
      // Randomizes the order of cards currently in the deck.

      int size() const;
      // Returns the number of cards currently in the deck.

      node<Card>* deal();
      // Removes and returns the front node of the deck. The caller
      // is responsible for deleting the returned node when done.
      // Assumption: deck is non-empty before calling.

      void replace(node<Card>* cardNode);
      // Appends an existing node to the back of the deck.
      // Assumption: cardNode is a valid, non-null pointer.

      friend ostream& operator<<(ostream& os, const Deck& d);
      // Prints all cards in the deck in order to the output stream os.

   private:

      node<Card>* front;  // pointer to the first node in the list
      int deckSize;       // current number of cards in the deck

      void clear();
      // Deletes all nodes in the linked list and resets the deck
      // to an empty state.

      void pushBack(const Card& c);
      // Appends a new node containing c to the end of the linked
      // list. Used internally when building the deck.

}; // end class Deck

#endif // DECK_H