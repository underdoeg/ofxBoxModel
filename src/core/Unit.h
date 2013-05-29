#ifndef UNIT_H
#define UNIT_H

#include "ofMain.h"


namespace boxModel
{

namespace core
{

class BoxModel;

class Unit
{
public:
	class Event: public ofEventArgs
	{
	public:
		Event(Unit* u) {
			unit = u;
		}

		Unit* unit;
	};

	enum Type {
	    Auto,
	    Pixel,
	    Percent
	};

	Unit():bSet(false),value(0),type(Pixel) {
	}
	
	void set(float value, Type type){
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
		Event e(this);
		ofNotifyEvent(changed, e);
	}

	void set(Type t) {
		if(bSet && type == t)
			return;
		bSet = true;
		type = t;
		Event e(this);
		ofNotifyEvent(changed, e);
	}

	void set(Unit u) {
		if(bSet && value == u.value && type == u.type)
			return;
		bSet = true;
		type = u.type;
		value = u.value;
		Event e(this);
		ofNotifyEvent(changed, e);
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

	float getValueCalculated(){
		return getValueCalculated(containerSize);
	}
	/*
	std::ostream& operator<<(std::ostream& os){

	}
	 */
	 
	 void setContainerSize(float s){
		 containerSize = s;
	 }

	ofEvent<Event> changed;

private:
	float getValueCalculated(float parentSize) { //helper function, only for internal use
		if(type == Percent){
			return value*.01*parentSize;
		}else if(type == Auto)
			return 0;
		return value;
	}

	bool bSet;
	float value;
	Type type;

	float containerSize;
	
	friend class BoxModel;
};

class UnitGroup
{
public:
	UnitGroup() {

	}

	~UnitGroup() {

	}
	
	void add(Unit* u){
		ofAddListener(u->changed, this, &UnitGroup::unitChanged);
		units.push_back(u);
	}
	
	void set(float value, Unit::Type type){
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
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++){
			(*it)->set(value);
		}
	}

	void set(Unit value) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++){
			(*it)->set(value);
		}
	}

	void set(Unit::Type type) {
		for(typename std::vector<Unit*>::iterator it = units.begin(); it < units.end(); it++){
			(*it)->set(type);
		}
	}
	
	ofEvent<Unit::Event> changed;
	
private:
	void unitChanged(Unit::Event& e) {
		ofNotifyEvent(changed, e);
	}
	std::vector<Unit*> units;
};

}

}

#endif // UNIT_H
