#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <map>

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
		std::string value;
	};
	
	typedef std::map<std::string, Value> KeyValueList;

	Serializable(){};
	~Serializable(){};
	
	KeyValueList getSerialized(){
		
	}
};

}

}

#endif // SERIALIZABLE_H
