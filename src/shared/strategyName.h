#pragma once

enum StrategyName
{
    ALL_D,
    RANDOM,
    TIT_FOR_TAT,
    TESTER,
    JOSS,
    NONE
};

inline const char* label(StrategyName s)
{
    switch (s)
    {
    case StrategyName::ALL_D:       return "ALL_D";
    case StrategyName::RANDOM:      return "RANDOM";
    case StrategyName::TIT_FOR_TAT: return "TIT_FOR_TAT";
    case StrategyName::TESTER:      return "TESTER";
    case StrategyName::JOSS:        return "JOSS";
    default:                        return "NONE";
    }
}