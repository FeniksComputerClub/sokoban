#include "sys.h"
#include "Directions.h"
#include <string>
#include <ostream>

Directions::Directions()
{
  reset();
}

Directions::Directions(DirectionsData data)
{
  set(data);
}

Directions::Directions(bool right, bool down, bool left, bool up)
{
  set(right, down, left, up);
}

void Directions::reset()
{
  m_data = none;
}

void Directions::set(DirectionsData data)
{
  m_data = data & all;
}

void Directions::set(bool right, bool down, bool left, bool up)
{
  reset();
  if (right)
    m_data |= right;
  if (down)
    m_data |= down;
  if (left)
    m_data |= left;
  if (up)
    m_data |= up;
}

int Directions::get() const
{
  int output = 0;
  if (m_right)
    output &= right_pos;
  if (m_down)
    output &= down_pos;
  if (m_left)
    output &= left_pos;
  if (m_up)
    output &= up_pos;
  return output;
}

void Directions::reverse()
{
  m_data = (m_data >> 2) | (m_data << 2) & all;
}

bool Directions::next()
{
  m_data >>= 1;
  if (m_data & !all)
  {
    m_data = (m_data | right) & all;
    return true;
  }
  return false;
}

std::string Directions::name() const
{
  std::string names;
  if (m_data & right)
    names.append(" and right");
  if (m_data & down)
    names.append(" and down");
  if (m_data & left)
    names.append(" and left");
  if (m_data & up)
    names.append(" and up");
  if (names.length())
    names = names.substr(5);
  return names;
}

std::ostream& operator<<(std::ostream& outputstream, Directions const& input)
{
  outputstream << input.name();
  return outputstream;
}
