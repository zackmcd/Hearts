#include <iostream>
#include <cstdlib>
#include "trick.h"
#include "scoreboard.h"
#include "player.h"
#include "deck.h"
#include "cpu.h"
#include "card.h"

using namespace std;

void Deal(Deck D, Player P1, CPU C2, CPU C3, CPU C4);

void passLeft(Player &P1, CPU &C2, CPU &C3, CPU &C4);

void passRight(Player &P1, CPU &C2, CPU &C3, CPU &C4);

void passCross(Player &P1, CPU &C2, CPU &C3, CPU &C4);

void playHand(Scoreboard &score, Player &P1, CPU &C2, CPU &C3, CPU &C4);

int main()
{
  srand(time(0));

  Deck D;
  D.Create();

  Scoreboard score;

  Player P1;
  CPU C2;
  CPU C3;
  CPU C4;
/*
  int pass = 1; // left = 1, right = 2, cross = 3, hold = 4

  while (!score.Over())
  {
    // deal
    Deal(D, P1, C2, C3, C4);
    P1.order();
    C2.order();
    C3.order();
    C4.order();


    P1.print();
    cout << endl;
    C2.print();
    cout << endl;
    C3.print();
    cout << endl;
    C4.print();
    cout << endl;

    // passing
    if (pass == 1)
    {
      //pass left
      passLeft(P1, C2, C3, C4);
      //playLeft
      playHand(score, P1, C2, C3, C4);

      pass++;
    }
    else if (pass == 2)
    {
      //pass right
      passRight(P1, C2, C3, C4);
      //playRight
      playHand(score, P1, C2, C3, C4);

      pass++;
    }
    else if (pass == 3)
    {
      //pass cross
      passCross(P1, C2, C3, C4);
      //playCross
      playHand(score, P1, C2, C3, C4);

      pass++;
    }
    else if (pass == 4)
    {
      //playHold
      playHand(score, P1, C2, C3, C4);

      pass = 1;
    }

    P1.reset();
    C2.reset();
    C3.reset();
    C4.reset();

  }
*/
  return 0;

}

void Deal(Deck D, Player P1, CPU C2, CPU C3, CPU C4)
{
  // dealing the deck
  int num = 0;

  for (int i = 0; i < 13; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      bool test = true;

      while (test)
      {
        num = (rand() % 52);

	if (j == 0 && !D.dealt[num]) // P1
        {
          D.dealt[num] = true;
	  test = false;
          P1.insert(D.deck[num], i);
        }
        else if (j == 1 && !D.dealt[num]) // cpu2
        {
          D.dealt[num] = true;
	  test = false;
          C2.insert(D.deck[num], i);
        }
        else if (j == 2 && !D.dealt[num]) // cpu3
        {
          D.dealt[num] = true;
	  test = false;
          C3.insert(D.deck[num], i);
        }
        else if (j == 3 && !D.dealt[num]) // cpu4
        {
          D.dealt[num] = true;
	  test = false;
          C4.insert(D.deck[num], i);
        }
      }
    }
  }

  //set dealt back to start state
  for (int i = 0; i < 52; i++)
    D.dealt[i] = false;
}

void playHand(Scoreboard &score, Player &P1, CPU &C2, CPU &C3, CPU &C4)
{
  int turn = 0;

  if (P1.start())
    turn = 1;
  else if (C2.start())
    turn = 2;
  else if (C3.start())
    turn = 3;
  else if (C4.start())
    turn = 4;

  //play hand
  for (int i = 0; i < 13; i++)
  {
    int j = 0;
    Trick trick;
    type::SUIT ss = type::UNASSIGNED;

    while (j < 4)
    {
      if (i == 0 && j == 0) // playing 2 of clubs
      {
        if (turn == 1)
        {
	  P1.startHand();
	  trick.start(turn); // start will insert 2 of clubs at turn
	  turn++;
        }
	else if (turn == 2)
	{
          C2.startHand();
	  trick.start(turn); // insert into trick
          turn++;
	}
	else if (turn == 3)
	{
          C3.startHand();
	  trick.start(turn); // insert into trick
          turn++;
	}
	else if (turn == 4)
	{
          C4.startHand();
	  trick.start(turn); // insert into trick
	  turn = 1;
	}

	j++;
	trick.setS(type::CLUBS);
	ss = type::CLUBS;
      }
      else //when its not the first trick
      {

        if (turn == 1)
	{
	  trick.print();
	  cout << endl;
	  P1.playCard(trick, turn, ss); // P1 play card
	  turn++;
	}
	else if (turn == 2)
	{
	  C2.playCard(trick, turn, ss, j); //C2 play card
	  turn++;
	}
	else if (turn == 3)
	{
	  C3.playCard(trick, turn, ss, j); //C3 play card
	  turn++;
	}
	else if (turn == 4)
	{
	  C4.playCard(trick, turn, ss, j); //C4 play card
	  turn = 1;
        }

        j++;
      }
    }

    // figure out who gets points using trick
    trick.print();
    turn = trick.points(score, ss);
    //cout << "T = " << turn << endl;

    cout << endl;
    cout << "End of trick " << i+1 << endl;
    cout << "****************" << endl;
    cout << endl;
    cout << endl;
    score.cur();
    cout << endl;
    cout << endl;

    //testing
    P1.print();
    cout << endl;
    C2.print();
    cout << endl;
    C3.print();
    cout << endl;
    C4.print();
    cout << endl;

  }

  // adjust score for hand
  score.endHand();
  score.Print();
  cout << endl;

}

void passLeft(Player &P1, CPU &C2, CPU &C3, CPU &C4)
{
  Card p1;
  Card p2;
  Card p3;
  P1.pass(p1, p2, p3);

  Card c21;
  Card c22;
  Card c23;
  cout << "C2" << endl;
  C2.pass(c21, c22, c23);

  Card c31;
  Card c32;
  Card c33;
  cout << "C3" << endl;
  C3.pass(c31, c32, c33);

  Card c41;
  Card c42;
  Card c43;
  cout << "C4" << endl;
  C4.pass(c41, c42, c43);

  P1.accept(c41, c42, c43);
  C2.accept(p1, p2, p3);
  C3.accept(c21, c22, c23);
  C4.accept(c31, c32, c33);

}

void passRight(Player &P1, CPU &C2, CPU &C3, CPU &C4)
{
  Card p1;
  Card p2;
  Card p3;
  P1.pass(p1, p2, p3);

  Card c21;
  Card c22;
  Card c23;
  C2.pass(c21, c22, c23);

  Card c31;
  Card c32;
  Card c33;
  C3.pass(c31, c32, c33);

  Card c41;
  Card c42;
  Card c43;
  C4.pass(c41, c42, c43);

  P1.accept(c21, c22, c23);
  C2.accept(c31, c32, c33);
  C3.accept(c41, c42, c43);
  C4.accept(p1, p2, p3);

}

void passCross(Player &P1, CPU &C2, CPU &C3, CPU &C4)
{
  Card p1;
  Card p2;
  Card p3;
  P1.pass(p1, p2, p3);

  Card c21;
  Card c22;
  Card c23;
  C2.pass(c21, c22, c23);

  Card c31;
  Card c32;
  Card c33;
  C3.pass(c31, c32, c33);

  Card c41;
  Card c42;
  Card c43;
  C4.pass(c41, c42, c43);

  P1.accept(c31, c32, c33);
  C2.accept(c41, c42, c43);
  C3.accept(p1, p2, p3);
  C4.accept(c21, c22, c23);

}
