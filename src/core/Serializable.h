#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>
#include <map>
#include "BoxModel.h"
#include "Utils.h"

namespace boxModel {

namespace core {

class Serializable {
public:

	class Value {
	public:
		Value(){
			setValue("");
		}
		
		Value(std::string v) {
			setValue(v);
		}

		Value(float v) {
			setValue(floatToString(v));
		}

		Value(Point p) {
			setValue(floatToString(p.x)+" "+floatToString(p.y));
		}

		void setValue(std::string v) {
			value = v;
		}

		int asInt() {
			return stringToInt(value);
		}

		float asFloat() {
			return stringToFloat(value);
		}

		Point asPoint() {
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
	
	typedef std::map<std::string, Value> ValueMap;

	class ValueList{
		public:
		void set(std::string key, std::string value){
			map[key].setValue(value);
		}

		void set(std::string key, Value value){
			map[key] = value;
		}	
		
		Value get(std::string key){
			return map[key];
		}
		
		ValueMap map;
	};
	

	class Event {
	public:
		Event(Serializable* s, ValueList* vals) {
			sender = s;
			values = vals;
		}

		Serializable* sender;
		ValueList* values;
	};

	Serializable() {};
	~Serializable() {};

	ofEvent<Event> serialized;
	
	ValueList getSerialized() {
		ValueList v;
		Event e(this, &v);
		ofNotifyEvent(serialized, e);
		return v;
	}
};

}

}

#endif // SERIALIZABLE_H
