#pragma once

#include "sys.h"
#include <iostream>
#include <string>

class Directions {
  private:
    int const right_pos;
    int const down_pos;
    int const left_pos = 4;
    int const up_pos = 8;
    int const max_pos = right_pos | down_pos | left_pos | up_pos;
    int const reverse_pos = 2;

    bool m_right;
    bool m_down;
    bool m_left;
    bool m_up;

  public:
    Directions();
    Directions(int input);
    void reset();
    void set(int input);
    int get() const;
    Directions reverse() const;
    std::string name() const;

    friend int operator()();
    friend std::ostream& operator<<(std::ostream& outputstream, Directions const& input);
    friend bool operator<(Directions const& left, Directions const& right);
    friend Directions& operator|=(int input);
    friend Directions& operator&=(int input);
    friend Directions& operator^=(int input);
