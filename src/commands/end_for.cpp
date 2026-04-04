#include <command>

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
