#pragma once

#include <string>
#include <regex>
#include <vector>

struct Command
{
	Command(const std::string& line)
	{
		std::smatch matches;
		std::regex rgx("(.*?)\\s+(.*)");
		if (std::regex_match(line, matches, rgx))
		{
			if (matches.size() >= 2)
			{
				name = std::move(matches[1]);
			}
			if (matches.size() == 3)
			{
				args = std::move(matches[2]);
			}
		}

	}

	std::string name;
	std::string args;
};
using Commands = std::vector<Command>;

