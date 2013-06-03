#ifndef BASETYPES_H
#define BASETYPES_H

#include "nano_signal_slot.hpp"
#include "ofMain.h"

namespace boxModel {

namespace core {

typedef ofPoint Point;

template <class Type>
class EventValue {
	Nano::signal<void(Type)> changed;

	operator const Type() const {
		return value;
	}

	const Type operator=(Type val) {
		set(val);
		return value;
	}

	void set(Type val) {
		if(value == val)
			return;
		value = val;
		changed(value);
	}
private:
	Type value;
};

typedef EventValue<float> EventFloat;

class EventPoint {
public:
	Nano::signal<void(float, float)> changed;

	void set(float x, float y);

	EventFloat x;
	EventFloat y;
};

class Rectangle {
public:
	EventPoint position;
	EventPoint size;
};



}

}

#endif // BASETYPES_H
