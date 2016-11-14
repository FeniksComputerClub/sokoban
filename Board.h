#pragma once

#include "BitBoard.h"
#include <iosfwd>

typedef std::string BoardString;

using namespace cwchess;

class Board {
  private:
    BitBoard m_walls;
    BitBoard m_stones;
    BitBoard m_targets;
    Index m_player;

  public:
    Board();
    Board(std::string const&);
    void read(BoardString const&);

    friend std::ostream& operator<<(std::ostream& os, Board const& board);
    friend std::istream& operator>>(std::istream& is, Board& board);
};
