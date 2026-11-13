#include "strategy.h"


Choice strategies::getChoice(const StrategyName& strategy)
{
    switch (strategy) 
    {
        case StrategyName::ALL_D:
            return strategies::runAllDAlgorithm();

/*         case StrategyName::RANDOM:
            return strategies::runRandomAlgotithm();
        
        case StrategyName::TIT_FOR_TAT:
            return strategies::runTitForTatAlgotithm();

        case StrategyName::TESTER:
            return strategies::runTesterAlgotithm();
        
        case StrategyName::JOSS:
            return strategies::runJossAlgotithm(); */
        
        default:
            return Choice::NO_CHOICE;
    };
}

Choice strategies::runAllDAlgorithm()
{
    return Choice::D;
}