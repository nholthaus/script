#pragma once

#include <command.h>
#include <commandCallback.h>
#include <contextFrame.h>
#include <unordered_map>

// There are probably macros you should be using instead of invoking these functions
// directly.
struct ScriptInstance
{
	friend class Script;
	using Callback                        = std::function<void(const std::string&)>;

	// Singleton...
	static ScriptInstance& getInstance();

	ScriptInstance(const ScriptInstance&) = delete;
	void operator=(const ScriptInstance&) = delete;

	static Command&        getCurrentCommand();
	static Command&        getCommand(size_t index);
	static size_t          getCommandCount();
	static Commands&       getCommands();
	static size_t&         getInstructionIndex();
	static size_t          getLineNumber();
	static StringMap&      getLocalMetadata();
	static StringMap&      getLocalVariables();
	static std::string     getMetadata(const std::string& name);
	static Source&         getSource();
	static std::string     getVariable(const std::string& name);
	static bool            hasMetadata(const std::string& name);
	static bool            hasVariable(const std::string& name);
	static bool            isValidInstruction(size_t index);
	static bool            popStack();
	static void            pushStack(size_t returnIndex, ContextFrame::Policy policy = ContextFrame::INHERIT);
	static void            registerCommand(CommandCallback&& cc);
	static bool            removeMetadata(const std::string& name);
	static bool            removeVariable(const std::string& name);
	static Commands&       setCommands(Commands&& commands);
	static void            setInstruction(size_t index);
	static void            setMetadata(const std::string& name, const std::string& value);
	static void            setVariable(const std::string& name, const std::string& value);

private:

	ScriptInstance();

	std::unordered_map<std::string, Callback>    m_callbacks{};
	Commands                                     m_commands{};
	size_t                                       m_instructionIndex = 0;
	std::vector<ContextFrame>                    m_callstack{};
	std::unordered_map<std::string, std::string> m_variables{};
};
