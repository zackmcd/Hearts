#ifndef CARD_H_
#define CARD_H_

namespace type
{
  enum SUIT { CLUBS = 100, SPADES = 200, DIAMONDS = 300, HEARTS = 400, UNASSIGNED = 500};
}

class Card
{
    int num;
    type::SUIT suit;

  public :
    Card();
    Card(int n, type::SUIT s);
    void alter(int n, type::SUIT s);
    void print();
    int getNum();
    type::SUIT getSuit();

};

#endif
