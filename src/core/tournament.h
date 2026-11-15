#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

#include "../shared/player.h"


class Tournament
{
  public: 
    Tournament(size_t tours, size_t rounds) : m_tours(tours), m_rounds(rounds), m_playerA(nullptr), m_playerB(nullptr)
    {
        clearHistory();
    };

    void run(Player* playerA, Player* playerB);

  private:
    void startTour();
    void endTour(int currentTour);
    void endTournament();
    void runRound(size_t currentRound);

    void storeResult(size_t currentTurn, const RoundResult& rr);
    void clearHistory()  { m_runsHistory.assign(m_rounds, RoundResult()); }
    std::tuple<int, int> pointsFromResult(const Choice choiceA, const Choice choiceB);

  private:
    size_t m_tours;
    size_t m_rounds;
    std::vector<RoundResult> m_runsHistory;
    Player* m_playerA;
    Player* m_playerB;
};