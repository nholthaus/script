#ifndef SCRIPT_NO_OP_H
#define SCRIPT_NO_OP_H

#include <string>

/// no-op scripting operation (i.e. valid, but does nothing)
inline constexpr auto no_op = [](const std::string&) {};

#endif //SCRIPT_NO_OP_H
