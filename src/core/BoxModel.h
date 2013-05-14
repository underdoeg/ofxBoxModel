#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Property.h"
#include "core/Unit.h"

namespace ofx {

namespace boxModel {



namespace core {

class LayoutableBase;


/*****
 * Class to store the box model definitions. This is pretty much the base for anything...
 ****/

typedef ofVec3f Point;
typedef ofColor Color;

enum Position {
    Relative,
    Absolute,
    Fixed
};

enum Floating {
    FloatLeft,
    FloatRight,
    FloatNone
};



class BoxModel {
public:
	class Event: public ofEventArgs {
	public:
		Event(BoxModel* d) {
			boxModel = d;
		}
		BoxModel* boxModel;
	};

	class ReadOnlyFloat {
	public:
		class Event: public ofEventArgs {
		public:
			Event(float val, ReadOnlyFloat* s) {
				value = val;
				sender = s;
			}

			float value;
			ReadOnlyFloat* sender;
		};

		ReadOnlyFloat() {
			value = 0;
		};
		~ReadOnlyFloat() {};
		operator const float & () const {
			return value;
		}

		ofEvent<Event> changed;
	private:
		const float& operator=(float val) {
			value = val;
			Event e(val, this);
			ofNotifyEvent(changed, e);
			return value;
		}

		float value;
		friend class BoxModel;
		friend class core::LayoutableBase;
	};

	class ReadOnlyPoint {
	public:
		class Event: public ofEventArgs {
		public:
			Event(Point p, ReadOnlyPoint* s) {
				value = p;
				sender = s;
			}

			Point value;
			ReadOnlyPoint* sender;
		};

		ReadOnlyPoint() {
			ofAddListener(x.changed, this, &ReadOnlyPoint::onChange);
			ofAddListener(y.changed, this, &ReadOnlyPoint::onChange);
		}

		operator const Point() const {
			const Point p(x, y);
			return p;
		}

		Point  operator+( const Point& pnt ) const {
			return Point(x+pnt.x, y+pnt.y);
		}

		ofEvent<Event> changed;
		ReadOnlyFloat x;
		ReadOnlyFloat y;
	private:
		void onChange(ReadOnlyFloat::Event& ep) {
			Event e(Point(x,y), this);
			ofNotifyEvent(changed, e);
		}
	};

	BoxModel();

	void unitChanged(Unit::Event& e) {
		recalculate();
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
	ofEvent<Event> sizeChanged;
	ofEvent<Event> widthChanged;
	ofEvent<Event> heightChanged;

	UnitGroup padding;
	UnitGroup margin;
	UnitGroup border;

	ReadOnlyPoint position;
	ReadOnlyPoint outerSize;
	ReadOnlyPoint size;
	ReadOnlyPoint contentSize;
	ReadOnlyPoint contentPosition;
	//Point containerSize;

	void recalculate();
protected:


private:
	std::vector<PropertyBase*> properties;
};

}

}

}

#endif // BOXMODEL_H
