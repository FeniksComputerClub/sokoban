#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <map>
#include <list>

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
  std::string setup_h = //another puzzle I found online test setup for solving, solvable in 10 moves
    "########"
    "########"
    "#. $ .##"
    "#.$$$@##"
    "#. $ .##"
    "########"
    "########"
    "########";
  std::string setup_i = //test setup for testing if multiple solutions are calculated, solvable in 4 moves
    "########"
    "#     ##"
    "#     ##"
    "# .#$@##"
    "#     ##"
    "#     ##"
    "########"
    "########";
  std::string setup_j = //setup from sokoban app, solvable in 24 moves
    "########"
    "#####  #"
    "#####  #"
    "###  $ #"
    "###.$ .#"
    "####.$ #"
    "####@ ##"
    "########";

  try {
    // Store all possible boards in all_boards.
    typedef std::map<Board, int> all_boards_type;
    all_boards_type all_boards;
    // Store iterators to the parent of all boards.
    typedef std::map<Board, all_boards_type::iterator> all_children_type;
    all_children_type all_children;

    // Start with just the initial problem setup.
    all_boards.emplace(setup_i, 0);

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
        #if(0)
        if (new_board->first.solved())
          std::cout << "Solved in " << new_board->second << " moves" << std::endl;
        #endif
        if (new_board->first.deadstone())
          continue;
        for (Board move : new_board->first.get_moves())
        {
          auto result = all_boards.insert(all_boards_type::value_type(move, count));
          if (result.second)
          {
            next_boards.push_back(result.first);
            all_children.insert(all_children_type::value_type(move, new_board));
          }
        }
      }
      new_boards = next_boards;
      ++count;
    }
    while(!new_boards.empty());

    // find the solved board
    all_children_type::iterator child = all_children.begin();
    while(child != all_children.end())
    {
      if (child->first.solved())
        break;
      ++child;
    }

    // find the parents of the solution by matching their children and put them in list solution
    std::list<Board> solution;
    while(child != all_children.end())
    {
      solution.push_front(child->first);
      all_boards_type::iterator parent = child->second;
      child = all_children.find(parent->first);
    }

    // print boards from setup to solution
    count = 0;
    BitBoard player(empty);
    for (auto board = solution.begin(); board != solution.end();)
    {
      std::cout << ++count << ":\n" << board->write(false, empty, player) << std::endl;
      auto parent = board++;
      player = parent->getstones() & ~board->getstones();
    }
    if (count)
      std::cout << "Solved in " << count << " moves" << std::endl;
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
