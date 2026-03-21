#pragma once

#include "commandCallback.h"

#include <unordered_map>

// There are probably macros you should be using instead of invoking these functions
// directly.
struct ScriptInstance
{
	friend class Script;
	using Callback = std::function<void(const std::string&)>;

	ScriptInstance(const ScriptInstance&) = delete;
	void operator=(const ScriptInstance&) = delete;

	static ScriptInstance& getInstance()
	{
		static ScriptInstance m_instance;
		return m_instance;
	}
	static void registerCommand(CommandCallback&& cc)
	{
		getInstance().m_callbacks.emplace(std::move(cc.name), std::move(cc.callback));
	}

private:

	ScriptInstance() = default;

	std::unordered_map<std::string, Callback> m_callbacks;
};