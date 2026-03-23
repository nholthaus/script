#include <command>

REGISTER_COMMAND
(
	std::cout << args;
	std::cout.flush();
)