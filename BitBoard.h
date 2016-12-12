#pragma once

#include "cwchess/BitBoard.h"
#include <string>

namespace directions
{
  int const right = 1;
  int const down = 2;
  int const left = 4;
  int const up = 8;

  inline int reverse(int direction)
  {
    // Swap left/right and up/down bits.
    return ((direction >> 2) | (direction << 2)) & (right | down | left | up);
  }

  inline std::string const name(int direction)
  {
    std::string names;
    if ((direction & right))
      names.append(" and right");
    if ((direction & down))
      names.append(" and down");
    if ((direction & left))
      names.append(" and left");
    if ((direction & up))
      names.append(" and up");
    names = names.substr(5);
    return names;
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
    BitBoard() { }
    BitBoard(cwchess::BitBoard const& base) : cwchess::BitBoard(base) { }

    using cwchess::BitBoard::operator=;
    BitBoard& operator|=(cwchess::BitBoardData const& data) { cwchess::BitBoard::operator|=(data); return *this; }
    BitBoard& operator|=(cwchess::BitBoard const& base) { cwchess::BitBoard::operator|=(base); return *this; }
    BitBoard& operator&=(cwchess::BitBoardData const& data) { cwchess::BitBoard::operator&=(data); return *this; }
    BitBoard& operator&=(cwchess::BitBoard const& base) { cwchess::BitBoard::operator&=(base); return *this; }
    BitBoard& operator^=(cwchess::BitBoardData const& data) { cwchess::BitBoard::operator^=(data); return *this; }
    BitBoard& operator^=(cwchess::BitBoard const& base) { cwchess::BitBoard::operator^=(base); return *this; }

    BitBoard operator~(void) const { return BitBoard(~M_bitmask); }

    friend bool operator==(BitBoard const& bitboard1, BitBoard const& bitboard2) { return bitboard1.M_bitmask == bitboard2.M_bitmask; }
    friend bool operator==(BitBoard const& bitboard1, cwchess::BitBoard const& bitboard2) { return bitboard1.M_bitmask == bitboard2(); }
    friend bool operator==(BitBoard const& bitboard1, cwchess::BitBoardData const& bitboard2) { return bitboard1.M_bitmask == bitboard2.M_bitmask; }
    friend bool operator==(cwchess::BitBoard const& bitboard1, BitBoard const& bitboard2) { return bitboard1() == bitboard2.M_bitmask; }
    friend bool operator==(cwchess::BitBoardData const& bitboard1, BitBoard const& bitboard2) { return bitboard1.M_bitmask == bitboard2.M_bitmask; }
    friend bool operator!=(BitBoard const& bitboard1, BitBoard const& bitboard2) { return bitboard1.M_bitmask != bitboard2.M_bitmask; }
    friend bool operator!=(BitBoard const& bitboard1, cwchess::BitBoard const& bitboard2) { return bitboard1.M_bitmask != bitboard2(); }
    friend bool operator!=(BitBoard const& bitboard1, cwchess::BitBoardData const& bitboard2) { return bitboard1.M_bitmask != bitboard2.M_bitmask; }
    friend bool operator!=(cwchess::BitBoard const& bitboard1, BitBoard const& bitboard2) { return bitboard1() != bitboard2.M_bitmask; }
    friend bool operator!=(cwchess::BitBoardData const& bitboard1, BitBoard const& bitboard2) { return bitboard1.M_bitmask != bitboard2.M_bitmask; }

    friend BitBoard operator|(BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask | bitboard2.M_bitmask); }
    friend BitBoard operator|(BitBoard const& bitboard1, cwchess::BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask | bitboard2()); }
    friend BitBoard operator|(BitBoard const& bitboard1, cwchess::BitBoardData const& bitboard2) { return BitBoard(bitboard1.M_bitmask | bitboard2.M_bitmask); }
    friend BitBoard operator|(cwchess::BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1() | bitboard2.M_bitmask); }
    friend BitBoard operator|(cwchess::BitBoardData const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask | bitboard2.M_bitmask); }
    friend BitBoard operator&(BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask & bitboard2.M_bitmask); }
    friend BitBoard operator&(BitBoard const& bitboard1, cwchess::BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask & bitboard2()); }
    friend BitBoard operator&(BitBoard const& bitboard1, cwchess::BitBoardData const& bitboard2) { return BitBoard(bitboard1.M_bitmask & bitboard2.M_bitmask); }
    friend BitBoard operator&(cwchess::BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1() & bitboard2.M_bitmask); }
    friend BitBoard operator&(cwchess::BitBoardData const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask & bitboard2.M_bitmask); }
    friend BitBoard operator^(BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask ^ bitboard2.M_bitmask); }
    friend BitBoard operator^(BitBoard const& bitboard1, cwchess::BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask ^ bitboard2()); }
    friend BitBoard operator^(BitBoard const& bitboard1, cwchess::BitBoardData const& bitboard2) { return BitBoard(bitboard1.M_bitmask ^ bitboard2.M_bitmask); }
    friend BitBoard operator^(cwchess::BitBoard const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1() ^ bitboard2.M_bitmask); }
    friend BitBoard operator^(cwchess::BitBoardData const& bitboard1, BitBoard const& bitboard2) { return BitBoard(bitboard1.M_bitmask ^ bitboard2.M_bitmask); }

    using cwchess::BitBoard::reset;
    using cwchess::BitBoard::set;
    using cwchess::BitBoard::toggle;
    using cwchess::BitBoard::test;
    void reset(BitBoard const& bitboard) { M_bitmask &= ~bitboard.M_bitmask; }
    void set(BitBoard const& bitboard) { M_bitmask |= bitboard.M_bitmask; }
    void toggle(BitBoard const& bitboard) { M_bitmask ^= bitboard.M_bitmask; }
    bool test(BitBoard const& bitboard) const { return M_bitmask & bitboard.M_bitmask; }

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
      return result & ~original;
    }
};
