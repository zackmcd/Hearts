#include <iostream>
#include "trick.h"
#include "player.h"
#include "card.h"

using namespace std;

Player::Player()
{
  hand = new Card[13];
  used = new bool[13];

  for (int i = 0; i < 13; i++)
    used[i] = false;
}

Player::~Player()
{
  delete [] hand;
  delete [] used;
}

void Player::insert(Card c, int index)
{
  hand[index] = c;
}

void Player::print()
{
  for (int i = 0; i < 13; i++)
    if (!used[i])
    {
      cout << i << " : ";
      hand[i].print();
    }
}

bool Player::start()
{
  for (int i = 0; i < 13; i++)
    if (hand[i].getNum() == 2 && hand[i].getSuit() == 100)
      return true;

  return false;
}

void Player::startHand()
{
  int i = 0;
  for (; i < 13; i++)
    if (hand[i].getNum() == 2 && hand[i].getSuit() == 100)
    {
      used[i] = true;
      break;
    }

  cout << "Since you have the two of Clubs you must start the first trick." << endl;
  cout << endl;
  //cout << "TRICK :" << endl;
  //hand[i].print();
  cout << endl;

}

void Player::playCard(Trick &T, int p, type::SUIT &s)
{
  // for testing
  //T.insert(12, type::SPADES, p);
  //if (s == type::UNASSIGNED)
  //{
  //  T.setS(type::SPADES);
  //  s = type::SPADES;
  //}

  print();
  cout << endl;
  cout << "Select a card to play by entering the index of the card." << endl;

  int choice;
  cin >> choice;

  T.insert(hand[choice].getNum(), hand[choice].getSuit(), p);
  if (s == type::UNASSIGNED)
  {
    T.setS(hand[choice].getSuit());
    s = hand[choice].getSuit();
  }

  used[choice] = true;

  cout << endl;

}

void Player::pass(Card &c1, Card &c2, Card &c3)
{
  // for testing
  //c1 = hand[0];
  //c2 = hand[1];
  //c3 = hand[2];
  //used[0] = true;
  //used[1] = true;
  //used[2] = true;

  //print hand
  print();

  cout << "Select three cards to pass by entering the index of each card." << endl;

  int s1, s2, s3;
  cin >> s1;
  cin >> s2;
  cin >> s3;

  c1 = hand[s1];
  c2 = hand[s2];
  c3 = hand[s3];
  used[s1] = true;
  used[s2] = true;
  used[s3] = true;
  cout << endl;

}

void Player::order()
{
  int h[13];
  int d[13];
  int s[13];
  int c[13];
  int h1 = 0;
  int d1 = 0;
  int s1 = 0;
  int c1 = 0;

  for (int i = 0; i < 13; i++)
  {
    if (hand[i].getSuit() == type::HEARTS)
    {
      h[h1] = hand[i].getNum();
      h1++;
    }
    else if (hand[i].getSuit() == type::DIAMONDS)
    {
      d[d1] = hand[i].getNum();
      d1++;
    }
    else if (hand[i].getSuit() == type::SPADES)
    {
      s[s1] = hand[i].getNum();
      s1++;
    }
    else if (hand[i].getSuit() == type::CLUBS)
    {
      c[c1] = hand[i].getNum();
      c1++;
    }
  }

  for (int i = 1; i < h1; i++)
  {
    int key = h[i];
    int j = i - 1;

    while (j >= 0 && h[j] > key)
    {
      h[j+1] = h[j];
      j--;
    }
    h[j+1] = key;
  }

  for (int i = 1; i < d1; i++)
  {
    int key = d[i];
    int j = i - 1;

    while (j >= 0 && d[j] > key)
    {
      d[j+1] = d[j];
      j--;
    }
    d[j+1] = key;
  }

  for (int i = 1; i < s1; i++)
  {
    int key = s[i];
    int j = i - 1;

    while (j >= 0 && s[j] > key)
    {
      s[j+1] = s[j];
      j--;
    }
    s[j+1] = key;
  }

  for (int i = 1; i < c1; i++)
  {
    int key = c[i];
    int j = i - 1;

    while (j >= 0 && c[j] > key)
    {
      c[j+1] = c[j];
      j--;
    }
    c[j+1] = key;
  }

  int ret = 0;
  for (int i = 0; i < h1; i++)
  {
    hand[ret].alter(h[i], type::HEARTS);
    ret++;
  }

  for (int i = 0; i < d1; i++)
  {
    hand[ret].alter(d[i], type::DIAMONDS);
    ret++;
  }

  for (int i = 0; i < s1; i++)
  {
    hand[ret].alter(s[i], type::SPADES);
    ret++;
  }

  for (int i = 0; i < c1; i++)
  {
    hand[ret].alter(c[i], type::CLUBS);
    ret++;
  }
}

void Player::reset()
{
  for (int i = 0; i < 13; i++)
    used[i] = false;
}

void Player::accept(Card &c1, Card &c2, Card &c3)
{
  for (int i = 0; i < 13; i++)
  {
    if (used[i])
    {
      hand[i] = c1;
      used[i] = false;
      break;
    }
  }

  for (int i = 0; i < 13; i++)
  {
    if (used[i])
    {
      hand[i] = c2;
      used[i] = false;
      break;
    }
  }

  for (int i = 0; i < 13; i++)
  {
    if (used[i])
    {
      hand[i] = c3;
      used[i] = false;
      break;
    }
  }

  order();

  cout << "You got passed these cards:" << endl;
  c1.print();
  c2.print();
  c3.print();
  cout << endl;

}
