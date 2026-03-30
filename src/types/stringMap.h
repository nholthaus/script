#pragma once

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <vector>

struct StringMap
{
	using Map = std::unordered_map<std::string, std::string>;

	const std::string& operator[](const std::string& key) const
	{
		return m_values.at(key);
	}

	std::string& operator[](const std::string& key)
	{
		return m_values[key];
	}

	bool contains(const std::string& key) const
	{
		return m_values.contains(key);
	}

	bool remove(const std::string& key)
	{
		return m_values.erase(key) > 0;
	}

	std::string_view view(const std::string& key) const
	{
		return (*this)[key];
	}

	int asInt(const std::string& key) const
	{
		return parseIntegral<int>(key);
	}

	long asLong(const std::string& key) const
	{
		return parseIntegral<long>(key);
	}

	long long asLongLong(const std::string& key) const
	{
		return parseIntegral<long long>(key);
	}

	unsigned asUnsigned(const std::string& key) const
	{
		return parseIntegral<unsigned>(key);
	}

	size_t asSizeT(const std::string& key) const
	{
		return parseIntegral<size_t>(key);
	}

	float asFloat(const std::string& key) const
	{
		return std::stof((*this)[key]);
	}

	double asDouble(const std::string& key) const
	{
		return std::stod((*this)[key]);
	}

	bool asBool(const std::string& key) const
	{
		const auto& value = (*this)[key];
		if (value == "true" || value == "1")
			return true;
		if (value == "false" || value == "0")
			return false;

		throw std::invalid_argument("StringMap value is not a bool: " + value);
	}

	std::vector<std::string> keys() const
	{
		std::vector<std::string> result;
		result.reserve(m_values.size());
		for (const auto& [key, value] : m_values)
			result.push_back(key);
		return result;
	}

	Map::const_iterator begin() const
	{
		return m_values.begin();
	}

	Map::const_iterator end() const
	{
		return m_values.end();
	}

private:
	template <typename T>
	T parseIntegral(const std::string& key) const
	{
		const auto& value = (*this)[key];
		T parsed{};
		const auto* begin = value.data();
		const auto* end = begin + value.size();
		if (const auto [ptr, ec] = std::from_chars(begin, end, parsed); ec != std::errc{} || ptr != end)
			throw std::invalid_argument("StringMap value is not an integer: " + value);

		return parsed;
	}

	Map m_values{};
};
