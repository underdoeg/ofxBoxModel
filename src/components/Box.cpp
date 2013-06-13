#include "Box.h"
#include "Stack.h"

using namespace boxModel::core;
using namespace boxModel::components;

void Box::setup(){
	stack = NULL;
	
	contentSize.changed.connect<Box, &Box::onContenSizeChanged>(this);
	
	LISTEN_FOR_COMPONENT(Stack, Box, onStack)
}

void Box::onStack(Stack* s){
	stack = s;
	onContenSizeChanged(contentSize);
	stack->childAdded.connect<Box, &Box::onChildAdded>(this);
}

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

void Box::onContenSizeChanged(core::Point p)
{
	if(stack != NULL){
		for(Stack* child: stack->getChildren()){
			child->components->setUnitContainerSize(p.x, p.y);
		}
	}
}

void Box::onChildAdded(Stack* child)
{
	child->components->setUnitContainerSize(contentSize.x, contentSize.y);
}
