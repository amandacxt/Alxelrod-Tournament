// -------------------------------------------
// The program handles the prisoner's dilemma,
// a classic concept in game theory showing why two rational people might not cooperate,
// even when it is in their best interest to do so.
// It was created as the second project of the POA subject,
// Master Imagine, Universite de Montpellier
// Guimaraes Caixeta Silva Amanda, 2026
// -------------------------------------------

#include <iostream>

#include "shared/strategyName.h"
#include "shared/player.h"

#include "core/tournament.h"

#if false
    #define DEBUG_POINTS(x) std::cout << x << std::endl
#else
    #define DEBUG_POINTS(x) ((void)0)
#endif

int main(int argc, char ** argv)
{
    auto tournament = new Tournament(2);
    srand(time(nullptr));

    //auto pa = new Player(StrategyName::ALL_D);
    //auto pb = new Player(StrategyName::ALL_D);

    auto pa = new Player(StrategyName::RANDOM);
    auto pb = new Player(StrategyName::RANDOM);
    tournament->run(pa,pb);

    DEBUG_POINTS("Player A: " << pa->points() << "\nPlayer B: " << pb->points());


    return 0;
}