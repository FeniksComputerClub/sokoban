#pragma once

#include <string>
#include <iosfwd>


class Directions {
  private:
    //struct DirectionsData {
    //  uint64_t bitmask;
    //};
    typedef uint64_t DirectionsData; // why can't things be easy?

    //DirectionsData operator|(DirectionsData input_x, DirectionsData input_y) { return Directionsdata(input_x.bitmask | input_y.bitmask); }
    //DirectionsData operator&(DirectionsData input_x, DirectionsData input_y) { return Directionsdata(input_x.bitmask & input_y.bitmask); }
    //DirectionsData operator^(DirectionsData input_x, DirectionsData input_y) { return Directionsdata(input_x.bitmask ^ input_y.bitmask); }

    DirectionsData m_data;

  public:
    DirectionsData const right = 1; // { CW_MASK_T_CONST(0x1) };
    DirectionsData const down = 2; // { CW_MASK_T_CONST(0x2) };
    DirectionsData const left = 4; // { CW_MASK_T_CONST(0x4) };
    DirectionsData const up = 8; // { CW_MASK_T_CONST(0x8) };
    DirectionsData const none = 0; // { CW_MASK_T_CONST(0x0) };
    DirectionsData const all = 15; // { CW_MASK_T_CONST(0x15) };

    Directions();
    Directions(DirectionsData data);
    Directions(bool set_right, bool set_down, bool set_left, bool set_up);

    void set(DirectionsData data);
    void set(bool set_right, bool set_down, bool set_left, bool set_up);
    void reset();
    void reverse();
    bool next();

    DirectionsData get() const { return m_data; } // make this private
    DirectionsData test(DirectionsData data) const { return m_data & data; }
    std::string name() const;

    Directions& operator|=(Directions const& input) { set(m_data | input.get()); return *this; }
    Directions& operator&=(Directions const& input) { set(m_data & input.get()); return *this; }
    Directions& operator^=(Directions const& input) { set(m_data ^ input.get()); return *this; }

    friend Directions operator|(Directions const& input1, Directions const& input2) { return Directions(input1.get() | input2.get()); }
    friend Directions operator&(Directions const& input1, Directions const& input2) { return Directions(input1.get() & input2.get()); }
    friend Directions operator^(Directions const& input1, Directions const& input2) { return Directions(input1.get() ^ input2.get()); }
    friend Directions operator~(Directions const& input) { Directions output(input); output.reverse(); return output; }

    friend std::ostream& operator<<(std::ostream& outputstream, Directions const& input);
    friend bool operator<(Directions const& input1, Directions const& input2) { return input1.get() < input2.get(); };

};
