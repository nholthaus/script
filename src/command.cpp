#include "command.h"
#include <regex>
#include <source.h>

Command::Command(const std::string& line, Source source)
	: source(std::move(source))
{
	// split line into command + args
	// args are a single string so that each newly added command can
	// parse them as they please
	const std::regex rgx("(.*?)\\s+(.*)");
	if (std::smatch matches; std::regex_match(line, matches, rgx))
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
	else
	{
		name = line;
	}
}
