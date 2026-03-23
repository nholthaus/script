#include <command>
#include <split.h>

REGISTER_COMMAND
(
	const auto splitArgs = utils::splitQuoted(args);
	if (splitArgs.size() != 2)
	{
		std::cerr << "ERROR: 'var' requires <name> <value> arguments. Line: " << CURRENT_LINE << std::endl;
	}

	ScriptInstance::registerVariable(splitArgs[0], splitArgs[1]);
)