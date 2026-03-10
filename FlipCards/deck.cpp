// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Implementation file for the Deck class. Contains definitions for
// Deck, ~Deck, clear, pushBack, size, shuffle, deal, replace,
// and operator<<.
//
// Shuffle implementation based on C++ Standard Library random utilities:
// std::random_device, std::mt19937, and random index generation.
// Reference: https://en.cppreference.com/w/cpp/algorithm/random_shuffle

#include "deck.h"
#include <vector>
#include <random>

Deck::Deck(bool makeStandardDeck) : front(NULL), deckSize(0)
// Constructs a Deck object. If makeStandardDeck is true, builds a
// standard 52-card deck (4 suits x 13 values) appended in order to
// the linked list. If false, initializes an empty deck.
{
   if (makeStandardDeck)
   {
      // array of suit strings used to construct each Card
      std::string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};

      // generate all 52 cards and append each to the linked list
      for (int s = 0; s < 4; s++)
      {
         for (int v = 1; v <= 13; v++)
         {
            pushBack(Card(v, suits[s]));

         } // end for v

      } // end for s

   } // end if

} // end Deck constructor

Deck::~Deck()
// Destructor. Frees all dynamically allocated nodes in the linked list.
{
   clear();

} // end ~Deck

void Deck::clear()
// Deletes every node in the linked list and resets the deck to empty.
{
   node<Card>* current = front;

   // walk through the list deleting each node one by one
   while (current != NULL)
   {
      node<Card>* temp = current;  // save pointer to node being deleted
      current = current->next;     // advance before deleting
      delete temp;

   } // end while

   // reset deck state after all nodes are freed
   front = NULL;
   deckSize = 0;

} // end clear

void Deck::pushBack(const Card& c)
// Appends a new node containing c to the end of the linked list.
// Used internally when constructing or rebuilding the deck.
{
   node<Card>* newNode = new node<Card>(c);

   // if the list is empty, the new node becomes the front
   if (front == NULL)
   {
      front = newNode;
   }
   else
   {
      // traverse to the last node and link the new node
      node<Card>* current = front;

      while (current->next != NULL)
      {
         current = current->next;
      }

      current->next = newNode;

   } // end if

   deckSize++;

} // end pushBack

int Deck::size() const
// Returns the current number of cards in the deck.
{
   return deckSize;

} // end size

void Deck::shuffle()
// Shuffles the deck by performing 1000 random swaps of Card values
// between nodes. The linked list structure is preserved; only the
// data stored in each node is exchanged.
// Assumption: deck contains at least 2 cards to be worth shuffling.
{
   // no meaningful shuffle possible with fewer than 2 cards
   if (deckSize < 2)
      return;

   // set up Mersenne Twister RNG with a non-deterministic seed
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dist(0, deckSize - 1);

   // perform 1000 random swaps to thoroughly mix the deck
   for (int k = 0; k < 1000; k++)
   {
      // pick two random positions in the deck
      int i = dist(gen);
      int j = dist(gen);

      // walk from front to locate the i-th and j-th nodes
      node<Card>* nodeI = front;
      node<Card>* nodeJ = front;

      for (int a = 0; a < i; a++)
         nodeI = nodeI->next;

      for (int b = 0; b < j; b++)
         nodeJ = nodeJ->next;

      // swap the Card values stored in the two nodes
      Card temp = nodeI->nodeValue;
      nodeI->nodeValue = nodeJ->nodeValue;
      nodeJ->nodeValue = temp;

   } // end for

} // end shuffle

node<Card>* Deck::deal()
// Removes and returns the front node of the deck. The caller is
// responsible for deleting the returned node. Returns NULL if the
// deck is empty.
{
   if (front == NULL)
      return NULL;

   node<Card>* topCard = front;  // save the front node to return
   front = front->next;          // advance front to next card
   topCard->next = NULL;         // isolate the returned node

   deckSize--;

   return topCard;

} // end deal

void Deck::replace(node<Card>* cardNode)
// Appends an existing node to the back of the deck. Does nothing if
// cardNode is NULL.
// Assumption: cardNode is a valid pointer not already in the list.
{
   if (cardNode == NULL)
      return;

   cardNode->next = NULL;  // ensure node does not trail extra links

   // if deck is empty, the node becomes the new front
   if (front == NULL)
   {
      front = cardNode;
   }
   else
   {
      // traverse to the last node and attach cardNode
      node<Card>* current = front;

      while (current->next != NULL)
      {
         current = current->next;
      }

      current->next = cardNode;

   } // end if

   deckSize++;

} // end replace

ostream& operator<<(ostream& os, const Deck& d)
// Prints all cards in d from front to back, one per line, with
// 1-based numbering. Returns os to support stream chaining.
{
   node<Card>* current = d.front;  // start traversal at front of list
   int count = 1;                  // 1-based index for display

   // walk the list and print each card
   while (current != NULL)
   {
      os << count << ". " << current->nodeValue << "\n";
      current = current->next;
      count++;

   } // end while

   return os;

} // end operator