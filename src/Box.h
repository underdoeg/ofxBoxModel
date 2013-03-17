#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "ofMain.h"

namespace ofx
{
namespace BoxModel
{

typedef ofVec2f Point;
	
class Unit
{
public:
	enum Type {
	    Pixel,
	    Percent
	};
	
	Unit(){
		value = 0;
		type = Pixel;
	}	
	
	const Unit& operator=(float val){
		setValue(val);
		return *this;
	}
	
	const Unit& operator=(Type t){
		setType(t);
		return *this;
	}

	void setValue(float val){
		value = val;
	}
	void setType(Type t){
		type = t;
	}
	
private:

	float value;
	Type type;
};

class Box
{
		public:
	
	typedef ofPtr<Box> Ptr;
	typedef std::deque<Ptr> List;
	
	Box();
	~Box();
	
	void debugDraw();
	
	virtual void layout(){};
	virtual void draw(){};
	
	void add(Box* box);
	
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
	Unit marignTop;
	Unit marginBottom;

	Unit borderLeft;
	Unit borderRight;
	Unit borderTop;
	Unit borderBottom;

private:	
	List children;
};

}
}

#endif // BOXMODEL_H
