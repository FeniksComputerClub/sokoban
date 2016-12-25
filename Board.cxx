#include "sys.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>


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

std::string Board::write(BitBoard const& colors, bool showreachables) const
{
  static char const* const reset_color = "\e[0m";
  static char const* const marker_color = "\e[104m";
  static char const* const reachable_color = "\e[102m";

  std::string outputstring;
  bool isplayerset = false;
  for (Index i = index_begin; i < index_end; ++i)
  {
    if (i > index_begin && i() % 8 == 0)
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
      if (showreachables && !iscolorset)
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

void Board::reachable(BitBoard const& start)
{
  m_reachables = start.flowthrough(~(m_walls | m_stones));
}

BitBoard Board::pushable(Directions direction) const
{
  BitBoard const not_obstructed = ~(m_walls | m_stones);
  return m_reachables.spread(direction) & m_stones & not_obstructed.spread(~direction);
}

void Board::move(Index stone, Directions direction)
{
  if(pushable(direction).test(stone))
  {
    m_stones.reset(stone);
    BitBoard boardstone = BitBoard(stone);
    BitBoard temp = boardstone.spread(direction);
    m_stones |= temp;
    if ((temp & m_reachables))
      reachable(stone);
    else
      m_reachables |= boardstone.flowthrough(~(m_walls | m_stones | m_reachables));
  }
}

std::list<Board> Board::get_moves() const
{
  std::list<Board> boardlist;
  Directions direction = Directions();
  while (direction.next())
  {
    BitBoard pushables = pushable(direction);
    Index pushable_stone = index_pre_begin;
    while (true) // loops once for each stone in pushable(direction)
    {
      pushable_stone.next_bit_in(pushables());
      if (pushable_stone == index_end)
        break;
      Board moved(*this);
      moved.move(pushable_stone, direction);
      // if (!moved.deadstone())
        boardlist.push_back(moved);
    }
  }
  return boardlist;
}

bool Board::solved() const
{
  return m_stones == m_targets;
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
  reachable(BitBoard(player));

  std::string errorstring;
  if (!sane(errorstring) || manyplayers)
  {
    errorstring.insert(0, "invalid input:\n");
    if (manyplayers)
      errorstring.append("error: There are multiple players in input!\n");
    throw std::runtime_error(errorstring);
  }
}

bool Board::sane() const
{
  return sanestring() == "";
}

bool Board::sane(std::string& errorstring) const
{
  errorstring += sanestring();
  return errorstring == "";
}

std::string Board::sanestring() const
{
  std::string errorstring;
  if (m_reachables == empty)
    errorstring.append("error: No player defined!\n");
  if (m_targets == empty)
    errorstring.append("error: There are no goals!\n");
  if (__builtin_popcountll(m_stones()) != __builtin_popcountll(m_targets()))
    errorstring.append("error: The amount of stones is not equal to the amount of goals!\n");
  if ((m_walls & default_walls) != default_walls)
    errorstring.append("error: Surrounding walls are missing! (should never occur)\n");
  if (((m_stones & m_walls) != empty) && ((m_targets & m_walls) != empty) && ((m_reachables & m_walls) != empty))
    errorstring.append("error: Another object is inside a wall! (should never occur)\n");
  if (deadstone())
    errorstring.append("error: Some stones in input can never be moved!\n");
  if ((m_reachables.flowthrough(~m_walls).spread(Directions(1, 1, 1, 1)) & (m_stones | m_targets)) != (m_stones | m_targets))
    errorstring.append("error: Some stones or targets in input can never be reached!\n");
  return errorstring;
}

BitBoard Board::deadstone() const
{
#if 0
  BitBoard obstructed = m_walls | m_stones;
  BitBoard deadstones = m_stones & obstructed.spread(Directions(1, 0, 1, 0)) & obstructed.spread(Directions(0, 1, 0, 1));
  while (obstructed != (obstructed & (~m_stones | deadstones)))
  {
    obstructed &= ~m_stones | deadstones;
    deadstones &= obstructed.spread(Directions(1, 0, 1, 0)) & obstructed.spread(Directions(0, 1, 0, 1));
  }
  return deadstones & ~m_targets;
#endif
  return m_stones & m_walls.spread(Directions(1, 0, 1, 0)) & m_walls.spread(Directions(0, 1, 0, 1)) & ~m_targets; //a simpler check that doesn't take stones into acoount
}

std::ostream& operator<<(std::ostream& outputstream, Board const& board)
{
  outputstream << board.write();
  return outputstream;
}

std::istream& operator>>(std::istream& inputstream, Board& board)
{
  char getchars[65];
  inputstream.get(getchars, 65);

  BoardString inputstring(getchars);
  board.read(inputstring);
  return inputstream;
}

bool operator<(Board const& b1, Board const& b2)
{
  return b1.m_stones() != b2.m_stones() ? b1.m_stones() < b2.m_stones() : b1.m_reachables() < b2.m_reachables();
}
