#include "Box.h"
#include "Stack.h"
#include "core/Utils.h"

using namespace boxModel::core;
using namespace boxModel::components;

std::string Box::getName(){
	return "box";
}

void Box::setup() {
	stack = NULL;

	contentSize.changed.connect<Box, &Box::onContenSizeChanged>(this);

	LISTEN_FOR_COMPONENT(Stack, Box, onStack)
}

void Box::onStack(Stack* s) {
	stack = s;
	onContenSizeChanged(contentSize);
	stack->childAdded.connect<Box, &Box::onChildAdded>(this);
}

Point Box::getGlobalPosition() {
	if(!components->hasComponent<Stack>())
		return position;
	Point pos;
	Stack* rootStack = components->getComponent<Stack>();
	Stack* stack = rootStack;
	int i = 0;
	while(stack->hasParent()) {
		if(stack->components->hasComponent<Box>()) {
			Box* box = stack->components->getComponent<Box>();
			pos += box->position;//box->contentPosition;
			if(stack != rootStack)
				pos += box->contentPosition;// << endl;
		}
		stack = stack->getParent();
		i++;
	}
	if(stack != rootStack && stack->components->hasComponent<Box>()) {
		Box* box = stack->components->getComponent<Box>();
		pos += box->contentPosition;
	}
	return pos;
}

void Box::onContenSizeChanged(core::Point p) {
	if(stack != NULL) {
		for(Stack* child: stack->getChildren()) {
			child->components->setUnitContainerSize(p.x, p.y);
		}
	}
}

void Box::onChildAdded(Stack* child) {
	child->components->setUnitContainerSize(contentSize.x, contentSize.y);
}

void Box::copyFrom(Box* box) {
	position = box->position;
	outerSize = box->outerSize;
	size = box->size;
	contentSize = box->contentSize;
	contentPosition = box->contentPosition;
}


////

bool Box::isInside(core::Point p){
	return isInside(p.x, p.y);
}

bool Box::isInside(float x, float y){
	return core::rectContains(x, y, position.x, position.y, size.x, size.y);
}

bool Box::isInsideContent(core::Point p){
	return isInsideContent(p.x, p.y);
}
bool Box::isInsideContent(float x, float y){
	return core::rectContains(x, y, position.x + contentPosition.x, position.y + contentPosition.y, contentSize.x, contentSize.y);
}