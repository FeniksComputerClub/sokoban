#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

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
  mask_t const not_obstructed = BitBoard(~(m_walls | m_stones))();
  mask_t output = BitBoard(m_player)();
  mask_t previous(0);
  do
  {
    previous = output;
    output |= /*spread(previous, 4)*/(previous >> 8 | previous >> 1 | previous << 1 | previous << 8)/**/ & not_obstructed;
  }
  while(output != previous);
  return BitBoard(output);
}

BitBoard Board::spread(BitBoard const& input, int const& direction) const
{
  mask_t inputmask = input();
  switch(direction)
  {
    case RIGHT : return BitBoard(inputmask << 1); break;
    case DOWN : return BitBoard(inputmask << 8); break;
    case LEFT : return BitBoard(inputmask >> 1); break;
    case UP : return BitBoard(inputmask >> 8); break;
    default : return BitBoard(inputmask >> 8 | inputmask >> 1 | inputmask << 1 | inputmask << 8); break;
  }
}

BitBoard Board::pushable(BitBoard const& reachables, int const& direction) const // directions: 0 = right, 1 = down, 2 = left, 3 = up
{
  mask_t const empty = ~(m_walls | m_stones)();
  mask_t pushables(0);
  switch(direction)
  {
    case RIGHT : pushables = (m_stones() & (reachables() << 1)) & (empty >> 1); break;
    case DOWN : pushables = (m_stones() & (reachables() << 8)) & (empty >> 8); break;
    case LEFT : pushables = (m_stones() & (reachables() >> 1)) & (empty << 1); break;
    case UP : pushables = (m_stones() & (reachables() >> 8)) & (empty << 8); break;
    default : pushables = (m_stones() & (reachables() << 1)) & (empty >> 1); break;
  }
  return /*spread(reachables, direction) & m_stones & spread(~(m_walls | m_stones), (direction + 2) % 4);*/ BitBoard(pushables);/**/
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
