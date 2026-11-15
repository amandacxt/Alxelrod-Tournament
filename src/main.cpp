// -------------------------------------------
// The program handles the prisoner's dilemma,
// a classic concept in game theory showing why two rational people might not cooperate,
// even when it is in their best interest to do so.
// It was created as the second project of the POA subject,
// Master Imagine, Universite de Montpellier
// Guimaraes Caixeta Silva Amanda, 2026
// -------------------------------------------

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "shared/strategyName.h"
#include "shared/player.h"

#include "core/tournament.h"


namespace
{

const size_t TOURS  = 5;
const size_t ROUNDS = 200;

const std::vector<StrategyName> ALL_STRATEGIES = {
    StrategyName::ALL_D,
    StrategyName::RANDOM,
    StrategyName::TIT_FOR_TAT,
    StrategyName::TESTER,
    StrategyName::JOSS,
    StrategyName::TIT_FOR_TWO_TATS
};


void printUsage(const char* program)
{
    std::cout << "Usage:\n"
              << "  " << program << " <s>        both players use strategy s\n"
              << "  " << program << " <sA> <sB>  player A vs player B\n"
              << "  " << program << " all        round-robin tournament\n"
              << "Strategies: 0=ALL_D 1=RANDOM 2=TIT_FOR_TAT 3=TESTER 4=JOSS 5=TIT_FOR_TWO_TATS 6=NONE (random)\n";
}


StrategyName randomStrategy()
{
    return ALL_STRATEGIES[rand() % ALL_STRATEGIES.size()];
}


bool parseStrategy(const char* arg, StrategyName& out)
{
    char* end = nullptr;
    const long n = std::strtol(arg, &end, 10);

    if (end == arg || *end != '\0' || n < 0 || n > static_cast<long>(StrategyName::NONE))
        return false;

    out = static_cast<StrategyName>(n);

    if (out == StrategyName::NONE)
    {
        out = randomStrategy();
        std::cout << "Random strategy chosen: " << label(out) << "\n";
    }
    return true;
}


std::pair<int, int> playMatch(StrategyName a, StrategyName b)
{
    Tournament tournament(TOURS, ROUNDS);
    Player pa(1, a);
    Player pb(2, b);
    tournament.run(&pa, &pb);

    return {pa.totalPoints(), pb.totalPoints()};
}


void runRoundRobin()
{
    std::vector<int> totalPoints(ALL_STRATEGIES.size(), 0);

    for (size_t i = 0; i < ALL_STRATEGIES.size(); ++i)
    {
        for (size_t j = i + 1; j < ALL_STRATEGIES.size(); ++j)
        {
            std::cout << "\n " << label(ALL_STRATEGIES[i]) << " vs " << label(ALL_STRATEGIES[j]) << " \n";
            const auto [pointsA, pointsB] = playMatch(ALL_STRATEGIES[i], ALL_STRATEGIES[j]);
            totalPoints[i] += pointsA;
            totalPoints[j] += pointsB;
        }
    }

    // Sort strategies from more to less points
    std::vector<size_t> order(ALL_STRATEGIES.size());
    for (size_t i = 0; i < order.size(); ++i)
        order[i] = i;
    std::sort(order.begin(), order.end(),
              [&](size_t x, size_t y) { return totalPoints[x] > totalPoints[y]; });

    
    std::cout << "\n--- ALXELROD TOURNAMENT RANKING ---" << std::endl;
    for (size_t rank = 0; rank < order.size(); ++rank)
    {
        const size_t i = order[rank];
        std::cout << rank + 1 << ". " << label(ALL_STRATEGIES[i]) << ": " << totalPoints[i] << std::endl;
    }
}

} // end namespace

int main(int argc, char ** argv)
{
    const unsigned int SEED = 42;
    srand(SEED);

    if (argc < 2 || argc > 3)
    {
        printUsage(argv[0]);
        return 1;
    }

    if (argc == 2 && std::string(argv[1]) == "all")
    {
        runRoundRobin();
        return 0;
    }

    StrategyName a = StrategyName::NONE;
    StrategyName b = StrategyName::NONE;

    if (!parseStrategy(argv[1], a))
    {
        std::cout << "Invalid strategy: " << argv[1] << "\n";
        printUsage(argv[0]);
        return 1;
    }

    if (argc == 3)
    {
        if (!parseStrategy(argv[2], b))
        {
            std::cout << "Invalid strategy: " << argv[2] << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }
    else
    {
        b = a;   // só uma estratégia: as duas iguais
    }

    playMatch(a, b);

    return 0;
}