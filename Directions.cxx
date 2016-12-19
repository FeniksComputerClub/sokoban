#include "sys.h"
#include "Directions.h"
#include <iostream>
#include <string>

Directions::Directions()
{
  reset();
}

Directions::Directions(int input)
{
  set(input);
}

void Directions::reset()
{
  m_right = false;
  m_down = false;
  m_left = false;
  m_up = false;
}

void Directions::set(int input)
{
  if (input & right_pos)
    m_right = true;
  else
    m_right = false;
  
  if (input & down_pos)
    m_down = true;
  else
    m_down = false;
  
  if (input & left_pos)
    m_left = true;
  else
    m_left = false;
  
  if (input & up_pos)
    m_up = true;
  else
    m_up = false;
}

int Directions::get() const
{
  int output;
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

Directions reverse() const
{
  return ((get() >> reverse_pos) | (get() << reverse_pos)) & (max_pos);
}

std::string name() const
{
  std::string names;
  if (m_right)
    names.append(" and right");
  if (m_down)
    names.append(" and down");
  if (m_left)
    names.append(" and left");
  if (m_up)
    names.append(" and up");
  names = names.substr(5);
  return names;
}

std::ostream& operator<<(std::ostream& outputstream, Directions const& input)
{
  outputstream << input.name();
  return outputstream;
}