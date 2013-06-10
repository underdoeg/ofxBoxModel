#ifndef BASETYPES_H
#define BASETYPES_H

#include "nano_signal_slot.hpp"
#include "ofMain.h"

namespace boxModel {

namespace core {

typedef ofPoint Point;
typedef ofRectangle Rectangle;
typedef ofColor Color;

template <class Type>
class Value {
public:
	Nano::signal<void(Type)> changed;
	//Nano::signal<void(Type, Type)> changed2;

	operator const Type() const {
		return value;
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
