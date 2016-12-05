#include "cwchess/BitBoard.h"

using cwchess::Index;
using cwchess::index_end;
using cwchess::index_begin;
using cwchess::index_pre_begin;
using cwchess::file_a;
using cwchess::rank_1;
using cwchess::rank_8;

class BitBoard : public cwchess::BitBoard {
   using cwchess::BitBoard::BitBoard;
};
