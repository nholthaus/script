#include <command>
#include <thread>

REGISTER_COMMAND
(
	std::this_thread::sleep_for(std::chrono::seconds(std::stoi(args)));
)