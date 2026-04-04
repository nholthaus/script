#include <command>
#include <split.h>

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
