#pragma once

#include "nfpch.h"

namespace Nifty
{
	extern bool ContainsCharacter(const std::string& str, const char& chr)
	{
		for (unsigned int i = 0; i < str.length(); ++i)
			if (str[i] == chr) return true;
		return false;
	}

	extern void RemoveCharacter(std::string& str, const char& chr)
	{
		std::string clean_str;
		for (unsigned int i = 0; i < str.length(); ++i)
		{
			if (str[i] != chr) clean_str += str[i];
		}
		str = std::string(clean_str);
	}
}