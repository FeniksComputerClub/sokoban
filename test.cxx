#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

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
    Board beta(setup_d);
    for (int direction = 1; direction <= 8; direction <<= 1)
    {
      BitBoard const pushables(beta.pushable(direction));
      Index pushable_stone = index_pre_begin;
      pushable_stone.next_bit_in(pushables());
      while (pushable_stone != index_end)
      {
        std::cout << "\nThis stone can be pushed " << directions::name(direction) << ":\n" << beta.write(pushable_stone) << std::endl;
        pushable_stone.next_bit_in(pushables());
      }
    }

#if 0
    std::cout << "test: ";
    for (int i = 0; i <= 120; ++i)
      std::cout << "\e[" << i << "m-" << i << "-" << "\e[0m";
    std::cout << std::endl;
#endif
  }
  catch(std::runtime_error const& error) {
    std::cout << "error: " << error.what() << std::endl;
  }
}
