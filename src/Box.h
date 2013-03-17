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

	const Unit& operator=(float val) {
		setValue(val);
		return *this;
	}

	const Unit& operator=(Type t) {
		setType(t);
		return *this;
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

	ofEvent<UnitEvent> changed;

private:

	float value;
	Type type;
};

class Definition;

class DefinitionEvent: public ofEventArgs{
	public:
	DefinitionEvent(Definition* d){
		definition = d;
	}
	Definition* definition;
};

class Definition
{
public:
	Definition(){
		ofAddListener(x.changed, this, &Definition::unitChanged);
	}
	
	void unitChanged(UnitEvent& e){
		DefinitionEvent de(this);
		ofNotifyEvent(changed, de);
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
};

class Box
{
public:

	typedef ofPtr<Box> Ptr;
	typedef std::deque<Ptr> List;

	Box();
	~Box();

	void debugDraw();

	virtual void layout();

	virtual void calculateContentSize();
	virtual void draw() {};

	void add(Box::Ptr box);

	float getContentWidth();
	float getContentHeight();

	float getInnerWidth();
	float getInnerHeight();

	float getWidth();
	float getHeight();

	float getOuterWidth();
	float getOuterHeight();

	float getX();
	float getY();

	Definition definition;
private:
	Ptr parent;

	Point position;
	Point outerSize;
	Point size;
	Point innerSize;
	Point contentSize;

	List children;
};

}
}

#endif // BOXMODEL_H
