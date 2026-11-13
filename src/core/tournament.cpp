#include "tournament.h"

#include "strategy.h"
#include <iostream>

#if true
    #define DEBUG_RESULTS(x) std::cout << x << std::endl
#else
    #define DEBUG_RESULTS(x) ((void)0)
#endif


void Tournament::run(Player* playerA, Player* playerB)
{
    m_playerA = playerA;
    m_playerB = playerB;
    for (size_t round = 0; round < m_rounds; ++round) 
    {
        runRound(round);
    }
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
    DEBUG_RESULTS("Choice Player A: " << choiceA << "\n Choice Player B: " << choiceB);

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
