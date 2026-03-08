#include "deck.h"
#include <vector>
#include <random>

// Shuffle implementation based on C++ Standard Library random utilities:
// std::random_device, std::mt19937, and random index generation.
// Note: This implementation performs many random swaps of node values.
// Reference: https://en.cppreference.com/w/cpp/algorithm/random_shuffle.html

// Constructor
// Creates a standard 52-card deck in order and stores it in a linked list 
// starting at front.
Deck::Deck(bool makeStandardDeck) : front(NULL), deckSize(0) {

    if(makeStandardDeck) {
         // Array of valid suit strings used to create each Card
        std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

        // Generate 4 * 13 = 52 cards and append each to the linked list
        for (int s = 0; s < 4; s++) {
            for (int v = 1; v <= 13; v++) {
                pushBack(Card(v, suits[s]));   // Add card to end of deck
            }
        }
    }
}

// Destructor
// Frees all dynamically allocated nodes in the linked list.
Deck::~Deck() { clear(); };

// Deletes every node in the linked list and resets the deck to empty.
void Deck::clear() {
    node<Card>* current = front;

    // Walk through the list, deleting nodes one-by-one
    while (current != NULL) {
        node<Card>* temp = current;     // Save node to delete
        current = current->next;        // Move forward before deleting
        delete temp;                    // Free old node
    }

    // Reset deck state after clearing all nodes
    front = NULL;
    deckSize = 0;
}

// Appends a card to the end of the linked list.
void Deck::pushBack(const Card &c) {
    node<Card>* newNode = new node<Card>(c);   // Allocate new node storing c

    // If list is empty, this node becomes the front
    if (front == NULL) {
        front = newNode;
    } // endif
    else {
        // Otherwise, traverse to the last node and link the new node
        node<Card>* current = front;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    deckSize++;   // Track number of cards in the deck
}

// Returns the current number of cards in the deck.
int Deck::size() const {
    return deckSize;
}

// Shuffles the deck by performing many random swaps of node values.
// This keeps the linked list structure the same, but randomizes the Card data
// stored in each node.
void Deck::shuffle() {

    // No need to shuffle if there are fewer than 2 cards
    if (deckSize < 2) return;

    // Random generator setup
    std::random_device rd;                      // Non-deterministic seed source
    std::mt19937 gen(rd());                     // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(0, deckSize - 1); // Random indices

    // Repeat many times to increase mixing of cards
    for (int k = 0; k < 1000; k++) {

        // Pick two random positions in the deck
        int i = dist(gen);
        int j = dist(gen);

        // Find the i-th and j-th nodes by walking from the front
        node<Card>* nodeI = front;
        node<Card>* nodeJ = front;

        for (int a = 0; a < i; a++)
            nodeI = nodeI->next;

        for (int b = 0; b < j; b++)
            nodeJ = nodeJ->next;

        // Swap the card values stored in the two nodes
        Card temp = nodeI->nodeValue;
        nodeI->nodeValue = nodeJ->nodeValue;
        nodeJ->nodeValue = temp;
    }
}

node<Card>* Deck::deal() {
    if (front == NULL) {
        return NULL;
    } //endif

    node<Card>* topCard = front;    // Save old front node
    front = front->next;            // Move front forward

    topCard->next = NULL;           // Disconnect returned node
    
    deckSize--;

    return topCard;
}

void Deck::replace(node<Card>* cardNode) {
    if(cardNode == NULL) {
        return;
    } //endif

    cardNode->next = NULL; // make sure it ends the list

    if (front == NULL) {
        front = cardNode;
    } else {
        node<Card>* current = front;
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = cardNode;
    }

    deckSize++;
}

// Overloaded << operator
// Prints the deck from front to back, one card per line, with numbering.
ostream& operator<<(ostream& os, const Deck& d) {

    node<Card>* current = d.front;   // Start at the front of the list
    int count = 1;                   // 1-based numbering for printing

    // Walk through the linked list and print each card
    while (current != NULL) {
        os << count << ". " << current->nodeValue << "\n";
        current = current->next;
        count++;
    }

    return os;   // Return stream for chaining
}