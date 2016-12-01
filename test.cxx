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
	std::string setup_d = 
		"########"
		"#@----$-"
		"###$----"
		"#---$--$"
		"#--#$---"
		"#---$###"
		"#......-"
		"########";

	try {
		Board beta(setup_d);
		std::cout << "\nReachable:\n" << beta.write(beta.reachable()) << std::endl;
		std::cout << "\nPushable:\n" << beta.write(beta.pushable()) << std::endl;
	}
	catch(std::runtime_error const& error) {
		std::cout << "error: " << error.what() << std::endl;
	}
}
