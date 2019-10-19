#include <iostream>
#include "scoreboard.h"

using namespace std;

Scoreboard::Scoreboard() : player1T(0), cpu2T(0), cpu3T(0), cpu4T(0), p1H(0), c2H(0), c3H(0), c4H(0) {}

void Scoreboard::Update(int p, int c2, int c3, int c4)
{
  p1H = p1H + p;
  c2H = c2H + c2;
  c3H = c3H + c3;
  c4H = c4H + c4;
}

bool Scoreboard::Over()
{
  if (player1T >= 100)
    return true;
  if (cpu2T >= 100)
    return true;
  if (cpu3T >= 100)
    return true;
  if (cpu4T >= 100)
    return true;

  return false;
}

void Scoreboard::Print()
{
  cout << "Player 1 : " << player1T << endl;
  cout << "CPU 2 : " << cpu2T << endl;
  cout << "CPU 3 : " << cpu3T << endl;
  cout << "CPU 4 : " << cpu4T << endl;

}

void Scoreboard::cur()
{
  cout << "Player 1 : " << p1H << endl;
  cout << "CPU 2 : " << c2H << endl;
  cout << "CPU 3 : " << c3H << endl;
  cout << "CPU 4 : " << c4H << endl;

}

void Scoreboard::endHand()
{
  int shot = 0;
  if (p1H == 26)
    shot = 1;
  else if (c2H == 26)
    shot = 2;
  else if (c3H == 26)
    shot = 3;
  else if (c4H == 26)
    shot = 4;

  if (shot == 0)
  {
    player1T = player1T + p1H;
    cpu2T = cpu2T + c2H;
    cpu3T = cpu3T + c3H;
    cpu4T = cpu4T + c4H;
    p1H = 0;
    c2H = 0;
    c3H = 0;
    c4H = 0;
  }
  else // if someone shot the moon
  {
    if (shot == 1)
    {
      cpu2T = cpu2T + 26;
      cpu3T = cpu3T + 26;
      cpu4T = cpu4T + 26;
      p1H = 0;
      cout << "Great Job! You shot the moon!" << endl;
    }
    else if (shot == 2)
    {
      player1T = player1T + 26;
      cpu3T = cpu3T + 26;
      cpu4T = cpu4T + 26;
      c2H = 0;
      cout << "UH-OH! You let them shoot the moon!" << endl;
    }
    else if (shot == 3)
    {
      player1T = player1T + 26;
      cpu2T = cpu2T + 26;
      cpu4T = cpu4T + 26;
      c3H = 0;
      cout << "UH-OH! You let them shoot the moon!" << endl;
    }
    else if (shot == 4)
    {
      player1T = player1T + 26;
      cpu2T = cpu2T + 26;
      cpu3T = cpu3T + 26;
      c4H = 0;
      cout << "UH-OH! You let them shoot the moon!" << endl;
    }
  }
}
