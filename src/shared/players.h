#pragma once

#include "strategyName.h"

class Player
{
  public:
    Player() : m_points(0), m_strategy(NONE) {};

    Player(StrategyName strategy) : m_points(0), m_strategy(strategy) {};

    StrategyName strategy() const { return m_strategy;}
    int poinst() const { return m_points; }

    void increasePointsBy(unsigned value) { m_points += value; }
    void decreasePointsBy(unsigned value) { m_points -= value; }

    void changeStrategy(StrategyName strategy) { m_strategy = strategy; }

  private:
    StrategyName m_strategy; 
    int m_points;
};