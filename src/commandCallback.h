#pragma once

#include <string>
#include <functional>

struct CommandCallback
{
	std::string name;
	std::function<void(const std::string&)> callback;
};

constexpr int32_t basename_index(const char * const path, const int32_t index = 0, const int32_t slash_index = -1)
{
	return path[index]
		? (path[index] == '/'
			? basename_index(path, index + 1, index)
			: basename_index(path, index + 1, slash_index)
			)
		: (slash_index + 1)
		;
}