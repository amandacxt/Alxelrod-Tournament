#pragma once

#include <cstddef>
#include <tuple>
#include <vector>

#include "../shared/player.h"


class Tournament
{
  public: 
    Tournament(size_t tours, size_t rounds, double continueProbability = 1.0, double noiseProbability = 0.0) :
        m_tours(tours), 
        m_rounds(rounds),
        m_continueProbability(continueProbability),
        m_noiseProbability(noiseProbability),
        m_playerA(nullptr), 
        m_playerB(nullptr)
    {
        clearHistory();
    };

    void run(Player* playerA, Player* playerB);

    bool isUnknownHorizon() const { return m_continueProbability < 1.0; }

  private:
    void startTour();
    void endTour(int currentTour, size_t roundsPlayed);
    void runRound(size_t currentRound);
    bool shouldContinue(size_t roundsPlayed) const;

    Choice applyNoise(Choice choice) const;

    void storeResult(const RoundResult& rr);
    void clearHistory()  { m_runsHistory.clear(); }
    std::tuple<int, int> pointsFromResult(const Choice choiceA, const Choice choiceB);

  private:
    size_t m_tours;
    size_t m_rounds;
    double m_continueProbability;
    double m_noiseProbability;
    std::vector<RoundResult> m_runsHistory;
    Player* m_playerA;
    Player* m_playerB;
};