#pragma once

#include <fstream>
#include "command.h"

struct Parser
{
	static Commands parse(const std::string& filePath);
};