#ifndef UNIT_H
#define UNIT_H

namespace ofx {

namespace boxModel {

namespace core {

typedef ofVec2f Point;

class BoxBase;

/****************************
 *
 ***************************/

class Unit {
public:
	class Event: public ofEventArgs {
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

	operator const float & () const {
		return value;
	}

	const float& operator=(float val) {
		setValue(val);
		return value;
	}

	const Type& operator=(Type t) {
		setType(t);
		return type;
	}

	void setValue(float val) {

		if(bSet && val == value)
			return;
		bSet = true;
		value = val;
		Event e(this);
		ofNotifyEvent(changed, e);
	}

	void setType(Type t) {
		if(type == t)
			return;
		type = t;
		Event e(this);
		ofNotifyEvent(changed, e);
	}

	float getValue() {
		return value;
	}

	Type getType() {
		return type;
	}

	bool isSet() {
		return bSet;
	}

	ofEvent<Event> changed;

private:
	friend class BoxBase;
	float getValueCalculated(float parentSize) { //helper function, only for internal use
		if(type == Percent)
			return value*.01*parentSize;
		return value;
	}

	bool bSet;
	float value;
	Type type;
};

/****************************
 *
 ***************************/

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

/****************************
 *
 ***************************/

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

	operator const T & () const {
		return value;
	}

	const T& operator=(T val) {
		setValue(val);
		return value;
	}

	void setValue(T v) {
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

/****************************
 *
 ***************************/

class Properties {
public:
	class Event: public ofEventArgs {
	public:
		Event(Properties* d) {
			definition = d;
		}
		Properties* definition;
	};

	enum Position {
	    Relative,
	    Absolute,
	    Fixed
	};

	enum Floating {
	    Left,
	    Right,
	    NoFloat
	};

	Properties() {
		units.push_back(&left);
		units.push_back(&top);
		units.push_back(&width);
		units.push_back(&height);

		paddings.push_back(&paddingLeft);
		paddings.push_back(&paddingRight);
		paddings.push_back(&paddingTop);
		paddings.push_back(&paddingBottom);
		units.insert( units.end(), paddings.begin(), paddings.end() );

		margins.push_back(&marginLeft);
		margins.push_back(&marginRight);
		margins.push_back(&marginTop);
		margins.push_back(&marginBottom);
		units.insert( units.end(), margins.begin(), margins.end() );

		borders.push_back(&borderLeft);
		borders.push_back(&borderRight);
		borders.push_back(&borderTop);
		borders.push_back(&borderBottom);
		units.insert( units.end(), borders.begin(), borders.end() );

		coords.push_back(&left);
		coords.push_back(&right);
		coords.push_back(&top);
		coords.push_back(&bottom);
		units.insert( units.end(), coords.begin(), coords.end() );

		position = Relative;
		floating = NoFloat;
		clear = false;

		properties.push_back(&position);
		properties.push_back(&floating);

		for(std::vector<Unit*>::iterator it = units.begin(); it!=units.end(); it++) {
			ofAddListener((*it)->changed, this, &Properties::unitChanged);
		}

		for(std::vector<PropertyBase*>::iterator it = properties.begin(); it!=properties.end(); it++) {
			ofAddListener((*it)->changed, this, &Properties::propertyChanged);
		}
	}

	void unitChanged(Unit::Event& e) {
		Event de(this);
		ofNotifyEvent(changed, de);
	}

	void propertyChanged(PropertyBase::Event& e) {
		Event de(this);
		ofNotifyEvent(changed, de);
	}

	void setMargin(float value, Unit::Type type = Unit::Pixel) {
		for(std::vector<Unit*>::iterator it = margins.begin(); it!=margins.end(); it++) {
			(*it)->setValue(value);
			(*it)->setType(type);
		}
	}

	void setPadding(float value, Unit::Type type = Unit::Pixel) {
		for(std::vector<Unit*>::iterator it = paddings.begin(); it!=paddings.end(); it++) {
			(*it)->setValue(value);
			(*it)->setType(type);
		}
	}

	void setBorder(float value, Unit::Type type = Unit::Pixel) {
		for(std::vector<Unit*>::iterator it = borders.begin(); it!=borders.end(); it++) {
			(*it)->setValue(value);
			(*it)->setType(type);
		}
	}

	Unit left;
	Unit top;
	Unit bottom;
	Unit right;

	Unit width;
	Unit height;

	Unit paddingLeft;
	Unit paddingRight;
	Unit paddingTop;
	Unit paddingBottom;

	Unit marginLeft;
	Unit marginRight;
	Unit marginTop;
	Unit marginBottom;

	Unit borderLeft;
	Unit borderRight;
	Unit borderTop;
	Unit borderBottom;

	Property<Floating> floating;
	Property<Position> position;
	Property<bool> clear;

	ofEvent<Event> changed;

private:
	std::vector<Unit*> units;
	std::vector<Unit*> paddings;
	std::vector<Unit*> margins;
	std::vector<Unit*> borders;
	std::vector<Unit*> coords;
	std::vector<PropertyBase*> properties;
};


}

}

}

#endif // UNIT_H
