#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>

std::string const board_string =
	"########"
	"#       "
	"#       "
	"#       "
	"#       "
	"#       "
	"#       "
	"########";

int main()
{
  Board b;
  std::stringstream s;
  s << b;
  Board a(board_string);
  s >> a;
  std::cout<< board_string <<std::endl;
}
