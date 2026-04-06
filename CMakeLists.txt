#-------------------------------------------------------------------------------
#	CMAKE SETTINGS
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)

#-------------------------------------------------------------------------------
#	COMMAND SOURCE CODE
#-------------------------------------------------------------------------------

# Glob command files and configure CMake to reconfigure when files are added/removed
file(GLOB COMMAND_SOURCE_FILES CONFIGURE_DEPENDS
	"src/commands/*.cpp"
	"src/commands/command"
)

#-------------------------------------------------------------------------------
#	TYPES SOURCE CODE
#-------------------------------------------------------------------------------

# Glob utils files and configure CMake to reconfigure when files are added/removed
file(GLOB TYPES_HEADER_FILES CONFIGURE_DEPENDS
		"src/types/*.h"
)

file(GLOB TYPES_SOURCE_FILES CONFIGURE_DEPENDS
		"src/types/*.cpp"
)

#-------------------------------------------------------------------------------
#	UTILS SOURCE CODE
#-------------------------------------------------------------------------------

# Glob utils files and configure CMake to reconfigure when files are added/removed
file(GLOB UTILS_HEADER_FILES CONFIGURE_DEPENDS
	"src/utils/*.h"
)

file(GLOB UTILS_SOURCE_FILES CONFIGURE_DEPENDS
	"src/utils/*.cpp"
)

#-------------------------------------------------------------------------------
#	SCRIPT SOURCE CODE
#-------------------------------------------------------------------------------

# Glob main source files and configure CMake to reconfigure when files are added/removed
file(GLOB HEADER_FILES CONFIGURE_DEPENDS
	"src/*.h"
)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS
	"src/*.cpp"
)

# on windows, append headers to source so they show up in visual studio
if(WIN32)
	LIST(APPEND SOURCE_FILES
			${HEADER_FILES}
			${TYPES_HEADER_FILES}
			${UTILS_HEADER_FILES})
endif()

# Set the project name
PROJECT(script)

#-------------------------------------------------------------------------------
#	COMPILE FLAGS
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

if(MSVC)
	add_compile_options(/MP)
elseif(CMAKE_COMPILER_IS_GNUCXX)
	add_compile_options(-std=c++23)
endif(MSVC)

#-------------------------------------------------------------------------------
#	HELPERS
#-------------------------------------------------------------------------------

# Helper function to add preprocessor definition of FILE_BASENAME
# to pass the filename without directory path for debugging use.
#
# Example:
#
#   define_file_basename_for_sources(my_target)
#
# Will add -DFILE_BASENAME="filename" for each source file depended on
# by my_target, where filename is the name of the file.
#
function(define_file_basename_for_sources targetname)
    get_target_property(source_files "${targetname}" SOURCES)
    foreach(sourcefile ${source_files})
        # Get source file's current list of compile definitions.
        get_property(defs SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS)
        # Add the FILE_BASENAME=filename compile definition to the list.
        get_filename_component(basename "${sourcefile}" NAME_WE)
        list(APPEND defs "FILE_BASENAME=${basename}")
        # Set the updated compile definitions on the source file.
        set_property(
            SOURCE "${sourcefile}"
            PROPERTY COMPILE_DEFINITIONS ${defs})
    endforeach()
endfunction()



#-------------------------------------------------------------------------------
#	GENERATE EXECUTABLE
#-------------------------------------------------------------------------------

# Set additional include directories
include_directories(
		${INCLUDE_DIRS}
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/src/commands
		${PROJECT_SOURCE_DIR}/src/utils
		${PROJECT_SOURCE_DIR}/src/types
)

# Generate the executable
add_executable(${PROJECT_NAME}
		${SOURCE_FILES}
		${COMMAND_SOURCE_FILES}
		${UTILS_SOURCE_FILES}
		${TYPES_SOURCE_FILES}
)

define_file_basename_for_sources(${PROJECT_NAME})

enable_testing()

function(add_script_output_test test_name script_file expected_file)
	add_test(
		NAME ${test_name}
		COMMAND ${CMAKE_COMMAND}
			-DSCRIPT_EXECUTABLE=$<TARGET_FILE:${PROJECT_NAME}>
			-DSCRIPT_FILE=${script_file}
			-DEXPECTED_FILE=${expected_file}
			-P ${PROJECT_SOURCE_DIR}/tests/RunScriptOutputTest.cmake
	)
endfunction()

file(GLOB TEST_SCRIPT_FILES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/tests/scripts/*.script"
)

foreach(test_script ${TEST_SCRIPT_FILES})
	get_filename_component(test_name "${test_script}" NAME_WE)
	set(expected_file "${PROJECT_SOURCE_DIR}/tests/expected/${test_name}.txt")

	if (NOT EXISTS "${expected_file}")
		message(FATAL_ERROR "Missing expected output for ${test_script}: ${expected_file}")
	endif()

	add_script_output_test("script_${test_name}" "${test_script}" "${expected_file}")
endforeach()

file(GLOB EXAMPLE_SCRIPT_FILES CONFIGURE_DEPENDS
	"${PROJECT_SOURCE_DIR}/examples/*.script"
)

foreach(example_script ${EXAMPLE_SCRIPT_FILES})
	get_filename_component(example_name "${example_script}" NAME_WE)
	set(example_expected_file "${PROJECT_SOURCE_DIR}/tests/expected/examples/${example_name}.txt")

	if (EXISTS "${example_expected_file}")
		add_script_output_test("example_${example_name}" "${example_script}" "${example_expected_file}")
	endif()
endforeach()
