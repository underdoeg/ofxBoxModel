#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Property.h"
#include "core/Unit.h"

namespace ofx
{

namespace boxModel
{

namespace core
{

/*****
 * Class to store the box model definitions. This is pretty much the base for anything...
 ****/

typedef ofVec2f Point;

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

class BoxModel
{
public:
	class Event: public ofEventArgs
	{
	public:
		Event(BoxModel* d) {
			boxModel = d;
		}
		BoxModel* boxModel;
	};

	class ReadOnlyFloat
	{
	public:
		ReadOnlyFloat() {
			value = 0;
		};
		~ReadOnlyFloat() {};
		operator const float & () const {
			return value;
		}
	private:
		const float& operator=(float val) {
			value = val;
			return value;
		}

		float value;
		friend class BoxModel;
	};

	class ReadOnlyPoint
	{
	public:
		ReadOnlyFloat x;
		ReadOnlyFloat y;
		operator const Point & () const {
			return Point(x, y);
		}
	};

	BoxModel();

	void unitChanged(Unit::Event& e) {
		Event de(this);
		ofNotifyEvent(changed, de);
	}

	void propertyChanged(PropertyBase::Event& e) {
		Event de(this);
		ofNotifyEvent(changed, de);
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
	Property<Position> positioning;
	Property<bool> clearing;

	ofEvent<Event> changed;

	UnitGroup padding;
	UnitGroup margin;
	UnitGroup border;

	ReadOnlyPoint position;
	ReadOnlyPoint outerSize;
	ReadOnlyPoint size;
	ReadOnlyPoint contentSize;
	ReadOnlyPoint contentPosition;

protected:
	void calculateSize(Point containerSize);

private:
	std::vector<PropertyBase*> properties;
};

}

}

}

#endif // BOXMODEL_H
