#ifndef BOXMODEL_H
#define BOXMODEL_H

#include "core/Component.h" // Base class: boxModel::src::Component
#include "core/BaseTypes.h"

namespace boxModel
{

namespace components
{
	
class Stack;

class Box : public core::Component
{
public:
	//COMPONENT()
	
	Box(){};
	~Box(){};
	
	void setup();
	
	core::Point getGlobalPosition();
	
	core::ValuePoint position;
	core::ValuePoint outerSize;
	core::ValuePoint size;
	core::ValuePoint contentSize;
	core::ValuePoint contentPosition;
	
	void copyFrom(Box* box);
	
	bool isInside(core::Point p);
	bool isInside(float x, float y);
	
	bool isInsideContent(core::Point p);
	bool isInsideContent(float x, float y);
	
private:
	void onStack(Stack* stack);
	void onContenSizeChanged(core::Point p);
	void onChildAdded(Stack* child);
	Stack* stack;
};

}

}

#endif // BOXMODEL_H

