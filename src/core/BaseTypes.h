#ifndef BASETYPES_H
#define BASETYPES_H

#include "nano_signal_slot.hpp"
#include "ofMain.h"

namespace boxModel {

namespace core {

typedef ofPoint Point;
typedef ofRectangle Rectangle;

template <class Type>
class Value{
	Nano::signal<void(Type)> changed;
	Nano::signal<void(Type, Type)> changed2;

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
		Type oldValue = value;
		value = val;
		changed(value);
		changed2(value, oldValue);
	}
private:
	Type value;
};

}

}

#endif // BASETYPES_H
