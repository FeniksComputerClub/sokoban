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
      std::cout << "\e[" << i << "m-" << i << "-" << "\e[0m";
    std::cout << std::endl;
  }
  catch(std::runtime_error const& error) {
    std::cout << "error: " << error.what() << std::endl;
  }

  cwchess::BitBoardData const x = { 0 };
  cwchess::BitBoard const y(x);

  // Construction.
  BitBoard const z;
  BitBoard const z2(x);
  BitBoard const z3(y);
  BitBoard const z4(z);

  // Assignment.
  BitBoard b;
  b = x;
  b = y;
  b = z;

  // operator~
  b = ~z;

  // operator...=
  b |= x;
  b |= y;
  b |= z;
  b &= x;
  b &= y;
  b &= z;
  b ^= x;
  b ^= y;
  b ^= z;

  // operator|
  b = z | x;
  b = z | y;
  b = z | z;
  b = x | z;
  b = y | z;
  b = z & x;
  b = z & y;
  b = z & z;
  b = x & z;
  b = y & z;
  b = z ^ x;
  b = z ^ y;
  b = z ^ z;
  b = x ^ z;
  b = y ^ z;

  // toggle
  b.reset(x);
  b.reset(y);
  b.reset(z);
  b.set(x);
  b.set(y);
  b.set(z);
  b.toggle(x);
  b.toggle(y);
  b.toggle(z);
  bool d;
  d = b.test(x);
  d = b.test(y);
  d = b.test(z);
  d = z == x;
  d = z == y;
  d = x == z;
  d = y == z;
  d = z == z;
  d = z != x;
  d = z != y;
  d = z != z;
  d = x != z;
  d = y != z;
}
