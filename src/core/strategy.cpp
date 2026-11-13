#include "strategy.h"
#include <cstdlib>


Choice strategies::getChoice(const StrategyName& strategy, const std::vector<RoundResult>& history)
{
    switch (strategy) 
    {
        case StrategyName::ALL_D:
            return strategies::runAllDAlgorithm();

        case StrategyName::RANDOM:
            return strategies::runRandomAlgorithm();
        
    /*    case StrategyName::TIT_FOR_TAT:
            return strategies::runTitForTatAlgorithm();

        case StrategyName::TESTER:
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