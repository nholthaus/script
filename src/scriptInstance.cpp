#include "scriptInstance.h"

ScriptInstance& ScriptInstance::getInstance()
{
	static ScriptInstance m_instance;
	return m_instance;
}
void ScriptInstance::registerCommand(CommandCallback&& cc)
{
	getInstance().m_callbacks.emplace(std::move(cc.name), std::move(cc.callback));
}
void ScriptInstance::setVariable(const std::string& name, const std::string& value)
{
	getInstance().m_callstack.back().localVariables().insert_or_assign(name, value);
}
void ScriptInstance::setMetadata(const std::string& name, const std::string& value)
{
	getInstance().m_callstack.back().metadata().insert_or_assign(name, value);
}
Commands& ScriptInstance::setCommands(Commands&& commands)
{
	auto& instance              = getInstance();
	instance.m_commands         = std::move(commands);
	instance.m_instructionIndex = 0;
	instance.m_callstack        = {};
	return instance.m_commands;
}
Commands& ScriptInstance::getCommands()
{
	return getInstance().m_commands;
}
size_t ScriptInstance::getCommandCount()
{
	return getInstance().m_commands.size();
}
Command& ScriptInstance::getCommand(size_t index)
{
	return getInstance().m_commands.at(index);
}
std::string ScriptInstance::getVariable(const std::string& name)
{
	for (auto stackItr = getInstance().m_callstack.rbegin(); stackItr != getInstance().m_callstack.rend(); ++stackItr)
	{
		if (stackItr->localVariables().contains(name))
			return stackItr->localVariables()[name];
		if (stackItr->policy() != ContextFrame::INHERIT)
			break;
	}
	throw std::runtime_error("Undefined variable '" + name + "'");
}
std::string ScriptInstance::getMetadata(const std::string& name)
{
	return getInstance().m_callstack.back().metadata()[name];
}
bool ScriptInstance::hasVariable(const std::string& name)
{
	for (auto stackItr = getInstance().m_callstack.rbegin(); stackItr != getInstance().m_callstack.rend(); ++stackItr)
	{
		if (stackItr->localVariables().contains(name))
			return true;
		if (stackItr->policy() != ContextFrame::INHERIT)
			break;
	}
	return false;
}
bool ScriptInstance::hasMetadata(const std::string& name)
{
	return getInstance().m_callstack.back().metadata().contains(name);
}
bool ScriptInstance::removeVariable(const std::string& name)
{
	for (auto stackItr = getInstance().m_callstack.rbegin(); stackItr != getInstance().m_callstack.rend(); ++stackItr)
	{
		if (stackItr->localVariables().remove(name))
			return true;
		if (stackItr->policy() != ContextFrame::INHERIT)
			break;
	}
	return false;
}
bool ScriptInstance::removeMetadata(const std::string& name)
{
	return getInstance().m_callstack.back().metadata().remove(name);
}
Command& ScriptInstance::getCurrentCommand()
{
	return getCommand(getInstructionIndex());
}
Source& ScriptInstance::getSource()
{
	return getCurrentCommand().source;
}
size_t ScriptInstance::getLineNumber()
{
	return getCurrentCommand().source.lineNumber();
}
StringMap& ScriptInstance::getLocalMetadata()
{
	return getInstance().m_callstack.back().metadata();
}
StringMap& ScriptInstance::getLocalVariables()
{
	return getInstance().m_callstack.back().localVariables();
}
size_t& ScriptInstance::getInstructionIndex()
{
	return getInstance().m_instructionIndex;
}
bool ScriptInstance::isValidInstruction(size_t index)
{
	return index < getCommandCount();
}
void ScriptInstance::setInstruction(size_t index)
{
	getInstructionIndex() = index;
}
void ScriptInstance::pushStack(size_t returnIndex, ContextFrame::Policy policy)
{
	if (getInstance().m_callstack.size() >= 100)
		throw std::runtime_error("STACK OVERFLOW");

	const Command& currentCommand = getCurrentCommand();
	ContextFrame   stackFrame(currentCommand.source, returnIndex, policy);
	getInstance().m_callstack.push_back(std::move(stackFrame));
}
bool ScriptInstance::popStack()
{
	getInstance().m_instructionIndex = getInstance().m_callstack.back().returnIndex();
	getInstance().m_callstack.pop_back();

	if (getInstance().m_callstack.empty())
		return false;

	return true;
}
ScriptInstance::ScriptInstance() = default;
