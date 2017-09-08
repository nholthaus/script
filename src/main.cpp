#include "script.h"
#include "parser.h"

int main(int argc, char* argv[])
{
	Script::instance().run(Parser::parse(argv[1]));
	return 0;
}