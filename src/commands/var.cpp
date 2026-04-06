#include <command>
#include <split.h>

/*
NAME
    var - define or overwrite a variable

SYNOPSIS
    var <name> <value>

DESCRIPTION
    Stores <value> in <name>. The value argument is quote-aware and variables
    inside the value are expanded before assignment.
*/
REGISTER_COMMAND
{
	auto splitArgs = utils::splitQuoted(args);
	if (splitArgs.size() != 2)
	{
		ERROR("requires <name> <value> arguments");
	}

	DEREFERENCE(splitArgs[1]);
	SET_VARIABLE(splitArgs[0], splitArgs[1]);
};
