#pragma once

#include "cwchess/BitBoard.h"

namespace directions
{
  int const right = 1;
  int const down = 2;
  int const left = 4;
  int const up = 8;

  inline int reverse(int direction)
  {
    // Swap left/right and up/down bits.
    int m = direction;
    m ^= m << 2;
    m |= m >> 2;
    m &= 15;
    return direction ^ m;
  }

  inline char const* name(int direction)
  {
    switch(direction)
    {
      case right: return "right";
      case down: return "down";
      case left: return "left";
      case up: return "up";
    }
    return "UNKNOWN";
  }
} // namespace directions

using cwchess::Index;
using cwchess::index_end;
using cwchess::index_begin;
using cwchess::index_pre_begin;

// POD constants.
cwchess::BitBoardData const empty = { CW_MASK_T_CONST(0x0) };
cwchess::BitBoardData const default_walls = cwchess::file_a|cwchess::rank_1|cwchess::rank_8;

class BitBoard : public cwchess::BitBoard {
  public:
    using cwchess::BitBoard::BitBoard;

    BitBoard& operator<<=(int bits) { M_bitmask <<= bits; return *this; }
    BitBoard& operator>>=(int bits) { M_bitmask >>= bits; return *this; }

    friend BitBoard operator<<(BitBoard const& bitboard, int bits) { BitBoard result(bitboard); result <<= bits; return result; }
    friend BitBoard operator>>(BitBoard const& bitboard, int bits) { BitBoard result(bitboard); result >>= bits; return result; }

    BitBoard spread(int direction) const
    {
      using namespace directions;
      BitBoard const original(*this);
      BitBoard result(empty);
      if ((direction & right))
	result |= original << 1;
      if ((direction & down))
	result |= original << 8;
      if ((direction & left))
	result |= original >> 1;
      if ((direction & up))
	result |= original >> 8;
      return result;
    }
};
