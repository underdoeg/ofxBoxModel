#ifndef PROPERTY_H
#define PROPERTY_H

#include "ofEvents.h"

namespace ofx
{

namespace boxModel
{

namespace core
{



/**********************************
 * 
 ****************************************/

class PropertyBase
{
public:
	class Event: public ofEventArgs
	{
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
class Property: public PropertyBase
{
public:
	class Event: public ofEventArgs
	{
	public:
		Event(Property<T>* p) {
			property = p;
		}
		Property<T>* property;
	};

	operator const T & () const {
		return value;
	}

	const T& operator=(T val) {
		set(val);
		return value;
	}

	void set(T v) {
		if(value == v)
			return;
		value = v;

		PropertyBase::triggerChangedEvent();
		Event e(this);
		ofNotifyEvent(changed, e);
	}

	ofEvent<Event> changed;

private:
	T value;
};

}

}

}

#endif // PROPERTY_H
