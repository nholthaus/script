#include <command>
#include <findMatch.h>

/*
NAME
    for - execute a counted loop

SYNOPSIS
    for <loop_var> <start> <end> <unary_func>

DESCRIPTION
    Iterates from <start> toward the exclusive <end> bound using unary_func,
    which must currently be inc or dec. The current value is stored in
    <loop_var> for the body of the loop.
*/
REGISTER_COMMAND
{
	auto splitArgs = utils::split(args);

	// The built-in loop only understands operators with predictable direction.
	enum class Direction
	{
		Increment,
		Decrement,
	};

	// The first visit initializes loop state. After `end_for` jumps back here,
	// the saved metadata tells us to advance or finish the existing loop instead.
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

		// Return to the instruction immediately after the matching `end_for`.
		const auto index = utils::findMatch("end_for");
		PUSH_STACK(index + 1);

		// `end_for` uses this to jump back here, and the next visit uses it to
		// decide how to update the loop variable.
		SET_METADATA("LOOP_START_INDEX", std::to_string(INSTRUCTION));
		SET_METADATA("LOOP_END_INDEX", std::to_string(index));
		SET_METADATA("LOOP_START_VALUE", splitArgs[1]);
		SET_METADATA("LOOP_END_VALUE", splitArgs[2]);
		SET_METADATA("LOOP_UNARY_FUNC", splitArgs[3]);

		SET_VARIABLE(splitArgs[0], std::to_string(start));

		// The end value is exclusive, so some ranges execute zero times.
		if (direction == Direction::Increment ? start >= end : start <= end)
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

		// Advance once per completed body execution, then stop when the exclusive
		// bound is reached or crossed.
		if (unaryFunc == "inc" ? loopVar >= end : loopVar <= end)
			POP_STACK;
	}
};
