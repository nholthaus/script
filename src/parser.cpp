#include "parser.h"

#include <sstream>

Commands Parser::parse(const std::string& script)
{
    Commands commands;
    std::istringstream ss(script);

	std::string line;
	size_t lineNumber = 0;
	while (std::getline(ss, line))
		commands.emplace_back(line, ++lineNumber);

	return commands;
}

