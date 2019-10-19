#ifndef DECK_H
#define DECK_H

#include "card.h"

class Deck
{
  public :
    Card *deck;
    bool *dealt; // true = it was dealt // false = it is still needs to be dealt
    
    Deck();
    void Create();
    void print();

};

#endif // DECK_H
