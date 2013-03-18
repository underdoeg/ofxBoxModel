#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "ofMain.h"

namespace ofx
{
namespace BoxModel
{

typedef ofVec2f Point;

class Unit;

class UnitEvent: public ofEventArgs
{
public:
	UnitEvent(Unit* u) {
		unit = u;
	}

	Unit* unit;
};

class Unit
{
public:
	enum Type {
	    Auto,
	    Pixel,
	    Percent
	};

	Unit() {
		value = 0;
		type = Pixel;
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
		if(val == value)
			return;
		value = val;
		UnitEvent e(this);
		ofNotifyEvent(changed, e);
	}
	void setType(Type t) {
		if(type == t)
			return;
		type = t;
		UnitEvent e(this);
		ofNotifyEvent(changed, e);
	}

	float getValue() {
		return value;
	}

	Type getType() {
		return type;
	}

	ofEvent<UnitEvent> changed;

private:

	float value;
	Type type;
};

class Definition;

class DefinitionEvent: public ofEventArgs
{
public:
	DefinitionEvent(Definition* d) {
		definition = d;
	}
	Definition* definition;
};

class Definition
{
public:
	Definition() {
		units.push_back(&x);
		units.push_back(&y);
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


		for(std::vector<Unit*>::iterator it = units.begin(); it!=units.end(); it++) {
			ofAddListener((*it)->changed, this, &Definition::unitChanged);
		}
	}

	void unitChanged(UnitEvent& e) {
		DefinitionEvent de(this);
		ofNotifyEvent(changed, de);
	}
	
	void setMargin(float value, Unit::Type type = Unit::Pixel){
		for(std::vector<Unit*>::iterator it = margins.begin(); it!=margins.end(); it++) {
			(*it)->setValue(value);
			(*it)->setType(type);
		}
	}
	
	void setPadding(float value, Unit::Type type = Unit::Pixel){
		for(std::vector<Unit*>::iterator it = paddings.begin(); it!=paddings.end(); it++) {
			(*it)->setValue(value);
			(*it)->setType(type);
		}
	}

	Unit x;
	Unit y;

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

	ofEvent<DefinitionEvent> changed;

private:
	std::vector<Unit*> units;
	std::vector<Unit*> paddings;
	std::vector<Unit*> margins;
	std::vector<Unit*> borders;

};

class Box
{
public:

	typedef std::deque<Box*> List;

	Box();
	~Box();

	void debugDraw();

	virtual void draw() {};

	Box* getRootBox();
	Box* getParent();
	bool hasParent();

	Box* createChild();
	void add(Box* box);

	Definition definition;
private:
	void setParent(Box* parent);
	void calculateSize();
	virtual void layout();
	
	void definitionChanged(DefinitionEvent& e);

	Point position;
	Point outerSize;
	Point size;
	Point contentSize;
	Point contentPosition;

	
	bool bParent;
	Box* parent;

	List children;
};

}
}

#endif // BOXMODEL_H
