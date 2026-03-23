#include "parser.h"

#include <sstream>

Commands Parser::parse(const std::string& script)
{
    Commands commands;
    std::istringstream ss(script);

	std::string line;
	while (std::getline(ss, line))
		commands.emplace_back(line);

	return commands;
}

