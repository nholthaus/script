#pragma once

#include <charconv>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <vector>

struct StringValue
{
	explicit StringValue(std::string value)
	  : m_value(std::move(value))
	{
	}

	operator const std::string&() const
	{
		return m_value;
	}

	operator std::string_view() const
	{
		return m_value;
	}

	const std::string& str() const
	{
		return m_value;
	}

	std::string_view view() const
	{
		return m_value;
	}

	int asInt() const
	{
		return parseIntegral<int>();
	}

	long asLong() const
	{
		return parseIntegral<long>();
	}

	long long asLongLong() const
	{
		return parseIntegral<long long>();
	}

	unsigned asUnsigned() const
	{
		return parseIntegral<unsigned>();
	}

	size_t asSizeT() const
	{
		return parseIntegral<size_t>();
	}

	float asFloat() const
	{
		return std::stof(m_value);
	}

	double asDouble() const
	{
		return std::stod(m_value);
	}

	bool asBool() const
	{
		if (m_value == "true" || m_value == "1")
			return true;
		if (m_value == "false" || m_value == "0")
			return false;

		throw std::invalid_argument("String value is not a bool: " + m_value);
	}

private:
	template <typename T>
	T parseIntegral() const
	{
		T parsed{};
		const auto* begin = m_value.data();
		const auto* end = begin + m_value.size();
		if (const auto [ptr, ec] = std::from_chars(begin, end, parsed); ec != std::errc{} || ptr != end)
			throw std::invalid_argument("String value is not an integer: " + m_value);

		return parsed;
	}

	std::string m_value;
};

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

	bool empty() const
	{
		return m_values.empty();
	}

	Map::iterator find(const std::string& key)
	{
		return m_values.find(key);
	}

	Map::const_iterator find(const std::string& key) const
	{
		return m_values.find(key);
	}

	std::string& insert_or_assign(const std::string& key, const std::string& value)
	{
		return m_values.insert_or_assign(key, value).first->second;
	}

	void clear()
	{
		m_values.clear();
	}

	bool remove(const std::string& key)
	{
		return m_values.erase(key) > 0;
	}

	size_t size() const
	{
		return m_values.size();
	}

	std::string_view view(const std::string& key) const
	{
		return (*this)[key];
	}

	StringValue get(const std::string& key) const
	{
		return StringValue((*this)[key]);
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

	Map::iterator end()
	{
		return m_values.end();
	}

	Map::const_iterator end() const
	{
		return m_values.end();
	}

	Map::iterator begin()
	{
		return m_values.begin();
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
