#include "script.h"
#include "parser.h"
#include "scriptInstance.h"

#include <iostream>

ScriptInstance& Script::instance = ScriptInstance::getInstance();

void Script::run(const std::string& script)
{
	for (const Command& command : Parser::parse(script))
	{
		instance.m_callbacks[command.name](command.args);
	}
}
