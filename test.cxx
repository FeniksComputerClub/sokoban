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
	Board alpha;
	Board beta;
	std::stringstream setupstream;

	try {
		alpha = Board(setup);
		std::cout << alpha << std::endl;
		setupstream << setup;
		setupstream >> beta;
		std::cout << beta << std::endl;
	}
	catch(std::runtime_error const& error) {
		std::cout << "error: " << error.what() << std::endl;
	}
}