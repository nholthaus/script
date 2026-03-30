#pragma once

#include <functional>
#include <string>

struct CommandCallback
{
	std::string name;
	std::function<void(const std::string&)> callback;
};
