#include <command>
#include <no_op.h>


namespace
{
	// This is a special registration case, not the normal command pattern.
	// It's good if you're making some other command that uses no-ops or
	// symbols that can't be in file names.
	struct CommentCommands
	{
		CommentCommands()
		{
			ScriptInstance::registerCommand({"#", no_op});
			ScriptInstance::registerCommand({"//", no_op});
			ScriptInstance::registerCommand({"///", no_op});
		}
	} commentCommands;
}
