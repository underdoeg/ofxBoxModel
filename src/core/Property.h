#ifndef PROPERTY_H
#define PROPERTY_H

#include "ofEvents.h"

namespace boxModel {

namespace core {



/**********************************
 *
 ****************************************/

class PropertyBase {
public:
	class Event: public ofEventArgs {
	public:
		Event(PropertyBase* p) {
			property = p;
		}
		PropertyBase* property;
	};

	ofEvent<Event> changed;
protected:
	void triggerChangedEvent() {
		Event e(this);
		ofNotifyEvent(changed, e);
	}
};


template <class T>
class Property: public PropertyBase {
public:
	class Event: public ofEventArgs {
	public:
		Event(Property<T>* p) {
			property = p;
		}
		Property<T>* property;
	};
	
	Property():bSet(false){
		
	}

	operator const T & () const {
		return value;
	}

	const T& operator=(T val) {
		set(val);
		return value;
	}

	void set(T v) {
		if(bSet && value == v)
			return;
		value = v;
		bSet = true;
		PropertyBase::triggerChangedEvent();
		Event e(this);
		ofNotifyEvent(changed, e);
	}
	
	bool isSet(){
		return bSet;
	}

	ofEvent<Event> changed;

private:
	bool bSet;
	T value;
};

}

}

#endif // PROPERTY_H
