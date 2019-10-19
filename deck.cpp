#include "card.h"
#include "deck.h"

Deck::Deck()
{
  deck = new Card[52];
  dealt = new bool[52];
}

void Deck::Create()
{

  for (int i = 0; i < 52; i++)
    dealt[i] = false;

  int num = 2;
  type::SUIT place = type::CLUBS;

  for (int i = 0; i < 52; i++)
  {
    Card temp(num, place);
    deck[i] = temp;
    num++;

    if (num == 15)
    {
      num = 2;
      if (place == type::CLUBS)
        place = type::SPADES;
      else if (place == type::SPADES)
        place = type::DIAMONDS;
      else if (place == type::DIAMONDS)
        place = type::HEARTS;
    }

  }

}

void Deck::print()
{
  for (int i = 0; i < 52; i++)
    deck[i].print();
}

