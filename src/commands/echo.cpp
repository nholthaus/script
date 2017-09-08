#include "echo.h"
#include "script.h"
#include "commandCallback.h"

#include <iostream>

Echo::Echo()	
{
	Script::instance().registerCommand(
	{
		"echo",
		[](const std::string& args)
		{
			std::cout << args;
			std::cout.flush();
		}
	});
};
