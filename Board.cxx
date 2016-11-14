#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

BitBoard const empty(0);
BitBoard const default_walls = file_a|rank_1|rank_8;

Board::Board() : m_walls(default_walls), m_stones(empty), m_targets(empty), m_player(0, 0)
{
}

Board::Board(std::string const& inputstring)
{
  read(inputstring);
}

void Board::reset()
{
  m_walls.reset();
  m_stones.reset();
  m_targets.reset();
  m_player = cwchess::ia1;
}

void Board::read(BoardString const& string)
{
  reset();
  size_t len = string.length();
  if (len != 64)
    throw std::runtime_error("String too short");
  for(Index i = index_begin; i < index_end; ++i)
  {
    char readchar = string[i()];
    if (readchar == '#')
      m_walls.set(i);
    else if (readchar == '$' || readchar == '*')
      m_stones.set(i);
    else if (readchar == '@' || readchar == '+')
      m_player = i;
    if (readchar == '.' || readchar == '*' || readchar == '+')
      m_targets.set(i);
  }
}

std::ostream& operator<<(std::ostream& os, Board const& board)
{
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i() > 0 && i() % 8 == 0)
      os << '\n';
    if (board.m_walls.test(i))
      os << '#';
    else if (board.m_stones.test(i))
      os << (board.m_targets.test(i) ? '*' : '$');
    else if (board.m_targets.test(i))
      os << (i == board.m_player ? '+' : '.');
    else if (i == board.m_player)
      os << '@';
    else
      os << ' ';
  }
  return os;
}

std::istream& operator>>(std::istream& is, Board& board)
{
  return is;
}
