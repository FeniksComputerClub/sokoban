#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>

int main(){
	std::string guts = 
		"########"
		"#--@----"
		"#**$-.--"
		"#-#####$"
		"#-@--$$$"
		"#+--  --"
		"#LOL$---"
		".#######";
	Board apple;
	Board banana;
	std::stringstream orange;

	orange << guts;
	orange >> banana;
	std::cout << banana << std::endl;
}
