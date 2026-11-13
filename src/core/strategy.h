#pragma once

#include "../shared/strategyName.h"

namespace strategies 
{
    static Choice getChoice(const StrategyName& strategy);

    static Choice runAllDAlgotithm();

    static Choice runRandomAlgotithm();

    static Choice runTitForTatAlgotithm();

    static Choice runTesterAlgotithm();

    static Choice runJossAlgotithm();

};