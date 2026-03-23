#pragma once

#include "commandCallback.h"
#include "command.h"

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

    static void registerVariable(const std::string& name, const std::string& value)
    {
        getInstance().m_variables.emplace(name, value);
    }

    static std::string getVariable(const std::string& name)
    {
        return getInstance().m_variables.at(name);
    }

	static size_t getCurrentLine()
    {
	    return getInstance().m_currentLine;
    }

	static void incrementCurrentLine()
    {
	    getInstance().m_currentLine++;
    }

private:
    ScriptInstance() = default;

    std::unordered_map<std::string, Callback> m_callbacks{};
    Commands m_commands{};
    std::unordered_map<std::string, std::string> m_variables{};
	size_t m_currentLine = 1;
};
