#pragma once

#include <iostream>

#include "strategyName.h"

enum Choice
{
    C, // Cooperate
    D,  // Disclose
    NO_CHOICE
};

inline std::ostream& operator<<(std::ostream& os, Choice c)
{
    switch (c)
    {
        case Choice::C:         return os << "C";
        case Choice::D:         return os << "D";
        case Choice::NO_CHOICE: return os << "NO_CHOICE";
    }
    return os << "UNKNOWN";
}

struct RoundResult
{
    RoundResult(Choice a, Choice b)
    {
        playerA = a;
        playerB = b;
    }

    Choice playerA;
    Choice playerB;
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