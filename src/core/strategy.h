#pragma once

#include "../shared/strategyName.h"
#include "../shared/player.h"

namespace strategies 
{
    Choice getChoice(const StrategyName& strategy);

    Choice runAllDAlgorithm();

     Choice runRandomAlgorithm();

/*    Choice runTitForTatAlgorithm();

    Choice runTesterAlgorithm();

    Choice runJossAlgorithm(); */

};