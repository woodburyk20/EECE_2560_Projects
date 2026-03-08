// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Header file for the Deck class.
// This class represents a full deck of playing cards stored
// as a singly linked list using node<Card>.
// The deck supports construction of a standard 52-card deck,
// shuffling, size checking, and printing.

#ifndef DECK_H
#define DECK_H

#include "card.h"     // Card class definition
#include "d_node.h"   // node<T> linked list template

class Deck {

private:
    // Pointer to the first node in the linked list.
    // Each node stores a Card and a pointer to the next node.
    node<Card>* front;

    // Tracks the current number of cards in the deck.
    int deckSize;

    // Deletes all nodes in the linked list
    // and resets the deck to an empty state.
    void clear();

    // Appends a Card to the end of the linked list.
    // Used internally when building the deck.
    void pushBack(const Card& c);
    
public: 

    // Constructor
    // Builds a standard 52-card deck (4 suits × 13 values)
    // and stores it in the linked list.
    Deck(bool makeStandardDeck);

    // Destructor
    // Frees all dynamically allocated memory.
    ~Deck();

    // Randomizes the order of cards in the deck.
    void shuffle();

    // Returns the number of cards currently in the deck.
    int size() const;


    node<Card>* deal();
    void replace(node<Card>* cardNode);

    // Overloaded << operator
    // Prints all cards in the deck in order.
    friend ostream& operator<<(ostream& os, const Deck &d);

};

#endif // DECK_H