if (NOT DEFINED SCRIPT_EXECUTABLE)
	message(FATAL_ERROR "SCRIPT_EXECUTABLE is required")
endif()

if (NOT DEFINED SCRIPT_FILE)
	message(FATAL_ERROR "SCRIPT_FILE is required")
endif()

if (NOT DEFINED EXPECTED_FILE)
	message(FATAL_ERROR "EXPECTED_FILE is required")
endif()

execute_process(
	COMMAND "${CMAKE_COMMAND}" -E env "SCRIPT_DISABLE_WAIT=1" "${SCRIPT_EXECUTABLE}" "${SCRIPT_FILE}"
	RESULT_VARIABLE script_result
	OUTPUT_VARIABLE script_stdout
	ERROR_VARIABLE script_stderr
)

if (NOT script_result EQUAL 0)
	message(FATAL_ERROR
		"Script exited with ${script_result}\n"
		"stderr:\n${script_stderr}\n"
		"stdout:\n${script_stdout}")
endif()

file(READ "${EXPECTED_FILE}" expected_stdout)

string(REPLACE "\r\n" "\n" script_stdout "${script_stdout}")
string(REPLACE "\r\n" "\n" expected_stdout "${expected_stdout}")
string(REGEX REPLACE "\n$" "" script_stdout "${script_stdout}")
string(REGEX REPLACE "\n$" "" expected_stdout "${expected_stdout}")

if (NOT script_stdout STREQUAL expected_stdout)
	message(FATAL_ERROR
		"Output mismatch for ${SCRIPT_FILE}\n"
		"Expected:\n${expected_stdout}\n"
		"Actual:\n${script_stdout}\n")
endif()
