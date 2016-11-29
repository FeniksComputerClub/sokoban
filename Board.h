#pragma once

#include "BitBoard.h"
#include <iosfwd>
#include <string>

typedef std::string BoardString;

using namespace cwchess;

class Board {
    typedef cwchess::mask_t mask_t;

  private:
    BitBoard m_walls;
    BitBoard m_stones;
    BitBoard m_targets;
    Index m_player;
    static Index const s_noplayer;

  public:
    Board();
    Board(std::string const&);

    void reset();
    std::string write(BitBoard const& colors = BitBoard(0)) const;
    BitBoard reachable() const;
    void read(BoardString const&);
    bool sane();

    friend std::ostream& operator<<(std::ostream& os, Board const& board);
    friend std::istream& operator>>(std::istream& is, Board& board);
};
