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

class BoxDefinition
{
public:
	class Event: public ofEventArgs
	{
	public:
		Event(BoxDefinition* d) {
			boxModel = d;
		}
		BoxDefinition* boxModel;
	};

	BoxDefinition() {

		padding.add(&paddingLeft);
		padding.add(&paddingRight);
		padding.add(&paddingTop);
		padding.add(&paddingBottom);
		ofAddListener(padding.changed, this, &BoxDefinition::unitChanged);

		margin.add(&marginLeft);
		margin.add(&marginRight);
		margin.add(&marginTop);
		margin.add(&marginBottom);
		ofAddListener(margin.changed, this, &BoxDefinition::unitChanged);

		border.add(&borderLeft);
		border.add(&borderRight);
		border.add(&borderTop);
		border.add(&borderBottom);
		ofAddListener(border.changed, this, &BoxDefinition::unitChanged);

		position = Relative;
		floating = NoFloat;
		clear = false;

		properties.push_back(&position);
		properties.push_back(&floating);
		properties.push_back(&clear);

		for(std::vector<PropertyBase*>::iterator it = properties.begin(); it!=properties.end(); it++) {
			ofAddListener((*it)->changed, this, &BoxDefinition::propertyChanged);
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

class BoxModel
{
public:
	class FloatReadOnly
	{
	public:
	};
	BoxModel();
	~BoxModel();

	BoxDefinition def;

private:
	void calculateSize();

	void definitionChanged(BoxDefinition::Event& e);

	Point position;
	Point outerSize;
	Point size;
	Point contentSize;
	Point contentPosition;
};

}

}

}

#endif // BOXMODEL_H
