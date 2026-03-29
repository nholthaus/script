#include <command>

REGISTER_COMMAND
(
	int value = 0;
	try
	{
		if (args.size() != 1)
			throw std::invalid_argument("Too many arguments");
		value = std::stoi(args);
	}
	catch (...)
	{
		ERROR("requires a single integer argument <value>");
	}

	if (!POP_STACK)
		std::exit(value);
)