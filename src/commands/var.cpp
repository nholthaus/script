#include <command>
#include <split.h>

REGISTER_COMMAND
(
	const auto splitArgs = utils::splitQuoted(args);
	if (splitArgs.size() != 2)
	{
		ERROR("requires <name> <value> arguments");
	}

	ScriptInstance::registerVariable(splitArgs[0], splitArgs[1]);
)