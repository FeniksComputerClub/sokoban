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

Directions::Directions(bool right, bool down, bool left, bool up)
{
  set(right, down, left, up);
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
  m_right = input & right_pos;
  m_down = input & down_pos;
  m_left = input & left_pos;
  m_up = input & up_pos;
}

void Directions::set(bool right, bool down, bool left, bool up)
{
  m_right = right;
  m_down = down;
  m_left = left;
  m_up = up;
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
  std::swap(m_right, m_left);
  std::swap(m_down, m_up);
}

bool Directions::next()
{
  if(!(m_right | m_down | m_left | m_up))
    set(1, 0, 0, 0);
  else if (m_right && !m_down)
    std::swap(m_right, m_down);
  else if (m_down && !m_left)
    std::swap(m_down, m_left);
  else if (m_left && !m_up)
    std::swap(m_left, m_up);
  else if (m_up && !m_right)
  {
    std::swap(m_up, m_right);
    return false;
  }
  else
    return false;
  return true;
}

std::string Directions::name() const
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
  if (names.length())
    names = names.substr(5);
  return names;
}

std::ostream& operator<<(std::ostream& outputstream, Directions const& input)
{
  outputstream << input.name();
  return outputstream;
}
