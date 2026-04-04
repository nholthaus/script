#pragma once

#include "types/commandCallback.h"
#include "scriptInstance.h"
#include <string>
#include <utility>

// You probably don't need to be in or understand this file. It's black
// magic to implemend the macros in commands/command. Use those instead.

#ifndef FILE_BASENAME
#error FILE_BASENAME must be defined by the build system for command registration.
#endif

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)
#define JOIN_IMPL(a, b) a##b
#define JOIN(a, b) JOIN_IMPL(a, b)

template <typename Callback>
bool operator+(const char* name, Callback&& callback)
{
	ScriptInstance::registerCommand(
	{
		name,
		std::forward<Callback>(callback)
	});
	return true;
}

#define REGISTER_COMMAND_IMPL(name)                                                               \
	static const bool JOIN(name, _command) = STRINGIFY(name) + [](const std::string& args)
