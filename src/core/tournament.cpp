#include "tournament.h"

#include "strategy.h"
#include <iostream>
#include <ostream>

#if false
    #define DEBUG_RESULTS(x) std::cout << x << std::endl
#else
    #define DEBUG_RESULTS(x) ((void)0)
#endif

#if false
    #define DEBUG_POINTS(x) std::cout << x << std::endl
#else
    #define DEBUG_POINTS(x) ((void)0)
#endif

void Tournament::startTour()
{
    if (m_playerA == nullptr || m_playerB == nullptr) 
    {
        std::cout << "Tounament failed to start. Player missing." << std::endl;
        return;
    }
    m_playerA->resetPoints();
    m_playerB->resetPoints();

    clearHistory();
}

void Tournament::endTour(int currentTour, size_t roundsPlayed)
{
    DEBUG_POINTS("Player A: " << m_playerA->points() << "\nPlayer B: " << m_playerB->points());

    std::cout << "\bTOUR " << currentTour << " (" << roundsPlayed << " rounds)"
            << "\n\b Player A: " << m_playerA->points() 
            << " vs Player B: " << m_playerB->points() <<std::endl;
}

bool Tournament::shouldContinue(size_t roundsPlayed) const
{
    if (!isUnknownHorizon())
        return roundsPlayed < m_rounds;

    return (rand() / (RAND_MAX + 1.0)) < m_continueProbability;
}

void Tournament::run(Player* playerA, Player* playerB)
{
    m_playerA = playerA;
    m_playerB = playerB;
    m_playerA->resetGame();
    m_playerB->resetGame();

    for (size_t tour = 0; tour < m_tours; ++tour)
    {
        startTour();
        size_t round = 0;

        do
        {
            runRound(round);
            ++round;
        } while (shouldContinue(round));

        endTour(tour, round);
    }
}

void Tournament::runRound(size_t currentRound)
{
    const auto choiceA = strategies::getChoice(*m_playerA, m_runsHistory, currentRound);
    const auto choiceB = strategies::getChoice(*m_playerB, m_runsHistory, currentRound);

    auto result = RoundResult();
    result.emplace(m_playerA->id(), choiceA);
    result.emplace(m_playerB->id(), choiceB);
    storeResult(result);

    auto [pointsA, pointsB] = pointsFromResult(choiceA, choiceB);
    m_playerA->increasePointsBy(pointsA);
    m_playerB->increasePointsBy(pointsB);
}

void Tournament::storeResult(const RoundResult& rr)
{
    m_runsHistory.push_back(rr);
}

std::tuple<int, int> Tournament::pointsFromResult(const Choice choiceA, const Choice choiceB)
{
    DEBUG_RESULTS("\nChoice Player A: " << choiceA << "\nChoice Player B: " << choiceB);

    if (choiceA == Choice::NO_CHOICE || choiceB == Choice::NO_CHOICE)
    {
        std::cout << "ISSUE DECIDING CHOICE";
        return {0,0};
    }

    if (choiceA == Choice::C && choiceB == Choice::C) 
    {
        return {3, 3};
    }

    if (choiceA == Choice::C && choiceB == Choice::D) 
    {
        return {0, 5};
    }

    if (choiceA == Choice::D && choiceB == Choice::C) 
    {
        return {5, 0};
    }

    if (choiceA == Choice::D && choiceB == Choice::D) 
    {
        return {2, 2};
    }

    std::cout << "INVALID CHOICE VALUES";
    return {0,0};
}
