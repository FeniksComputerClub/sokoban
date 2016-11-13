#include "sys.h"
#include "Board.h"
#include <iostream>
#include <sstream>

int main(){
	std::string guts = 
		"########"
		"#-------"
		"#-------"
		"#-------"
		"#-------"
		"#-------"
		"#-------"
		"########";
	Board apple;
	Board banana;
	std::stringstream orange;

	orange << apple;
	orange >> banana;
}