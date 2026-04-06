#include <command>

/*
NAME
    endl - write a newline to standard output

SYNOPSIS
    endl

DESCRIPTION
    Flushes a single line ending to standard output.
*/
REGISTER_COMMAND
{
	std::cout << std::endl;
	std::cout.flush();
};
