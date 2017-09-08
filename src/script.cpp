#include "script.h"
#include "commandCallback.h"
#include "command.h"
#include "parser.h"

#include <iostream>

void Script::registerCommand(CommandCallback&& cc)
{
	m_callbacks.insert(std::make_pair(std::move(cc.name), std::move(cc.callback)));
}

void Script::run(const std::string& filePath)
{
	auto& me = instance();
	auto&& commands = Parser::parse(filePath);
	for (const Command& command : commands)
	{
		me.m_callbacks[command.name](command.args);
	}
}

Script& Script::instance()
{
	static Script m_instance;
	return m_instance;
}
