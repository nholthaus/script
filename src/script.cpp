#include "script.h"
#include "parser.h"
#include "scriptInstance.h"

#include <iostream>

ScriptInstance& Script::instance = ScriptInstance::getInstance();

void Script::run(const std::string& filePath)
{
	for (const Command& command : Parser::parse(filePath))
	{
		instance.m_callbacks[command.name](command.args);
	}
}
