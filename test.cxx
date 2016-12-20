#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>
#include <map>

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
    typedef std::map<Board, int> all_boards_type;
    all_boards_type all_boards;
    // Store iterators to the parent of all boards.
    typedef std::map<Board, all_boards_type::iterator> all_parents_type;
    all_parents_type all_parents;

    // Start with just the initial problem setup.
    all_boards.emplace(setup_f, 0);

    // Store new boards that we didn't see before in new_boards.
    std::vector<all_boards_type::iterator> new_boards;
    new_boards.push_back(all_boards.begin());           // Fill it with the initial problem.

    int count = 1;
    do
    {
      // Run over all new boards, generate moves and put new moves in next_boards.
      typedef std::vector<all_boards_type::iterator> next_boards_type;
      next_boards_type next_boards;
      for (next_boards_type::value_type new_board : new_boards)
      {
        //std::cout << "New board (at move " << new_board->second << "):\n" << new_board->first << std::endl;
        for (Board move : new_board->first.get_moves())
        {
          //std::cout << "Move:\n" << move << std::endl;

          auto result = all_boards.insert(all_boards_type::value_type(move, count));
          if (result.second)
	  {
            next_boards.push_back(result.first);
	    all_parents.insert(all_parents_type::value_type(move, new_board));
	    if (move.solved())
	    {
	      std::cout << "Solved in " << count << " moves:\n" << move << std::endl;
	    }
	  }
        }
      }
      new_boards = next_boards;
      ++count;
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
