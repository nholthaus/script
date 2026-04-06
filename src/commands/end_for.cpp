#include <command>

/*
NAME
    end_for - jump back to the matching for loop

SYNOPSIS
    end_for

DESCRIPTION
    Uses loop metadata recorded by for to continue iteration or fall through
    when the loop is complete.
*/
REGISTER_COMMAND
{
	try
	{
		const auto index = GET_METADATA("LOOP_START_INDEX").asSizeT();
		SET_INSTRUCTION(index);
	}
	catch (const std::exception& e)
	{
		ERROR(std::format("No matching 'for'"));
	}
};
