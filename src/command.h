#pragma once

#include <string>
#include <vector>

struct Command
{
	Command(const std::string& line, size_t lineNumber);

	std::string name;
	std::string args;
	size_t lineNumber;
};

using Commands = std::vector<Command>;