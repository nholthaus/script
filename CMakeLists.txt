#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8.12)

#-------------------------------------------------------------------------------
#	COMMAND SOURCE CODE
#-------------------------------------------------------------------------------

# .h files
list(APPEND COMMAND_HEADER_FILES
src/commands/echo.h
src/commands/wait.h
)

# .cpp files
list(APPEND COMMAND_SOURCE_FILES
src/commands/echo.cpp
src/commands/wait.cpp
)

# on windows, append headers to source so they show up in visual studio
if(WIN32)
	LIST(APPEND COMMAND_SOURCE_FILES ${COMMAND_HEADER_FILES})
endif()

#-------------------------------------------------------------------------------
#	SOURCE CODE
#-------------------------------------------------------------------------------

# .h files
list(APPEND HEADER_FILES
src/command.h
src/commandCallback.h
src/parser.h
src/script.h
)

# .cpp files
list(APPEND SOURCE_FILES
src/main.cpp
src/parser.cpp
src/script.cpp
)

# on windows, append headers to source so they show up in visual studio
if(WIN32)
	LIST(APPEND SOURCE_FILES ${HEADER_FILES})
endif()

# Set the project name
PROJECT(script)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
	add_compile_options(/MP)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++17)
endif(MSVC)

#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------

# Set additional include directories
include_directories(${INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/src)

# Generate the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${COMMAND_SOURCE_FILES})