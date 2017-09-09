#include "script.h"
#include "parser.h"
#include "scriptInstance.h"

#include <iostream>


ScriptInstance& Script::instance = ScriptInstance::getInstance();

void Script::run(const std::string& filePath)
{
	auto&& commands = Parser::parse(filePath);
	for (const Command& command : commands)
	{
		instance.m_callbacks[command.name](command.args);
	}
}
