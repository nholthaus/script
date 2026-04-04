#include <command>
#include <thread>

REGISTER_COMMAND
{
	int value = 0;
	try
	{
		if (args.size() != 1)
			throw std::invalid_argument("Too many arguments");
		value = std::stoi(args);
	}
	catch (...)
	{
		ERROR("requires a single integer argument <time_s>");
	}

	std::this_thread::sleep_for(std::chrono::seconds(value));
};