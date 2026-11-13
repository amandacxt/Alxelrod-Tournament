#include "strategy.h"
#include <cassert>
#include <cstdlib>

#define N_ALGORITHMS 5

int getCompetitorId(int playerId, const std::vector<RoundResult>& history)
{
    assert(history.size() >= 1);

    auto firstResult = history[0];
    assert(firstResult.size() == 2);

    for (const auto r : firstResult) 
    {
        if(r.first == playerId)
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
    return getChoice(player, player.strategy(), history, currentRound);
}

Choice strategies::getChoice(const Player& player,
                             const StrategyName strategy,
                             const std::vector<RoundResult>& history,
                             size_t currentRound)
{
    switch (strategy)
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
        
        default:
            return chooseAlgorithmRandomly(player, history, currentRound);
    };
}

Choice strategies::runAllDAlgorithm()
{
    return Choice::D;
}

Choice strategies::runRandomAlgorithm()
{
    auto value = rand() % 2;
    return (value == 0 ? Choice::D : Choice::C);
}

Choice strategies::runTitForTatAlgorithm(const Player& player,
                                         const std::vector<RoundResult>& history,
                                         size_t currentRound)
{
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
    if (currentRound == 0 /* first round*/)
    {
        return Choice::D;
    }

    auto competitorId = getCompetitorId(player.id(), history);

    // Check competitor's first round choice
    auto competitorChoice = history[0 /* first round*/].at(competitorId);
    if (competitorChoice == Choice::D) 
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
    auto tftResult = runTitForTatAlgorithm(player, history, currentRound);
    if(tftResult == Choice::D)
    {
        return tftResult;
    }

    return rand() % 10 == 0 ? Choice::D : Choice::C;
}


Choice strategies::chooseAlgorithmRandomly(const Player& player,
                                    const std::vector<RoundResult>& history,
                                    size_t currentRound)
{
    static const StrategyName all[] = 
    {
        StrategyName::ALL_D,
        StrategyName::RANDOM,
        StrategyName::TIT_FOR_TAT,
        StrategyName::TESTER,
        StrategyName::JOSS
    };

    auto strategy = all[rand() % N_ALGORITHMS];

    return getChoice(player, strategy, history, currentRound);
}