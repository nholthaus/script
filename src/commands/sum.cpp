#include <command>

/*
NAME
    sum - add two integers and store the result

SYNOPSIS
    sum <output> <a> <b>

DESCRIPTION
    Expands variables in the numeric inputs, adds the two integer values, and
    stores the result in <output>.
*/
REGISTER_COMMAND
{
	auto vars = args;
	DEREFERENCE(vars);
	const auto& splitVars = utils::split(vars);

	if (splitVars.size() != 3)
		ERROR("requires 3 arguments <output> <a> <b>");

	try
	{
		const int a = std::stoi(splitVars[1].c_str());
		const int b = std::stoi(splitVars[2].c_str());
		SET_VARIABLE(splitVars[0], std::to_string(a + b));
	}
	catch (std::exception& e)
	{
		ERROR("Input values must be integers");
	}
};
