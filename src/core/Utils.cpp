#include "Utils.h"

#include <functional>
#include <algorithm>
#include <fstream>

#include <chrono>

namespace boxModel {

namespace core {

using namespace std;

std::string stringLoadFromFile(std::string filePath) {
	std::string ret;
	std::string line;
	std::ifstream file (filePath);
	if (file.is_open()) {
		while ( file.good() ) {
			getline (file,line);
			ret += line;
		}
		file.close();
	}
	else debug::error("Unable to open file: "+filePath);
	return ret;
}

std::string floatToString(float number) {
	std::ostringstream buff;
	buff<<number;
	return buff.str();
}

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string stringTrim(std::string s) {
	return ltrim(rtrim(s));
}

std::vector<std::string> stringSplit(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		std::string e = stringTrim(item);
		if(!e.empty())
			elems.push_back(item);
	}
	return elems;
}

vector <string> stringSplit(const string & source, const string & delimiter) {
	vector<string> result;
	if (delimiter.empty()) {
		result.push_back(source);
		return result;
	}
	std::string::const_iterator substart = source.begin(), subend;
	while (true) {
		subend = search(substart, source.end(), delimiter.begin(), delimiter.end());
		string sub(substart, subend);

		if (!sub.empty()) {
			result.push_back(sub);
		}
		if (subend == source.end()) {
			break;
		}
		substart = subend + delimiter.size();
	}
	return result;
}

std::string stringReplace(std::string s, std::string toReplace, std::string replaceWith) {
	size_t pos = 0;
	while ((pos = s.find(toReplace, pos)) != std::string::npos) {
		s.replace(pos, toReplace.length(), replaceWith);
		pos += replaceWith.length();
	}
	return s;
}

std::string stringRemoveLineBreaks(std::string s) {
	std::string str = s;
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
}

std::string stringToLower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string stringToUpper(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

float stringToFloat(std::string s) {
	return ::atof(s.c_str());
}

bool stringContains(std::string s, std::string find) {
	return s.find(find) != std::string::npos;
}

int stringToInt(std::string s) {
	return atoi(s.c_str());
}

std::string intToHexString(int i) {
	if(i == 0)
		return "00";
	std::stringstream str;
	return str.str();
}

///to string

std::string toString(std::vector<std::string> vec)
{
	std::string ret;
	for(std::string str:vec){
		ret += str;
		ret += ", ";
	}
	if(ret.size() > 2)
		ret = ret.substr(0, ret.size()-2);
	return ret;
}

std::string toString(std::vector<int> vec)
{
	std::string ret;
	for(int i:vec){
		ret += toString(i);
		ret += ", ";
	}
	if(ret.size() > 2)
		ret = ret.substr(0, ret.size()-2);
	return ret;
}

std::string toString(int i){
	std::ostringstream convert;
	convert << i;
	return convert.str();
}
/*
std::string toString(bool b){
	if(b)
		return "true";
	return "false";
}
*/

//////////////////////////////////////////////////////////////////

bool rectContains(float x, float y, float rx, float ry, float rw, float rh)
{
	if(x < rx)
		return false;
	if(y < ry)
		return false;
	if(x > rx + rw)
		return false;
	if(y > ry + rh)
		return false;
	return true;
}

/****************************************************************************/
unsigned long long getSystemTime( ) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

//end namespace
}

}
