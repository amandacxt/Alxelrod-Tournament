#include "strategy.h"


static Choice strategies::getChoice(const StrategyName& strategy)
{
    switch (strategy) 
    {
        case StrategyName::ALL_D:
            return strategies::runAllDAlgotithm();
            break;

        case StrategyName::RANDOM:
            return strategies::runRandomAlgotithm();
            break;
        
        case StrategyName::TIT_FOR_TAT:
            return strategies::runTitForTatAlgotithm();
            break;

        case StrategyName::TESTER:
            return strategies::runTesterAlgotithm();
            break;
        
        case StrategyName::JOSS:
            return strategies::runJossAlgotithm();
            break;
        
        default:
            return Choice::NO_CHOICE;
            break;
    }
}