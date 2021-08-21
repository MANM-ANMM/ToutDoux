#pragma once

#include <string>
#include <string_view>

namespace util
{
	std::string trim(std::string_view str)
	{
		str.remove_prefix(std::min(str.find_first_not_of(" \t\n"), str.size()));

		return std::string(str);
	}
}
