#include <command>
#include <format>
#include <split.h>

REGISTER_COMMAND
{
	try
	{
		auto expandedArgs = args;
		DEREFERENCE(expandedArgs);
		size_t numArgs = utils::split(expandedArgs).size();
		if (expandedArgs.empty())
			throw std::invalid_argument("requires a single integer argument <value>");
		if (numArgs > 1)
			throw std::invalid_argument(std::format("Too many arguments. Expected 1 got {}", numArgs));

		const int value = std::stoi(expandedArgs);

		if (!POP_STACK)
			std::exit(value);
	}
	catch (const std::exception& e)
	{
		ERROR(e.what());
	}
};
