#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cassert>

using namespace directions;

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

std::string Board::write(BitBoard const& colors) const
{
  std::string outputstring;
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i() > 0 && i() % 8 == 0)
      outputstring += '\n';

    bool iscolorset = colors.test(i);
    if (iscolorset)
      outputstring += "\e[45m";
    if (m_walls.test(i))
      outputstring += '#';
    else if (m_stones.test(i))
      outputstring += (m_targets.test(i) ? '*' : '$');
    else if (m_targets.test(i))
      outputstring += (i == m_player ? '+' : '.');
    else if (i == m_player)
      outputstring += '@';
    else
      outputstring += ' ';
    if (iscolorset)
      outputstring += "\e[0m";
  }
  return outputstring;
}

BitBoard Board::reachable() const
{
  BitBoard const not_obstructed = ~(m_walls | m_stones);
  BitBoard output(m_player);
  BitBoard previous(0);
  do
  {
    previous = output;
    output |= output.spread(left|right|up|down) & not_obstructed;
  }
  while(output != previous);
  return BitBoard(output);
}

BitBoard Board::pushable(BitBoard const& reachables, int direction) const
{
  assert((direction & (direction -1)) == 0); // Only one bit may be set.
  BitBoard const not_obstructed = ~(m_walls | m_stones);
  return reachables.spread(direction) & m_stones & not_obstructed.spread(reverse(direction));
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
    if(manyplayers)
      std::cout << "error: There are multiple players in input!" << std::endl;
    throw std::runtime_error("invalid input");
  }
}

bool Board::sane()
{
  std::string errorstring;
  if (__builtin_popcountll(m_stones()) != __builtin_popcountll(m_targets()))
    errorstring.append("The amount of stones is not equal to the amount of goals!\n");
  if ((m_walls & default_walls) != default_walls)
    errorstring.append("Surrounding walls are missing! (should never occur)\n");
  if (((m_stones & m_walls) != empty) && ((m_targets & m_walls) != empty) && ((BitBoard(m_player) & m_walls) != empty))
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
  outputstream << board.write();
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
