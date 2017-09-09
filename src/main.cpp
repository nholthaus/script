#include <script.h>

#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
	// read script from a file
	std::ifstream file;
	file.open(argv[1], std::ios::in);
	std::stringstream buffer;
	buffer << file.rdbuf();

	// run it
	Script::run(buffer.str());
	return 0;
}