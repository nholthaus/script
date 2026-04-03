#include <command>
#include <findMatch.h>

REGISTER_COMMAND
{
	auto splitArgs = utils::split(args);

	enum class Direction
	{
		Increment,
		Decrement,
	};

	// loop initialization
	if (!HAS_METADATA("LOOP_START_INDEX") ||
		(HAS_METADATA("LOOP_START_INDEX") && GET_METADATA("LOOP_START_INDEX").asSizeT() != INSTRUCTION))
	{
		if (splitArgs.size() != 4)
		{
			ERROR("requires <loop_var> <start> <end> <unary_func> arguments");
		}

		// dereference args
		DEREFERENCE(splitArgs[1]);
		DEREFERENCE(splitArgs[2]);

		const auto direction = [&]() -> Direction
		{
			if (splitArgs[3] == "inc")
				return Direction::Increment;
			if (splitArgs[3] == "dec")
				return Direction::Decrement;
			throw std::invalid_argument("requires unary_func to be 'inc' or 'dec'");
		}();

		long long start = std::stoll(splitArgs[1]);
		long long end   = std::stoll(splitArgs[2]);

		// push a new stack frame scope
		const auto index = utils::findMatch("end_for");
		PUSH_STACK(index + 1);

		// set the required loop metadata/debug info
		SET_METADATA("LOOP_START_INDEX", std::to_string(INSTRUCTION));
		SET_METADATA("LOOP_END_INDEX", std::to_string(index));
		SET_METADATA("LOOP_START_VALUE", splitArgs[1]);
		SET_METADATA("LOOP_END_VALUE", splitArgs[2]);
		SET_METADATA("LOOP_UNARY_FUNC", splitArgs[3]);

		SET_VARIABLE(splitArgs[0], std::to_string(start));

		const bool shouldSkip = direction == Direction::Increment ? start >= end : start <= end;
		if (shouldSkip)
			POP_STACK;
	}
	else
	{
		DEREFERENCE(splitArgs[0]);
		auto loopVar = GET_VARIABLE(splitArgs[0]).asLongLong();
		const auto end = GET_METADATA("LOOP_END_VALUE").asLongLong();
		const auto unaryFunc = std::string(GET_METADATA("LOOP_UNARY_FUNC").str());

		if (unaryFunc == "inc")
			++loopVar;
		else if (unaryFunc == "dec")
			--loopVar;
		else
			throw std::invalid_argument("invalid loop unary_func metadata");

		SET_VARIABLE(splitArgs[0], std::to_string(loopVar));

		const bool shouldExit = unaryFunc == "inc" ? loopVar >= end : loopVar <= end;
		if (shouldExit)
			POP_STACK;
	}
};
