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

void Directions::reset()
{
  m_data = none;
}

void Directions::set(DirectionsData data)
{
  m_data = data & all;
}

Directions Directions::reverse() const
{
  return ((m_data >> 2) | (m_data << 2)) & all;
}

bool Directions::next()
{
  if (m_data)
    m_data <<= 1;
  else
    m_data = right;
  if (m_data & ~all)
  {
    m_data = (m_data | right) & all;
    return false;
  }
  return true;
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
