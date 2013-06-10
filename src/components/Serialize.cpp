#include "Serialize.h"

namespace boxModel
{

namespace components
{

Serialize::Serialize()
{
}

Serialize::~Serialize()
{
}

void Serialize::setup()
{
}

void Serialize::deserialize(core::VariantList values)
{
	deserialized(values);
}

core::VariantList Serialize::serialize()
{
	core::VariantList values;
	serialized(values);
	return values;class Variant {
public:
	Variant() {
		setValue("");
	}

	Variant(std::string v) {
		setValue(v);
	}

	Variant(float v) {
		setValue(core::floatToString(v));
	}

	Variant(core::Point p) {
		setValue(core::floatToString(p.x)+" "+core::floatToString(p.y));
	}

	operator const string & () {
		return value;
	}

	void setValue(std::string v) {
		value = v;
	}

	int asInt() {
		return core::stringToInt(value);
	}

	float asFloat() {
		return core::stringToFloat(value);
	}

	core::Point asPoint() {
		core::Point ret;
		std::vector<std::string> parts = core::stringSplit(value, " ");
		if(parts.size()>0)
			ret.x = core::stringToFloat(parts[0]);
		if(parts.size()>1)
			ret.y = core::stringToFloat(parts[1]);
		return ret;
	}

	std::string value;
};

typedef std::unordered_map<std::string, Variant> VariantMap;

class VariantList {
public:
	void set(std::string key, std::string value) {
		map[key].setValue(value);
	}

	void set(std::string key, Variant value) {
		map[key] = value;
	}

	Variant get(std::string key) {
		if(map.count(key) == 1)
			return map[key];
		else
			return Variant();
	}

	bool hasKey(std::string key) {
		return map.count(key) == 1;
	}

	VariantMap map;
};
}

}

}


