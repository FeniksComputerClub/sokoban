#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

BitBoard const empty(0);
BitBoard const default_walls = file_a|rank_1|rank_8;

Index const Board::s_noplayer(index_end);

namespace {

int popcount(uint64_t mask)
{
  mask = (mask & 0x5555555555555555LU) + (mask >> 1 & 0x5555555555555555LU);	
 mask = (mask & 0x3333333333333333LU) + (mask >> 2 & 0x3333333333333333LU);
  mask = mask + (mask >> 4) & 0x0F0F0F0F0F0F0F0FLU;
  mask = mask + (mask >> 8);
  mask = mask + (mask >> 16);
  mask = mask + (mask >> 32) & 0x7FLU;

  return (int) mask;
}

} // namespace

Board::Board()
{
  reset();
}

Board::Board(BoardString const& inputstring)
{
  read(inputstring);
}

void Board::reset()
{
  m_walls = default_walls;
  m_stones = empty;
  m_targets = empty;
  m_player = s_noplayer;
}

void Board::write(std::ostream& outputstream) const
{
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i() > 0 && i() % 8 == 0)
      outputstream << '\n';
    if (m_walls.test(i))
      outputstream << '#';
    else if (m_stones.test(i))
      outputstream << (m_targets.test(i) ? '*' : '$');
    else if (m_targets.test(i))
      outputstream << (i == m_player ? '+' : '.');
    else if (i == m_player)
      outputstream << '@';
    else
      outputstream << ' ';
  }
}

void Board::read(BoardString const& inputstring)
{
  size_t len = inputstring.length();
  bool manyplayers = false;

  reset();
  if (len != 64)
    throw std::runtime_error("input too short");

  for(Index i = index_begin; i < index_end; ++i)
  {
    char readchar = inputstring[i()];
    if (i() < 8 || (i() > 0 && i() % 8 == 0) || i() > 8 * 7)
      continue;
    if (readchar == '#')
      m_walls.set(i);
    else if (readchar == '$' || readchar == '*')
      m_stones.set(i);
    else if (readchar == '@' || readchar == '+') {
      if (m_player == s_noplayer)
        m_player = i;
      else
        manyplayers = true;
    }
    if (readchar == '.' || readchar == '*' || readchar == '+')
      m_targets.set(i);
  }

  if (manyplayers || !sane()) {
    throw std::runtime_error("invalid input");
  }
}

bool Board::sane()
{
  if (popcount(m_stones()) != popcount(m_targets()))
  {
    std::cout << "Number of targets nor equal to number of stones" << std::endl;
    return false;
  }
  if ((m_walls & default_walls) != default_walls)
  {
    std::cout << "Default walls missing" << std::endl;
    return false;
  }
  if ((m_stones & m_walls) != 0)
  {
    std::cout << "A stone on a wall" << std::endl;
    return false;
  }
  if ((m_targets & m_walls) != 0)
  {
    std::cout << "Target on a wall" << std::endl;
    return false;
  }
  if (m_player == s_noplayer)
  {
    std::cout << "No player defined!" << std::endl;
    return false;
  }
  if ((BitBoard(m_player) & m_walls) != 0)
  {
    std::cout << "Player on the wall" << std::endl;
    return false;
  }
  return true;
}

std::ostream& operator<<(std::ostream& outputstream, Board const& board)
{
  board.write(outputstream);
  return outputstream;
}

std::istream& operator>>(std::istream& inputstream, Board& board)
{
  BoardString inputstring;
  char getchars[65];
  inputstream.get(getchars, 65);

  inputstring.assign(getchars);
  board.read(inputstring);
  return inputstream;
}
