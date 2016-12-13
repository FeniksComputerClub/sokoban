#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <list>
int timetostop = 0;
bool itstimetostop(int whentostop){
  ++timetostop;
  std::cout << "moves left: " << timetostop - whentostop << std::endl;
  if(timetostop >= whentostop)
    return true;
  return false;
}


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
  std::string setup_e = //simple test setup for solving, solvable
    "########"
    "#@-$---."
    "########"
    "########"
    "########"
    "########"
    "########"
    "########";

  try {
    using namespace directions;
    Board beta(setup_d);

    std::list<std::list<Board>> iterationlist;
            std::cout << "go -1" << std::endl;
    std::list<Board> inputlist;
    inputlist.push_back(beta);
    iterationlist.push_back(inputlist);

    bool win = false;
            std::cout << "go 0" << std::endl;
    int repeatamount = 10;
    for (int repeat = 0; repeat <= repeatamount; ++repeat)
    {
std::cout << "go 1 each board in current iteration list, repeats left: " << (repeat - repeatamount) << std::endl;
      std::list<Board> nextlist;

      std::list<Board> currentlist = iterationlist.back();
      std::list<Board>::const_iterator currentit;
      currentit = currentlist.begin();
      while (currentit != currentlist.end())
      {
std::cout << "go 2 each board in current's moves list" << std::endl;
        std::list<Board> boardlist;
        boardlist = Board(*currentit).get_moves();
        if (boardlist.empty())
          currentlist.erase(currentit);
        std::list<Board>::const_iterator boardit;
        boardit = boardlist.begin();
        while (boardit != boardlist.end())
        {
std::cout << "go 3 a board in current's moves list" << std::endl;
          std::cout << std::endl << *boardit << std::endl;
          win = Board(*boardit).win();
          if (win)
            break;
          win = itstimetostop(10000);
          if (win)
            break;
          nextlist.push_back(*boardit);
          ++boardit;
        }
        if (win)
          break;
        ++currentit;
      }
      if (win)
        break;
      iterationlist.push_back(nextlist);
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
}
