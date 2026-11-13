#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

#include "../shared/player.h"


class Tournament
{
  public: 
    Tournament(size_t rounds) : m_rounds(rounds), m_playerA(nullptr), m_playerB(nullptr)
    {
        m_runsHistory = std::vector<RoundResult>(m_rounds - 1);
    };

    void run(Player* playerA, Player* playerB);

  private:
    void runRound(size_t currentRound);

    void storeResult(size_t currentTurn, const RoundResult& rr);
    void clearResults() { m_runsHistory = std::vector<RoundResult>(m_rounds - 1); }

    std::tuple<int, int> pointsFromResult(const Choice choiceA, const Choice choiceB);

  private:
    size_t m_rounds;
    std::vector<RoundResult> m_runsHistory;
    Player* m_playerA;
    Player* m_playerB;
};