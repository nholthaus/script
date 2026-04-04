#include <command>

REGISTER_COMMAND
{
	auto output = args;
	DEREFERENCE(output);
	std::cout << output;
	std::cout.flush();
};
