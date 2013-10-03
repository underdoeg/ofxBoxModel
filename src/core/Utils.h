#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <sstream>
#include "assert.h"
#include <typeinfo>
#include "debug/Print.h"

namespace boxModel {

namespace core {


/** is base of implementation **/
template <typename B, typename D>
struct isBaseOf { // check if B is a base of D
	typedef char yes[1];
	typedef char no[2];

	static yes& test(B*);
	static no& test(...);

	static D* get(void);

	static const bool value = sizeof(test(get())) == sizeof(yes);
};

template <typename Type, typename Base>
bool instanceIsBaseOf(Type* type){
	return dynamic_cast<Base*>(type) != NULL;
}

template <typename From, typename To>
To* castTo(From* from, bool typecheck = true){
	if(!typecheck)
		return static_cast<To*>(from);
	
	To* to = NULL;
	if(isBaseOf<From, To>::value){
		to = static_cast<To*>(from);
	}else{
		assert(false && "Invalid casting");
	}
	return to;
}


/****************************************************************************/
/* STRING STUFF																*/
/****************************************************************************/
std::string stringLoadFromFile(std::string filePath);
std::string floatToString(float number);
std::string stringTrim(std::string s);
std::vector<std::string> stringSplit(const std::string &in, char delimiter = ' ');
std::vector<std::string> stringSplit(const std::string & source, const std::string & delimiter);
std::string stringReplace(std::string s, std::string toReplace, std::string replaceWith);
std::string stringRemoveLineBreaks(std::string);
std::string stringToLower(std::string s);
std::string stringToUpper(std::string s);
float stringToFloat(std::string s);
int stringToInt(std::string s);
bool stringContains(std::string s, std::string find);
std::string intToHexString(int i);

//to stirng functions
std::string toString(std::vector<std::string> vec);
std::string toString(std::vector<int> vec);
std::string toString(int i);

//std::string toString(Point p);
//std::string toString(bool b);
/****************************************************************************/
/* MATH STUFF																*/
/****************************************************************************/
bool rectContains(float x, float y, float rx, float ry, float rw, float rh);

/****************************************************************************/
/* OTHER STUFF																*/
/****************************************************************************/
unsigned long long getSystemTime( );

}

}

#endif // UTILS_H