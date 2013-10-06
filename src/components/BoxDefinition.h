#ifndef BOX_DEFINITION_H
#define BOX_DEFINITION_H

#include "core/Component.h" // Base class: boxModel::src::Component
#include "core/BaseTypes.h"


namespace boxModel
{

namespace components
{
	
class Stack;

class BoxDefinition: public core::Component
{
public:
	//COMPONENT()
	
	BoxDefinition(){};
	~BoxDefinition(){};
	
	std::string getName();
	
	void setup();
	
	core::Point getGlobalPosition();
	
	core::ValuePoint position;
	core::ValuePoint outerSize;
	core::ValuePoint size;
	core::ValuePoint contentSize;
	core::ValuePoint contentPosition;
	
	void copyFrom(BoxDefinition* box);
	
	bool isInside(core::Point p);
	bool isInside(float x, float y);
	
	bool isInsideContent(core::Point p);
	bool isInsideContent(float x, float y);
	
	void getInfo(core::Component::Info& info);
	
private:
	void onStack(Stack* stack);
	void onContentSizeChanged(core::Point p);
	void onChildAdded(Stack* child);
	Stack* stack;
};

}

}

#endif // BOX_DEFINITION_H

