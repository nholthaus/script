#include <command>
#include <thread>

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
		std::cerr << "ERROR: " << COMMAND_NAME << " required a single integer argument <time_s>. Line: " << CURRENT_LINE << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(value));
)