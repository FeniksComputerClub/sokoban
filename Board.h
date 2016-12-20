#pragma once

#include "BitBoard.h"
#include "Directions.h"
#include <iosfwd>
#include <string>
#include <list>

typedef std::string BoardString;

class Board {
  private:
    BitBoard m_walls;
    BitBoard m_stones;
    BitBoard m_targets;
    BitBoard m_reachables;

  public:
    Board();
    Board(std::string const&);

    std::string write(BitBoard const& colors = BitBoard(0), bool showreachables = true) const;
    BitBoard pushable(Directions direction) const;
    std::list<Board> get_moves() const;
    bool solved() const;
    void read(BoardString const&);
    bool sane() const;
    bool sane(std::string& errorstring) const;
    BitBoard deadstone() const;

    BitBoard getreachables() const;

    friend std::ostream& operator<<(std::ostream& os, Board const& board);
    friend std::istream& operator>>(std::istream& is, Board& board);
    friend bool operator<(Board const& b1, Board const& b2);
    
  private:
    void reset();
    void reachable(BitBoard const& start);
    void move(Index stone, Directions direction);
    std::string sanestring() const;
};
