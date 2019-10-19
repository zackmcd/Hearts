#include <iostream>
#include "card.h"

using namespace std;

Card::Card() : num(0), suit(type::UNASSIGNED) {} 

Card::Card(int n, type::SUIT s) : num(n), suit(s) {}

void Card::alter(int n, type::SUIT s)
{
  num = n;
  suit = s;
}

void Card::print()

{
  int temp = 0;
  const char *name;
  bool check = false;

  if (getNum() == 0)
    return;

  if (getNum() == 11)
  {
    check = true;
    name = "Jack";
  }
  else if (getNum() == 12)
  {
    check = true;
    name = "Queen";
  }
  else if (getNum() == 13)
  {
    check = true;
    name = "King";
  }
  else if (getNum() == 14)
  {
    check = true;
    name = "Ace";
  }

  if (check)
  {
    cout << name << " of ";
  }
  else
  {
    cout << getNum() << " of ";
  }

  if (getSuit() == 100)
    cout << "Clubs" << endl;
  else if (getSuit() == 200)
    cout << "Spades" << endl;
  else if (getSuit() == 300)
    cout << "Diamonds" << endl;
  else if (getSuit() == 400)
    cout << "Hearts" << endl;

}

int Card::getNum() 
{
  return num;
}

type::SUIT Card::getSuit()
{
  return suit;
}

