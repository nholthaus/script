#pragma once

#include <filesystem>
#include <ostream>
#include <string>
#include <utility>

/// Small class that represents a file/line pair
struct Source
{
	Source() = default;

	Source(std::filesystem::path path, const size_t lineNumber = 0)
		: m_path(std::move(path)), m_lineNumber(lineNumber)
	{
	}

	[[nodiscard]] const std::filesystem::path& path() const
	{
		return m_path;
	}

	[[nodiscard]] size_t lineNumber() const
	{
		return m_lineNumber;
	}

	void setPath(std::filesystem::path path)
	{
		m_path = std::move(path);
	}

	void setLineNumber(size_t lineNumber)
	{
		m_lineNumber = lineNumber;
	}

	std::filesystem::path absolutePath() const
	{
		if (m_path.is_absolute())
			return m_path;

		return std::filesystem::absolute(m_path);
	}

	std::filesystem::path absolutePath(const std::filesystem::path& relativePath) const
	{
		if (relativePath.is_absolute())
			return relativePath;

		if (m_path.empty())
			return std::filesystem::absolute(relativePath);

		const auto sourcePath = absolutePath();
		const auto basePath = sourcePath.has_filename() ? sourcePath.parent_path() : sourcePath;
		return std::filesystem::absolute(basePath / relativePath);
	}

	std::string string() const
	{
		if (m_lineNumber == 0)
			return m_path.string();

		return m_path.string() + ":" + std::to_string(m_lineNumber);
	}

	operator std::string() const
	{
		return string();
	}

private:
	std::filesystem::path m_path{};
	size_t m_lineNumber = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Source& source)
{
	return os << source.string();
}
