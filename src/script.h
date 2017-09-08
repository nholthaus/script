#pragma once

#include <string>
#include <functional>
#include <map>
#include <vector>

struct Command;
struct CommandCallback;

class Script
{
public:

	using Callback = std::function<void(const std::string&)>;
	
	static Script& instance();
	
	void registerCommand(CommandCallback&& cc);
	void run(const std::string& filePath);

private:

	Script() = default;
	Script(const Script&) = delete;
	void operator=(const Script&) = delete;

	std::map<std::string, Callback> m_callbacks;
};