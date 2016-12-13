#pragma once

#include "BitBoard.h"
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

    void reset();
    std::string write(BitBoard const& colors = BitBoard(0)) const;
    BitBoard pushable(int direction) const;
    std::list<Board> get_moves() const;
    void read(BoardString const&);
    bool sane() const;

    BitBoard getreachables() const;

    friend std::ostream& operator<<(std::ostream& os, Board const& board);
    friend std::istream& operator>>(std::istream& is, Board& board);
    
  private:
    void reachable(Index start);
    void reachable(BitBoard start);
    void move(Index stone, int direction);
};
