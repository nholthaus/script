#pragma once

#include "command.h"
#include <filesystem>

struct Parser
{
	static void dereferenceVariables(std::string& line);
	static Commands parse(const std::filesystem::path& filePath);
};