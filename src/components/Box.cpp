#include "Box.h"
#include "Stack.h"

using namespace boxModel::core;
using namespace boxModel::components;

Point Box::getGlobalPosition()
{
	if(!components->hasComponent<Stack>())
		return position;
	Point pos;
	Stack* rootStack = components->getComponent<Stack>();
	Stack* stack = rootStack;
	int i = 0;
	while(stack->hasParent()){
		if(stack->components->hasComponent<Box>()){
			Box* box = stack->components->getComponent<Box>();
			pos += box->position;//box->contentPosition;
			if(stack != rootStack)
				pos += box->contentPosition;// << endl;
		}
		stack = stack->getParent();
		i++;
	}
	return pos;
}