#pragma once

#include "strategyName.h"

enum Choice
{
    C, // Cooperate
    D,  // Disclose
    NO_CHOICE
};

class Player
{
  public:
    Player() : m_points(0), m_strategy(NONE) {};

    Player(StrategyName strategy) : m_points(0), m_strategy(strategy) {};

    StrategyName strategy() const { return m_strategy;}
    int points() const { return m_points; }

    void increasePointsBy(unsigned value) { m_points += value; }

    void changeStrategy(StrategyName strategy) { m_strategy = strategy; }

  private:
    int m_points;
    StrategyName m_strategy;
};