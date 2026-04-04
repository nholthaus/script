#include "parser.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <source.h>

Commands Parser::parse(const std::filesystem::path& script)
{
	Commands commands;
	std::ifstream file(script, std::ios::in);
	if (!file.is_open())
		throw std::runtime_error("could not open script file: " + script.string());

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::istringstream ss(buffer.str());

	std::string line;
	size_t lineNumber = 0;
	while (std::getline(ss, line))
		commands.emplace_back(line, Source{script, ++lineNumber});

	return commands;
}
