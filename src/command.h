#pragma once

#include <string>
#include <vector>
#include <source.h>

struct Command
{
	Command(const std::string& line, Source source);

	std::string name;
	std::string args;
	Source source;
};

using Commands = std::vector<Command>;