#include <command>
#include <cstdlib>
#include <thread>

/*
NAME
    wait - pause execution for a number of seconds

SYNOPSIS
    wait <seconds>

DESCRIPTION
    Expands the argument, parses it as an integer second count, and sleeps for
    that duration unless test mode disables real waits.
*/
REGISTER_COMMAND
{
	int value = 0;
	try
	{
		auto expandedArgs = args;
		DEREFERENCE(expandedArgs);
		if (expandedArgs.size() != 1)
			throw std::invalid_argument("Too many arguments");
		value = std::stoi(expandedArgs);
	}
	catch (...)
	{
		ERROR("requires a single integer argument <time_s>");
	}

	// Tests can disable real sleeps to keep script output checks fast.
	if (const char* disableWait = std::getenv("SCRIPT_DISABLE_WAIT"))
	{
		if (disableWait[0] != '\0' && disableWait[0] != '0')
			return;
	}

	std::this_thread::sleep_for(std::chrono::seconds(value));
};
