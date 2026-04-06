#include <command>

/*
NAME
    echo - write text to standard output

SYNOPSIS
    echo <text>

DESCRIPTION
    Expands variables in the provided text and writes the result without
    appending a trailing newline.
*/
REGISTER_COMMAND
{
	auto output = args;
	DEREFERENCE(output);
	std::cout << output;
	std::cout.flush();
};
