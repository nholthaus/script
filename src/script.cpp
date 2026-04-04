#include "script.h"
#include "parser.h"
#include "scriptInstance.h"
#include <filesystem>
#include <iostream>
#include <regex>

ScriptInstance& Script::instance = ScriptInstance::getInstance();


void Script::run(const std::filesystem::path& scriptPath)
{
	auto& commands = ScriptInstance::setCommands(Parser::parse(scriptPath));
	auto& executionIndex = ScriptInstance::getInstructionIndex();
	ScriptInstance::pushStack(commands.size());
	for (executionIndex = 0; executionIndex < commands.size();)
	{
		const size_t currentIndex = executionIndex;
		auto& command = commands[executionIndex];
		try
		{
			instance.m_callbacks[command.name](command.args);
		}
		catch (const std::bad_function_call&)
		{
			if (!command.name.empty())
			{
				std::cerr << std::endl << "FATAL ERROR: Unknown command '" << command.name << "' : " << command.source << std::endl;
				std::exit(1);
			}
		}
		catch (const std::exception& e)
		{
			if (!command.name.empty())
			{
				const std::string_view message = e.what();
				std::cerr << std::endl << "FATAL ERROR: '" << command.name << "' ";
				if (message.empty())
					std::cerr << "threw an exception";
				else
					std::cerr << message;
				std::cerr << " : " << command.source << std::endl;
				std::exit(1);
			}
		}
		catch (...)
		{
			if (!command.name.empty())
			{
				std::cerr << std::endl << "FATAL ERROR: Invalid command '" << command.name << "': " << command.source << std::endl;
				std::exit(1);
			}
		}

		if (executionIndex == currentIndex)
			++executionIndex;
	}
}

void Script::dereferenceVariables(std::string& args)
{
	// matches variables that start with $.
	const std::regex varRx(R"(\$(\w*))");
	std::string transformed = args;

	for (;;)
	{
		std::smatch match;
		if (!std::regex_search(transformed, match, varRx))
			break;

		if (match.size() >= 2)
		{
			const auto varName = match[1].str();
			if (!ScriptInstance::hasVariable(varName))
				throw std::runtime_error("Undefined variable '" + varName + "'");

			const auto varValue = ScriptInstance::getVariable(varName);
			transformed.replace(match.position(), match.length(), varValue.c_str());
		}
	}

	args = std::move(transformed);
}
