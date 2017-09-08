#pragma once

#include <fstream>

#include "command.h"

struct Parser
{
	static Commands parse(const std::string& filePath)
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
};