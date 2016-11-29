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
		alpha.write(std::cout, colors);
		std::cout << std::endl;

		beta = Board(setup_b);
		colors = beta.reachable();
		beta.write(std::cout, colors);
		std::cout << std::endl;
	}
	catch(std::runtime_error const& error) {
		std::cout << "error: " << error.what() << std::endl;
	}
}
