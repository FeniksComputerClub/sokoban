#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

int main(){
	std::string setup_a = 
		"########"
		"#--@-  -"
		"#**$-.--"
		"#-#####$"
		"#- --$$$"
		"# --  .."
		"#LOL$..."
		"########";
	std::string setup_b = 
		".#######"
		"#--@-++-"
		"#**$-.--"
		"#-#####$"
		"#-@--$$$"
		"#+--  --"
		"#LOL$---"
		".#######";
	std::string setup_c = 
		"########"
		"#-------"
		"#######-"
		"#---$##@"
		"#---#.#-"
		"#-#-###-"
		"#-------"
		"########";
	Board alpha;
	Board beta;
	std::stringstream setupstream;
	BitBoard colors;

	try {
		alpha = Board(setup_a);
		colors = alpha.reachable();
		std::cout << alpha << std::endl;

		beta = Board(setup_a);
		colors = beta.reachable();
		std::cout << beta.write(colors) << std::endl;
	}
	catch(std::runtime_error const& error) {
		std::cout << "error: " << error.what() << std::endl;
	}
}
