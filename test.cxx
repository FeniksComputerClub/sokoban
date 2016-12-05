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
    BitBoard reachables = beta.reachable();
    std::cout << "\nReachable:\n" << beta.write(reachables) << std::endl;
    for (int i = 0; i < 4; ++i)
      std::cout << "\nPushable direction " << i << ":\n" << beta.write(beta.pushable(reachables, i)) << std::endl;
    std::cout << "directions: 0 = right, 1 = down, 2 = left, 3 = up" << std::endl;
  }
  catch(std::runtime_error const& error) {
    std::cout << "error: " << error.what() << std::endl;
  }
}
