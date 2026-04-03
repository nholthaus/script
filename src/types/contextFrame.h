#ifndef SCRIPT_CONTEXTFRAME_H
#define SCRIPT_CONTEXTFRAME_H

#include <source.h>
#include <stringMap.h>

/**
 * @class ContextFrame
 *
 * @brief Represents a frame of context which contains a return index, local variables, and metadata.
 *
 * This class maintains information about a specific context frame in an execution or processing environment.
 * It holds a return index to track control flow and provides containers for local variables and metadata
 * that can be accessed or modified as needed.
 */
class ContextFrame
{
public:

	enum Policy
	{
		INHERIT, ///< Can see variables from the parent scope
		ISOLATE, ///< Cannot see variables from the parent scope
	};
	explicit ContextFrame(Source source, size_t returnIndex, Policy policy = INHERIT);

	[[nodiscard]] const Source&    source() const noexcept;
	[[nodiscard]] Policy           policy() const noexcept;
	[[nodiscard]] size_t           returnIndex() const noexcept;
	[[nodiscard]] StringMap&       localVariables() noexcept;
	[[nodiscard]] const StringMap& localVariables() const noexcept;
	[[nodiscard]] StringMap&       metadata() noexcept;
	[[nodiscard]] const StringMap& metadata() const noexcept;

private:

	Policy    m_policy      = INHERIT;
	size_t    m_returnIndex = 0;
	Source    m_source;
	StringMap m_localVariables;
	StringMap m_metadata;
};

//======================================================================================================================
//	METHOD IMPLEMENTATIONS
//======================================================================================================================

inline ContextFrame::ContextFrame(Source source, size_t returnIndex, Policy policy)
  : m_policy(policy)
  , m_returnIndex(returnIndex)
  , m_source(std::move(source))
{
}

inline ContextFrame::Policy ContextFrame::policy() const noexcept
{
	return m_policy;
}

inline size_t ContextFrame::returnIndex() const noexcept
{
	return m_returnIndex;
}

inline StringMap& ContextFrame::localVariables() noexcept
{
	return m_localVariables;
}

inline const StringMap& ContextFrame::localVariables() const noexcept
{
	return m_localVariables;
}

inline StringMap& ContextFrame::metadata() noexcept
{
	return m_metadata;
}

inline const StringMap& ContextFrame::metadata() const noexcept
{
	return m_metadata;
}

#endif // SCRIPT_CONTEXTFRAME_H
