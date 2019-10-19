#include <iostream>
#include "trick.h"
#include "scoreboard.h"
#include "card.h"

using namespace std;

Trick::Trick()
{
  cards = new Card[5];
  who = new bool[5];
  who[0] = false;
  s = type::UNASSIGNED;
}

void Trick::start(int T)
{
  who[T] = true;
  type::SUIT c = type::CLUBS;
  Card temp(2, c);
  cards[T] = temp;
}

void Trick::print()
{
  cout << "The Current Trick : " << endl;
  for (int i = 0; i < 5; i++)
    if (who[i])
      cards[i].print();
}

int Trick::points(Scoreboard &S, type::SUIT ss)
{
  int count = 0;
  int temp = 0, index = 0;

  for (int i = 0; i < 5; i++)
  {
    if (who[i])
    {
      if (cards[i].getSuit() == type::HEARTS)
      {
        count++;
      }
      else if (cards[i].getSuit() == type::SPADES && cards[i].getNum() == 12)
      {
        count = count + 13;
      }
    }
  }

  //cout << "C = " << count << endl;
  //cout << "S = " << s << endl;

  for (int i = 0; i < 5; i++)
  {
    if (who[i])
    {
      if (cards[i].getSuit() == s)
      {
        if (cards[i].getNum() > temp)
	{
          temp = cards[i].getNum();
	  //cout << "TEMP = " << temp << endl;
	  index = i;
	}
      }
    }
  }

  if (index == 1)
    S.Update(count, 0, 0, 0);
  else if (index == 2)
    S.Update(0, count, 0, 0);
  else if (index == 3)
    S.Update(0, 0, count, 0);
  else if (index == 4)
    S.Update(0, 0, 0, count);

  return index;

}

void Trick::insert(int n, type::SUIT s2, int t)
{
  Card c(n, s2);
  cards[t] = c;
  who[t] = true;
}

void Trick::setS(type::SUIT x)
{
  s = x;
}
