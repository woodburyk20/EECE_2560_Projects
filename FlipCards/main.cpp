// EECE 2560 – Flip Card
// Katherine Woodbury, Nathan Tan, Yamin Mahmood, Bryce Pippin
//
// Main driver file for the Flip Card project. Contains declarations
// for playFlip and main.
//

#include <iostream>
#include "Deck.h"

void playFlip()
// Runs the Flip Card game. Creates a main deck and a hand deck,
// shuffles the main deck, deals 24 cards into the hand, then enters
// a loop where the player flips cards one at a time to accumulate
// points. 
//
// Scoring: ace=+10, face card=+5, 8/9/10=+0, 7=half points,
// 2-6=reset to 0. Hearts add 1 bonus point.
{
   int score = 0;

   // initialize main deck with full set of cards; hand starts empty
   Deck mainDeck(true);
   Deck handDeck(false);

   cout << "Main deck before shuffle: \n";
   cout << mainDeck << endl;

   // shuffle main deck three times for randomness
   mainDeck.shuffle();
   mainDeck.shuffle();
   mainDeck.shuffle();

   cout << "Main deck after shuffle: \n";
   cout << mainDeck << endl;

   // deal 24 cards from the main deck into the player's hand
   for (int i = 0; i < 24; i++)
   {
      node<Card>* dealtCard = mainDeck.deal();
      handDeck.replace(dealtCard);

   } // end for

   cout << "Current hand: \n";
   cout << handDeck << endl;

   cout << "Remaining cards in the main deck: \n";
   cout << mainDeck << endl;

   cout << "Starting main game cycle\n";

   // main game loop: continue until hand is empty or player quits
   while (handDeck.size() > 0)
   {
      cout << "What would you like to do?\n";
      cout << "   1: Flip Card\n";
      cout << "   2: End Game\n";

      int choice;
      cin >> choice;

      if (choice == 2)
      {
         break;
      } // end if

      // flip the top card and retrieve its value and suit
      node<Card>* flipped = handDeck.deal();
      Card c = flipped->nodeValue;
      cout << "You flipped: " << c << endl;

      int v = c.getValue();
      string s = c.getSuit();

      // apply scoring rules based on card value
      if (v == 1)
      {
         score += 10;           // ace is worth 10 points
      }
      else if (v >= 11)
      {
         score += 5;            // face cards are worth 5 points
      }
      else if (v >= 8)
      {
         score += 0;            // 8, 9, 10 are neutral
      }
      else if (v == 7)
      {
         score /= 2;            // 7 halves the current score
      }
      else
      {
         score = 0;             // 2-6 resets score to zero
      } // end if

      // apply heart suit bonus
      if (s == "Hearts")
      {
         score += 1;
      } // end if

      cout << "Current score: " << score << endl;

      delete flipped;

   } // end while

   // display final score when game ends
   cout << "Final Score: " << score << endl;

} // end playFlip

int main()
// Calls playFlip to start the game.
{
   playFlip();

   return 0;

} // end main