#ifndef UNIT_H
#define UNIT_H

#include "ofMain.h"


namespace boxModel {

namespace core {

class Unit {
public:

	enum Type {
	    Auto,
	    Pixel,
	    Percent
	};

	Nano::signal<void(Unit*)> changed;
	Nano::signal<void(float)> valueChanged;
	Nano::signal<void(Type)> typeChanged;

	Unit():bSet(false),value(0),type(Pixel) {
	}

	void set(float value, Type type) {
		set(value);
		set(type);
	}

	operator const float & () const {
		return value;
	}

	const float& operator=(float val) {
		set(val);
		return value;
	}

	const Type& operator=(Type t) {
		set(t);
		return type;
	}

	const Unit operator=(Unit t) {
		set(t);
		return t;
	}

	void set(float val) {

		if(bSet && val == value)
			return;
		bSet = true;
		value = val;
		dispatchChanged();
		valueChanged(value);
	}

	void set(Type t) {
		if(bSet && type == t)
			return;
		bSet = true;
		type = t;
		dispatchChanged();
		typeChanged(type);
	}

	void set(Unit u) {
		set(u.getType());
		set(u.getValue());
	}

	const float getValue() {
		return value;
	}

	Type getType() {
		return type;
	}

	bool isSet() {
		return bSet;
	}

	float getValueCalculated() {
		return getValueCalculated(containerSize);
	}
	
	void setContainerSize(float s) {
		containerSize = s;
	}


private:
	void dispatchChanged() {
		changed(this);
	}

	float getValueCalculated(float parentSize) { //helper function, only for internal use
		if(type == Percent) {
			return value*.01*parentSize;
		} else if(type == Auto)
			return 0;
		return value;
	}

	bool bSet;
	float value;
	Type type;

	float containerSize;

	friend class BoxModel;
};

class UnitGroup {
public:
	UnitGroup() {
		add(&top);
		add(&bottom);
		add(&left);
		add(&right);
	}

	~UnitGroup() {

	}

	void add(Unit* u) {
		u->changed.connect<UnitGroup, &UnitGroup::onUnitChanged>(this);
		units.push_back(u);
	}

	void set(float value, Unit::Type type) {
		set(value);
		set(type);
	}

	const float operator=(float val) {
		set(val);
		return val;
	}

	const Unit::Type operator=(Unit::Type t) {
		set(t);
		return t;
	}

	const Unit operator=(Unit u) {
		set(u);
		return u;
	}

	void set(float value) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(value);
		}
	}

	void set(Unit value) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(value);
		}
	}

	void set(Unit::Type type) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++) {
			(*it)->set(type);
		}
	}
	
	Nano::signal<void(UnitGroup*)> changed;
	Nano::signal<void(Unit*)> unitChanged;
	
	core::Unit top;
	core::Unit right;
	core::Unit bottom;
	core::Unit left;

private:
	void onUnitChanged(Unit* u) {
		changed(this);
		unitChanged(u);
	}
	std::vector<Unit*> units;
};

}

}

#endif // UNIT_H
