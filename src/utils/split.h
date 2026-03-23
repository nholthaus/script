#ifndef STRING_SPLITTER_H
#define STRING_SPLITTER_H

#include <sstream>
#include <string>
#include <vector>

namespace utils
{

	/**
	 * Split a string by a single delimiter character
	 */
	inline std::vector<std::string> split(const std::string& str, const char delimiter)
	{
		std::vector<std::string> tokens;
		std::string              token;
		std::istringstream       tokenStream(str);

		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}

		return tokens;
	}

	/**
	 * Split a string by a delimiter string
	 */
	inline std::vector<std::string> split(const std::string& str, const std::string& delimiter)
	{
		std::vector<std::string> tokens;
		size_t                   start = 0;
		size_t                   end   = str.find(delimiter);

		while (end != std::string::npos)
		{
			tokens.push_back(str.substr(start, end - start));
			start = end + delimiter.length();
			end   = str.find(delimiter, start);
		}

		tokens.push_back(str.substr(start));
		return tokens;
	}

	/**
	 * Split a string by delimiter with option to skip empty tokens
	 */
	inline std::vector<std::string> split(const std::string& str, const char delimiter, const bool skipEmpty)
	{
		std::vector<std::string> tokens;
		std::string              token;
		std::istringstream       tokenStream(str);

		while (std::getline(tokenStream, token, delimiter))
		{
			if (!skipEmpty || !token.empty())
			{
				tokens.push_back(token);
			}
		}

		return tokens;
	}

	/**
	 * Split a string by delimiter string with option to skip empty tokens
	 */
	inline std::vector<std::string> split(const std::string& str, const std::string& delimiter, const bool skipEmpty)
	{
		std::vector<std::string> tokens;
		size_t                   start = 0;
		size_t                   end   = str.find(delimiter);

		while (end != std::string::npos)
		{
			std::string token = str.substr(start, end - start);
			if (!skipEmpty || !token.empty())
			{
				tokens.push_back(token);
			}
			start = end + delimiter.length();
			end   = str.find(delimiter, start);
		}

		std::string lastToken = str.substr(start);
		if (!skipEmpty || !lastToken.empty())
		{
			tokens.push_back(lastToken);
		}

		return tokens;
	}

	/**
	 * Split a string by any whitespace characters
	 */
	inline std::vector<std::string> split(const std::string& str)
	{
		std::vector<std::string> tokens;
		std::istringstream       iss(str);
		std::string              token;

		while (iss >> token)
		{
			tokens.push_back(token);
		}

		return tokens;
	}

	/**
	 * Split a string by delimiter while respecting quotes
	 * Quoted sections (single or double quotes) are kept together as a single token
	 * Quotes are stripped from the tokens by default
	 *
	 * Examples:
	 *   splitQuoted("a b c", ' ') -> ["a", "b", "c"]
	 *   splitQuoted("a \"b c\" d", ' ') -> ["a", "b c", "d"]
	 *   splitQuoted("a 'b c' d", ' ') -> ["a", "b c", "d"]
	 *   splitQuoted("a \"b 'c' d\" e", ' ') -> ["a", "b 'c' d", "e"]
	 */
	inline std::vector<std::string> splitQuoted(const std::string& str, const char delimiter, const bool keepQuotes = false)
	{
		std::vector<std::string> tokens;
		std::string              current;
		bool                     inDoubleQuote = false;
		bool                     inSingleQuote = false;
		bool                     escaped       = false;

		for (size_t i = 0; i < str.length(); ++i)
		{
			const char c = str[i];

			if (escaped)
			{
				current += c;
				escaped = false;
				continue;
			}

			if (c == '\\')
			{
				if (keepQuotes)
					current += c;
				escaped = true;
				continue;
			}

			if (c == '"' && !inSingleQuote)
			{
				if (keepQuotes)
					current += c;
				inDoubleQuote = !inDoubleQuote;
				continue;
			}

			if (c == '\'' && !inDoubleQuote)
			{
				if (keepQuotes)
					current += c;
				inSingleQuote = !inSingleQuote;
				continue;
			}

			if (c == delimiter && !inDoubleQuote && !inSingleQuote)
			{
				if (!current.empty())
				{
					tokens.push_back(current);
					current.clear();
				}
				continue;
			}

			current += c;
		}

		// Add the last token if it's not empty
		if (!current.empty())
		{
			tokens.push_back(current);
		}

		return tokens;
	}

	/**
	 * Split a string by any whitespace while respecting quoted sections
	 * This is a convenience function that splits by space and handles multiple consecutive spaces
	 */
	inline std::vector<std::string> splitQuoted(const std::string& str, const bool keepQuotes = false)
	{
		std::vector<std::string> tokens;
		std::string              current;
		bool                     inDoubleQuote = false;
		bool                     inSingleQuote = false;
		bool                     escaped       = false;

		for (size_t i = 0; i < str.length(); ++i)
		{
			const char c = str[i];

			if (escaped)
			{
				current += c;
				escaped = false;
				continue;
			}

			if (c == '\\')
			{
				if (keepQuotes)
					current += c;
				escaped = true;
				continue;
			}

			if (c == '"' && !inSingleQuote)
			{
				if (keepQuotes)
					current += c;
				inDoubleQuote = !inDoubleQuote;
				continue;
			}

			if (c == '\'' && !inDoubleQuote)
			{
				if (keepQuotes)
					current += c;
				inSingleQuote = !inSingleQuote;
				continue;
			}

			if (std::isspace(c) && !inDoubleQuote && !inSingleQuote)
			{
				if (!current.empty())
				{
					tokens.push_back(current);
					current.clear();
				}
				continue;
			}

			current += c;
		}

		// Add the last token if it's not empty
		if (!current.empty())
		{
			tokens.push_back(current);
		}

		return tokens;
	}

} // namespace utils

#endif // STRING_SPLITTER_H
