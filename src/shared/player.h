#pragma once

#include <iostream>
#include <map>

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


using RoundResult = std::map<int, Choice>;


class Player
{
  public:
    Player(int id) : m_id(id), m_points(0), m_wins(0), m_strategy(NONE) {};

    Player(int id, StrategyName strategy) : m_id(id), m_points(0), m_strategy(strategy) {};

    int id() const { return m_id; }
    int points() const { return m_points; }
    int wins() { return m_wins; }

    StrategyName strategy() const { return m_strategy; }

    void resetPoints() { m_points = 0; }
    void resetGame() { resetPoints(); m_wins = 0; }
    void increasePointsBy(unsigned value) { m_points += value; }
    void addWin() { m_wins += 1; }

    void changeStrategy(StrategyName strategy) { m_strategy = strategy; }

  private:
    int m_id;
    int m_points;
    int m_wins;
    StrategyName m_strategy;
};