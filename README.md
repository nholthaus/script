# script

Lightweight, extensible, text-based scripting engine written in C++17.

This project demonstrates a simple command registration pattern where commands are defined in C++ and executed from plain-text script files.

## Features

- C++17 implementation with CMake build
- Line-based script parsing
- Built-in commands:
  - `echo <text>`
  - `wait <seconds>`
- Simple macro-based command registration for adding new commands

## Requirements

- CMake 3.10+
- C++17-compatible compiler
  - MSVC, GCC, or Clang

## Build

### Windows (PowerShell)

```powershell
cmake -S . -B build
cmake --build build --config Release
```

### Linux/macOS

```bash
cmake -S . -B build
cmake --build build -j
```

## Run

The executable expects a script file path as the first argument.

```bash
./build/script examples/helloWorld.script
```

On multi-config generators (for example Visual Studio), run the binary from the selected configuration directory.

## Script Format

Each line is interpreted as:

```text
<command> <args>
```

Example (`examples/helloWorld.script`):

```text
echo Hello
wait 1
echo .
wait 1
echo .
wait 1
echo .
wait 1
echo World!
wait 2
```

## Adding Commands

Commands are registered through the `REGISTER_COMMAND(...)` macro in files under `src/commands/`.

Commands are required to:
- split their own arguments (see `utils` for common helpers)
- error check their own args (use `std::cerr` and `CURRENT_LINE`)

All variables will be dereferenced prior to the invocation of the command callback.

Minimal example:

```cpp
#include <command>
#include <iostream>

REGISTER_COMMAND
(
    std::cout << args;
    std::cout.flush();
)
```

How registration works:

- The command name is derived from the source file basename.
  - Example: `src/commands/echo.cpp` registers command `echo`.
- Command files are added to `COMMAND_SOURCE_FILES` in `CMakeLists.txt` via `GLOB`.

## Macro Reference

Macros are defined in `src/commands/command`.

### `REGISTER_COMMAND(code)`

Primary macro for command authors.

Use this in a command source file under `src/commands/` to register one command callback.

- Input: a C++ code block that can use `args` (`const std::string&`)
- Behavior: creates a static registration object at startup
- Command name: inferred from the file basename via `FILE_BASENAME`

Use this macro for normal command implementation work.

## Project Layout

```text
src/
  main.cpp            # entry point
  parser.*            # line-based script parser
  command.*           # command line splitting
  script.*            # script execution
  commands/           # built-in and custom command implementations
examples/
  helloWorld.script   # sample script
```

## Notes

- Lines are expected to include both a command and arguments.
- Unknown command names currently result in a failed callback lookup.

## Ideas for Improvement

- Streamlined error handling
- Command help registration
- More commands
  - Math
  - Loops
  - Conditionals
  - Scopes
  
## License

MIT. See [LICENSE](LICENSE).
