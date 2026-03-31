#include <script.h>

#include <iostream>

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "ERROR: expected a script file path argument" << std::endl;
		return 1;
	}

	try
	{
		Script::run(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
