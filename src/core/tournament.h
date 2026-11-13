#pragma once

#include <cstddef>


class Tournement
{
  public: 
    Tournement(size_t rounds) :
        m_rounds(rounds)
    {};


  private:
    size_t m_rounds;
};