#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>

int main(){
  std::string setup_a = //test setup for error throwing but does not throw errors, not solvable
    "########"
    "#--@-  -"
    "#**$-.--"
    "#-#####$"
    "#- --$$$"
    "# --  .."
    "#LOL$..."
    "########";
  std::string setup_b = //test setup for error throwing but throws as many errors as possible, not printable
    ".#######"
    "#--@-++-"
    "#**$-.--"
    "#-#####$"
    "#-@--$$$"
    "#+--  --"
    "#LOL$---"
    ".#######";
  std::string setup_c = //test setup for reachable calculation, not solvable
    "########"
    "#-------"
    "#######-"
    "#---$##@"
    "#---#.#-"
    "#-#-###-"
    "#-------"
    "########";
  std::string setup_d = //test setup for pushable calculation, not solvable
    "########"
    "#@----$-"
    "###$#---"
    "#---$--$"
    "#--#$---"
    "#---$###"
    "#......-"
    "########";

  try {
    using namespace directions;
    Board beta(setup_d);

    std::list<BitBoard> boardlist;
    for (int direction = right; direction <= up; direction <<= 1)
      boardlist.push_back(beta.pushable(direction));

    std::list<BitBoard>::const_iterator it;
    it = boardlist.begin();
      std::cout << "go 1" << std::endl;
    while (it != boardlist.end())
    {
      std::cout << "go 2" << std::endl;
      Index pushable_stone = index_pre_begin;
      pushable_stone.next_bit_in(BitBoard(*it)());
      while (pushable_stone != index_end)
      {
        std::cout << "go 3" << std::endl;
        Board moved = beta;
        moved.move(pushable_stone, 1 << (std::distance(std::list<BitBoard>::const_iterator(boardlist.begin()), it) - 1));
        std::cout << "\nThis stone is pushed " << name(1 << (std::distance(std::list<BitBoard>::const_iterator(boardlist.begin()), it) - 1)) << ":\n" << beta.write(pushable_stone) << std::endl;
        pushable_stone.next_bit_in(BitBoard(*it)());
      }
      ++it;
    }
#if 0
    std::cout << "test: ";
    for (int i = 0; i <= 120; ++i)
      std::cout << "\e[" << i << "m-" << i << "-" << "\e[0m";
    std::cout << std::endl;
#endif
  }
  catch(std::runtime_error const& error) {
    std::cout << "runtime error: " << error.what() << std::endl;
  }
  catch(std::logic_error const& error) {
    std::cout << "logic error: " << error.what() << std::endl;
  }
  catch(std::exception const& error) {
    std::cerr << "EXCEPTION!" << std::endl;
  }
  std::cout << "Leaving main()" << std::endl;
}
