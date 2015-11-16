/*
 * File: CountFifteens.cpp
 * -----------------------
 * Name: aotian
 * Section: csb
 * This file is the starter code for the CountFifteens problem from
 * Assignment #3.
 */

#include <exception>
#include <iostream>
#include <string>
#include "card.h"
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "vector.h"
using namespace std;

/* Function prototypes */
int countFifteens(Vector<Card> & cards, int totalWays = 0);

/*
 * Main program
 * ------------
 * This test program does no error-checking on the input.  One of the
 * extensions you might consider is adding code to this program (and
 * possibly to the Card class) to allow the program to report errors.
 */

int main() {
   while (true) {
      string line = getLine("Enter a hand of cards: ");
      if (line == "") break;
      TokenScanner scanner(line);
      scanner.ignoreWhitespace();
      Vector<Card> hand;
      while (scanner.hasMoreTokens()) {
         hand.add(Card(scanner.nextToken()));
      }
      int nWays = countFifteens(hand);
      string plural = (nWays == 1) ? "" : "s";
      cout << nWays << " way" << plural << endl;
   }
   return 0;
}

/*
 * Counts the number of ways of making a total of 15 from the vector of
 * cards.
 */
int countFifteens (Vector<Card> &cards, int totalWays){
    if(cards.isEmpty () && totalWays != 15){
        return 0;
    }else if(cards.isEmpty () && totalWays == 15){
        return 1;
    }else{
        int cardRank = cards[0].getRank ();
        totalWays+=cardRank;
        cout<< "total = " << totalWays << endl;
        Vector<Card> cardsCopy = cards;
        cardsCopy.remove (0);
        return countFifteens (cardsCopy, totalWays) + countFifteens (cardsCopy, totalWays - cardRank);
    }
}
