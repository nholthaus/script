#include "script.h"
#include "parser.h"
#include "scriptInstance.h"
#include <iostream>
#include <regex>

ScriptInstance& Script::instance = ScriptInstance::getInstance();


void Script::run(const std::string& script)
{
	auto& commands = ScriptInstance::setCommands(Parser::parse(script));
	auto& executionIndex = ScriptInstance::getInstructionIndex();
    for (executionIndex = 0; executionIndex < commands.size(); ++executionIndex)
    {
		auto& command = commands[executionIndex];
    	try
    	{
    		dereferenceVariables(command.args);
    		instance.m_callbacks[command.name](command.args);
    	}
    	catch (...)
    	{
    		if (!command.name.empty())
    		{
    			std::cerr << std::endl << "FATAL ERROR: Invalid command '" << command.name << "'" << std::endl;
    		}
    	}
    }
}

void Script::dereferenceVariables(std::string& args)
{
    // matches variables that start with $.
    std::regex varRx(R"(\$(\w*))");
    std::smatch matches;
    auto lineBegin = std::sregex_iterator(args.begin(), args.end(), varRx);
    auto lineEnd = std::sregex_iterator();

    for (auto itr = lineBegin; itr != lineEnd; ++itr)
    {
		if (const auto& match = *itr; match.size() >= 2)
        {
            auto varName = match[1].str();
            try
            {
                auto varValue = ScriptInstance::getVariable(varName);
                args.replace(match.position(), match.length(), varValue.c_str());
            }
            catch (const std::out_of_range&)
            {
                std::cout << "ERROR: undefined variable: " << varName << std::endl;
                std::exit(1);
            }
        }
    }
}
