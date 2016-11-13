#pragma once

#include "BitBoard.h"
#include <iosfwd>

using namespace cwchess;

class Board {
  private:
    BitBoard m_walls;
    BitBoard m_stones;
    BitBoard m_targets;
    Index m_player;

  public:
    Board();

    friend std::ostream& operator<<(std::ostream& os, Board const& board);
    friend std::istream& operator>>(std::istream const& is, Board& board);
};
