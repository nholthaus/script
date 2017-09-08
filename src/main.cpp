#include "script.h"


int main(int argc, char* argv[])
{
	Script::instance().run(argv[1]);
	return 0;
}