#ifndef TRICK_H_
#define TRICK_H_

#include "card.h"
#include "scoreboard.h"

class Trick
{
  public :
    Card *cards;
    bool *who; // true if player at certain position played card
    type::SUIT s;

    Trick();
    void start(int T);
    void print();
    int points(Scoreboard &S, type::SUIT ss);
    void insert(int n, type::SUIT s22, int t);
    void setS(type::SUIT x);
};

#endif
