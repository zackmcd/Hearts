#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard
{
    int player1T;
    int cpu2T;
    int cpu3T;
    int cpu4T;
    int p1H;
    int c2H;
    int c3H;
    int c4H;

  public :
    Scoreboard();
    void Update(int p, int c2, int c3, int c4);
    bool Over(); //returns true if anyone is over 100
    void Print();
    void cur();
    void endHand();
};

#endif
