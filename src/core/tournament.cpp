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

void Tournament::endTour(int currentTour)
{
    DEBUG_POINTS("Player A: " << pa.points() << "\nPlayer B: " << pb.points());
    if(m_playerA->points() > m_playerB->points())
    {
        m_playerA->addWin();
    }
    else if(m_playerB->points() > m_playerA->points())
    {
        m_playerB->addWin();
    }

    std::cout << "\bTOUR " << currentTour 
            << "\n\b Player A: " << m_playerA->points() 
            << " vs Player B: " << m_playerB->points() <<std::endl;
}

void Tournament::endTournament()
{
    std::cout << "FINAL RESULT" << std::endl;

    if(m_playerA->wins() > m_playerB->wins())
    {
        std::cout << "\b Winner: Player A! " << std::endl;
    }
    else if(m_playerB->wins() > m_playerA->wins())
    {
        std::cout << "\b Winner: Player B! " << std::endl;
    }
    else 
    {
        std::cout << "\b Tournament tie! " << std::endl;
    }

    std::cout << "\b Player A: " << m_playerA->wins() << " vs Player B: " << m_playerB->wins() <<std::endl;
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
        for (size_t round = 0; round < m_rounds; ++round)
        {
            runRound(round);
        }
        endTour(tour);
    }
    endTournament();
}

void Tournament::runRound(size_t currentRound)
{
    const auto choiceA = strategies::getChoice(*m_playerA, m_runsHistory, currentRound);
    const auto choiceB = strategies::getChoice(*m_playerB, m_runsHistory, currentRound);

    auto result = RoundResult();
    result.emplace(m_playerA->id(), choiceA);
    result.emplace(m_playerB->id(), choiceB);
    storeResult(currentRound, result);

    auto [pointsA, pointsB] = pointsFromResult(choiceA, choiceB);
    m_playerA->increasePointsBy(pointsA);
    m_playerB->increasePointsBy(pointsB);
}

void Tournament::storeResult(size_t currentRound, const RoundResult& rr)
{
    m_runsHistory[currentRound] = rr;
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
