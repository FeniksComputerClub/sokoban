#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

int main(){
	std::string setup = 
		"########"
		"#--@-  -"
		"#**$-.--"
		"#-#####$"
		"#- --$$$"
		"# --  .."
		"#LOL$..."
		"########";
	std::string setupb = 
		".#######"
		"#--@-++-"
		"#**$-.--"
		"#-#####$"
		"#-@--$$$"
		"#+--  --"
		"#LOL$---"
		".#######";
	std::string setupc = 
		"########"
		"#@------"
		"#######-"
		"#---$##-"
		"#-#-#.#-"
		"#-#####-"
		"#-------"
		"########";
	Board alpha;
	Board beta;
	std::stringstream setupstream;
	BitBoard colors;

	try {
		alpha = Board(setup);
		std::cout << alpha << std::endl;
		setupstream << setup;
		setupstream >> beta;
		beta.reachable(colors);
		beta.write(std::cout, colors);
		std::cout << std::endl;
	}
	catch(std::runtime_error const& error) {
		std::cout << "error: " << error.what() << std::endl;
	}
}
