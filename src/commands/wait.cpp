#include "wait.h"
#include "script.h"
#include "commandCallback.h"

#include <thread>

Wait::Wait()
{
	Script::instance().registerCommand(
	{
		"wait",
		[](const std::string& args)
		{
			std::this_thread::sleep_for(std::chrono::seconds(std::stoi(args)));
		}
	});
};