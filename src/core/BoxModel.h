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

	BoxModel() {

		padding.add(&paddingLeft);
		padding.add(&paddingRight);
		padding.add(&paddingTop);
		padding.add(&paddingBottom);
		ofAddListener(padding.changed, this, &BoxModel::unitChanged);

		margin.add(&marginLeft);
		margin.add(&marginRight);
		margin.add(&marginTop);
		margin.add(&marginBottom);
		ofAddListener(margin.changed, this, &BoxModel::unitChanged);

		border.add(&borderLeft);
		border.add(&borderRight);
		border.add(&borderTop);
		border.add(&borderBottom);
		ofAddListener(border.changed, this, &BoxModel::unitChanged);

		position = Relative;
		floating = NoFloat;
		clear = false;

		properties.push_back(&position);
		properties.push_back(&floating);
		properties.push_back(&clear);

		for(std::vector<PropertyBase*>::iterator it = properties.begin(); it!=properties.end(); it++) {
			ofAddListener((*it)->changed, this, &BoxModel::propertyChanged);
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

	UnitGroup padding;
	UnitGroup margin;
	UnitGroup border;

private:
	std::vector<PropertyBase*> properties;
};

}

}

}

#endif // BOXMODEL_H
