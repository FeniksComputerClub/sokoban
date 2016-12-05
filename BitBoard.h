#include "cwchess/BitBoard.h"

namespace directions
{
  int const right = 1;
  int const down = 2;
  int const left = 4;
  int const up = 8;

  int reverse(int direction)
  {
    // Swap left/right and up/down bits.
    int m = direction;
    m ^= m << 2;
    m |= m >> 2;
    m &= 15;
    return direction ^ m;
  }
} // namespace directions

using cwchess::Index;
using cwchess::index_end;
using cwchess::index_begin;
using cwchess::index_pre_begin;
using cwchess::file_a;
using cwchess::rank_1;
using cwchess::rank_8;

class BitBoard : public cwchess::BitBoard {
  public:
    using cwchess::BitBoard::BitBoard;

    friend BitBoard operator|(BitBoard const& bitboard1, BitBoard const& bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) | static_cast<cwchess::BitBoard const&>(bitboard2); }
    friend BitBoard operator|(BitBoard const& bitboard1, BitBoardData bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) | bitboard2; }
    friend BitBoard operator|(BitBoardData bitboard1, BitBoard const& bitboard2) { return bitboard1 | static_cast<cwchess::BitBoard const&>(bitboard2); }
    friend BitBoard operator&(BitBoard const& bitboard1, BitBoard const& bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) & static_cast<cwchess::BitBoard const&>(bitboard2); }
    friend BitBoard operator&(BitBoard const& bitboard1, BitBoardData bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) & bitboard2; }
    friend BitBoard operator&(BitBoardData bitboard1, BitBoard const& bitboard2) { return bitboard1 & static_cast<cwchess::BitBoard const&>(bitboard2); }
    friend bool operator!=(BitBoard const& bitboard1, BitBoard const& bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) != static_cast<cwchess::BitBoard const&>(bitboard2); }
    friend bool operator!=(BitBoard const& bitboard1, BitBoardData bitboard2) { return static_cast<cwchess::BitBoard const&>(bitboard1) != bitboard2; }
    friend bool operator!=(BitBoardData bitboard1, BitBoard const& bitboard2) { return bitboard1 != static_cast<cwchess::BitBoard const&>(bitboard2); }

    BitBoard& operator<<=(int bits) { M_bitmask <<= bits; return *this; }
    BitBoard& operator>>=(int bits) { M_bitmask >>= bits; return *this; }

    friend BitBoard operator<<(BitBoard const& bitboard, int bits) { BitBoard result(bitboard); result <<= bits; return result; }
    friend BitBoard operator>>(BitBoard const& bitboard, int bits) { BitBoard result(bitboard); result >>= bits; return result; }

    BitBoard spread(int const& direction) const
    {
      using namespace directions;
      cwchess::mask_t result = 0;
      if ((direction & right))
	result |= M_bitmask << 1;
      if ((direction & down))
	result |= M_bitmask << 8;
      if ((direction & left))
	result |= M_bitmask >> 1;
      if ((direction & up))
	result |= M_bitmask >> 8;
      return BitBoard(result);
    }
};
