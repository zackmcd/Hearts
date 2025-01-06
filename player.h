#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "trick.h"

class Player
{
    Card *hand;
    bool *used; // false if still in hand // true if used
  public :
    Player();
    void insert(Card c, int index);
    void print();
    bool start();
    void startHand();
    void reset();
    void order();
    void playCard(Trick &T, int p, type::SUIT &s);
    void pass(Card &c1, Card &c2, Card &c3);
    void accept(Card &c1, Card &c2, Card &c3);
    virtual ~Player();
};

#endif
