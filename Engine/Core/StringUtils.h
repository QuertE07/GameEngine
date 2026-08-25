#pragma once

#include <string>
#include <iostream>

namespace gl
{
	inline std::string ToLower(const std::string& str)
	{
		std::string lower = str;

		for (char chr : lower)
		{
			chr = std::tolower(chr);
		}

		return lower;
	}
	
	inline std::string ToUpper(const std::string& str)
	{
		std::string upper = str;

		for (char chr : upper)
		{
			chr = std::toupper(chr);
		}

		return upper;
	}

	inline bool EqualsIgnoreCase(const std::string& str1, const std::string& str2)
	{
		if (str1.size() != str2.size()) return false;
		return ToLower(str1) == ToLower(str2);
	}
}