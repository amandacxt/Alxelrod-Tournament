#pragma once

#include <vector>

#include "../shared/strategyName.h"
#include "../shared/player.h"

namespace strategies 
{
    Choice getChoice(const Player& player,
                     const std::vector<RoundResult>& history,
                     size_t currentRound);

    Choice runAllDAlgorithm();

    Choice runRandomAlgorithm();

    /* For the first round returns C, otherwise,
      returns the same choice as the other player in the previous round */
    Choice runTitForTatAlgorithm(const Player& player,
                                 const std::vector<RoundResult>& history,
                                 size_t currentRound);

    /*Choice runTesterAlgorithm();

    Choice runJossAlgorithm(); */

};