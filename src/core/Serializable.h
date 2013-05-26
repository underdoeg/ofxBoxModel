#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <map>
#include "BoxModel.h"

namespace boxModel
{

namespace core
{

template<class BoxModelType>
class Serializable
{
public:
	class Value{
		Value(std::string v){
			value = v;
		}
		
		int asInt(){
			return stringToInt(value.c_str());
		}
		
		float asFloat(){
			return stringToFloat(value.c_str());
		}
		
		Point asPoint(){
			Point ret;
			std::vector<std::string> parts = stringSplit(value, " ");
			if(parts.size()>0)
				ret.x = stringToFloat(parts[0]);
			if(parts.size()>1)
				ret.y = stringToFloat(parts[1]);
			return ret;
		}
		
		std::string value;
	};
	
	typedef std::map<std::string, Value> ValuleMap;

	Serializable(){};
	~Serializable(){};
	
	ValuleMap getSerialized(){
		
	}
};

}

}

#endif // SERIALIZABLE_H
