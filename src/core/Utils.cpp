#include "Utils.h"

#include <functional> 
#include <algorithm> 

namespace ofx
{

namespace boxModel
{

namespace core
{

// trim from start
static inline std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string trimString(std::string &s)
{
	return ltrim(rtrim(s));
}

std::vector<std::string> splitString(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		if(item != "")
			elems.push_back(item);
	}
	return elems;
}


}

}

}
