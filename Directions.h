#pragma once

#include "sys.h"
#include <iostream>
#include <string>

class Directions {
  private:
    static int const right_pos = 1;
    static int const down_pos = 2;
    static int const left_pos = 4;
    static int const up_pos = 8;
    static int const max_pos = right_pos | down_pos | left_pos | up_pos;
    static int const reverse_pos = 2;

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

    int operator()() { return get(); };
    Directions& operator|=(int input) { set(get() | input); return *this; };
    Directions& operator&=(int input) { set(get() & input); return *this; };
    Directions& operator^=(int input) { set(get() ^ input); return *this; };
    
    friend std::ostream& operator<<(std::ostream& outputstream, Directions const& input);
    friend bool operator<(Directions const& left, Directions const& right) { return left.get() < right.get(); };
};
