#pragma once

#include "command.h"

struct Parser
{
	static void dereferenceVariables(std::string& line);
	static Commands parse(const std::string& filePath);
};