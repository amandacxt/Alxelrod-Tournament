#pragma once


enum Strategy
{
    ALL_D,
    RANDOM,
    TIT_FOR_TAT,
    TESTER,
    JOSS,
    NONE
};

class Player
{
  public:
    Player() : m_points(0), m_strategy(NONE) {};

    Player(Strategy strategy) : m_points(0), m_strategy(strategy) {};

    Strategy strategy() const { return m_strategy;}
    int poinst() const { return m_points; }

    void increasePointsBy(unsigned value) { m_points += value; }
    void decreasePointsBy(unsigned value) { m_points -= value; } 

  private:
    Strategy m_strategy; 
    int m_points;
};