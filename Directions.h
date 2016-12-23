#pragma once

#include <string>
#include <iosfwd>

class Directions {
  private:
    // static int const right_pos = 1;
    // static int const down_pos = 2;
    // static int const left_pos = 4;
    // static int const up_pos = 8;
    // static int const max_pos = right_pos | down_pos | left_pos | up_pos;

    bool m_right;
    bool m_down;
    bool m_left;
    bool m_up;

  public:
    Directions();
    Directions(bool right, bool down, bool left, bool up);

    void set(bool right, bool down, bool left, bool up);
    void reset();
    void reverse();
    bool next();

    bool right() const { return m_right; }; 
    bool down() const { return m_down; };
    bool left() const { return m_left; };
    bool up() const { return m_up; };
    std::string name() const;
    
    Directions& operator|=(Directions const& input) { set(input.right() | right(), input.down() | down(), input.left() | left(), input.up() | up()); return *this; }
    Directions& operator&=(Directions const& input) { set(input.right() & right(), input.down() & down(), input.left() & left(), input.up() & up()); return *this; }
    Directions& operator^=(Directions const& input) { set(input.right() ^ right(), input.down() ^ down(), input.left() ^ left(), input.up() ^ up()); return *this; }

    friend Directions operator|(Directions const& input1, Directions const& input2) { return Directions(input1.right() | input2.right(), input1.down() | input2.down(), input1.left() | input2.left(), input1.up() | input2.up()); }
    friend Directions operator&(Directions const& input1, Directions const& input2) { return Directions(input1.right() & input2.right(), input1.down() & input2.down(), input1.left() & input2.left(), input1.up() & input2.up()); }
    friend Directions operator^(Directions const& input1, Directions const& input2) { return Directions(input1.right() ^ input2.right(), input1.down() ^ input2.down(), input1.left() ^ input2.left(), input1.up() ^ input2.up()); }
    friend Directions operator~(Directions const& input) { Directions output(input); output.reverse(); return output; }
    
    friend std::ostream& operator<<(std::ostream& outputstream, Directions const& input);
    friend bool operator<(Directions const& input1, Directions const& input2) { return input1.right() != input2.right() ? input1.right() < input2.right() : input1.down() != input2.down() ? input1.down() < input2.down() : input1.left() != input2.left() ? input1.left() < input2.left() : input1.up() < input2.up(); };

  // private:
    // int get() const;
};
