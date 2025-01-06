#include <iostream>
#include "cpu.h"
#include "trick.h"
#include "card.h"

using namespace std;

CPU::CPU()
{
  hand = new Card[13];
  used = new bool[13];

  for (int i = 0; i < 13; i++)
    used[i] = false;

  shoot = false;
}

CPU::~CPU()
{
  delete [] hand;
  delete [] used;
}

void CPU::insert(Card c, int index)
{
  hand[index] = c;
}

void CPU::print()
{
  for (int i = 0; i < 13; i++)
    if (!used[i])
      hand[i].print();
}

bool CPU::start()
{
  for (int i = 0; i < 13; i++)
    if (hand[i].getNum() == 2 && hand[i].getSuit() == 100)
      return true;

  return false;
}

void CPU::startHand()
{
  for (int i = 0; i < 13; i++)
  {
    if (hand[i].getNum() == 2 && hand[i].getSuit() == 100)
    {
      used[i] = true;
      break;
    }
  }

  cout << "Since the cpu has the two of Clubs they must start the first trick." << endl;
  cout << endl;
  cout << endl;

}

bool CPU::suitCheck(type::SUIT &s)
{
  for (int i = 0; i < 13; i++)
  {
    if (s == hand[i].getSuit())
    {
      return true;
    }
  }
  return false;
}

void CPU::playCard(Trick &T, int p, type::SUIT &s, int pos)
{
  // for testing
  //T.insert(14, type::HEARTS, p);
  //if (s == type::UNASSIGNED)
  //{
  //  T.setS(type::HEARTS);
  //  s = type::HEARTS;
  //}

  int choice = 0;
  bool hasSuit = false;
  bool first = false;

  /* let cpu figure out its choice */

  // check if this is the first card in the trick
  if (pos == 0)
  {
    first = true;
  }
  else
  { // check if hand has a card in the starting suit
    hasSuit = suitCheck(s);
  }

  // if a card hasnt been played in the trick yet
  if (first)
  {
    if (shoot) // if u have the suit and the cpu is shooting
    {

    }
    else // if u have the suit and the cpu isnt shooting
    {

    }
  }
  else // if a card has been played in the trick already
  {
    // if hand has a card in the starting suit
    if (hasSuit)
    {
      if (shoot) // if u have the suit and the cpu is shooting
      {

      }
      else // if u have the suit and the cpu isnt shooting
      {

      }
    }
    else // if hand does not have the starting suit
    {
      if (shoot) // if u dont have the suit and the cpu is shooting
      {

      }
      else // if u dont have the suit and the cpu isnt shooting
      {

      }
    }
  }

  // insert the cpu's choice into the trick and update cpu class
  T.insert(hand[choice].getNum(), hand[choice].getSuit(), p);
  if (s == type::UNASSIGNED)
  {
    T.setS(hand[choice].getSuit());
    s = hand[choice].getSuit();
  }

  used[choice] = true;
}

void CPU::pass(Card &c1, Card &c2, Card &c3)
{
  bool one = false;
  bool two = false;
  bool three = false;

  int lossHearts = 0; //num of losing hearts
  int *trash = new int[13];
  int *lDiam = new int[13];
  int *lSpad = new int[13];
  int *lClub = new int[13];
  int *trashB = new int[13];
  int *lDiamB = new int[13];
  int *lSpadB = new int[13];
  int *lClubB = new int[13];
  int totalLoss = 0; //num of total losers in hand
  int numDanger = 0; //num of high spades

  for (int i = 0; i < 13; i++)
  {
    trash[i] = 0;
    lDiam[i] = 0;
    lSpad[i] = 0;
    lClub[i] = 0;
    trashB[i] = 0;
    lDiamB[i] = 0;
    lSpadB[i] = 0;
    lClubB[i] = 0;
  }

  for (int i = 400; i >= 100; i = i - 100)
  {
    int nums[13];

    for (int q = 0; q < 13; q++)
      nums[q] = 0;

    int numWins = 0;
    int numLoss = 0;
    int k = 0;
    for (int j = 0; j < 13; j++)
    {
      if (hand[j].getSuit() == i)
      {
        nums[k] = hand[j].getNum();
        k++;

        if (hand[j].getSuit() == type::SPADES)
        {
          if (hand[j].getNum() >= 12)
	    numDanger++;
        }
      }
    }

    for (int z = 0; z < 13; z++)
    {
      if (i == 400)
      {
        trash[z] = nums[z];
        trashB[z] = nums[z];
      }
      else if (i == 300)
      {
        lDiam[z] = nums[z];
        lDiamB[z] = nums[z];
      }
      else if (i == 200)
      {
        lSpad[z] = nums[z];
        lSpadB[z] = nums[z];
      }
      else if (i == 100)
      {
        lClub[z] = nums[z];
        lClubB[z] = nums[z];
      }
    }

    // go through nums for particular suit
    if (i == 400)
      numWins = winners(nums, k, 14, trash);
    else if (i == 300)
      numWins = winners(nums, k, 14, lDiam);
    else if (i == 200)
      numWins = winners(nums, k, 14, lSpad);
    else if (i == 100)
      numWins = winners(nums, k, 14, lClub);

    numLoss = k - numWins;
    totalLoss = totalLoss + numLoss;

    if (i == 400)
    {
      lossHearts = numLoss;
      if (numLoss > 3)
      {
        shoot = false;
        break;
      }
    }
  }



  if ((totalLoss <= 10) && (numDanger >= 2)) // ratio and probability of shooting the moon
    shoot = true;

  if (!shoot)
    cout << "the computer is not shooting" << endl;
  else
    cout << "the computer is shooting" << endl;

  if (shoot)
  {
    if (lossHearts > 0)
    {
      for (int i = 0; i < 13; i++)
      {
        for (int j = 0; j < 13; j++)
        {
	  if (hand[j].getSuit() == type::HEARTS)
          {
	    if (hand[j].getNum() == trash[i])
            {
	      if (!one)
	      {
                c1 = hand[j];
		one = true;
	        used[j] = true;
	        trash[i] = 0; //****
	      }
	      else if (!two)
              {
		c2 = hand[j];
		two = true;
	        used[j] = true;
	        trash[i] = 0; //****
	      }
	      else if (!three)
              {
		c3 = hand[j];
		three = true;
	        used[j] = true;
	        trash[i] = 0; //****
              }
	    }
          }
	}
      }
    }

    // when passing stuff other than low hearts
    int diam = 0;
    int spad = 0;
    int club = 0;

    for (int i = 0; i < 13; i++)
    {
      if (hand[i].getSuit() == type::DIAMONDS)
        diam++;
      else if (hand[i].getSuit() == type::SPADES)
        spad++;
      else if (hand[i].getSuit() == type::CLUBS)
        club++;
    }

    while ((!one) || (!two) || (!three))
    {
      // stuff
      if ((diam <= spad) && (diam <= club))
      {
        bool t1 = true;

	for (int i = 0; i < 13; i++)
        {
	  for (int j = 0; j < 13; j++)
	  {
            // assuming arrays r sorted
	    if (lDiam[i])
	    {
	      if(hand[j].getSuit() == type::DIAMONDS)
	      {
	        if (hand[j].getNum() == lDiam[i])
                {
		  // ifs for which card to put it in
	          if (!one)
	          {
                    c1.alter(lDiam[i], type::DIAMONDS);
	            one = true;
	            used[j] = true;
	            lDiam[i] = 0;
	          }
	          else if (!two)
                  {
	            c2.alter(lDiam[i], type::DIAMONDS);
	            two = true;
	            used[j] = true;
	            lDiam[i] = 0;
	          }
	          else if (!three)
                  {
	            c3.alter(lDiam[i], type::DIAMONDS);
	            three = true;
	            used[j] = true;
	            lDiam[i] = 0;
                  }

	          t1 = false;
	        }
	      }
	    }
	  }
	}

	if (t1)
	  diam = 1000;
      }
      else if ((club <= diam) && (club <= spad))
      {
        bool t2 = true;

	for (int i = 0; i < 13; i++)
        {
	  for (int j = 0; j < 13; j++)
	  {
            // assuming arrays r sorted
	    if (lClub[i])
	    {
	      if (hand[j].getSuit() == type::CLUBS)
	      {
	        if (hand[j].getNum() == lClub[i] && lClub[i] < 12)
		{
                  // ifs for which card to put it in
	          if (!one)
	          {
                    c1.alter(lClub[i], type::CLUBS);
	            one = true;
	            used[j] = true;
	            lClub[i] = 0;
	          }
	          else if (!two)
                  {
	            c2.alter(lClub[i], type::CLUBS);
	            two = true;
	            used[j] = true;
	            lClub[i] = 0;
	          }
	          else if (!three)
                  {
	            c3.alter(lClub[i], type::CLUBS);
	            three = true;
	            used[j] = true;
	            lClub[i] = 0;
                  }

	          t2 = false;
                }
	      }
	    }
	  }
	}

	if (t2)
	  club = 1000;

      }
      else if ((spad <= club) && (spad <= diam))
      {
        bool t3 = true;

	for (int i = 0; i < 13; i++)
        {
	  for (int j = 0; j < 13; j++)
	  {
            // assuming arrays r sorted
	    if (lSpad[i])
	    {
	      if (hand[j].getSuit() == type::SPADES)
	      {
	        if (hand[j].getNum() == lSpad[i] && lSpad[i] < 12)
		{
                  // ifs for which card to put it in
	          if (!one)
	          {
                    c1.alter(lSpad[i], type::SPADES);
	            one = true;
	            used[j] = true;
	            lSpad[i] = 0;
	          }
	          else if (!two)
                  {
	            c2.alter(lSpad[i], type::SPADES);
	            two = true;
	            used[j] = true;
	            lSpad[i] = 0;
	          }
	          else if (!three)
                  {
	            c3.alter(lSpad[i], type::SPADES);
	            three = true;
	            used[j] = true;
	            lSpad[i] = 0;
                  }

	          t3 = false;
	        }
	      }
	    }
	  }
	}

	if (t3)
	  spad = 1000;

      }
    }

  }
  else
  {
    int high = 0;

    if (numDanger > 0)
    {
      for (int i = 12; i >= 0; i--)
      {
        if (lSpadB[i] == 14 || lSpadB[i] == 13 || lSpadB[i] == 12)
	{
	  for (int j = 0; j < 13; j++)
	  {
	    if (hand[j].getSuit() == type::SPADES && hand[j].getNum() == lSpadB[i])
	    {
	      if (!one)
	      {
                c1.alter(lSpadB[i], type::SPADES);
	        one = true;
	        high++;
	        used[j] = true;
	        lSpadB[i] = 0; //****
	      }
	      else if (!two)
              {
	        c2.alter(lSpadB[i], type::SPADES);
	        two = true;
	        high++;
	        used[j] = true;
	        lSpadB[i] = 0; //****
	      }
	      else if (!three)
              {
	        c3.alter(lSpadB[i], type::SPADES);
	        three = true;
	        high++;
	        used[j] = true;
	        lSpadB[i] = 0; //****
              }
	    }
	  }
	}
      }
    }

    //passing after spades
    bool tester = true;
    while (tester)
    {
      for (int i = 12; i >= 0 && tester; i--)
      {
        for (int j = 0; j < 13 && tester; j++)
	{
          if (trashB[i])
          {
	    if (hand[j].getSuit() == type::HEARTS && hand[j].getNum() == trashB[i])
	    {
              if (!one)
              {
                c1.alter(trashB[i], type::HEARTS);
                one = true;
                high++;
                used[j] = true;
	        trashB[i] = 0; //****
              }
              else if (!two)
              {
                c2.alter(trashB[i], type::HEARTS);
                two = true;
                high++;
                used[j] = true;
	        trashB[i] = 0; //****
              }
              else if (!three)
              {
                c3.alter(trashB[i], type::HEARTS);
                three = true;
                high++;
                used[j] = true;
	        trashB[i] = 0; //****
              }

	      if (high > 1)
	        tester = false;
	    }
	  }
	}
      }

      for (int i = 12; i >= 0 && tester; i--)
      {
        for (int j = 0; j < 13 && tester; j++)
	{
          if (lDiamB[i])
          {
	    if (hand[j].getSuit() == type::DIAMONDS && hand[j].getNum() == lDiamB[i])
	    {
              if (!one)
              {
                c1.alter(lDiamB[i], type::DIAMONDS);
                one = true;
                high++;
                used[j] = true;
                lDiamB[i] = 0; //****
              }
              else if (!two)
              {
                c2.alter(lDiamB[i], type::DIAMONDS);
                two = true;
                high++;
                used[j] = true;
                lDiamB[i] = 0; //****
              }
              else if (!three)
              {
                c3.alter(lDiamB[i], type::DIAMONDS);
                three = true;
                high++;
                used[j] = true;
                lDiamB[i] = 0; //****
              }

	      if (high > 1)
	        tester = false;
	    }
	  }
	}
      }

      for (int i = 12; i >= 0 && tester; i--)
      {
        for (int j = 0; j < 13 && tester; j++)
	{
	  if (lClubB[i])
          {
	    if (hand[j].getSuit() == type::CLUBS && hand[j].getNum() == lClubB[i])
	    {
              if (!one)
              {
                c1.alter(lClubB[i], type::CLUBS);
                one = true;
                high++;
                used[j] = true;
                lClubB[i] = 0; //****
              }
              else if (!two)
              {
                c2.alter(lClubB[i], type::CLUBS);
                two = true;
                high++;
                used[j] = true;
                lClubB[i] = 0; //****
              }
              else if (!three)
              {
                c3.alter(lClubB[i], type::CLUBS);
                three = true;
                high++;
                used[j] = true;
                lClubB[i] = 0; //****
              }

	      if (high > 1)
	        tester = false;
	    }
	  }
        }
      }
    }

    // passing one low card
    for (int i = 0; i < 13; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        if (trashB[i])
        {
          if (hand[j].getSuit() == type::HEARTS && hand[j].getNum() == trashB[i])
	  {
	    if (!one)
            {
              c1.alter(trashB[i], type::HEARTS);
              one = true;
              used[j] = true;
	      trashB[i] = 0; // ****
            }
            else if (!two)
            {
              c2.alter(trashB[i], type::HEARTS);
              two = true;
              used[j] = true;
	      trashB[i] = 0; // ****
            }
            else if (!three)
            {
              c3.alter(trashB[i], type::HEARTS);
              three = true;
              used[j] = true;
	      trashB[i] = 0; // ****
            }
          }
	}
      }
    }

    for (int i = 0; i < 13; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        if (lDiamB[i])
        {
          if (hand[j].getSuit() == type::DIAMONDS && hand[j].getNum() == lDiamB[i])
	  {
	    if (!one)
            {
              c1.alter(lDiamB[i], type::DIAMONDS);
              one = true;
              used[j] = true;
	      lDiamB[i] = 0; //***
            }
            else if (!two)
            {
              c2.alter(lDiamB[i], type::DIAMONDS);
              two = true;
              used[j] = true;
	      lDiamB[i] = 0; //***
            }
            else if (!three)
            {
              c3.alter(lDiamB[i], type::DIAMONDS);
              three = true;
              used[j] = true;
	      lDiamB[i] = 0; //***
            }
          }
	}
      }
    }

    for (int i = 0; i < 13; i++)
    {
      for (int j = 0; j < 13; j++)
      {
        if (lClubB[i])
        {
	  if (hand[j].getSuit() == type::CLUBS && hand[j].getNum() == lClubB[i])
	  {
            if (!one)
            {
              c1.alter(lClubB[i], type::CLUBS);
              one = true;
              used[j] = true;
	      lClubB[i] = 0; //***
            }
            else if (!two)
            {
              c2.alter(lClubB[i], type::CLUBS);
              two = true;
              used[j] = true;
	      lClubB[i] = 0; //***
            }
            else if (!three)
            {
              c3.alter(lClubB[i], type::CLUBS);
              three = true;
              used[j] = true;
	      lClubB[i] = 0; //***
            }
          }
	}
      }
    }
  }

  cout << "Computer chose:" << endl;
  c1.print();
  c2.print();
  c3.print();

  // delete news
  delete [] trash;
  delete [] lDiam;
  delete [] lSpad;
  delete [] lClub;
  delete [] trashB;
  delete [] lDiamB;
  delete [] lSpadB;
  delete [] lClubB;
}

int CPU::winners(int *nums, int size, int top, int *trash)
{
  for (int i = 0; i < size; i++)
  {
    if (nums[i] == top)
    {
      trash[i] = 0;
      return (1 + winners(nums, size, (top - 1), trash));
    }
  }

  return 0;
}

void CPU::order()
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

void CPU::reset()
{
  for (int i = 0; i < 13; i++)
    used[i] = false;
}

void CPU::accept(Card &c1, Card &c2, Card &c3)
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

  //see if cards passed were losing hearts
  int nums[13];
  int temp[13];

  for (int q = 0; q < 13; q++)
    nums[q] = 0;

  int numWins = 0;
  int numLoss = 0;
  int k = 0;
  for (int j = 0; j < 13; j++)
  {
    if (hand[j].getSuit() == type::HEARTS)
    {
      nums[k] = hand[j].getNum();
      k++;
    }
  }

  numWins = winners(nums, k, 14, temp);
  numLoss = k - numWins;

  if (numLoss > 0)
    shoot = false;

  if (shoot)
    cout << "computer is still shooting" << endl;
  else
    cout << "computer is not shooting now" << endl;

}
