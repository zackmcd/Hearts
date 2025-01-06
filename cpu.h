#ifndef CPU_H
#define CPU_H

#include "card.h"
#include "trick.h"

class CPU
{
    Card *hand;
    bool *used;
    bool shoot; // false = bitch, true = shooting the moon
  public :
    CPU();
    void insert(Card c, int index);
    void print();
    bool start();
    void startHand();
    void reset();
    void order();
    bool suitCheck(type::SUIT &s);
    int winners(int *nums, int size, int top, int *trash);
    void playCard(Trick &T, int p, type::SUIT &s, int pos);
    void pass(Card &c1, Card &c2, Card &c3);
    void accept(Card &c1, Card &c2, Card &c3);
    virtual ~CPU();
};

#endif
