# script

Lightweight, extensible, text-based scripting engine written in C++17.

This project demonstrates a simple command registration pattern where commands are defined in C++ and executed from plain-text script files.

## Design Philosophy

This project is intentionally built around a very small core runtime.

The core is responsible for:
- registering commands
- parsing each line into a command name plus raw argument text
- owning runtime program state
- exposing execution control and variable state
- dispatching commands

New language features should be implemented as commands whenever possible.

That means control flow, syntax conventions, and higher-level language behavior are meant to grow additively through command implementations rather than through constant core refactors.

The design goal is a tiny, stable kernel with a wide command surface, so commands can be implemented independently and in parallel.

## Features

- C++17 implementation with CMake build
- Line-based script parsing
- Built-in commands:
  - `echo <text>`
  - `wait <seconds>`
  - `var <name> <value>`
- Variable system with `$` dereferencing
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

### Linux Fast Path

For this repo on Linux, prefer Ninja + `ccache`:

```bash
cmake --preset linux-ninja-debug
cmake --build --preset build-debug
```

Release build:

```bash
cmake --preset linux-ninja-release
cmake --build --preset build-release
```

From the workspace root, you can also use the helper wrapper:

```bash
/workspace/build-fast
```

This temporarily switches `powerprofilesctl` to `performance` for the build and restores the previous profile on exit.

For other repos, use the generic wrapper from the workspace root:

```bash
/workspace/repo-build-fast /path/to/repo
```

Aggressive build boost plus hard drop back to lounge mode afterward:

```bash
AFTER_BUILD_MODE=lounge /workspace/repo-build-fast /path/to/repo
```

The simpler shell command is:

```bash
build-fast script
build-fast debug script
build-fast target script script
```

With no arguments, `build-fast` tries to detect the current repo from your working directory.

Detection order:

- `CMakePresets.json`
- `CMakeLists.txt`
- `meson.build`
- `Makefile`

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
var helloWhat World!
echo Hello
wait 1
echo .
wait 1
echo .
wait 1
echo .
wait 1
echo $helloWhat
wait 2
ret 0
```

### Variables

Variables can be defined and referenced in scripts:

**Defining variables:**
```text
var <name> <value>
```

**Using variables:**
```text
echo $variableName
```

**Features:**
- Variable names support alphanumeric characters and underscores
- Values can contain spaces if quoted: `var message "Hello World"`
- Variables are dereferenced automatically before command execution
- Variables persist throughout the script's lifetime
- Variables are implicitly stored as string values

**Example:**
```text
var greeting "Hello, World!"
var count 42
echo $greeting
echo Count: $count
```

## Adding Commands

Commands are registered through the `REGISTER_COMMAND(...)` macro in files under `src/commands/`.

Commands are required to:
- split their own arguments (see `utils` for common helpers)
- error check their own args (use `ERROR(...)` and `LINE`)

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

User-facing command macros are defined in `src/commands/command`.
Macro implementation details live in `src/commands/command_impl.h`.

### `REGISTER_COMMAND(code)`

Primary macro for command authors.

Use this in a command source file under `src/commands/` to register one command callback.

- Input: a C++ code block that can use `args` (`const std::string&`)
- Behavior: creates a static registration object at startup
- Command name: inferred from the file basename via `FILE_BASENAME`

Use this macro for normal command implementation work.

### `COMMAND`

Expands to the current command name inferred from the source file basename.

Useful in diagnostics and logging.

### `LINE`

Expands to the current script line number at execution time.

Use this in command error messages.

### `INSTRUCTION`

Expands to the current instruction index in the active program.

This is intended for control-flow commands that need execution position.

### `PUSH_STACK`

Pushes the current instruction index onto the call stack.

Use this when implementing command-driven call/return behavior.

### `POP_STACK`

Pops the most recent instruction index from the call stack and restores it as the current instruction.

Returns `false` if the stack is empty.

### `SET_VARIABLE(name, value)`

Sets or overwrites a variable.

### `GET_VARIABLE(name)`

Returns the value of a variable.

This throws if the variable does not exist.

### `HAS_VARIABLE(name)`

Returns whether a variable exists.

### `REMOVE_VARIABLE(name)`

Removes a variable and returns whether one was removed.

### `ERROR(msg)`

Writes a standardized command error message including the command name and current line number.

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
- `compile_commands.json` is generated by the Linux presets for `clangd` support.
- The presets use `ccache` when it is installed.

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
