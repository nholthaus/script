#pragma once

#include <string>
#include <functional>
#include <map>

#include "commandCallback.h"
#include "command.h"

class Script
{
public:

	using Callback = std::function<void(const std::string&)>;
	
	static Script& instance();
	
	void registerCommand(CommandCallback&& cc);
	void run(const Commands& commands);

private:

	Script() = default;
	Script(const Script&) = delete;
	void operator=(const Script&) = delete;

	std::map<std::string, Callback> m_callbacks;
};