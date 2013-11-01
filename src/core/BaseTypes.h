#ifndef BASETYPES_H
#define BASETYPES_H

#include "nano_signal_slot.hpp"
#include "ofMain.h"
#include "Utils.h"

namespace boxModel {

namespace core {

typedef ofPoint Point;
typedef ofRectangle Rectangle;
typedef ofColor Color;

class Variant {
public:
	Variant() {
		setValue("");
	}

	Variant(std::string v) {
		setValue(v);
	}

	Variant(float v) {
		setValue(floatToString(v));
	}

	Variant(core::Point p) {
		setValue(core::floatToString(p.x)+" "+core::floatToString(p.y));
	}

	Variant(std::vector<std::string> stringArray) {
		setValue(std::accumulate( stringArray.begin(), stringArray.end(), std::string(" ") ));
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

	std::string asString() {
		return value;
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

	std::vector<std::string> asStringList(){
		return stringSplit(value, ' ');
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

template <class Type>
class Value {
public:
	Nano::signal<void(Type)> changed;
	//Nano::signal<void(Type, Type)> changed2;

	operator const Type() const {
		return value;
	}

	const Value<Type> operator=(Value<Type> val) {
		set(val.get());
		return *this;
	}

	const Type operator=(Type val) {
		set(val);
		return value;
	}

	Type operator+( const Type& in ) const {
		return value + in;
	}

	Type operator-( const Type& in ) const {
		return value - in;
	}

	Type get() {
		return value;
	}

	void set(Type val) {
		if(value == val)
			return;
		oldValue = value;
		value = val;
		changed(value);
		//changed2(value, oldValue);
	}
private:
	Type value;
	Type oldValue;
};

class ValuePoint {
public:
	ValuePoint() {
		x.changed.connect<ValuePoint, &ValuePoint::onXChanged>(this);
		y.changed.connect<ValuePoint, &ValuePoint::onYChanged>(this);
	}

	Nano::signal<void(Point)> changed;
	//Nano::signal<void(Point, Point)> changed2;

	operator const Point() const {
		const Point p(x, y);
		return p;
	}

	Point operator+( const Point& pnt ) const {
		return Point(x+pnt.x, y+pnt.y);
	}

	Point operator-( const Point& pnt ) const {
		return Point(x-pnt.x, y-pnt.y);
	}

	void set(float nx, float ny){
		x = nx;
		y = ny;
	}

	void setX(float nx){
		x = nx;
	}

	void setY(float ny){
		y = ny;
	}

	void set(Point p){
		x = p.x;
		y = p.y;
	}

	Value<float> x;
	Value<float> y;
private:
	void onXChanged(float v) {
		dispatchEvent();
	}

	void onYChanged(float v) {
		dispatchEvent();
	}

	void dispatchEvent() {
		changed(*this);
	}

	//Point oldVal;
};

}

}

#endif // BASETYPES_H
