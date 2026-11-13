#pragma once

#include <vector>

#include "../shared/strategyName.h"
#include "../shared/player.h"

namespace strategies 
{
    Choice getChoice(const Player& player,
                     const std::vector<RoundResult>& history,
                     size_t currentRound);

    /* Returns only choice D*/
    Choice runAllDAlgorithm();

    /* Chooses randomly between C or D*/
    Choice runRandomAlgorithm();

    /* For the first round returns C, otherwise,
      returns the same choice as the other player in the previous round */
    Choice runTitForTatAlgorithm(const Player& player,
                                 const std::vector<RoundResult>& history,
                                 size_t currentRound);

    /* For the first round returns D, in case competitor figth back (D)
       uses Tit for Tat otherwise returns CCD in order */
    Choice runTesterAlgorithm(const Player& player,
                              const std::vector<RoundResult>& history,
                              size_t currentRound);

    Choice runJossAlgorithm(const Player& player,
                            const std::vector<RoundResult>& history,
                            size_t currentRound);

};