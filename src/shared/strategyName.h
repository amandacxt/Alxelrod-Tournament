#pragma once

enum StrategyName
{
    ALL_D,
    RANDOM,
    TIT_FOR_TAT,
    TESTER,
    JOSS,
    TIT_FOR_TWO_TATS,
    GRUDGER,
    NONE
};

inline const char* label(StrategyName s)
{
    switch (s)
    {
    case StrategyName::ALL_D:               return "ALL_D";
    case StrategyName::RANDOM:              return "RANDOM";
    case StrategyName::TIT_FOR_TAT:         return "TIT_FOR_TAT";
    case StrategyName::TESTER:              return "TESTER";
    case StrategyName::JOSS:                return "JOSS";
    case StrategyName::TIT_FOR_TWO_TATS:    return "TIT_FOR_TWO_TATS";
    case StrategyName::GRUDGER:             return "GRUDGER";
    default:                                return "NONE";
    }
}