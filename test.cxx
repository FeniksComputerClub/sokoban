#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>

int main(){
	std::string setup = 
		".#######"
		"#--@-++-"
		"#**$-.--"
		"#-#####$"
		"#-@--$$$"
		"#+--  --"
		"#LOL$---"
		".#######";
	Board alpha;
	Board beta;
	std::stringstream setupstream;

	alpha = Board(setup);
	std::cout << alpha << std::endl;
	setupstream << setup;
	setupstream >> beta;
	std::cout << beta << std::endl;
}
