#pragma once

#include <string>
#include <vector>

struct Command
{
	Command(const std::string& line);

	std::string name;
	std::string args;
};

using Commands = std::vector<Command>;