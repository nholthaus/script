#include "commandCallback.h"
#include "command.h"

#include <map>

struct ScriptInstance
{
public:

	friend class Script;
	using Callback = std::function<void(const std::string&)>;

	static ScriptInstance& getInstance()
	{
		static ScriptInstance m_instance;
		return m_instance;
	}
	static void registerCommand(CommandCallback&& cc)
	{
		getInstance().m_callbacks.emplace(std::make_pair(std::move(cc.name), std::move(cc.callback)));
	}

private:

	ScriptInstance() = default;
	ScriptInstance(const ScriptInstance&) = delete;
	void operator=(const ScriptInstance&) = delete;

	std::map<std::string, Callback> m_callbacks;
};