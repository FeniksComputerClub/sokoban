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
    for (int i = 1; i <= 8; i <<= 1)
      std::cout << "\nPushable direction " << directions::name(i) << ":\n" << beta.write(beta.pushable(i)) << std::endl;
    std::cout << "test: ";
    for (int i = 0; i <= 120; ++i)
      std::cout << "\e[" << i << "m-" << i << "-";
    std::cout << std::endl;
  }
  catch(std::runtime_error const& error) {
    std::cout << "error: " << error.what() << std::endl;
  }
}
