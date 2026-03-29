#include "scriptInstance.h"

namespace
{
	struct CommentCommands
	{
		CommentCommands()
		{
			ScriptInstance::registerCommand({"#", [](const std::string&) {}});
			ScriptInstance::registerCommand({"//", [](const std::string&) {}});
			ScriptInstance::registerCommand({"///", [](const std::string&) {}});
		}
	} commentCommands;
}
