#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

BitBoard const empty(0);
BitBoard const default_walls = file_a|rank_1|rank_8;

Index const Board::s_noplayer(index_end);

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

void Board::write(std::ostream& outputstream, BitBoard const& colors) const
{
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i() > 0 && i() % 8 == 0)
      outputstream << '\n';

    bool iscolorset = colors.test(i);
    if (iscolorset)
      outputstream << "\e[45m";
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
    if (iscolorset)
      outputstream << "\e[0m";
  }
}

void Board::reachable(BitBoard& outputboard) const
{
  outputboard = ~(m_walls | m_stones);
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
    if (i() < 8 || (i() > 0 && i() % 8 == 0) || i() > 8 * 7)
      continue;
    char readchar = inputstring[i()];
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

  if (!sane() ||  manyplayers) {
    throw std::runtime_error(/*(manyplayers ? "There are multiple players in input!\n" : "") .*/ "invalid input");
  }
}

bool Board::sane()
{
  std::string errorstring;
  if (__builtin_popcountll(m_stones()) != __builtin_popcountll(m_targets()))
    errorstring.append("The amount of stones is not equal to the amount of goals!\n");
  if ((m_walls & default_walls) != default_walls)
    errorstring.append("Surrounding walls are missing! (should never occur)\n");
  if (((m_stones & m_walls) != 0) && ((m_targets & m_walls) != 0) && ((BitBoard(m_player) & m_walls) != 0))
    errorstring.append("Another object is inside a wall! (should never occur)\n");
  if (m_player == s_noplayer)
    errorstring.append("No player defined!\n");

  if(errorstring == "")
    return true;
  std::cout << "error: " << errorstring;
  return false;
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
