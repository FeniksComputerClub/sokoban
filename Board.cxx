#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cassert>

using namespace directions;

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
  m_reachables = empty;
}

std::string Board::write(BitBoard const& colors) const
{
  static char const* const reset_color = "\e[0m";
  static char const* const marker_color = "\e[104m";
  static char const* const reachable_color = "\e[102m";

  std::string outputstring;
  bool isplayerset = false;
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i() > 0 && i() % 8 == 0)
      outputstring += '\n';

    bool iscolorset = colors.test(i);
    if (iscolorset)
      outputstring += marker_color;

    if (m_walls.test(i))
      outputstring += '#';
    else if (m_stones.test(i))
      outputstring += m_targets.test(i) ? '*' : '$';
    else if (m_reachables.test(i))
    {
      if (!iscolorset)
      {
        outputstring += reachable_color;
        iscolorset = true;
      }
      if (!isplayerset)
      {
        outputstring += m_targets.test(i) ? '+' : '@';
        isplayerset = true;
      }
      else
        outputstring += ' ';
    }
    else if (m_targets.test(i))
      outputstring += '.';
    else
      outputstring += ' ';

    if (iscolorset)
      outputstring += reset_color;
  }
  return outputstring;
}

void Board::reachable(Index start)
{
  BitBoard const not_obstructed = ~(m_walls | m_stones);
  m_reachables = BitBoard(start);
  BitBoard previous(0);
  do
  {
    previous = m_reachables;
    m_reachables |= m_reachables.spread(left|right|up|down) & not_obstructed;
  }
  while(m_reachables != previous);
}

BitBoard Board::pushable(int direction) const
{
  direction -= direction & (direction -1); // Only one bit may be set.
  BitBoard const not_obstructed = ~(m_walls | m_stones);
  return m_reachables.spread(direction) & m_stones & not_obstructed.spread(reverse(direction));
}

void Board::read(BoardString const& inputstring)
{
  reset();

  size_t const len = inputstring.length();
  if (len != 64)
    throw std::runtime_error(len < 64 ? "input too short" : "input too long");

  Index player(index_end);
  bool manyplayers = false;
  for (Index i = index_begin; i != index_end; ++i)
  {
    if ((default_walls.M_bitmask & index2mask(i))) // default_walls.test(i)
      continue;

    char readchar = inputstring[i()];
    if (readchar == '#')
      m_walls.set(i);
    else if (readchar == '$' || readchar == '*')
      m_stones.set(i);
    else if (readchar == '@' || readchar == '+')
    {
      if (player == index_end)
        player = i;
      else
        manyplayers = true;
    }
    if (readchar == '.' || readchar == '*' || readchar == '+')
      m_targets.set(i);
  }
  reachable(player);

  if (!sane() || manyplayers)
  {
    if (manyplayers)
      std::cout << "error: There are multiple players in input!" << std::endl;
    throw std::runtime_error("invalid input");
  }
}

bool Board::sane() const
{
  std::string errorstring;
  if (m_reachables == empty)
    errorstring.append("No player defined!\n");
  if (m_targets == empty)
    errorstring.append("There are no goals!\n");
  if (__builtin_popcountll(m_stones()) != __builtin_popcountll(m_targets()))
    errorstring.append("The amount of stones is not equal to the amount of goals!\n");
  if ((m_walls & default_walls) != default_walls)
    errorstring.append("Surrounding walls are missing! (should never occur)\n");
  if (((m_stones & m_walls) != empty) && ((m_targets & m_walls) != empty) && ((m_reachables & m_walls) != empty))
    errorstring.append("Another object is inside a wall! (should never occur)\n");

  if(errorstring == "")
    return true;
  std::cout << "error: " << errorstring;
  return false;
}

BitBoard Board::getreachables() const {return m_reachables;}

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
