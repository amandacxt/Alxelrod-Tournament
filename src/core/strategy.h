#pragma once

#include <vector>

#include "../shared/strategyName.h"
#include "../shared/player.h"

namespace strategies 
{
    Choice getChoice(const StrategyName& strategy, const std::vector<RoundResult>& history);

    Choice runAllDAlgorithm();

     Choice runRandomAlgorithm();

/*    Choice runTitForTatAlgorithm();

    Choice runTesterAlgorithm();

    Choice runJossAlgorithm(); */

};