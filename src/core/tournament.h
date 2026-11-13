#pragma once

#include <cstddef>
#include <tuple>

#include "../shared/player.h"

class Tournament
{
  public: 
    Tournament(size_t rounds) : m_rounds(rounds), m_playerA(nullptr), m_playerB(nullptr) {};

    void run(Player* playerA, Player* playerB);

  private:
    void runTurn(size_t currentRound);
    std::tuple<int, int> result(const Choice choiceA, const Choice choiceB);

  private:
    size_t m_rounds;
    Player* m_playerA;
    Player* m_playerB;
};