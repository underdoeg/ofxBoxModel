#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <vector>

namespace boxModel
{

namespace core
{

template<class BoxModelType>
class Serializable
{
public:
	class KeyValue{
		KeyValue(std::string k, std::string v){
			key = k;
			value = v;
		}
		std::string key;
		std::string value;
	};
	
	typedef std::vector<KeyValue> KeyValueList;

	Serializable(){};
	~Serializable(){};
	
	KeyValueList getSerialized(){
		
	}
};

}

}

#endif // SERIALIZABLE_H
