#include "parser.h"
#include "command.h"
#include "script.h"

Commands Parser::parse(const std::string& filePath)
{
	Commands commands;

	std::ifstream file;
	file.open(filePath, std::ios::in);

	std::string line;
	while (std::getline(file, line))
	{
		commands.push_back(line);
	}

	return commands;
}

