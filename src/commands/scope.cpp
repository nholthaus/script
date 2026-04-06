#include <command>
#include <no_op.h>

/*
NAME
    scope - register brace tokens as no-op commands

SYNOPSIS
    {
    }

DESCRIPTION
    Treats brace-only lines as valid commands that do nothing when executed.
*/

namespace
{
	// This is a special registration case, not the normal command pattern.
	// It's good if you're making some other command that uses no-ops or
	// symbols that can't be in file names.
	struct ScopeCommands
	{
		ScopeCommands()
		{
			ScriptInstance::registerCommand({"{", no_op});
			ScriptInstance::registerCommand({"}", no_op});
		}
	} commentCommands;
}
