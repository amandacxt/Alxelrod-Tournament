#include "strategy.h"
#include <cassert>
#include <cstdlib>

#if false
    #define DEBUG_STRATEGY(x) std::cout << x << std::endl
#else
    #define DEBUG_STRATEGY(x) ((void)0)
#endif

int getCompetitorId(int playerId, const std::vector<RoundResult>& history)
{
    assert(history.size() >= 1);

    auto firstResult = history[0];
    assert(firstResult.size() == 2);

    for (const auto r : firstResult) 
    {
        if(r.first != playerId)
        {
            return r.first;
        }
    }

    std::cout << " COMPETITOR KEY NOT FOUND";

    return 0;
}


Choice strategies::getChoice(const Player& player,
                             const std::vector<RoundResult>& history,
                             size_t currentRound)
{
    switch (player.strategy())
    {
        case StrategyName::ALL_D:
            return strategies::runAllDAlgorithm();

        case StrategyName::RANDOM:
            return strategies::runRandomAlgorithm();
        
        case StrategyName::TIT_FOR_TAT:
            return strategies::runTitForTatAlgorithm(player, history, currentRound);

        case StrategyName::TESTER:
            return strategies::runTesterAlgorithm(player, history, currentRound);
        
        case StrategyName::JOSS:
            return strategies::runJossAlgorithm(player, history, currentRound);
        
        case StrategyName::TIT_FOR_TWO_TATS:
            return strategies::runTitForTwoTatsAlgorithm(player, history, currentRound);
        
        case StrategyName::GRUDGER:
            return strategies::runGrudgerAlgorithm(player, history, currentRound);
        
        default:
            return Choice::NO_CHOICE;
    };
}

Choice strategies::runAllDAlgorithm()
{
    DEBUG_STRATEGY("STRATEGY: runAllDAlgorithm");
    return Choice::D;
}

Choice strategies::runRandomAlgorithm()
{
    DEBUG_STRATEGY("STRATEGY: runRandomAlgorithm");
    auto value = rand() % 2;
    return (value == 0 ? Choice::D : Choice::C);
}

Choice strategies::runTitForTatAlgorithm(const Player& player,
                                         const std::vector<RoundResult>& history,
                                         size_t currentRound)
{
    DEBUG_STRATEGY("STRATEGY: runTitForTatAlgorithm");
    if (currentRound == 0 /* first round*/)
    {
        return Choice::C;
    }

    auto competitorId = getCompetitorId(player.id(), history);
    auto roundResult = history[currentRound - 1 /*previous round*/];
    return roundResult.at(competitorId);
}

Choice strategies::runTesterAlgorithm(const Player& player,
                                      const std::vector<RoundResult>& history,
                                      size_t currentRound)
{
    DEBUG_STRATEGY("STRATEGY: runTesterAlgorithm");
    if (currentRound == 0 /* first round*/)
    {
        return Choice::D;
    }

    auto competitorId = getCompetitorId(player.id(), history);

    // Check competitor's second round choice
    if (currentRound >= 2 && history[1].at(competitorId) == Choice::D)
    {
        return strategies::runTitForTatAlgorithm(player, history, currentRound);
    }

    // Follows order CCD starting from round nº1
    return ((currentRound - 1) % 3 == 2) ? Choice::D : Choice::C;
}

Choice strategies::runJossAlgorithm(const Player& player,
                                    const std::vector<RoundResult>& history,
                                    size_t currentRound)
{
    DEBUG_STRATEGY("STRATEGY: runJossAlgorithm");
    auto tftResult = runTitForTatAlgorithm(player, history, currentRound);
    if(tftResult == Choice::D)
    {
        return tftResult;
    }

    return rand() % 10 == 0 ? Choice::D : Choice::C;
}


Choice strategies::runTitForTwoTatsAlgorithm(const Player& player,
                                             const std::vector<RoundResult>& history,
                                             size_t currentRound)
{
    DEBUG_STRATEGY("STRATEGY: runTitForTwoTatsAlgorithm");
    if (currentRound < 2)
    {
        return Choice::C;
    }

    auto competitorId = getCompetitorId(player.id(), history);
    const bool defectedLast     = history[currentRound - 1].at(competitorId) == Choice::D;
    const bool defectedBeforeIt = history[currentRound - 2].at(competitorId) == Choice::D;

    return (defectedLast && defectedBeforeIt) ? Choice::D : Choice::C;
}

Choice strategies::runGrudgerAlgorithm(const Player& player,
                                       const std::vector<RoundResult>& history,
                                       size_t currentRound)
{
    DEBUG_STRATEGY("STRATEGY: runGrudgerAlgorithm");
    if (currentRound == 0 /* first round */)
    {
        return Choice::C;
    }

    auto competitorId = getCompetitorId(player.id(), history);
    for (size_t round = 0; round < currentRound; ++round)
    {
        if (history[round].at(competitorId) == Choice::D)
        {
            return Choice::D;
        }
    }

    return Choice::C;
}