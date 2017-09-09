#pragma once

#include <string>
#include <functional>

struct CommandCallback
{
	std::string name;
	std::function<void(const std::string&)> callback;
};