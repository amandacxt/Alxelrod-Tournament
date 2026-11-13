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
        runTurn(round);
    }
}


void Tournament::runTurn(size_t currentTurn)
{
    const auto choiceA = strategies::getChoice(m_playerA->strategy());
    const auto choiceB = strategies::getChoice(m_playerB->strategy());

    DEBUG_RESULTS("Choice Player A: " << choiceA << "\n Choice Player B: " << choiceB);

    auto [pointsA, pointsB] = result(choiceA, choiceB);
    m_playerA->increasePointsBy(pointsA);
    m_playerB->increasePointsBy(pointsB);
}


std::tuple<int, int> Tournament::result(const Choice choiceA, const Choice choiceB)
{
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
