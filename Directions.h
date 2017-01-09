#pragma once

#include <string>
#include <iosfwd>

class Directions {
  private:
    typedef uint64_t DirectionsData;

    DirectionsData m_data;

  public:
    static DirectionsData const right = 1;
    static DirectionsData const down = 2;
    static DirectionsData const left = 4;
    static DirectionsData const up = 8;
    static DirectionsData const none = 0;
    static DirectionsData const horizontal = right|left;
    static DirectionsData const vertical = down|up;
    static DirectionsData const all = horizontal|vertical;

    Directions();
    Directions(DirectionsData data);

    void set(DirectionsData data);
    void reset();
    bool next();

    Directions reverse() const;
    std::string name() const;

    Directions& operator|=(Directions const& input) { m_data |= input.m_data; return *this; }
    Directions& operator&=(Directions const& input) { m_data &= input.m_data; return *this; }
    Directions& operator^=(Directions const& input) { m_data ^= input.m_data; return *this; }

    operator bool() const { return m_data; }

    friend Directions operator|(Directions const& input1, Directions const& input2) { return input1.m_data | input2.m_data; }
    friend Directions operator&(Directions const& input1, Directions const& input2) { return input1.m_data & input2.m_data; }
    friend Directions operator^(Directions const& input1, Directions const& input2) { return input1.m_data ^ input2.m_data; }

    friend Directions operator|(Directions const& input1, DirectionsData input2) { return input1.m_data | input2; }
    friend Directions operator&(Directions const& input1, DirectionsData input2) { return input1.m_data & input2; }
    friend Directions operator^(Directions const& input1, DirectionsData input2) { return input1.m_data ^ input2; }

    friend bool operator<(Directions const& input1, Directions const& input2) { return input1.m_data < input2.m_data; }
    friend std::ostream& operator<<(std::ostream& outputstream, Directions const& input);
};
