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
		std::cerr << "ERROR: " << COMMAND_NAME << " requires a single integer argument <value>. Line: " << CURRENT_LINE << std::endl;
	}

	std::exit(value);
)