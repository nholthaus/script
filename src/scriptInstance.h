#pragma once

#include "command.h"
#include "types/commandCallback.h"
#include <stack>
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

    static void setVariable(const std::string& name, const std::string& value)
    {
        getInstance().m_variables.insert_or_assign(name, value);
    }

    static Commands& setCommands(Commands&& commands)
    {
        auto& instance = getInstance();
        instance.m_commands = std::move(commands);
        instance.m_instructionIndex = 0;
        instance.m_callstack = {};
        return instance.m_commands;
    }

    static Commands& getCommands()
    {
        return getInstance().m_commands;
    }

    static size_t getCommandCount()
    {
        return getInstance().m_commands.size();
    }

    static Command& getCommand(size_t index)
    {
        return getInstance().m_commands.at(index);
    }

    static std::string getVariable(const std::string& name)
    {
        return getInstance().m_variables.at(name);
    }

    static bool hasVariable(const std::string& name)
    {
        return getInstance().m_variables.contains(name);
    }

    static bool removeVariable(const std::string& name)
    {
        return getInstance().m_variables.erase(name) > 0;
    }

    static Command& getCurrentCommand()
    {
        return getCommand(getInstructionIndex());
    }

	static Source& getSource()
    {
    	return getCurrentCommand().source;
    }

	static size_t getLineNumber()
	{
	    return getCurrentCommand().source.lineNumber();
    }

	static size_t& getInstructionIndex()
    {
	    return getInstance().m_instructionIndex;
    }

	static bool isValidInstruction(size_t index)
    {
	    return index < getCommandCount();
    }

	static void setInstruction(size_t index)
    {
	    getInstructionIndex() = index;
    }

	static void pushStack()
    {
	   getInstance().m_callstack.push(getInstructionIndex());
    }

	static bool popStack()
    {
    	if (getInstance().m_callstack.empty())
    		return false;

	    getInstance().m_instructionIndex = getInstance().m_callstack.top();
    	getInstance().m_callstack.pop();
    	return true;
    }

private:
    ScriptInstance() = default;

    std::unordered_map<std::string, Callback> m_callbacks{};
    Commands m_commands{};
	size_t m_instructionIndex = 0;
	std::stack<size_t> m_callstack{};
    std::unordered_map<std::string, std::string> m_variables{};
};
