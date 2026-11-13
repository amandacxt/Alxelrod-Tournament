#include "strategy.h"
#include <cstdlib>


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

    /*    case StrategyName::TESTER:
            return strategies::runTesterAlgorithm();
        
        case StrategyName::JOSS:
            return strategies::runJossAlgorithm(); */
        
        default:
            return Choice::NO_CHOICE;
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

    auto roundResult = history[currentRound - 1 /*previous round*/];
    auto choice = player.id() == roundResult.playerA.first ? roundResult.playerB.second
                                                           : roundResult.playerA.second;
    return choice;
}