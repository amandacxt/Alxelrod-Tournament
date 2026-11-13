#pragma once

#include <cstddef>

#include "../shared/players.h"

class Tournament
{
  public: 
    Tournament(size_t rounds) : m_rounds(rounds), m_playerA(Player()), m_playerB(Player()) {};

    void run(Player playerA, Player playerB);

  private:
    void runTurn(size_t currentRound);

  private:
    size_t m_rounds;
    Player m_playerA;
    Player m_playerB;
};