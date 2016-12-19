#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>

int main(){
  std::string setup_a = //test setup for error throwing but does not throw errors, not loadable
    "########"
    "#--@-  -"
    "#**$-.--"
    "#-#####$"
    "#- --$$$"
    "# --  .."
    "#LOL$..."
    "########";
  std::string setup_b = //test setup for error throwing but throws as many errors as possible, not loadable
    ".#######"
    "#--@-++-"
    "#**$-.--"
    "#-#### $"
    "#-@--$#$"
    "#+--  --"
    "#LOL$---"
    ".#######";
  std::string setup_c = //test setup for reachable calculation, not loadable
    "########"
    "#-------"
    "#######-"
    "#---$##@"
    "#---#.#-"
    "#-#-###-"
    "#-------"
    "########";
  std::string setup_d = //test setup for pushable calculation, not loadable
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
  std::string setup_f = //puzzle I found online test setup for solving, solvable in 15 moves
    "########"
    "###   ##"
    "### #   "
    "#    $$@"
    "# # ## #"
    "# . .  #"
    "##   ###"
    "########";
  std::string setup_g = //test setup for error throwing deadstones error, not loadable
    ".#######"
    "#@@@@@@ "
    "#      $"
    "# $    $"
    "# $$  $$"
    "#$ $$  $"
    "#$$ #  $"
    ".#######";

  try {
    // Store all possible boards in all_boards.
    std::map<Board, int> all_boards;
    // Start with just the initial problem setup.
    all_boards.insert(setup_f);


    // Store new boards that we didn't see before in new_boards.
    std::vector<std::set<Board>::iterator> new_boards;
    new_boards.push_back(all_boards.begin());           // Fill it with the initial problem.

    do
    {
      // Run over all new boards, generate moves and put new moves in next_boards.
      std::vector<std::set<Board>::iterator> next_boards;
      for (std::set<Board>::iterator new_board : new_boards)
      {
        std::cout << "New board:\n" << *new_board << std::endl;
        for (Board move : new_board->get_moves())
        {
          std::cout << "Move:\n" << move << std::endl;

          auto result = all_boards.insert(move);
          if (result.second)
            next_boards.push_back(result.first);
        }
      }
      new_boards = next_boards;
    }
    while(!new_boards.empty());
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
