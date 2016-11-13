#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>

int main(){
	std::string setup = 
		"########"
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

	setupstream << setup;
	setupstream >> beta;
	std::cout << beta << std::endl;
}