#include "tournament.h"

#include "../shared/players.h"


void Tournament::run(Player playerA, Player playerB)
{
    // If none strategy is set, they are chosen randomly by each turn
    for (auto round = 0; round < m_rounds; ++round) 
    {
        runTurn(round);
    }
}


void Tournament::runTurn(size_t currentTurn)
{

}
