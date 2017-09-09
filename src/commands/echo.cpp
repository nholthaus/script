#include <command>
#include <iostream>

REGISTER_COMMAND
(
	std::cout << args;
	std::cout.flush();
)