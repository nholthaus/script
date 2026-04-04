#ifndef SCRIPT_FINDMATCH_H
#define SCRIPT_FINDMATCH_H

#include <format>
#include <scriptInstance.h>
#include <string>

namespace utils
{
	/// finds a matching close statement, accounting for possible nesting
	static size_t findMatch(const std::string& close)
	{
		const std::string_view commandName = ScriptInstance::getCurrentCommand().name;
		size_t                 nest    = 0;

		for (size_t commandIndex = ScriptInstance::getInstance().getInstructionIndex() + 1;
			 commandIndex < ScriptInstance::getCommandCount(); ++commandIndex)
		{
			try
			{
				const auto& nextCommand = ScriptInstance::getCommands()[commandIndex].name;

				if ( nextCommand== commandName)
				{
					++nest;
				}
				if (nextCommand == close)
				{
					if (nest)
						--nest;
					else
						return commandIndex;
				}
			}
			catch (const std::out_of_range&)
			{
				{
					break;
				}
			}
		}

		throw std::runtime_error(std::format("No matching end to '{}' statement", commandName));
		return 0;
	}
} // namespace utils
#endif // SCRIPT_FINDMATCH_H
